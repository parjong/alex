#ifndef __NNI_CORE_ENGINE_H__
#define __NNI_CORE_ENGINE_H__

#include "Session.h"
#include "Arguments.h"

#include <memory>

extern "C" std::unique_ptr<Session> make_session(const Arguments &);

#endif // __NNI_CORE_ENGINE_H__
