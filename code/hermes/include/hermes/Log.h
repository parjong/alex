#ifndef __HERMES_LOG_H__
#define __HERMES_LOG_H__

#include "hermes/Severity.h"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace hermes
{

/**
 * @brief Event message
 */
class Message
{
public:
  Message(std::stringstream &ss);

public:
  // Return the number of lines
  uint32_t lines(void) const { return _lines.size(); }
  // Return the content of a specific line
  const std::string &line(uint32_t n) const { return _lines.at(n); }

private:
  std::vector<std::string> _lines;
};

/**
 * @brief Event log (including message, severity)
 *
 * TODO(parjong) Add "Source" field
 * TODO(parjong) Support extensible "annotation"
 */
class Log final
{
public:
  Log() = default;

public:
  void msg(std::unique_ptr<Message> &&b) { _msg = std::move(b); }
  const Message *msg(void) const { return _msg.get(); }

  void severity(std::unique_ptr<Severity> &&s) { _severity = std::move(s); }
  const Severity *severity(void) const { return _severity.get(); }

private:
  std::unique_ptr<Message> _msg;
  std::unique_ptr<Severity> _severity;
};

} // namespace hermes

#endif // __HERMES_LOG_H__
