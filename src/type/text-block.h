#ifndef RITSU_TYPE_TEXTBLOCK_H
#define RITSU_TYPE_TEXTBLOCK_H

typedef struct TextBlock {
    int left;
    int right;
    int top;
    int bottom;
    char *text;
} TextBlock;

void TextBlockDestruct(TextBlock this);

#endif  // RITSU_TYPE_TEXTBLOCK_H
