#include "image.h"

#include <lauxlib.h>
#include <lua.h>
#include <stdbool.h>

#include "type/image.h"

static int __ImageDelete(LuaContext restrict this) {
    Image *image = NULL;
    int argc = lua_gettop(this);
    if (argc < 1) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 1) {
        // TODO redundant paramter warning
    }

    image = (Image *)lua_touserdata(this, -1);
    if (image == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    ImageDelete(image);
    return 0;
}

void LuaAddImageMetatable(LuaContext restrict this) {
    if (luaL_newmetatable(this, LUA_IMAGE_METATABLE_NAME) == false) {
        // TODO redefination warning
    }
    lua_pushvalue(this, -1);
    lua_setfield(this, -2, "__index");
    lua_pushcfunction(this, __ImageDelete);
    lua_setfield(this, -2, "__gc");
    lua_pop(this, 1);
}