#ifndef RITSU_NEURAL_RECOGNIZER_H
#define RITSU_NEURAL_RECOGNIZER_H

#include <stdbool.h>

#include "collection/list.h"
#include "declaration.h"
#include "type/text-block.h"

typedef TessBaseAPI *Recognizer;

USE_LIST(TextBlock);

typedef List(TextBlock) RecognizerResult;

Recognizer RecognizerNew(const Path restrict modelDir,
                         const char *const restrict language);

void RecognizerDelete(Recognizer *const restrict this);

RecognizerResult RecognizerRecognize(Recognizer restrict this,
                                     const Image restrict image);

void RecognizerResultDelete(RecognizerResult *const restrict results);

bool RecognizerFindText(Recognizer restrict this, const Image restrict image,
                        const char *const restrict text,
                        Point *const restrict point);

#endif  // RITSU_NEURAL_RECOGNIZER_H
