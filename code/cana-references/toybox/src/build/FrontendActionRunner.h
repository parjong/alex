#ifndef FRONTEND_ACTION_RUNNER_H__
#define FRONTEND_ACTION_RUNNER_H__

#include <llvm/ADT/Twine.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/Host.h>
#include <llvm/Option/Option.h>

#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Driver/Tool.h>

#include <clang/Tooling/Tooling.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Frontend/FrontendDiagnostic.h>
#include <clang/Tooling/CompilationDatabase.h>


class FrontendActionRunner
{
  public:
    FrontendActionRunner();
  public:
    ~FrontendActionRunner();

  // Append Action
  private:
    std::vector<clang::FrontendAction *> actions_;
  public:
    void append(clang::FrontendAction& act);

  private:
    llvm::StringMap<llvm::StringRef> contents_;
    void addVirtualFile(llvm::StringRef path, llvm::StringRef content);
  private:
    std::vector<std::string> args(llvm::StringRef pathRef);
  private:
    clang::driver::Driver *getDriver(clang::DiagnosticsEngine *engine, const char *bin);
    const llvm::opt::ArgStringList *getCC1Arguments(
        clang::DiagnosticsEngine *Diagnostics,
        clang::driver::Compilation *Compilation);
    clang::CompilerInvocation *newInvocation(
        clang::DiagnosticsEngine *Diagnostics,
        const llvm::opt::ArgStringList &CC1Args);
  private:
    bool runInvocation(clang::CompilerInvocation *Invocation, 
                       clang::FileManager *Files, clang::FrontendAction *action);
    bool invoke(const std::vector<std::string>& args, clang::FrontendAction *action, clang::FileManager *fileManager);
  public:
    bool run(const llvm::Twine &code, const llvm::Twine &path);
};

#endif
