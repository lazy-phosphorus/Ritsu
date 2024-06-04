#ifndef RITSU_DECLARATION_H
#define RITSU_DECLARATION_H

#include "collection/array.h"

typedef Array(char) Path;
typedef struct Image *Image;
typedef struct TextBlock TextBlock;
typedef struct Point Point;

// tesseract
typedef struct TessBaseAPI TessBaseAPI;

// lua
typedef struct lua_State lua_State;
typedef lua_State *LuaContext;

#endif  // RITSU_DECLARATION_H
