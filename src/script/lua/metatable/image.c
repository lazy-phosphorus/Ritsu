#include "image.h"

#include <lauxlib.h>
#include <lua.h>
#include <stdbool.h>

#include "type/image.h"
#include "type/point.h"

static int __ImageDelete(LuaContext restrict this) {
    Image *image = NULL;
    int argc = lua_gettop(this);
    if (argc < 1) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 1) {
        // TODO redundant paramter warning
    }

    image = (Image *)lua_touserdata(this, 1);
    if (image == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    ImageDelete(image);
    return 0;
}

static int __ImageFindColor(LuaContext restrict this) {
    Point output;
    Image *image = NULL;
    lua_Integer red = 0, green = 0, blue = 0, threshold = 0;
    bool ret = false;
    int argc = lua_gettop(this), success = 0;
    if (argc < 4) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 5) {
        // TODO redundant paramter warning
    }

    image = (Image *)lua_touserdata(this, 1);
    if (image == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    red = lua_tointegerx(this, 2, &success);
    if (success == false || red > 255 || red < 0) {
        // TODO incorrect paramter type exceptioin
        return 0;
    }
    green = lua_tointegerx(this, 3, &success);
    if (success == false || green > 255 || green < 0) {
        // TODO incorrect paramter type exceptioin
        return 0;
    }
    blue = lua_tointegerx(this, 4, &success);
    if (success == false || blue > 255 || blue < 0) {
        // TODO incorrect paramter type exceptioin
        return 0;
    }

    if (argc == 4) {
        ret = ImageFindColor(*image, red, green, blue, &output);
        if (ret) {
            lua_pushinteger(this, output.x);
            lua_pushinteger(this, output.y);
            return 2;
        } else
            return 0;
    } else {
        threshold = lua_tointegerx(this, 5, &success);
        if (success == false || threshold > 255 || threshold < 0) {
            // TODO incorrect paramter type exceptioin
            return 0;
        }
        ret = ImageFindColorThreshold(*image, red, green, blue, threshold,
                                      &output);
        if (ret) {
            lua_pushinteger(this, output.x);
            lua_pushinteger(this, output.y);
            return 2;
        } else
            return 0;
    }
}

void LuaAddImageMetatable(LuaContext restrict this) {
    if (luaL_newmetatable(this, LUA_IMAGE_METATABLE_NAME) == false) {
        // TODO redefination warning
    }
    lua_pushvalue(this, -1);
    lua_setfield(this, -2, "__index");
    lua_pushcfunction(this, __ImageDelete);
    lua_setfield(this, -2, "__gc");
    lua_pushcfunction(this, __ImageFindColor);
    lua_setfield(this, -2, "FindColor");
    lua_pop(this, 1);
}