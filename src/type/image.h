#ifndef RITSU_TYPE_IMAGE_H
#define RITSU_TYPE_IMAGE_H

#include <stdbool.h>

#include "declaration.h"

typedef struct Image {
    int width;
    int height;
    int bytePerPixel;
    int bytePerLine;
    unsigned char *pixels;
} *Image;

Image ImageNew();

void ImageDelete(Image *const restrict this);

bool ImageFindColor(const Image restrict this, const unsigned char red,
                    const unsigned char green, const unsigned char blue,
                    Point *const restrict output);

bool ImageFindColorThreshold(const Image restrict this, const unsigned char red,
                             const unsigned char green,
                             const unsigned char blue,
                             const unsigned char threshold,
                             Point *const restrict output);

#endif  // RITSU_TYPE_IMAGE_H
