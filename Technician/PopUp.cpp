#include "PopUp.h"

int PopUp(LPCSTR text, LPCSTR caption) {
    return MessageBoxA(NULL, text, caption, MB_ICONINFORMATION);
}
