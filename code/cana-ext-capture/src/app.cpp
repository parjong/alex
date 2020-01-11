#include "app.h"
#include "action.h"
#include "lowering/command.h"
#include "parsing/command.h"

#include <map>
#include <memory>
#include <vector>
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#if 0
{
  "tools" : [
    {
      "path"  : "...",
      "lower" : [ { "pat" : "...", "actions" : [ ... ] }, ... ],
      "parse" : [ { "pat" : "...", "actions" : [ ... ] }, ... ]
    }
  ]
}
#endif

app::app(const cana::ext::service &s)
{
  _storage = s.storage();
}

void app::notifyProcessEnter(const cana::proc::info &pi)
{
  // DO NOTHING
}

void app::notifyProcessLeave(const cana::proc::info &pi)
{
  std::map<std::string, std::unique_ptr<lowering::command>> lowering_commands;
  std::map<std::string, std::unique_ptr<parsing::command>>  parsing_commands;

#define COMMAND(Name, Action) \
  lowering_commands[#Name] = std::unique_ptr<lowering::command>(new lowering::commands::Name());

#include "lowering/command.lst"
#undef COMMAND

#define COMMAND(Name, Action) \
  parsing_commands[#Name] = std::unique_ptr<parsing::command>(new parsing::commands::Name());

#include "parsing/command.lst"
#undef COMMAND

  std::ifstream ifs{_storage->resolve("config.json")};
  std::ofstream ofs{_storage->resolve("capture.log"), std::ios::app};

  std::vector<std::unique_ptr<action>> actions;

  boost::property_tree::ptree doc;
  boost::property_tree::read_json(ifs, doc);

  for (const auto &tool : doc.get_child("tools"))
  {
    std::string path = tool.second.get<std::string>("path");

    auto act = new action(ofs, path);

    //
    // Setup: Lowering Phase
    //
    for (const auto &node : tool.second.get_child("lower"))
    {
      std::string pat = node.second.get<std::string>("pat");

      auto &rule = act->le.rule(pat);

      for (const auto &action : node.second.get_child("actions"))
      {
        std::string tag = action.second.get_value<std::string>();
        lowering_commands[tag]->update(rule);
      }
    }

    //
    // Setup: Parsing Phase
    //
    for (const auto &node : tool.second.get_child("parse"))
    {
      std::string pat = node.second.get<std::string>("pat");

      auto &rule = act->pe.rule(pat);

      for (const auto &action : node.second.get_child("actions"))
      {
        std::string str = action.second.get_value<std::string>();

        std::string tag;
        std::string arg;

        std::string *cur = &tag;

        for (const char c : str)
        {
          if (c == ' ')
          {
            cur = &arg;
            continue;
          }

          cur->push_back(c);
        }

        parsing_commands[tag]->update(rule, arg);
      }
    }

    //
    // Setup: Running
    //
    for (const auto &action : tool.second.get_child("run"))
    {
      std::string str = action.second.get_value<std::string>();

      std::string tag;
      std::string arg;

      std::string *cur = &tag;

      for (const char c : str)
      {
        if (c == ' ')
        {
          cur = &arg;
          continue;
        }

        cur->push_back(c);
      }

      if (tag == "str")         { act->rcode.str(arg);   }
      else if (tag == "load")   { act->rcode.load(arg);  }
      else if (tag == "flush")  { act->rcode.flush(arg); }
      else if (tag == "prod")   { act->rcode.prod(arg);  }
      else if (tag == "run")    { act->rcode.run(arg);   }
    }

    actions.emplace_back(act);
  }

  for (const auto &action : actions)
  {
    if (action->act(pi))
    {
      ofs << "'" << pi.image() << "' is accepted" << std::endl;
      break;
    }
  }
}
