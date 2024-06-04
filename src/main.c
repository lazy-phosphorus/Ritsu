#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "hardware/cursor.h"
#include "hardware/screen.h"
#include "neural/recognizer.h"
#include "script/lua/context.h"
#include "type/image.h"
#include "type/path.h"
#include "type/point.h"

int main(const int argc, char **const restrict argv) {
    if (argc == 1) {
        // this branch is used in test for now.
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

        RecognizerResult results = RecognizerRecognize(ocr, image);

        ListNode(TextBlock) i = results->head;
        while (i != NULL) {
            printf("%s, (%d, %d)\n", i->value.text, i->value.left,
                   i->value.top);
            char *a = strstr(i->value.text, "鼠标\0");
            if (a != NULL) {
                int length = strlen(i->value.text);
                Point temp = {(i->value.right - i->value.left) *
                                      (a - i->value.text) / (length) +
                                  i->value.left,
                              (i->value.top + i->value.bottom) / 2};
                MouseMoveTo(temp);
                printf("founded\n");
                break;
            }
            i = i->next;
        }

        ListDelete1(TextBlock, &results, TextBlockDestruct);
        ImageDelete(&image);
        RecognizerDelete(&ocr);
        PathDelete(&path);
    } else {
        LuaContext lua = LuaContextNew(argc, argv);
        Path path = PathNew(argv[1]);
        LuaContextExecuteFile(lua, path);
        PathDelete(&path);
        LuaContextDelete(&lua);
    }

    return 0;
}
