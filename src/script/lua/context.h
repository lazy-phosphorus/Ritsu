#ifndef RITSU_SCRIPT_LUA_CONTEXT_H
#define RITSU_SCRIPT_LUA_CONTEXT_H

#include "declaration.h"

typedef lua_State *LuaContext;

LuaContext LuaContextNew(const int argc, char *const *const restrict argv);

void LuaContextExecuteFile(LuaContext restrict this,
                           const Path restrict filePath);

void LuaContextDelete(LuaContext *const restrict this);

#endif  // RITSU_SCRIPT_LUA_CONTEXT_H
