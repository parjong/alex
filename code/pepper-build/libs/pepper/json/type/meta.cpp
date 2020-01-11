#include <pepper/json/type/meta.hpp>

#include <pepper/json/cursor/field.hpp>

namespace pepper { namespace json { namespace type {

  void meta::add(const std::string &name, type::value &field)
  {
    _fields[name] = &field;
  }

  void meta::load_from(const cursor::base &curr)
  {
    for (auto it = _fields.begin(); it != _fields.end(); ++it)
    {      
      cursor::field next{ curr, it->first };        
      it->second->load_from( next );      
    }
  }

  void meta::dump_into(cursor::base &curr) const
  {
    for (auto it = _fields.begin(); it != _fields.end(); ++it)
    {
      cursor::field next{ curr, it->first };      
      it->second->dump_into( next );
    }
  }


} } }
