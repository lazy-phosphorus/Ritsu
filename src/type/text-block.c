#include "text-block.h"

#include <malloc.h>

void TextBlockDestruct(TextBlock this) { free(this.text); }
