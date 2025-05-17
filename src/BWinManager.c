/* BWinManager.c - 窗口管理器实现 */
#include "BWinManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>


static struct termios orig_termios;
static void initTerminal(BWinManager* this);
static void restoreTerminal();
static void mainLoop(BWinManager* this);
static int getActiveWinIndex(BWinManager* this);
static void setActiveWinIndex(BWinManager* this, int index);
static int getWinCount(BWinManager* this);
static void active(BWinManager* this, Window* win);

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
void delBismuth(BWinManager* this) {
    free(this);
}

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

/* 主事件循环 */
static void mainLoop(BWinManager* this) {
    char input;
    while (1) {
        // 清屏并绘制所有窗口
        printf("\033[2J");
        for (int i = 0; i < this->winCount; i++) {
            this->windows[i].drawWindow(&this->windows[i]);
        }
        fflush(stdout);

        // 读取输入
        read(STDIN_FILENO, &input, 1);

        if (input == '\n') { // 回车激活窗口
            for (int i = 0; i < this->winCount; i++) {
                this->windows[i].active = (i == this->activeWinIndex);
            }
        } else if (input == '\t') { // Tab退出
            break;
        }
    }
    delBismuth(this);
}

static int getActiveWinIndex(BWinManager* this) { return this->activeWinIndex; }

static int getWinCount(BWinManager* this) { return this->winCount; }

static void active(BWinManager* this, Window* win) {
    if (win->isActive(win)) return;
    Window* tmp = &this->windows[this->getActiveWinIndex(this)];
    tmp->setActive(tmp, false);
    this->_setActiveWinIndex(this, win->id);
    win->setActive(win, true);
}

static void setActiveWinIndex(BWinManager* this, int index) {
    this->activeWinIndex = index;
}