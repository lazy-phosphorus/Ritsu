#include <hardware/screen.h>

#include "neural/recognizer.h"
#include "type/image.h"

int main(int argc, char *argv[]) {
    Recognizer ocr = RecognizerNew(argv[0], "chi_sim");
    Image screenshot = ScreenShot();

    RecognizerRecognize(ocr, screenshot);

    RecognizerDelete(ocr);
    ImageDelete(screenshot);
    return 0;
}
