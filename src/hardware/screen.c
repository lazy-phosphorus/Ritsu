#include "screen.h"

#include <malloc.h>

#include "type/image.h"

#ifdef WIN32

#include <Windows.h>

Image ScreenShot() {
    LONG size = 0;
    HBITMAP bitmap = NULL;
    Image image = ImageNew();
    HDC screen = GetDC(NULL);
    HDC screenCompatible = CreateCompatibleDC(screen);

    image->width = GetSystemMetrics(SM_CXSCREEN);
    image->height = GetSystemMetrics(SM_CYSCREEN);
    size = image->width * image->height * 4;
    image->bytesPerPixel = 4;
    image->bytesPerLine = image->width * 4;
    image->data = (unsigned char *)calloc(size, sizeof(unsigned char));

    bitmap =
        CreateCompatibleBitmap(screenCompatible, image->width, image->height);
    SelectObject(screenCompatible, bitmap);
    BitBlt(screenCompatible, 0, 0, image->width, image->height, screen, 0, 0,
           SRCCOPY);
    GetBitmapBits(bitmap, size, image->data);

    DeleteObject(bitmap);
    DeleteDC(screenCompatible);
    ReleaseDC(NULL, screen);

    return image;
}

#elif defined(__linux__)

// TODO linux screen shot

#endif
