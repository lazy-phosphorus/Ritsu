#include "cursor.h"

#include <assert.h>
#include <lauxlib.h>
#include <lua.h>
#include <stdbool.h>

#include "hardware/cursor.h"
#include "type/point.h"

static int __MouseMoveTo(LuaContext restrict this) {
    Point point;
    int argc = lua_gettop(this);
    int success = false;
    if (argc < 2) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 2) {
        // TODO redundant paramter warning
    }

    point.x = lua_tointegerx(this, -1, &success);
    if (success == false) {
        // TODO incorrect paramter type exceptioin
        return 0;
    }
    point.y = lua_tointegerx(this, -2, &success);
    if (success == false) {
        // TODO incorrect paramter type exceptioin
        return 0;
    }

    MouseMoveTo(point);

    return 0;
}

static int __MouseLeftClick(LuaContext restrict this) {
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    MouseLeftClick();

    return 0;
}

static int __MouseRightClick(LuaContext restrict this) {
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    MouseRightClick();

    return 0;
}

static int __MouseLeftDown(LuaContext restrict this) {
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    MouseLeftDown();

    return 0;
}

static int __MouseLeftUp(LuaContext restrict this) {
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    MouseLeftUp();

    return 0;
}

static int __MouseRightDown(LuaContext restrict this) {
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    MouseRightDown();

    return 0;
}

static int __MouseRightUp(LuaContext restrict this) {
    if (lua_gettop(this) != 0) {
        // TODO redundant paramter warning
    }

    MouseRightUp();

    return 0;
}

void LuaAddCursorTable(LuaContext restrict this) {
    int type = lua_getglobal(this, "Ritsu");
    assert(type == LUA_TTABLE);

    lua_createtable(this, 0, 8);

    lua_pushcfunction(this, __MouseMoveTo);
    lua_setfield(this, -2, "MoveTo");
    lua_pushcfunction(this, __MouseLeftClick);
    lua_setfield(this, -2, "LeftClick");
    lua_pushcfunction(this, __MouseRightClick);
    lua_setfield(this, -2, "RightClick");
    lua_pushcfunction(this, __MouseLeftDown);
    lua_setfield(this, -2, "LeftDown");
    lua_pushcfunction(this, __MouseLeftUp);
    lua_setfield(this, -2, "LeftUp");
    lua_pushcfunction(this, __MouseRightDown);
    lua_setfield(this, -2, "RightDown");
    lua_pushcfunction(this, __MouseRightUp);
    lua_setfield(this, -2, "RightUp");

    lua_setfield(this, -2, "Cursor");
    lua_pop(this, 1);
}
