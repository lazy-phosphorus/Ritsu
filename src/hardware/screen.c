#include "screen.h"

#include <assert.h>
#include <stdbool.h>

#include "type/image.h"

#ifdef WIN32

// Windows screenshot reference: https://github.com/kbinani/screenshot

#include <windows.h>

Image ScreenCapture() {
    int width = 0, height = 0, i = 0;
    long size = 0;
    Image screenshot = NULL;
    HWND desktop = NULL;
    HDC screen = NULL, screenCompatible = NULL;
    HBITMAP bitmap = NULL;
    HGLOBAL cache = NULL;
    LPVOID cachep = NULL;
    BITMAPINFOHEADER info;
    HGDIOBJ temp = NULL;
    WINBOOL ret = false;

    info.biSize = sizeof(BITMAPINFOHEADER);
    info.biPlanes = 1;
    info.biBitCount = 32;
    info.biWidth = width;
    info.biHeight = -height;
    info.biCompression = BI_RGB;
    info.biSizeImage = 0;

    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);

    desktop = GetDesktopWindow();
    screen = GetDC(desktop);
    screenCompatible = CreateCompatibleDC(screen);
    assert(screen != NULL);
    bitmap = CreateCompatibleBitmap(screen, width, height);
    assert(bitmap != NULL);
    size = width * 4 * height;
    cache = GlobalAlloc(GMEM_MOVEABLE, size);
    assert(cache != NULL);
    cachep = GlobalLock(cache);
    assert(cachep != NULL);
    temp = SelectObject(screenCompatible, bitmap);
    ret = BitBlt(screenCompatible, 0, 0, width, height, screen, 0, 0, SRCCOPY);
    assert(ret == true);

    screenshot = ImageNew();
    screenshot->pixels =
        (unsigned char *)calloc(width * height * 4, sizeof(unsigned char));
    screenshot->width = width;
    screenshot->height = height;
    screenshot->bytePerLine = width * 4;
    screenshot->bytePerPixel = 4;
    ret = GetBitmapBits(bitmap, width * height * 4, screenshot->pixels);
    assert(ret != 0);

    for (int i = 0; i < size; i += 4) {
        unsigned char temp = screenshot->pixels[i];
        screenshot->pixels[i] = screenshot->pixels[i + 2];
        screenshot->pixels[i + 2] = temp;
        screenshot->pixels[i + 3] = 255;
    }

    SelectObject(screenCompatible, temp);
    GlobalUnlock(cache);
    GlobalFree(cache);
    DeleteObject(bitmap);
    DeleteDC(screenCompatible);
    ReleaseDC(desktop, screen);

    return screenshot;
}

#elif defined(__linux__)

// TODO linux support

#endif
