#ifndef BISMUTH_H
#define BISMUTH_H

#define MAX_WINDOWS 128

#include "TermWin.h"

typedef struct BWinManager BWinManager;
struct BWinManager {
    Window windows[MAX_WINDOWS];
    int activeWinIndex;
    int (*getActiveWinIndex)(BWinManager* this);
    void (*_setActiveWinIndex)(BWinManager* this, int index);
    int winCount;
    int (*getWinCount)(BWinManager* this);

    void (*restoreTerminal)();
    void (*initTerminal)(BWinManager* this);
    void (*mainLoop)(BWinManager* this);

    void (*active)(BWinManager* this, Window* win);
    bool (*isActive)(BWinManager* this, Window* win);
}; BWinManager* newBismuth(); void delBismuth(BWinManager* this);

#endif //BISMUTH_H
