#ifndef __HERMES_FILTER_H__
#define __HERMES_FILTER_H__

#include "hermes/Severity.h"

#include <array>
#include <initializer_list>
#include <set>
#include <vector>

namespace hermes
{

// SeverityGroupSpecifier
using SeverityGroupSpecifier = std::set<SeverityGroup>;

SeverityGroupSpecifier group(std::initializer_list<SeverityGroup> l);
SeverityGroupSpecifier all_groups(void);

enum FilterPolicy
{
  AcceptAll,
  DenyAll,
  /* ... */
};

/**
 * @brief Describe how to filter each logs
 *
 * A filtering rule consists of a policy (FilterPolicy) and related parameters.
 */
template <FilterPolicy P> class FilterRule;

/**
 * @brief Accept all the logs
 *
 * NOTE AcceptAll policy has no parameter
 */
template <> class FilterRule<AcceptAll>
{
public:
  FilterRule() = default;
};

/**
 * @brief Reject all the logs
 *
 * NOTE DenyAll policy has no parameter
 */
template <> class FilterRule<DenyAll>
{
public:
  FilterRule() = default;
};

FilterRule<AcceptAll> accept_all_rule(void);
FilterRule<DenyAll> deny_all_rule(void);

/**
 * Filter Internal Status
 */
using FilterState = std::array<int32_t, GROUP_NUM>;

/**
 * FilterUpdater<P> updates a filter (its state) according to a given rule
 */
template <FilterPolicy P> class FilterUpdater;

template <> class FilterUpdater<AcceptAll> final
{
private:
  FilterUpdater(FilterState *state) : _state{state}
  {
    // DO NOTHING
  }

public:
  void to(const SeverityGroupSpecifier &groups)
  {
    for (const auto &group : groups)
    {
      _state->at(static_cast<size_t>(group)) = 65536;
    }
  }

private:
  FilterState *_state;

public:
  static FilterUpdater<AcceptAll> make(FilterState *i, const FilterRule<AcceptAll> &)
  {
    return FilterUpdater<AcceptAll>{i};
  }
};

template <> class FilterUpdater<DenyAll> final
{
private:
  FilterUpdater(FilterState *state) : _state{state}
  {
    // DO NOTHJING
  }

public:
  void to(const SeverityGroupSpecifier &groups)
  {
    for (const auto &group : groups)
    {
      _state->at(static_cast<size_t>(group)) = -1;
    }
  }

private:
  FilterState *_state;

public:
  static FilterUpdater<DenyAll> make(FilterState *i, const FilterRule<DenyAll> &)
  {
    return FilterUpdater<DenyAll>{i};
  }
};

class Filter final
{
public:
  Filter()
  {
    // Deny all the logs by default
    apply(deny_all_rule()).to(all_groups());
  }

public:
  template <FilterPolicy P> FilterUpdater<P> apply(const FilterRule<P> &r)
  {
    return FilterUpdater<P>::make(&_state, r);
  }

private:
  inline int32_t ubound(const SeverityGroup &cat) const
  {
    return _state[static_cast<uint32_t>(cat)];
  }

public:
  /**
   * @brief Return true if this filter accepts logs with a given severity.
   *
   * This method SHOULD BE optimized as apps invoke this method even when logging is disabled.
   */
  inline bool accept(const Severity &s) const
  {
    return static_cast<int32_t>(s.level()) < ubound(s.group());
  }

private:
  /**
   * Allowed level for each category
   *
   * This filter will accept all the messages whose level belongs to [0, ulimit)
   * where ulimit correspondsto "limit(cat).value()"
   */
  FilterState _state;
};

} // namespace hermes

#endif // __HERMES_FILTER_H__
