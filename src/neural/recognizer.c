#include "recognizer.h"

#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <tesseract/capi.h>

#include "type/image.h"
#include "type/path.h"
#include "type/point.h"

Recognizer RecognizerNew(const Path restrict modelDir,
                         const char *const restrict language) {
    assert(modelDir != NULL);
    assert(language != NULL);
    int ret = 0;
    Recognizer this = TessBaseAPICreate();
    assert(this != NULL);

    // * according to official documentation, 0 will be returned on success
    ret = TessBaseAPIInit3(this, PathString(modelDir), language);
    assert(ret == 0);

    TessBaseAPISetPageSegMode(this, PSM_AUTO);

    // * according to official documentation, `true` wil be returned on success
    ret = TessBaseAPISetVariable(this, "debug_file", "/dev/null");
    assert(ret == true);
    return this;
}

void RecognizerDelete(Recognizer *const restrict this) {
    assert(this != NULL);
    TessBaseAPIEnd(*this);
    TessBaseAPIDelete(*this);
    *this = NULL;
}

RecognizerResult RecognizerRecognize(Recognizer restrict this,
                                     const Image restrict image) {
    assert(this != NULL);
    assert(image != NULL);
    int ret = 0;
    RecognizerResult results = ListNew(TextBlock);
    TessResultIterator *iterator = NULL;
    TessPageIterator *page = NULL;
    TextBlock temp;

    TessBaseAPISetImage(this, image->pixels, image->width, image->height,
                        image->bytePerPixel, image->bytePerLine);

    // * according to official documentation, 0 will be returned on success
    ret = TessBaseAPIRecognize(this, NULL);
    assert(ret == 0);

    iterator = TessBaseAPIGetIterator(this);
    if (iterator != NULL) {
        do {
            page = TessResultIteratorGetPageIterator(iterator);
            temp.text = TessResultIteratorGetUTF8Text(iterator, RIL_TEXTLINE);

            // * according to official documentation, if bounding box exists,
            // * `true` should be returned.
            ret = TessPageIteratorBoundingBox(page, RIL_TEXTLINE, &temp.left,
                                              &temp.top, &temp.right,
                                              &temp.bottom);
            assert(ret == true);
            ListPushBack(TextBlock, results, temp);
        } while (TessResultIteratorNext(iterator, RIL_TEXTLINE));
    }

    return results;
}

void RecognizerResultDelete(RecognizerResult *const restrict results) {
    assert(results != NULL);
    ListDelete1(TextBlock, results, TextBlockDestruct);
}

bool RecognizerFindText(Recognizer restrict this, const Image restrict image,
                        const char *const restrict text,
                        Point *const restrict point) {
    assert(this != NULL);
    assert(image != NULL);
    assert(text != NULL);
    assert(point != NULL);
    char *p = NULL;
    int length = 0;
    RecognizerResult results = RecognizerRecognize(this, image);
    ListNode(TextBlock) node = results->head;
    while (node != NULL) {
        p = strstr(node->value.text, text);
        if (p != NULL) {
            length = strlen(node->value.text);
            point->x = (node->value.right - node->value.left) *
                           (p - node->value.text) / (length) +
                       node->value.left;
            point->y = (node->value.top + node->value.bottom) / 2;
            RecognizerResultDelete(&results);
            return true;
        }
        node = node->next;
    }
    RecognizerResultDelete(&results);
    return false;
}
