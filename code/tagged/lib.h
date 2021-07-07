#ifndef __LIB_H__
#define __LIB_H__

#include <memory>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Controller;

// Logging Rule
struct Rule
{
  std::function<bool (const Controller &)> pred;
  std::function<void (Controller &)> manip;
};

struct Tag
{
  // DO NOTHING
};

class Context
{
public:
  virtual ~Context() = default;

public:
  void join(Controller *o);
  void leave(Controller *o);

public:
  void reload(void);
  void reload(Controller *o);

  std::vector<Rule> rules;

private:
  std::set<Controller *> objects;
};

void Context::join(Controller *o)
{ 
  objects.insert(o);
}

void Context::leave(Controller *o)
{
  objects.erase(o); 
}

void Context::reload(void)
{ 
  for (auto o : objects)
  {
    reload(o);
  }
}

void Context::reload(Controller *o)
{ 
  for (auto rule : rules)
  {
    if (rule.manip && rule.pred && rule.pred(*o))
    {
      rule.manip(*o);
    }
  }
}

struct Controller
{
public:
  Controller(Context *context, uint32_t *mask_ptr)
    : _context(context), _mask_ptr(mask_ptr)
  {
    _context->join(this);
  }

public:
  ~Controller()
  {
    _context->leave(this);
  }

public:
  std::set<Tag *> tags;

  void reload(void) { _context->reload(this); }

public:
  uint32_t &mask(void) { return *_mask_ptr; }

private:
  Context *_context;
  uint32_t *_mask_ptr;
};

enum class Level
{
  VERBOSE = 0,
};

class Point
{
public:
  Point(Context *context, const std::function<void (Controller *)> &fn)
  {
    _object = std::make_shared<Controller>(context, &_mask);

    fn(_object.get());

    _object->reload();
  }

public:
  bool active(const Level &lv) const { return _mask & (1 << (int)lv); }

private:
  uint32_t _mask;

private:
  std::shared_ptr<Controller> _object;
};


#endif
