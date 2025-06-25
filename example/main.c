#include "BWinManager.h"
#include "logger/logger.h"

int main() {
    log_init("app.log");
    BWinManager* wm = newBismuth();
    wm->initTerminal(wm);
    Window* win = newWindow(1, 1, 40, 10, "Window0", wm);
    Window* win1 = newWindow(5, 5, 40, 10, "Window1", wm);
    Window* win2 = newWindow(10, 10, 40, 10, "Window2", wm);
    // Window* win3 = newWindow(15, 15, 40, 10, "Window3", wm);
    // LOG_INFO("win id:%d\nwin1 id:%d\n", win->id, win1->id);
    LOG_INFO("%d", wm->activeWinIndex);
    wm->active(wm, win);
    wm->mainLoop(wm);
    log_close();
}