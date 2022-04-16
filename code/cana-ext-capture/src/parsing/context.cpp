#include "context.h"

namespace parsing {

  context::context(std::list<std::string> &args,
                   std::map<std::string, std::list<std::string>> &tags,
                   parsing::observer &observer) : _args(args), _tags(tags), _observer(observer), _error(false)
  {
    // DO NOTHING
  }

  bool context::has_next() const
  {
    return _args.size() > 0 && !_error;
  }

  void context::stop(void)
  {
    _error = true;
  }

  void context::tagged(const std::string &arg, const std::string &tag)
  {
    _observer.tagged(arg, tag);

    //
    // Insert into tagging table
    //
    auto it = _tags.find(tag);

    if (it == _tags.end())
    {
      it = _tags.emplace_hint(_tags.end(), tag, std::list<std::string>());
    }

    it->second.emplace_back(arg);
  }

}
