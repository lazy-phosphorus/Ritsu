#include "screen.h"

#include <assert.h>
#include <lauxlib.h>
#include <lua.h>

#include "hardware/screen.h"
#include "script/lua/metatable/image.h"
#include "type/image.h"

static int __ScreenCapture(LuaContext restrict this) {
    Image *image = NULL;
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    image = (Image *)lua_newuserdata(this, sizeof(Image));
    *image = ScreenCapture();
    luaL_setmetatable(this, LUA_IMAGE_METATABLE_NAME);
    return 1;
}

void LuaAddScreenTable(LuaContext restrict this) {
    int type = lua_getglobal(this, "Ritsu");
    assert(type == LUA_TTABLE);
    lua_createtable(this, 0, 2);

    lua_pushcfunction(this, __ScreenCapture);
    lua_setfield(this, -2, "Capture");

    lua_setfield(this, -2, "Screen");
    lua_pop(this, 1);
}