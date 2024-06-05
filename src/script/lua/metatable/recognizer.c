#include "recognizer.h"

#include <assert.h>
#include <lauxlib.h>
#include <lua.h>
#include <stdbool.h>

#include "neural/recognizer.h"
#include "type/path.h"
#include "type/point.h"

static int __RecognizerDelete(LuaContext restrict this) {
    Recognizer *ocr = NULL;
    int argc = lua_gettop(this);
    if (argc < 1) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 1) {
        // TODO redundant paramter warning
    }

    ocr = (Recognizer *)lua_touserdata(this, 1);
    if (ocr == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    RecognizerDelete(ocr);

    return 0;
}

static int __RecognizerResultDelete(LuaContext restrict this) {
    RecognizerResult *list = NULL;
    int argc = lua_gettop(this);
    if (argc < 1) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 1) {
        // TODO redundant paramter warning
    }

    list = (RecognizerResult *)lua_touserdata(this, 1);
    if (list == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }

    RecognizerResultDelete(list);
    return 0;
}

static int __RecognizerNew(LuaContext restrict this) {
    Path path = NULL;
    Recognizer ocr = NULL, *p = NULL;
    const char *temp = NULL;
    int type = 0, argc = lua_gettop(this);
    if (argc == 0) {
        type = lua_getglobal(this, "Args");
        if (type != LUA_TTABLE) {
            // TODO invalid args exception
            return 0;
        }
        type = lua_geti(this, -1, 0);
        if (type != LUA_TSTRING) {
            // TODO invalid args index exception
            return 0;
        }
        temp = lua_tostring(this, -1);
        if (temp == NULL) {
            // TODO invalid args index exception
        }

        path = PathNew(temp);
        PathParent(path);
        PathParent(path);
        PathJoin(path, "model");

        /* only chinese supported for now */
        ocr = RecognizerNew(path, "chi_sim");
        PathDelete(&path);
        lua_pop(this, 2);
    } else {
        if (argc > 1) {
            // TODO redundant paramter warning
        }
        temp = lua_tostring(this, 1);
        path = PathNew(temp);

        /* only chinese supported for now */
        ocr = RecognizerNew(path, "chi_sim");
        PathDelete(&path);
    }

    p = (Recognizer *)lua_newuserdata(this, sizeof(Recognizer));
    *p = ocr;
    luaL_setmetatable(this, LUA_RECOGNIZER_METATABLE_NAME);

    return 1;
}

static int __RecognizerRecognize(LuaContext restrict this) {
    Recognizer *ocr = NULL;
    Image *image = NULL;
    RecognizerResult list = NULL;
    ListNode(TextBlock) node = NULL;
    int argc = lua_gettop(this), i = 0;
    if (argc < 2) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 2) {
        // TODO redundant paramter warning
    }

    ocr = (Recognizer *)lua_touserdata(this, 1);
    if (ocr == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    image = (Image *)lua_touserdata(this, 2);
    if (image == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }

    list = RecognizerRecognize(*ocr, *image);
    lua_createtable(this, list->size, 0);

    node = list->head;
    i = 1;
    while (node != NULL) {
        lua_createtable(this, 0, 5);
        lua_pushinteger(this, node->value.left);
        lua_setfield(this, -2, "left");
        lua_pushinteger(this, node->value.right);
        lua_setfield(this, -2, "right");
        lua_pushinteger(this, node->value.top);
        lua_setfield(this, -2, "top");
        lua_pushinteger(this, node->value.bottom);
        lua_setfield(this, -2, "bottom");
        lua_pushstring(this, node->value.text);
        lua_setfield(this, -2, "text");

        lua_seti(this, -2, i);
        node = node->next;
        i++;
    }

    RecognizerResultDelete(&list);
    return 1;
}

static int __RecognizerFindText(LuaContext restrict this) {
    Point output;
    Recognizer *ocr = NULL;
    Image *image = NULL;
    RecognizerResult list = NULL;
    const char *text = NULL;
    bool ret = false;
    int argc = lua_gettop(this), i = 0;
    if (argc < 3) {
        // TODO missing paramter exception
        return 0;
    } else if (argc > 3) {
        // TODO redundant paramter warning
    }

    ocr = (Recognizer *)lua_touserdata(this, 1);
    if (ocr == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    image = (Image *)lua_touserdata(this, 2);
    if (image == NULL) {
        // TODO incorrect paramter type exception
        return 0;
    }
    text = lua_tostring(this, 3);
    if (text == NULL) {
        // TODO incorrect paramter type exception
    }

    ret = RecognizerFindText(*ocr, *image, text, &output);
    if (ret) {
        lua_pushinteger(this, output.x);
        lua_pushinteger(this, output.y);
        return 2;
    } else
        return 0;
}

void LuaAddRecognizerMetatable(LuaContext restrict this) {
    /* create `Recognizer` class */
    if (luaL_newmetatable(this, LUA_RECOGNIZER_METATABLE_NAME) == false) {
        // TODO redefination warning
    }
    lua_pushvalue(this, -1);
    lua_setfield(this, -2, "__index");
    lua_pushcfunction(this, __RecognizerDelete);
    lua_setfield(this, -2, "__gc");
    lua_pushcfunction(this, __RecognizerRecognize);
    lua_setfield(this, -2, "Recognize");
    lua_pushcfunction(this, __RecognizerFindText);
    lua_setfield(this, -2, "FindText");
    lua_pop(this, 1);

    /* add constructor function */
    int type = lua_getglobal(this, "Ritsu");
    assert(type == LUA_TTABLE);
    lua_pushcfunction(this, __RecognizerNew);
    lua_setfield(this, -2, "RecognizerNew");
    lua_pop(this, 1);
}
