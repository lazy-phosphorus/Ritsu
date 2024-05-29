#ifndef RITSU_DECLARATION_H
#define RITSU_DECLARATION_H

typedef struct __Image *Image;

/* tesseract declare */
typedef struct TessResultIterator TessResultIterator;
typedef struct TessBaseAPI TessBaseAPI;

/* lua declare */
typedef struct lua_State lua_State;
typedef int (*lua_CFunction)(lua_State *L);

#endif  // RITSU_DECLARATION_H
