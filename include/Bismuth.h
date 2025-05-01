#ifndef BISMUTH_BISMUTH_H
#define BISMUTH_BISMUTH_H

#define MAX_WINDOWS 128

#include "TermWin.h"

typedef struct Bismuth Bismuth;
struct Bismuth {
    Window windows[MAX_WINDOWS];
    int activeWinIndex;
    int (*getActiveWinIndex)(Bismuth* this);
    void (*_setActiveWinIndex)(Bismuth* this, int index);
    int winCount;
    int (*getWinCount)(Bismuth* this);

    void (*restoreTerminal)();
    void (*initTerminal)(Bismuth* this);
    void (*mainLoop)(Bismuth* this);

    void (*active)(Bismuth* this, Window* win);
    bool (*isActive)(Bismuth* this, Window* win);
}; Bismuth* newBismuth(); void delBismuth(Bismuth* this);

#endif //BISMUTH_BISMUTH_H
