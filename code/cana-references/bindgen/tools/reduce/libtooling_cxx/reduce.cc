#include <iostream>

#include <map>
#include <set>
#include <vector>
#include <functional>

#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/raw_os_ostream.h"

#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/ArgumentsAdjusters.h"
#include "clang/Index/USRGeneration.h"

#include "clang/Rewrite/Core/Rewriter.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
     
struct Context 
{
  typedef std::map<const NamedDecl *, EnumDecl *> map_t;

  map_t map_;
    
  std::set<const Decl *> collected_;
};

struct GlobalBuffer
{
  std::set<std::string> Found_;
};

class EnumReferenceVisitor : public RecursiveASTVisitor<EnumReferenceVisitor> 
{
  private:
    Context &ctxt_;
  public:
    EnumReferenceVisitor(Context &ctxt) : ctxt_(ctxt)
    { 
      // DO NOTHING
    }  
  public:
    virtual bool VisitEnumDecl(EnumDecl *D) 
    {
      for (auto it = D->decls_begin(); it != D->decls_end(); ++it) 
      {
        if ( EnumConstantDecl *ED = dyn_cast<EnumConstantDecl>(*it) ) 
        {
          ctxt_.map_[ED] = D;
        }
      }
      return false;
    }
};

/**
 *
 */
class ExprVisitor : public RecursiveASTVisitor<ExprVisitor> {
  std::function<void (const Expr *)> func_;
  public:
    ExprVisitor(std::function<void (const Expr *)> func) 
      : func_(func) 
    {  }
  public:
    virtual bool VisitExpr(const Expr *E) {
      func_(E);            
      return true;
    }
};

/**
 *
 */
class Collector 
{
  private:
    Context& ctxt_;
  public:
    Collector(Context& ctxt) : ctxt_(ctxt) 
    { 
      //
    }
  private:
    void addDeclRefExpr(const Expr *);
  private:
    void add(const Expr *E);
    void add(const QualType qty);  
    void add(const Type *ty);
  public:    
    void add(const Decl *D); 
};

void Collector::add(const Decl *D) 
{
  if ( D == nullptr ) return;
  if ( ctxt_.collected_.count(D) > 0 ) return;

  ctxt_.collected_.insert(D);

  if ( const TypedefNameDecl *TND = dyn_cast<TypedefNameDecl>(D) ) 
  {
    add( TND->getUnderlyingType() );
  }

  if ( const ValueDecl *VD = dyn_cast<ValueDecl>(D) ) 
  {
    add( VD->getType() );
  }

  if ( const FunctionDecl *FD = dyn_cast<FunctionDecl>(D) ) 
  {
    // Add Return Type
    add( FD->getReturnType() );

    // Add Parameter Type
    for (auto it = FD->param_begin(); it != FD->param_end(); ++it) {
      add( (*it)->getOriginalType() );
    }        
  }

  if ( const TagDecl *TD = dyn_cast<TagDecl>(D) ) 
  {
    for (auto it = TD->decls_begin(); it != TD->decls_end(); ++it) 
    {
      add(*it); // Field or EnumConstant
    }
  }

  if ( const EnumConstantDecl *ECD = dyn_cast<EnumConstantDecl>(D) ) 
  {
    add( ECD->getInitExpr() );
  }
}

void Collector::add(const Type *ty) 
{ 
  if ( ty == nullptr ) return;

  if ( const TypedefType *obj = ty->getAs<TypedefType>() ) 
  {
    add( obj->getDecl() );    
  }  
  
  if ( const TagType *obj = ty->getAs<TagType>() ) 
  {
    add( obj->getDecl() );
  }

  if ( const FunctionProtoType *obj = ty->getAs<FunctionProtoType>() ) 
  {
    add(obj->getReturnType());

    for (auto it = obj->param_type_begin(); it != obj->param_type_end(); ++it) 
    {
      add(*it);
    }
  }

  if ( const PointerType *obj = ty->getAs<PointerType>() ) 
  {
    add(obj->getPointeeType());
  }

  if ( const ArrayType *obj = dyn_cast<ArrayType>(ty) ) 
  {
    add(obj->getElementType());
  }
}

void Collector::add(const QualType qty) 
{
  add(qty.getTypePtr());
}

void Collector::addDeclRefExpr(const Expr *E) 
{
  if ( E == nullptr ) return;
   
  if ( const DeclRefExpr *obj = dyn_cast<DeclRefExpr>(E) ) 
  {
    const NamedDecl *ND = obj->getFoundDecl();
    
    if ( ND && ctxt_.map_.find(ND) != ctxt_.map_.end()) 
    {
      add( ctxt_.map_[ND] );
    }
  }
}

void Collector::add(const Expr *E) 
{
  ExprVisitor V(std::bind(&Collector::addDeclRefExpr, this, std::placeholders::_1));

  V.TraverseStmt(const_cast<Expr *>(E));
}

class Filter 
{ 
  private:
    ASTContext &C_;
  public:
    Filter(ASTContext &C) : C_(C) 
    { 
      //
    }
  public:
    bool filter(Decl *D) const;
};

bool Filter::filter(Decl *D) const 
{
  SourceManager &SM = C_.getSourceManager();  
  FullSourceLoc L = C_.getFullLoc(D->getLocation());

  return !L.isInSystemHeader();
}

/**
 *
 */
struct FunctionVisitor : public RecursiveASTVisitor<FunctionVisitor> 
{
  private:
    const Filter &F_;
    Collector& C_;
  public:
    FunctionVisitor(const Filter &F, Collector &C) : F_(F), C_(C) { }
  public:
    virtual bool VisitFunctionDecl(FunctionDecl *D) 
    {
      if ( !D->hasBody() ) return false;
      if ( !D->isExternallyVisible() ) return false;
      if ( !F_.filter(D) ) return false;

      C_.add(D);
      
      return false;
    }
};

class TypedefVisitor : public RecursiveASTVisitor<TypedefVisitor> 
{
  private:
    Context &CC_;
  public:
    explicit TypedefVisitor(Context &CC) 
      : CC_(CC)
    {
      //
    }
    virtual ~TypedefVisitor() { }
  public:
    virtual bool VisitTypedefNameDecl(TypedefNameDecl *TND) 
    {
      const TagType *TT = TND->getUnderlyingType().getTypePtr()->getAs<TagType>();
      
      if ( TT != nullptr ) 
      {
        const TagDecl *TD = TT->getDecl();

        if ( CC_.collected_.count(TD) > 0 ) {
            CC_.collected_.insert(TND);
        }
      }

      return false;
    }
};

/**
 *
 */
class EliminateUnusedDeclPass 
{
  private:
    const Context &CC_;
  public:
    EliminateUnusedDeclPass(Context &CC) : CC_(CC) { }
  private:
    void run(clang::DeclContext *DC);
  public:
    void eliminate(TranslationUnitDecl *TU);
};

void EliminateUnusedDeclPass::run(clang::DeclContext *DC)
{
  std::vector<Decl *> removed_;

  for (auto it = DC->decls_begin(); it != DC->decls_end(); ++it) 
  {
    Decl *D = *it;

    // Drop all the attributes
    D->dropAttrs();
    
    if ( FunctionDecl *FD = dyn_cast<FunctionDecl>(D) ) 
    {
      FD->setBody(nullptr);      
    }

    //
    if ( LinkageSpecDecl *ChildDC = dyn_cast<LinkageSpecDecl>(D) ) 
    {
      run(ChildDC);

      if ( ChildDC->decls_begin() == ChildDC->decls_end() ) 
      {
        removed_.push_back(D);
      }    
    }    
    else if ( CC_.collected_.count(D) == 0 ) 
    {
      removed_.push_back(D);    
    }     
  }

  for (Decl *D : removed_) 
  {
    DC->removeDecl(D);
  }
}

class EliminateDuplicatedDeclPass
{
  private:
    GlobalBuffer &Buffer_;
  public:
    EliminateDuplicatedDeclPass(GlobalBuffer &Buffer)
      : Buffer_(Buffer)
    { 
      //
    }
  public:
    void eliminate(DeclContext *DC)
    {
      std::vector<Decl *> removed_;

      for (auto it = DC->decls_begin(); it != DC->decls_end(); ++it) 
      {
        Decl *D = *it;

        llvm::SmallString<32> name;

        clang::index::generateUSRForDecl(D, name);

        std::string qual = name.str().split('@').second.str();

        std::cerr << "[CHECK] " << qual << std::endl;

        if ( Buffer_.Found_.count(qual) > 0 )
        {
          std::cerr << "[REMOVED] " << qual << std::endl;
          removed_.push_back(D);
        }

        Buffer_.Found_.insert(qual);
      }

      for (Decl *D : removed_) 
      {
        DC->removeDecl(D);
      }
    }
};

void EliminateUnusedDeclPass::eliminate(TranslationUnitDecl *TU)
{
  run(TU);
}

/**
 * AST Consumer
 */
class SampleASTConsumer : public ASTConsumer 
{
  private:
    GlobalBuffer &Buffer_;
  public:
    explicit SampleASTConsumer(GlobalBuffer &Buffer)
      : Buffer_(Buffer)
    {
      //
    }
    virtual ~SampleASTConsumer()
    {
      //
    }
  public:
    virtual void HandleTranslationUnit (ASTContext &Context); 
  private: 
    template <typename Derived> void traverseDeclContext(DeclContext *DC, Derived V) 
    {
      for (auto it = DC->decls_begin(); it != DC->decls_end(); ++it) 
      {        
        Decl *D = *it;

        V->TraverseDecl(D);   

        if ( LinkageSpecDecl *LSD = dyn_cast<LinkageSpecDecl>(D) )
        {
          traverseDeclContext(LSD, V);
        }
      }
    }
   
    template <typename Derived> inline void traverseTopLevelDecls(ASTContext &C, Derived V) 
    {
      traverseDeclContext(C.getTranslationUnitDecl(), V);
    }
};

void SampleASTConsumer::HandleTranslationUnit(ASTContext &C) 
{
  Context CC;
  {
    std::unique_ptr<EnumReferenceVisitor> V( new EnumReferenceVisitor(CC) );
    traverseTopLevelDecls(C, V.get());
  }

  Collector Collector(CC);
  Filter Filter(C);
  {
    std::unique_ptr<FunctionVisitor> V( new FunctionVisitor(Filter, Collector) );  

    traverseTopLevelDecls(C, V.get());
  }

  { 
    std::unique_ptr<TypedefVisitor> V( new TypedefVisitor(CC) );

    traverseTopLevelDecls(C, V.get());
  }

  // Remove
  TranslationUnitDecl *TU = C.getTranslationUnitDecl();
  {
    EliminateUnusedDeclPass P(CC);

    P.eliminate(TU);
  }

  {
    EliminateDuplicatedDeclPass P(Buffer_);

    P.eliminate(TU);
  }

  // Print
  llvm::raw_os_ostream out(std::cout);

  clang::PrintingPolicy Po(C.getPrintingPolicy());

  //Po.SuppressTag = true;
  //Po.SuppressTagKeyword = true;

  C.setPrintingPolicy(Po);

  TU->print(out, C.getPrintingPolicy(), 0, false);
}

/**
 *
 */
struct EliminateUnusedAction : public ASTFrontendAction 
{
  private:
    GlobalBuffer &Buffer_;
  public:
    EliminateUnusedAction(GlobalBuffer &Buffer) 
      : Buffer_(Buffer)
    {
      //
    }
  public:
    virtual ASTConsumer *CreateASTConsumer(CompilerInstance &CI, StringRef file) 
    {
      return new SampleASTConsumer(Buffer_); 
    }
};

/**
 *
 */
class ClangAppendArgumentsAdjuster : public ArgumentsAdjuster 
{
  public:
    CommandLineArguments Extra;
  public:
    ClangAppendArgumentsAdjuster() { }
  public:
    virtual CommandLineArguments Adjust(const CommandLineArguments &Args) override
    {
      CommandLineArguments Return(Args);

      for (const std::string ExtraArg : Extra) 
      {
        Return.push_back(ExtraArg);
      }

      return Return;
    }
};

struct BufferedFrontendActionFactory : public clang::tooling::FrontendActionFactory
{
  private:
    GlobalBuffer Buffer;
  public:
    BufferedFrontendActionFactory()
    {
      //
    }
  public:
    virtual clang::FrontendAction *create() override
    {
      return new EliminateUnusedAction(Buffer);
    }
};

static llvm::cl::OptionCategory ReduceCatagory("reduce options");

int main(int argc, const char **argv) 
{
  CommonOptionsParser Op(argc, argv, ReduceCatagory);       

  ClangTool Tool(Op.getCompilations(), Op.getSourcePathList());

  std::unique_ptr<BufferedFrontendActionFactory> F( new BufferedFrontendActionFactory() );

  return Tool.run( F.get() );
}
