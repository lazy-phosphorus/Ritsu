#include "cursor.h"

#include <assert.h>

#include "type/point.h"

#ifdef WIN32

#include <windows.h>

void MouseMoveTo(Point point) {
    WINBOOL ret = SetCursorPos(point.x, point.y);
    assert(ret == TRUE);
}

void MouseLeftClick() {
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void MouseRightClick() {
    mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void MouseLeftDown() { mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); }

void MouseLeftUp() { mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); }

void MouseRightDown() { mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); }

void MouseRightUp() { mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0); }

#elif defined(__linux__)

// TODO linux support

#endif