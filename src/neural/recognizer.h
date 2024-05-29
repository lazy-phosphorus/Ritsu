#ifndef RITSU_NEURAL_RECOGNIZER_H
#define RITSU_NEURAL_RECOGNIZER_H

#include "collection/list.h"
#include "declaration.h"

typedef TessBaseAPI *Recognizer;

typedef struct __RecognizerResult {
    char *text;
    int left;
    int right;
    int top;
    int bottom;
} __RecognizerResult;

typedef __RecognizerResult *RecognizerResult;

UseList(RecognizerResult);

Recognizer RecognizerNew(const char *const restrict modelDir,
                         const char *const restrict language);

void RecognizerDelete(const Recognizer restrict this);

RecognizerResult RecognizerResultNew();

void RecognizerResultDelete(RecognizerResult restrict this);

List(RecognizerResult) RecognizerRecognize(const Recognizer restrict this,
                                           const Image restrict image);

#endif  // RITSU_NEURAL_RECOGNIZER_H
