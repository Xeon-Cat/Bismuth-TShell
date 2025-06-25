/* BWinManager.c - 窗口管理器实现 */
#include "BWinManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "logger/logger.h"


static struct termios orig_termios;

/* 初始化终端原始模式 */
static void initTerminal(BWinManager* this) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(this->restoreTerminal);

    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    printf("\033[?1049h\033[2J"); // 进入备用屏幕缓冲
}

/* 恢复终端设置 */
static void restoreTerminal() {
    printf("\033[?1049l"); // 退出备用屏幕
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void drawWindows(BWinManager* master) {
    // 清屏并绘制所有窗口
    printf("\033[2J");
    for (int i = 0; i < master->getWinCount(master); i++) {
        master->windows[i].drawWindow(&master->windows[i]);
        master->windows[i].drawWindow(&master->windows[i]);
    }
    master->windows[master->getActiveWinIndex(master)]
    .drawWindow(&master->windows[master->getActiveWinIndex(master)]);
    fflush(stdout);
}

void drawModules(BWinManager* master) {}

/* 主事件循环 */
static void mainLoop(BWinManager* this) {
    char input;
    bool running = true;
    while (running) {
        // 绘制所管理的窗口
        drawWindows(this);
        // 读取输入
        read(STDIN_FILENO, &input, 1);
        if (input == 'q') { // press q to quit
            running = false;
        } else if (input == 'd') { // press d to activate the next window
            if (this->getActiveWinIndex(this) + 1 >= this->getWinCount(this)) {
                continue;
            }
            this->active(this, &this->windows[this->getActiveWinIndex(this) + 1]);

        } else if (input == 'u') { // press u to activate the previous window
            if (this->getActiveWinIndex(this) - 1 < 0) {
                continue;
            }
            this->active(this, &this->windows[this->getActiveWinIndex(this) - 1]);
        }
    }
    freeBismuth(this);
}

static int getActiveWinIndex(BWinManager* this) { return this->activeWinIndex; }

static int getWinCount(BWinManager* this) { return this->winCount; }

static void active(BWinManager* this, Window* win) {
    if (win == NULL) return;
    if (win->isActive(win)) return;

    Window* tmp = &this->windows[this->getActiveWinIndex(this)];
    tmp->setActive(tmp, false);
    this->_setActiveWinIndex(this, win->id);
    win->setActive(win, true);
}

static void setActiveWinIndex(BWinManager* this, int index) {
    this->activeWinIndex = index;
}



/* 构造函数 */
BWinManager* newBismuth() {
    BWinManager* this = malloc(sizeof(BWinManager));
    this->activeWinIndex = 0;
    this->winCount = 0;
    this->initTerminal = initTerminal;
    this->restoreTerminal = restoreTerminal;
    this->mainLoop = mainLoop;
    this->getActiveWinIndex = getActiveWinIndex;
    this->getWinCount = getWinCount;
    this->_setActiveWinIndex = setActiveWinIndex;
    this->active = active;
    return this;
}
/* 析构函数 */
void freeBismuth(BWinManager* this) {
    free(this);
}

