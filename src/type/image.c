#include "image.h"

#include <malloc.h>

Image ImageNew() {
    Image this = (Image)malloc(sizeof(__Image));
    this->data = NULL;
    this->bytesPerLine = 0;
    this->bytesPerPixel = 0;
    this->width = 0;
    this->height = 0;
    return this;
}

void ImageDelete(Image restrict this) {
    free(this->data);
    free(this);
}