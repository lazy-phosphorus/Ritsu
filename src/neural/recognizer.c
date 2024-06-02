#include "recognizer.h"

#include <tesseract/capi.h>

#include "type/image.h"
#include "type/path.h"

Recognizer RecognizerNew(const Path restrict modelDir,
                         const char *const restrict language) {
    Recognizer this = TessBaseAPICreate();
    TessBaseAPIInit3(this, PathString(modelDir), language);
    TessBaseAPISetPageSegMode(this, PSM_AUTO);
    return this;
}

void RecognizerDelete(Recognizer *const restrict this) {
    TessBaseAPIEnd(*this);
    TessBaseAPIDelete(*this);
    *this = NULL;
}

RecognizerResult RecognizerRecognize(Recognizer restrict this,
                                     const Image restrict image) {
    RecognizerResult results = ListNew(TextBlock);
    TessResultIterator *iterator = NULL;
    TessPageIterator *page = NULL;
    TextBlock temp;
    TessBaseAPISetImage(this, image->pixels, image->width, image->height,
                        image->bytePerPixel, image->bytePerLine);
    TessBaseAPIRecognize(this, NULL);

    iterator = TessBaseAPIGetIterator(this);
    if (iterator != NULL) {
        do {
            page = TessResultIteratorGetPageIterator(iterator);
            temp.text = TessResultIteratorGetUTF8Text(iterator, RIL_TEXTLINE);
            TessPageIteratorBoundingBox(page, RIL_TEXTLINE, &temp.left,
                                        &temp.top, &temp.right, &temp.bottom);
            printf("%s, (%d, %d)\n", temp.text, temp.left, temp.top);
            ListPushBack(TextBlock, results, temp);
        } while (TessResultIteratorNext(iterator, RIL_TEXTLINE));
    }

    return results;
}
