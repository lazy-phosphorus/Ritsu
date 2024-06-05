#include "context.h"

#include <assert.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <type/path.h>

#include "metatable/image.h"
#include "metatable/recognizer.h"
#include "table/cursor.h"
#include "table/screen.h"

LuaContext LuaContextNew(const int argc, char *const *const restrict argv) {
    assert(argv != NULL);
    LuaContext this = luaL_newstate();
    assert(this != NULL);
    luaL_openlibs(this);

    lua_createtable(this, 0, 3);
    lua_setglobal(this, "Ritsu");

    lua_createtable(this, argc, 0);
    for (int i = 0; i < argc; i++) {
        lua_pushstring(this, argv[i]);
        lua_seti(this, -2, i);
    }
    lua_setglobal(this, "Args");

    LuaAddImageMetatable(this);
    LuaAddRecognizerMetatable(this);

    LuaAddScreenTable(this);
    LuaAddCursorTable(this);

    return this;
}

void LuaContextExecuteFile(LuaContext restrict this,
                           const Path restrict filePath) {
    assert(this != NULL);
    assert(filePath != NULL);
    int ret = LUA_OK;
    ret = luaL_loadfile(this, PathString(filePath));
    if (ret != LUA_OK) {
        // TODO load exception
    }
    ret = lua_pcall(this, 0, 0, 0);
    if (ret != LUA_OK) {
        // TODO execution exception
    }
}

void LuaContextDelete(LuaContext *const restrict this) {
    assert(this != NULL);
    lua_gc(*this, LUA_GCCOLLECT);
    lua_close(*this);
    *this = NULL;
}
