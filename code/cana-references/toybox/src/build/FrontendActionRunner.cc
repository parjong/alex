#include "FrontendActionRunner.h"

FrontendActionRunner::FrontendActionRunner() 
{
  // Do NOTHING
}

FrontendActionRunner::~FrontendActionRunner()
{

  // Do NOTHING
}

void FrontendActionRunner::append(clang::FrontendAction& act)
{
  actions_.push_back( &act );
}

void FrontendActionRunner::addVirtualFile(llvm::StringRef path, llvm::StringRef content)
{
  llvm::SmallString<1024> pathStorage;

  llvm::sys::path::native(path, pathStorage);

  contents_[pathStorage] = content;
}

std::vector<std::string> FrontendActionRunner::args(llvm::StringRef pathRef) 
{
  std::vector<std::string> res;

  res.push_back("clang-tool");
  res.push_back("-fsyntax-only");
  // res.push_back("-g");
  res.push_back(pathRef.str());

  return res;
}

// From newDriver
clang::driver::Driver *FrontendActionRunner::getDriver(clang::DiagnosticsEngine *engine, const char *bin)
{
  clang::driver::Driver *obj = 
    new clang::driver::Driver(bin, llvm::sys::getDefaultTargetTriple(), *engine);

  obj->setTitle("clang_based_tool");

  return obj;
} 

const llvm::opt::ArgStringList *FrontendActionRunner::getCC1Arguments(
    clang::DiagnosticsEngine *Diagnostics,
    clang::driver::Compilation *Compilation) 
{
  // We expect to get back exactly one Command job, if we didn't something
  // failed. Extract that job from the Compilation.
  const clang::driver::JobList &Jobs = Compilation->getJobs();

  if (Jobs.size() != 1 || !llvm::isa<clang::driver::Command>(*Jobs.begin())) 
  {
    llvm::SmallString<256> error_msg;
    llvm::raw_svector_ostream error_stream(error_msg);
    Jobs.Print(error_stream, "; ", true);
    Diagnostics->Report(clang::diag::err_fe_expected_compiler_job)
      << error_stream.str();
    return nullptr;
  }

  // The one job we find should be to invoke clang again.
  const clang::driver::Command &Cmd =
    llvm::cast<clang::driver::Command>(*Jobs.begin());

  /**
    if (llvm::StringRef(Cmd.getCreator().getName()) != "clang") 
    {
    Diagnostics->Report(clang::diag::err_fe_expected_clang_command);
    return nullptr;
    }
    */

  return &Cmd.getArguments();
}

/// \brief Returns a clang build invocation initialized from the CC1 flags.
clang::CompilerInvocation *FrontendActionRunner::newInvocation(
    clang::DiagnosticsEngine *Diagnostics,
    const llvm::opt::ArgStringList &CC1Args) 
{
  assert(!CC1Args.empty() && "Must at least contain the program name!");

  clang::CompilerInvocation *Invocation = new clang::CompilerInvocation;

  clang::CompilerInvocation::CreateFromArgs(
      *Invocation, CC1Args.data() + 1, CC1Args.data() + CC1Args.size(),
      *Diagnostics);
  Invocation->getFrontendOpts().DisableFree = false;
  Invocation->getCodeGenOpts().DisableFree = false;
  Invocation->getDependencyOutputOpts() = clang::DependencyOutputOptions();
  return Invocation;
}

/** From FrontendActionFactory::runInvocation */
bool FrontendActionRunner::runInvocation(clang::CompilerInvocation *Invocation, 
    clang::FileManager *Files, clang::FrontendAction *action)
{
  clang::CompilerInstance Compiler;

  Compiler.setInvocation(Invocation);
  Compiler.setFileManager(Files);

  /// Create the compiler's actual diagnostics engine.
  Compiler.createDiagnostics(nullptr, false);

  if (!Compiler.hasDiagnostics())
    return false;

  Compiler.createSourceManager(*Files);

  clang::FrontendAction *scoped = action;

  const bool res = Compiler.ExecuteAction(*scoped);

  Files->clearStatCaches();
  return res;
}

/** From ToolInvocation::run() */
bool FrontendActionRunner::invoke(const std::vector<std::string>& args, clang::FrontendAction *action, clang::FileManager *fileManager)
{
  std::vector<const char*> argv;

  for (const std::string &arg : args)
    argv.push_back(arg.c_str());

  const char *const BinaryName = argv[0];

  llvm::IntrusiveRefCntPtr<clang::DiagnosticOptions> DiagOpts = 
    new clang::DiagnosticOptions();

  /** Q: What is the meaning of &*DiagOpts? */
  clang::TextDiagnosticPrinter DiagnosticPrinter(llvm::errs(), &*DiagOpts);

  llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagIDs = new clang::DiagnosticIDs();

  clang::DiagnosticsEngine Diagnostics(DiagIDs, &*DiagOpts, &DiagnosticPrinter, false);

  const std::unique_ptr<clang::driver::Driver> Driver(getDriver(&Diagnostics, BinaryName));

  Driver->setCheckInputsExist(false);

  const std::unique_ptr<clang::driver::Compilation> Compilation(
      Driver->BuildCompilation(llvm::makeArrayRef(argv)));

  const llvm::opt::ArgStringList *const CC1Args = 
    getCC1Arguments(&Diagnostics, Compilation.get());

  if (!CC1Args) 
    return false;  

  std::unique_ptr<clang::CompilerInvocation> Invocation(newInvocation(&Diagnostics, *CC1Args));

  for (const auto &It : contents_) 
  {
    // Inject the code as the given file name into the preprocessor options.
    std::unique_ptr<llvm::MemoryBuffer> In =
      llvm::MemoryBuffer::getMemBuffer(It.getValue());

    Invocation->getPreprocessorOpts().
      addRemappedFile(It.getKey(), In.release());
  }

  return runInvocation(Invocation.release(), fileManager, action);
}    

/** From runToolOnCodeWithArgs */
bool FrontendActionRunner::run(const llvm::Twine &code, const llvm::Twine &path) 
{
  bool res = true;

  for (clang::FrontendAction *action : actions_)
  {
    llvm::SmallString<16> pathStorage;

    llvm::StringRef pathRef = 
      path.toNullTerminatedStringRef(pathStorage);

    llvm::SmallString<1024> codeStorage;

    llvm::StringRef codeRef =
      code.toNullTerminatedStringRef(codeStorage);

    addVirtualFile(pathRef, codeRef);

    llvm::IntrusiveRefCntPtr<clang::FileManager> fileManager =
      new clang::FileManager(clang::FileSystemOptions());

    res = res & invoke(args(pathRef), action, fileManager.get());
  }

  return res;
}

