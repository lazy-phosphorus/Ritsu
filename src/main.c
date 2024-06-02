#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#include "hardware/screen.h"
#include "neural/recognizer.h"
#include "type/image.h"
#include "type/path.h"
#include "type/point.h"

int main(int argc, char *argv[]) {
    Point a;
    Path path = PathNew(argv[0]);
    PathParent(path);
    PathParent(path);
    PathJoin(path, "model");
    Recognizer ocr = RecognizerNew(path, "chi_sim");
    Image image = ScreenCapture();
    if (ImageFindColor(image, 255, 0, 0, &a))
        printf("(%d, %d)\n", a.x, a.y);
    else
        printf("failed.\n");

    // RecognizerResult results = RecognizerRecognize(ocr, image);

    // // ListNode(TextBlock) i = results->head;
    // // while (i != NULL) {
    // //     printf("%s, (%d, %d)\n", i->value.text, i->value.left,
    // i->value.top);
    // //     i = i->next;
    // // }

    // ListDelete1(TextBlock, &results, TextBlockDestruct);
    ImageDelete(&image);
    RecognizerDelete(&ocr);
    PathDelete(&path);
    return 0;
}
