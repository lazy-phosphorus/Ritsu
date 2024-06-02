#ifndef RITSU_TYPE_PATH_H
#define RITSU_TYPE_PATH_H

#include "collection/array.h"

USE_ARRAY(char);

typedef Array(char) Path;

Path PathNew(const char *const restrict path);

void PathDelete(Path *const restrict this);

void PathParent(Path restrict this);

void PathJoin(Path restrict this, const char *const restrict path);

const char *PathString(const Path restrict this);

#endif  // RITSU_TYPE_PATH_H
