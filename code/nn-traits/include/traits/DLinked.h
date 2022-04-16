#ifndef __TRAITS_DLINKED_H__
#define __TRAITS_DLINKED_H__

#include <map>

#include <cassert>
#include <type_traits>

namespace traits
{
//
// Parent SHOULD provide enlist method
//
// Child SHOULD inherit DLinked<Parent, Child>::Node
//  - 'parent(Parent *)' method
//
template<typename Parent, typename Child> struct DLinked
{
  struct Link
  {
  public:
    Parent *find(const Child *child) const
    {
      if (_content.find(child) == _content.end())
      {
        return nullptr;
      }

      return _content.at(child);
    }

  public:
    void unset(const Child *child)
    {
      _content.erase(child);
    }

  public:
    void set(const Child *child, Parent *parent)
    {
      _content[child] = parent;
    }

  private:
    std::map<const Child *, Parent *> _content;
  };

  class List
  {
  public:
    List(Link *link, Parent *parent)
        : _link{link}, _parent{parent}, _head{nullptr}, _tail{nullptr}
    {
      // DO NOTHING
    }

  public:
    Child *head(void) const { return _head; }
    Child *tail(void) const { return _tail; }

  public:
    bool empty(void) const
    {
      if (_head == nullptr)
      {
        assert(_head == nullptr && _tail == nullptr);
        return true;
      }
      else
      {
        assert(_head != nullptr && _tail != nullptr);
        return false;
      }
    }

  public:
    void enlist(Child *child)
    {
      assert(child->parent() == nullptr);

      if (empty())
      {
        _head = child;
        _tail = child;
      }
      else
      {
        if (_head == child->next())
        {
          _head = child;
        }

        if (_tail == child->prev())
        {
          _tail = child;
        }
      }

      _link->set(child, reinterpret_cast<Parent *>(this));
    }

  public:
    void append(Child *child)
    {
      if (empty())
      {
        enlist(child);
      }
      else
      {
        child->insert_after(_tail);
      }
    }

  private:
    Link * const _link;
    Parent * const _parent;

    Child *_head;
    Child *_tail;
  };

  struct Node
  {
  public:
    Node() : _prev{nullptr}, _next{nullptr}
    {
      static_assert(std::is_base_of<Node, Child>::value, "Child SHOULD inherit Node");
    }

  protected:
    // Child SHOULD implement these methods
    virtual void get(const Link **) const = 0;
    virtual List *list(void) const = 0;

  public:
    Parent *parent(void) const
    {
      const Link *link = nullptr;
      get(&link);
      return link->find(curr());
    }

  private:
    const Child *curr(void) const
    {
      return reinterpret_cast<const Child *>(this);
    }

    Child *curr(void)
    {
      return reinterpret_cast<Child *>(this);
    }

  public:
    Child *next(void) const { return _next; }
    Child *prev(void) const { return _prev; }

  public:
    void insert_after(Node *node)
    {
      assert(node->parent() != nullptr);
      assert(node->list() != nullptr);

      assert(parent() == nullptr);
      assert(prev() == nullptr);
      assert(next() == nullptr);

      _prev = node->curr();
      _next = node->next();

      if (auto next = node->next())
      {
        next->_prev = curr();
      }
      node->_next = curr();

      node->list()->enlist(curr());
    }

  private:
    Child *_next;
    Child *_prev;
  };
};

} // namespace traits

#endif // __TRAITS_DLINKED_H__
