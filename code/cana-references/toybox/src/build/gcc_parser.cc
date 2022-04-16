#include "build/gcc_parser.h"
#include "build/gcc_arity.h"

#include <memory>

#include <boost/algorithm/string/predicate.hpp>

GCCCmdlineParser::Hook::Hook()
{
  // Do NOTHING
}
  
GCCCmdlineParser::Hook::~Hook()
{
  // Do NOTHING
}

/**
 *
 */
GCCCmdlineParser::GCCCmdlineParser()  
{ 
  // Do NOTHING
}

GCCCmdlineParser::~GCCCmdlineParser() 
{ 
  for (Hook *hook : hooks_)
  {
    delete hook;
  }
}

void GCCCmdlineParser::add(Hook *hook)
{
  hooks_.push_back(hook);
}

GNUOptions *GCCCmdlineParser::parse(Emit& emit, hiberlite::sqlid_t id, const Command& cmd)
{
  std::unique_ptr<GNUOptions> res( new GNUOptions() );

  auto it = cmd.arg().begin() + 1;
  
  while ( it != cmd.arg().end() )
  {
    if ( !boost::algorithm::starts_with(*it, "-") )
    {
      res->append(new GNUSourceOption(*it));

      ++it;
      continue;
    }

    if ( boost::algorithm::starts_with(*it, "-I") )
    {
      if ( it->size() > 2 )
      {
        res->append(new GNUIncludeOption((it++)->substr(2)));
      }
      else
      {
        ++it;
        res->append(new GNUIncludeOption(*it));
        ++it;
      }
      continue;
    }

    int arity = GNUArity::instance().lookup(*it);

    if ( arity == 1 )
    {
      const std::string& opt = *(it++);

      res->append(new GNUUnaryOption(opt));

      continue;
    }

    if ( arity == 2 )
    {
      const std::string& opt = *(it++);
      const std::string& arg = *(it++);

      res->append(new GNUBinaryOption(opt, arg));

      continue;
    }

    for (Hook *hook : hooks_)
    {
      hook->accept(*it);
    }
    
    return nullptr;  
  } 

  return res.release();
}

