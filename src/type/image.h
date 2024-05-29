#ifndef RITSU_TYPE_IMAGE_H
#define RITSU_TYPE_IMAGE_H

typedef struct __Image {
    unsigned char *data;
    int width;
    int height;
    int bytesPerPixel;
    int bytesPerLine;
} __Image;

typedef __Image *Image;

Image ImageNew();

void ImageDelete(Image restrict this);

#endif  // RITSU_TYPE_IMAGE_H