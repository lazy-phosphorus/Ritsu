#include "recognizer.h"

#include <assert.h>
#include <malloc.h>
#include <tesseract/capi.h>

#include "type/image.h"

Recognizer RecognizerNew(const char *const restrict modelDir,
                         const char *const restrict language) {
    TessBaseAPI *this = TessBaseAPICreate();
    TessBaseAPIInit3(this, modelDir, language);
    TessBaseAPISetPageSegMode(this, PSM_AUTO);
    return this;
}

void RecognizerDelete(const Recognizer restrict this) {
    TessBaseAPIEnd(this);
    TessBaseAPIDelete(this);
}

List(RecognizerResult) RecognizerRecognize(const Recognizer restrict this,
                                           const Image restrict image) {
    TessResultIterator *iterator = NULL;
    TessPageIterator *page = NULL;
    RecognizerResult temp = RecognizerResultNew();
    List(RecognizerResult) list = ListNew(RecognizerResult);

    TessBaseAPISetImage(this, image->data, image->width, image->height,
                        image->bytesPerPixel, image->bytesPerLine);
    TessBaseAPIRecognize(this, NULL);
    iterator = TessBaseAPIGetIterator(this);
    if (iterator != NULL) {
        do {
            page = TessResultIteratorGetPageIterator(iterator);
            temp->text = TessResultIteratorGetUTF8Text(iterator, RIL_TEXTLINE);
            TessPageIteratorBoundingBox(page, RIL_TEXTLINE, &temp->left,
                                        &temp->top, &temp->right,
                                        &temp->bottom);
            ListPushBack(RecognizerResult, list, temp);
        } while (TessResultIteratorNext(iterator, RIL_TEXTLINE));
    }
    return list;
}

RecognizerResult RecognizerResultNew() {
    RecognizerResult this =
        (RecognizerResult)malloc(sizeof(__RecognizerResult));
    this->text = NULL;
    this->top = 0;
    this->bottom = 0;
    this->left = 0;
    this->right = 0;
    return this;
}

void RecognizerResultDelete(RecognizerResult restrict this) {
    free(this->text);
    free(this);
}
