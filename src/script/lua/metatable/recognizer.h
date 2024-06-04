#ifndef RITSU_SCRIPT_METATABLE_RECOGNIZER_H
#define RITSU_SCRIPT_METATABLE_RECOGNIZER_H

#include "declaration.h"

#define LUA_RECOGNIZER_METATABLE_NAME "Recognizer"
#define LUA_RECOGNIZER_RESULT_METATABLE_NAME "RecognizerResult"

void LuaAddRecognizerMetatable(LuaContext restrict this);

#endif  // RITSU_SCRIPT_METATABLE_RECOGNIZER_H
