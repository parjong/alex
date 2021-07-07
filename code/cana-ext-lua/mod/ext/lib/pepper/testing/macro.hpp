#ifndef __PEPPER_TESTING_MACRO_H__
#define __PEPPER_TESTING_MACRO_H__

#include <pepper/testing/core.hpp>

#define EXPECT_TRUE(expr) {                                           \
    if (!(expr)) {                                                    \
      pepper::testing::core::error err{                               \
        #expr " is expected to be true, but false"                    \
      };                                                              \
                                                                      \
      throw err;                                                      \
    }                                                                 \
  }

#define EXPECT_FALSE(expr) {                                          \
    if ((expr)) {                                                     \
      pepper::testing::core::error err{                               \
        #expr " is expected to be false, but true"                    \
      };                                                              \
                                                                      \
      throw err;                                                      \
    }                                                                 \
  }

#define EXPECT_EQ(lhs, rhs) {                                         \
    if (!((lhs) == (rhs))) {                                          \
      pepper::testing::core::error err{                               \
        #lhs " and " #rhs " are expected to be same, but different"   \
      };                                                              \
                                                                      \
      throw err;                                                      \
    }                                                                 \
  }

#define EXPECT_NE(lhs, rhs) {                                         \
    if (!((lhs) != (rhs))) {                                          \
      pepper::testing::core::error err{                               \
        #lhs " and " #rhs " are expected to be different, but same"   \
      };                                                              \
                                                                      \
      throw err;                                                      \
    }                                                                 \
  }


#define COLLECTION(name)                                              \
  namespace {                                                         \
    pepper::testing::core::suite __current{#name};                    \
  }                                                                   \
  namespace

#define FACT(name)                                                    \
    class __##name : public pepper::testing::core::fact               \
    {                                                                 \
      public:                                                         \
        __##name() : fact{::__current, #name}                         \
        {                                                             \
        }                                                             \
      public:                                                         \
        virtual ~__##name() = default;                                \
      public:                                                         \
        virtual void run(void) const;                                 \
    };                                                                \
                                                                      \
    __##name __##name##obj;                                           \
                                                                      \
    void __##name::run(void) const

#endif
