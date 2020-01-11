#ifndef GCC_OPTION_H__
#define GCC_OPTION_H__

#include <string>

/**
 *
 */
class GNUOptionVisitor;

class GNUOption
{
  public:
    GNUOption();
    virtual ~GNUOption();
  public:
    virtual void accept(GNUOptionVisitor& v) const = 0;
};

/**
 *
 */
class GNUIncludeOption;
class GNUDefineOption;
class GNUUndefineOption;
class GNUSourceOption;
class GNUUnaryOption;
class GNUBinaryOption;

class GNUOptionVisitor
{
  public:
    GNUOptionVisitor();
    virtual ~GNUOptionVisitor();
  public:
    virtual void visit(const GNUIncludeOption& arg) = 0;
    virtual void visit(const GNUDefineOption& arg) = 0;
    virtual void visit(const GNUUndefineOption& arg) = 0;
    virtual void visit(const GNUSourceOption& arg) = 0;
    virtual void visit(const GNUUnaryOption& arg) = 0;
    virtual void visit(const GNUBinaryOption& arg) = 0;
};

/**
 *
 */
class GNUIncludeOption : public GNUOption
{
  public:
    GNUIncludeOption(const std::string& dir);
    virtual ~GNUIncludeOption();
  private:
    std::string dir_;
  public:
    const std::string& dir(void) const;
  public:
    virtual void accept(GNUOptionVisitor& v) const;
};

class GNUDefineOption : public GNUOption
{
  public:
    GNUDefineOption(const std::string& def);
    virtual ~GNUDefineOption();
  private:
    std::string def_;
  public:
    const std::string& def(void) const;
  public:
    virtual void accept(GNUOptionVisitor& v) const;
};

class GNUUndefineOption : public GNUOption
{
  public:
    GNUUndefineOption(const std::string& undef)
      : undef_(undef)
    { } 
    virtual ~GNUUndefineOption() { }
  private:
    std::string undef_;
  public:
    const std::string& undef(void) const { return undef_; }
  public:
    virtual void accept(GNUOptionVisitor& v) const
    {
      v.visit(*this);
    }
};

class GNUSourceOption : public GNUOption
{
  public:
    GNUSourceOption(const std::string& src) 
      : src_(src)
    { 
    }
  public:
    virtual ~GNUSourceOption() { }
  private:
    std::string src_;
  public:
    const std::string& src() const
    { 
      return src_; 
    }
  public:
    virtual void accept(GNUOptionVisitor& v) const
    {
      v.visit(*this);
    }
};

class GNUUnaryOption : public GNUOption
{
  public:
    GNUUnaryOption(const std::string& opt)
      : opt_(opt)
    { } 
    virtual ~GNUUnaryOption() { }
  private:
    std::string opt_;
  public:
    const std::string& opt(void) const { return opt_; }
  public:
    virtual void accept(GNUOptionVisitor& v) const
    {
      v.visit(*this);
    }
};

class GNUBinaryOption : public GNUOption
{
  public:
    GNUBinaryOption(const std::string& opt, const std::string& arg)
      : opt_(opt), arg_(arg)
    { }
    virtual ~GNUBinaryOption() { }
  private:
    std::string opt_;
    std::string arg_;
  public:
    const std::string& opt(void) const { return opt_; }
    const std::string& arg(void) const { return arg_; }
  public:
    virtual void accept(GNUOptionVisitor& v) const
    {
      v.visit(*this);
    }
};

#endif
