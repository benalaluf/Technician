#include "PopUp.h"

int PopUp(LPCSTR text, LPCSTR caption) {
    return MessageBoxA(NULL, text, caption, MB_ICONINFORMATION);
}

void PopupLoop() {
    while (1) {
        PopUp(POPUP_LOOP_TEXT, POPUP_LOOP_CAPTION);
        Sleep(HOUR_IN_MILISECONDS);
    }
}
