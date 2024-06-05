#include "screen.h"

#include <assert.h>

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

    // * according to official documentation, 0 will be returned on failure.
    width = GetSystemMetrics(SM_CXSCREEN);
    assert(width != 0);
    height = GetSystemMetrics(SM_CYSCREEN);
    assert(height != 0);

    size = width * 4 * height;

    desktop = GetDesktopWindow();

    // * according to official documentation, `NULL` will be returned on
    // * failure.
    screen = GetDC(desktop);
    assert(screen != NULL);
    screenCompatible = CreateCompatibleDC(screen);
    assert(screen != NULL);
    bitmap = CreateCompatibleBitmap(screen, width, height);
    assert(bitmap != NULL);
    cache = GlobalAlloc(GMEM_MOVEABLE, size);
    assert(cache != NULL);
    cachep = GlobalLock(cache);
    assert(cachep != NULL);

    // * according to official documentation, `NULL` or `HGDI_ERROR` will be
    // * returned on failure.
    temp = SelectObject(screenCompatible, bitmap);
    assert(temp != HGDI_ERROR && temp != NULL);

    // * according to official documentation, 0 will be returned on failure.
    ret = BitBlt(screenCompatible, 0, 0, width, height, screen, 0, 0, SRCCOPY);
    assert(ret != 0);

    screenshot = ImageNew();
    screenshot->pixels =
        (unsigned char *)calloc(width * height * 4, sizeof(unsigned char));
    assert(screenshot->pixels != NULL);
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

    temp = SelectObject(screenCompatible, temp);
    assert(temp != HGDI_ERROR && temp != NULL);

    // * according to official documentation, if memory is unlocked, 0 will be
    // * returned and `GetLastError()` will return `NO_ERROR`.
    ret = GlobalUnlock(cache);
    assert(ret == 0 && GetLastError() == NO_ERROR);

    // * according to official documentation, `NULL` will be returned on
    // success.
    temp = GlobalFree(cache);
    assert(temp == NULL);

    // * according to official documentation, 0 will be returned on failure.
    ret = DeleteObject(bitmap);
    assert(ret != 0);
    ret = DeleteDC(screenCompatible);
    assert(ret != 0);

    // * according to official documentation, 1 will be returned on success.
    ret = ReleaseDC(desktop, screen);
    assert(ret == 1);

    return screenshot;
}

#elif defined(__linux__)

// TODO linux support

#endif
