#ifndef __CAPTURE_RUNNING_ENGINE_H__
#define __CAPTURE_RUNNING_ENGINE_H__

#include <string>
#include <list>
#include <map>

#include <unistd.h>
#include <string.h>

namespace running {

  struct state
  {
    //
    // Immutable
    //
    const std::map<std::string, std::list<std::string>> &_tags;

    //
    // Mutable
    //
    std::stack<std::string> _stack;
    std::vector<std::string> _buffer;

    state(const std::map<std::string, std::list<std::string>> &tags) : _tags(tags)
    {
      // DO NOTHING
    }
  };

  struct action
  {
    virtual ~action() = default;

    virtual void update(state &s) const = 0;
  };

}

namespace running { namespace actions {

  class str : public running::action
  {
    private:
      std::string _value;

    public:
      str(const std::string &value) : _value(value)
      {
        // DO NOTHING
      }

    public:
      virtual void update(state &s) const
      {
        s._stack.push(_value);
      }
  };

  class load : public running::action
  {
    private:
      std::string _tag;

    public:
      load(const std::string &tag) : _tag(tag)
      {
        // DO NOTHING
      }

    public:
      virtual void update(state &s) const
      {
        const auto &lst = s._tags.find(_tag)->second;

        for (auto it = lst.crbegin(); it != lst.crend(); ++it)
        {
          s._stack.push(*it);
        }
      }
  };

  class flush : public running::action
  {
    public:
      flush(const std::string &value)
      {
        // DO NOTHING
      }

    public:
      virtual void update(state &s) const
      {
        while (!s._stack.empty())
        {
          s._buffer.push_back(s._stack.top());
          s._stack.pop();
        }
      }
  };

  class prod : public running::action
  {
    public:
      prod(const std::string &value)
      {
        // DO NOTHING
      }

    public:
      virtual void update(state &s) const
      {
        std::string tag = s._stack.top();
        s._stack.pop();

        while (!s._stack.empty())
        {
          s._buffer.push_back(tag);
          s._buffer.push_back(s._stack.top());
          s._stack.pop();
        }
      }
  };

  class run : public running::action
  {
    public:
      run(const std::string &value)
      {
        // DO NOTHING
      }

    public:
      virtual void update(state &s) const
      {
        std::string command;

        command += s._buffer[0];

        for (size_t i = 1; i < s._buffer.size(); ++i)
        {
          command += " ";
          command += s._buffer[i];
        }

        system(command.c_str());

        s._buffer.clear();
      }
  };

} }

namespace running {

  struct code
  {
    std::vector<std::unique_ptr<running::action>> _actions;

    void str(const std::string &arg)    { _actions.emplace_back(new actions::str(arg));   }
    void load(const std::string &arg)   { _actions.emplace_back(new actions::load(arg));  }
    void flush(const std::string &arg)  { _actions.emplace_back(new actions::flush(arg)); }
    void prod(const std::string &arg)   { _actions.emplace_back(new actions::prod(arg));  }
    void run(const std::string &arg)    { _actions.emplace_back(new actions::run(arg));   }
  };

  class engine
  {
    private:
      running::state _state;
      const code &_code;

    public:
      engine(const std::map<std::string, std::list<std::string>> &tags, const running::code &code) : _state(tags), _code(code)
      {
        // DO NOTHING
      }

    public:
      void run()
      {
        for (const auto &action : _code._actions)
        {
          action->update(_state);
        }
      }
  };

}

#endif
