#ifndef __HERMES_SEVERITY_H__
#define __HERMES_SEVERITY_H__

#include <cstdint>

namespace hermes
{

enum SeverityGroup : uint16_t
{
  GROUP_MIN   = 0,
  // GROUP TAG BEGIN
  FATAL       = GROUP_MIN,
  ERROR       = 1,
  WARN        = 2,
  INFO        = 3,
  VERBOSE     = 4,
  // GROUP TAG END
  GROUP_MAX   = VERBOSE,
  GROUP_NUM   = GROUP_MAX + 1
};

using SeverityLevel = uint16_t;

/**
 * @brief Event severity
 *
 * GROUP FATAL > ERROR > WARN > INFO > VERBOSE
 * LEVEL     0 >         ...         >   65535
 */
class Severity final
{
public:
  friend inline Severity info(void);

private:
  Severity(const SeverityGroup &group, const SeverityLevel &level) : _group{group}, _level{level}
  {
    // DO NOTHING
  }

public:
  inline const SeverityGroup &group(void) const { return _group; }
  inline const SeverityLevel &level(void) const { return _level; }

private:
  SeverityGroup _group;
  SeverityLevel _level;
};

/**
 * NOTE
 *
 * The severity factory helpers below SHOULD HAVE minimal overhead as apps will invoke these
 * helpers even when logging is disabled.
 */
inline Severity info(void) { return Severity{INFO, 0}; }

} // namespace hermes

#endif // __HERMES_SEVERITY_H__
