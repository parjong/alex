#ifndef __PEPPER_RANDOM_NUMBER_HEAD_OBJECT_H__
#define __PEPPER_RANDOM_NUMBER_HEAD_OBJECT_H__

#include <pepper/stream.hpp>

namespace pepper { namespace random { namespace number { namespace head {

  class object : public pepper::stream::head::object<int>
  {
    private:
      int _value;

    private:
      void generate(void);

    public:
      virtual maybe::object<int> access(void) const;
      virtual void forward(void);

    public:
      object();
      virtual ~object() = default;
  };

} } } }

#endif
