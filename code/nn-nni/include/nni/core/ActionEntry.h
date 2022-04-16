#ifndef __NNI_CORE_ACTION_ENTRY_H__
#define __NNI_CORE_ACTION_ENTRY_H__

#include "Action.h"
#include "Arguments.h"

extern "C" std::unique_ptr<Action> make_action(const Arguments &);

#endif // __NNI_CORE_ACTION_ENTRY_H__
