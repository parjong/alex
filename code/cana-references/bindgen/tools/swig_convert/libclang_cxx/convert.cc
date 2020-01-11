#include <iostream>

#include <set>
#include <vector>
#include <string>

#include <regex>

#include <clang-c/Index.h>

namespace libclang {
  class CXStringBuf {
    friend std::ostream& operator<<(std::ostream& out, const CXStringBuf& rhs);       
    public:
      CXStringBuf(CXString str) : str_(str) {  }
    public:
      ~CXStringBuf() {
        clang_disposeString(str_);
      }
    private:
      CXString str_;
    public:
      const char *c_str(void) const {
        return clang_getCString(str_);
      }
  };

  std::ostream& operator<<(std::ostream& out, const CXStringBuf& rhs) {
    out << clang_getCString(rhs.str_);
    return out;             
  }

  class location {
    public:
      location(CXSourceLocation loc) {        
        CXFile file;

        clang_getExpansionLocation(loc, &file, &line_, &column_, &offset_);        
        filename_ = clang_getFileName(file);
      }
    public:
      ~location() {
        clang_disposeString(filename_);
      }
    private:
      CXString filename_;
      unsigned line_;
      unsigned column_;
      unsigned offset_;
    public:
      const char *getFilename(void) const { return clang_getCString(filename_); }
      unsigned getLine(void) const { return line_; }
      unsigned getColumn(void) const { return column_; }
  };
}

namespace libclang {
  CXChildVisitResult clang_getChildren_impl(CXCursor curr, CXCursor parent, CXClientData data) {
    std::vector<CXCursor> *out = static_cast<std::vector<CXCursor> *>(data);

    out->push_back(curr);

    return CXChildVisit_Continue;
  }

  void getChildren(std::vector<CXCursor> &out, CXCursor cursor) {
    clang_visitChildren(cursor, clang_getChildren_impl, &out);
  }
}

bool isEffective(CXCursor cursor) {
  return clang_isCursorDefinition(cursor)
      && clang_getCursorLinkage(cursor) == CXLinkage_External 
      && clang_getCursorKind(cursor) == CXCursor_FunctionDecl;
}

class GlobalContext {
  public:
    GlobalContext() { 
      // DO SOMETHING
    }
  public:
    ~GlobalContext() { 
      // DO SOMETHING
    }      
  private:
    std::vector<std::regex> excludes_;
  public:
    void addExcludePattern(const char *pattern) {
      excludes_.push_back(std::regex(pattern));
    }
    bool matchExcludePatterns(const char *str) const {
      for (std::regex exclude : excludes_) {
        if ( std::regex_match(str, exclude) ) {
          return true;
        }
      }

      return false;
    }
};

class TranslationContext {
  public:
    TranslationContext(const GlobalContext &global, CXTranslationUnit &tu) 
      : global_(global), tu_(tu)
    {
    }
  public:
    ~TranslationContext() {
      // DO NOTHING
    }

  private:
    const GlobalContext &global_;
  public:    
    const GlobalContext &getGlobalContext() const { return global_; }

  private:
    CXTranslationUnit &tu_;
  public:
    CXTranslationUnit &getTranslationUnit(void) const { return tu_; }

  private:
    std::set<std::string> reached_;
  public:
    void addReached(CXCursor cursor) {
      libclang::CXStringBuf usr = clang_getCursorUSR(cursor);

      reached_.insert(usr.c_str());
      // std::cout << "'" << usr << "' IS MARKED AS REACHED" << std::endl;
    } 
  public:
    bool isReached(CXCursor cursor) {
      libclang::CXStringBuf usr = clang_getCursorUSR(cursor);

      return reached_.count(usr.c_str()) > 0;
    }

  private:
    std::set<std::string> hidden_;
  public:
    void addHidden(CXCursor cursor) {
      libclang::CXStringBuf usr = clang_getCursorUSR(cursor);

      hidden_.insert(usr.c_str());
    }
  public:
    bool isHidden(CXCursor cursor) {
      libclang::CXStringBuf usr = clang_getCursorUSR(cursor);

      return hidden_.count(usr.c_str()) > 0;
    }
};

void markOnCursors(TranslationContext *t_ctxt, CXCursor cursor);

void markOnType(TranslationContext *t_ctxt, CXType type) {
  if ( type.kind == CXType_Invalid ) {
    return;
  }

  CXCursor cursor = clang_getTypeDeclaration(type);

  markOnCursors(t_ctxt, cursor);

  markOnType(t_ctxt, clang_getPointeeType(type));
  markOnType(t_ctxt, clang_getArrayElementType(type));

  markOnType(t_ctxt, clang_getResultType(type));

  int n_args = clang_getNumArgTypes(type);

  for (int i = 0; i < n_args; ++i) {
    markOnType(t_ctxt, clang_getArgType(type, i));
  }
}

void markOnCursors(TranslationContext *t_ctxt, CXCursor cursor) {
  if ( clang_isInvalid(clang_getCursorKind(cursor)) ) {
    return;
  }

  if ( t_ctxt->isReached(cursor) ) {
    return;
  }

  t_ctxt->addReached(cursor);

  markOnType(t_ctxt, clang_getCursorType(cursor));
  markOnType(t_ctxt, clang_getTypedefDeclUnderlyingType(cursor));

  std::vector<CXCursor> children;

  libclang::getChildren(children, cursor);
 
  for (CXCursor child : children) {
    markOnCursors(t_ctxt, child);
  } 
}

CXChildVisitResult scan(CXCursor curr, CXCursor parent, CXClientData data) {
  TranslationContext *t_ctxt = static_cast<TranslationContext *>(data);

  libclang::CXStringBuf usr = clang_getCursorUSR(curr);
  libclang::CXStringBuf cursor_kind = clang_getCursorKindSpelling(clang_getCursorKind(curr));

  if ( clang_getCursorKind(curr) == CXCursor_TypedefDecl ) {

    CXType base_ty = clang_getTypedefDeclUnderlyingType(curr);

    if ( base_ty.kind == CXType_Unexposed ) { 

      CXCursor base_cursor = clang_getTypeDeclaration(base_ty);

      t_ctxt->addHidden(base_cursor);
    }
  }

  // If it is a externally visible function decl,
  if ( !isEffective(curr) ) {
    return CXChildVisit_Continue;
  }

  // and its filename is not matched with the excluded patterns
  CXSourceLocation loc = clang_getCursorLocation(curr);
  {
    CXString filename;
    unsigned line;
    unsigned column;

    clang_getPresumedLocation(loc, &filename, &line, &column); 

    libclang::CXStringBuf buf = filename;

    if ( t_ctxt->getGlobalContext().matchExcludePatterns(buf.c_str()) ) {
      return CXChildVisit_Continue; 
    }
  }
  
  // Add it as a reached
  t_ctxt->addReached(curr);

  //
  std::vector<CXCursor> children;

  libclang::getChildren(children, curr);

  for (CXCursor child : children) {
    markOnCursors(t_ctxt, child);
  }

  return CXChildVisit_Continue;
}

void print_tokens(TranslationContext *tc, CXCursor curr) {
  libclang::CXStringBuf type_kind = clang_getTypeKindSpelling(clang_getCursorType(curr).kind); 
  libclang::CXStringBuf usr = clang_getCursorUSR(curr);
  libclang::CXStringBuf kind = clang_getCursorKindSpelling(clang_getCursorKind(curr));

  CXSourceRange curr_extent = clang_getCursorExtent(curr);

  CXToken *tokens = NULL;
  unsigned n_tokens = 0;

  clang_tokenize(tc->getTranslationUnit(), curr_extent, &tokens, &n_tokens);
      
  for (unsigned i = 0; i < n_tokens; ++i) {
    libclang::CXStringBuf token_spelling = clang_getTokenSpelling(tc->getTranslationUnit(), tokens[i]);

    if ( i > 0 )
      std::cout << " ";

    std::cout << token_spelling;
  }

  std::cout << std::endl;

  clang_disposeTokens(tc->getTranslationUnit(), tokens, n_tokens);
}

void print_function_decl(TranslationContext *tc, CXCursor curr) {
  libclang::CXStringBuf f_retty = clang_getTypeSpelling(clang_getResultType(clang_getCursorType(curr)));
  libclang::CXStringBuf f_name = clang_getCursorSpelling(curr);

  std::cout << f_retty << " " << f_name << "(";

  int n_args = clang_Cursor_getNumArguments(curr);

  for (int i = 0; i < n_args; ++i) {
    CXCursor arg = clang_Cursor_getArgument(curr, i);

    libclang::CXStringBuf arg_ty = clang_getTypeSpelling(clang_getCursorType(arg));
    libclang::CXStringBuf arg_name = clang_getCursorSpelling(arg);

    if ( i > 0 )
      std::cout << ", ";

    std::cout << arg_ty << " " << arg_name;
  }

  std::cout << ");" << std::endl;
}

void print_typedef_decl(TranslationContext *tc, CXCursor curr) {
  print_tokens(tc, curr);
}

CXChildVisitResult print_marked_top_decl(CXCursor curr, CXCursor parent, CXClientData data) {
  TranslationContext *t_ctxt = static_cast<TranslationContext *>(data);

  if ( !clang_isCursorDefinition(curr) ) {
    return CXChildVisit_Continue;
  }

  if ( t_ctxt->isHidden(curr) ) {
    return CXChildVisit_Continue;
  }

  if ( !t_ctxt->isReached(curr) ) {
    return CXChildVisit_Continue;
  }

  switch ( clang_getCursorKind(curr) ) {
    case CXCursor_TypedefDecl:
      print_typedef_decl(t_ctxt, curr); 
      break;
    case CXCursor_FunctionDecl:
      print_function_decl(t_ctxt, curr);
      break;
    default:
      print_tokens(t_ctxt, curr);
  }

  return CXChildVisit_Continue;
}

bool process_tu(const GlobalContext &g_ctxt, CXIndex index, const char *filename) {
  CXTranslationUnit tu = clang_createTranslationUnit(index, filename);

  if ( tu == NULL ) {
    std::cerr << "Error! Failed to load '" << filename << "'" << std::endl;
    return false;
  }

  TranslationContext t_ctxt(g_ctxt, tu);

  CXCursor top = clang_getTranslationUnitCursor(tu);
  
  clang_visitChildren(top, scan, &t_ctxt);
  clang_visitChildren(top, print_marked_top_decl, &t_ctxt);

  clang_disposeTranslationUnit(tu);

  return true;
}

int main(int argc, char **argv) {
  GlobalContext ctxt;

  // TODO
  ctxt.addExcludePattern("/usr/include/.+");

  CXIndex index = clang_createIndex(1, 0);

  process_tu(ctxt, index, argv[1]);

  clang_disposeIndex(index);

  return 0;
}
