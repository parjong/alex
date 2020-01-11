#ifndef GCC_UTILS_H__
#define GCC_UTILS_H__

#include "build/gcc_option.h"
#include "build/gcc_options.h"

#include <string>
#include <vector>

class GNUTokenExtractor : public GNUOptionVisitor
{
  public:
    GNUTokenExtractor(std::vector<std::string>& options)
      : options_(options)
    { }
  private:
    std::vector<std::string>& options_;
  public:
    virtual void visit(const GNUIncludeOption& arg) 
    {
      options_.push_back("-I");
      options_.push_back(arg.dir());
    }
    virtual void visit(const GNUDefineOption& arg) 
    { 
      options_.push_back("-D");
      options_.push_back(arg.def());
    }
    virtual void visit(const GNUUndefineOption& arg) 
    { 
      options_.push_back("-U");
      options_.push_back(arg.undef());
    }
    virtual void visit(const GNUSourceOption& arg) 
    {
      options_.push_back(arg.src());
    }
    virtual void visit(const GNUUnaryOption& arg) 
    { 
      options_.push_back(arg.opt());
    }
    virtual void visit(const GNUBinaryOption& arg) 
    { 
      options_.push_back(arg.opt());
      options_.push_back(arg.arg());
    }
};

class GNUSourceExtractor : public GNUOptionVisitor
{
  public:
    GNUSourceExtractor(std::vector<std::string>& sources) 
      : sources_(sources)
    { }
  private:
    std::vector<std::string>& sources_;
  public:
    virtual void visit(const GNUIncludeOption& arg) { return; }
    virtual void visit(const GNUDefineOption& arg) { return; }
    virtual void visit(const GNUUndefineOption& arg) { return; }
    virtual void visit(const GNUSourceOption& arg) 
    {
      sources_.push_back(arg.src());
    }
    virtual void visit(const GNUUnaryOption& arg) { return; }
    virtual void visit(const GNUBinaryOption& arg) { return; }
};

void extrSourcesFromGNUOptions(std::vector<std::string>& sources, const GNUOptions& opts);

class GNUPreprocessorOptionExtractor : public GNUOptionVisitor
{
  public:
    GNUPreprocessorOptionExtractor(GNUOptions& args) 
      : args_(args)
    { }
  private:
    GNUOptions& args_;
  public:
    virtual void visit(const GNUIncludeOption& arg) 
    { 
      args_.append(new GNUIncludeOption(arg.dir()));
    }
    virtual void visit(const GNUDefineOption& arg) 
    { 
      args_.append(new GNUDefineOption(arg.def()));
    }
    virtual void visit(const GNUUndefineOption& arg) 
    { 
      args_.append(new GNUUndefineOption(arg.undef()));
    }
    virtual void visit(const GNUSourceOption& arg) { return; }
    virtual void visit(const GNUUnaryOption& arg) { return; }
    virtual void visit(const GNUBinaryOption& arg) { return; }
};

void extrPPOptionsFromGNUOptions(GNUOptions& pp_options, const GNUOptions& options);

#endif
