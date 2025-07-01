#include "PopUp.h"

int PopUp(LPCSTR text, LPCSTR caption) {
    return MessageBoxA(NULL, text, caption, MB_ICONINFORMATION);
}

void PopupLoop() {
    while (1) {
        PopUp("MANAGMENT PROGRAM IS UP!", "virus");
        Sleep(HOUR_IN_MILISECONDS);
    }
}
