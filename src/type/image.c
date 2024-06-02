#include "image.h"

#include <assert.h>
#include <malloc.h>

#include "type/point.h"

Image ImageNew() {
    Image this = (Image)malloc(sizeof(struct Image));
    this->width = 0;
    this->height = 0;
    this->bytePerLine = 0;
    this->bytePerPixel = 0;
    this->pixels = NULL;
    return this;
}

void ImageDelete(Image *const restrict this) {
    free((*this)->pixels);
    free(*this);
    *this = NULL;
}

bool ImageFindColor(const Image restrict this, const unsigned char red,
                    const unsigned char green, const unsigned char blue,
                    Point *const restrict output) {
    assert(this != NULL);
    assert(output != NULL);
    assert(this->bytePerPixel >= 3);
    for (int i = 0; i < this->width * this->height * this->bytePerPixel;
         i += this->bytePerPixel) {
        if (this->pixels[i] == red && this->pixels[i + 1] == green &&
            this->pixels[i + 2] == blue) {
            output->y = i / this->bytePerLine;
            output->x = (i % this->bytePerLine) / this->bytePerPixel;
            return true;
        }
    }
    return false;
}
