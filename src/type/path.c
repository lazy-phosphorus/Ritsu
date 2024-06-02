#include "path.h"

#include <assert.h>
#include <malloc.h>
#include <string.h>

Path PathNew(const char *const restrict path) {
    unsigned int length = strlen(path);
    Path this = ArrayNew(char, length);
    memcpy(this->array, path, length * sizeof(char));
    this->size = length;
    return this;
}

void PathDelete(Path *const restrict this) { ArrayDelete(char, this); }

void PathParent(Path restrict this) {
    char temp = '\0';
    for (unsigned int i = this->size - 1; i > 0; i--) {
        temp = ArrayGet(char, this, i);
        if (temp == '/' || temp == '\\') {
            this->size = i + 1;
            ArraySet(char, this, i, '\0');
            return;
        }
    }
}

void PathJoin(Path restrict this, const char *const restrict path) {
    unsigned int length = strlen(path);

    if (path[length - 1] == '/' || path[length - 1] == '\\') {
        length--;
    }
    if (path[0] != '/' || path[0] != '\\')
        this->array[this->size - 1] = '/';
    else
        this->size--;
    ArrayPushBack1(char, this, path, length);
    ArrayPushBack(char, this, '\0');
}

const char *PathString(const Path restrict this) { return this->array; }
