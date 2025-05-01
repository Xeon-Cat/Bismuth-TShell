/* termwin.c - 终端窗口实现 */
#include "TermWin.h"
#include "Bismuth.h"

#include <stdio.h>
#include <string.h>

static void drawWindow(Window *this);
static int getX(const Window* this);
static int getY(const Window* this);
static void setPos(Window* this, int x, int y);
static int getWidth(const Window* this);
static int getHeight(const Window* this);
static void setSize(Window* this, int width, int height);
static int getID(const Window* this);
static char* getTitle(const Window* this);
static void setTitle(Window* this, const char* title);
static bool isActive(const Window* this);
static void setActive(Window* this, bool operation);


Window* newWindow(int x, int y,
                  int w, int h,
                  const char* title,
                  Bismuth* master) {
    if (master->winCount >= MAX_WINDOWS) return NULL;

    Window *win = &master->windows[master->winCount];
    win->id = master->winCount;
    master->winCount++;

    win->drawWindow = drawWindow;
    win->getX = getX; win->getY = getY;
    win->setPos = setPos;
    win->getWidth = getWidth;
    win->getHeight = getHeight;
    win->setSize = setSize;
    win->getID = getID;
    win->getTitle = getTitle;
    win->setTitle = setTitle;
    win->isActive = isActive;
    win->drawWindow = drawWindow;
    win->setActive = setActive;

    win->x = x;
    win->y = y;
    win->width = w;
    win->height = h;
    strncpy(win->title, title, TITLE_MAX);
    win->title[TITLE_MAX - 1] = '\0';
    win->active = false;
    return win;
}

/* 绘制单个窗口 */
static void drawWindow(Window *this) {
    // 设置颜色：活动窗口用蓝底白字，非活动灰底黑字
    printf("\033[%d;%dH", this->getY(this), this->getX(this)); // 定位到窗口左上角

    if (this->isActive(this)) {
        printf("\033[44;37m"); // 蓝底白字
    } else {
        printf("\033[47;30m"); // 灰底黑字
    }

    // 绘制顶边框
    printf("╔═%s", this->getTitle(this));
    for (int i = (int)strlen(this->getTitle(this)) + 3; i < this->getWidth(this); i++)
        printf("═");
    printf("╗\033[0m\n");

    // 绘制中间区域
    for (int y = 1; y < this->getHeight(this) - 1; y++) {
        printf("\033[%d;%dH║", this->getY(this) + y, this->getX(this));
        printf("\033[%d;%dH║\n", this->getY(this) + y, this->getX(this) + this->getWidth(this) - 1);
    }

    // 绘制底边框
    printf("\033[%d;%dH╚", this->getY(this) + this->getHeight(this) - 1, this->getX(this));
    for (int i = 1; i < this->getWidth(this) - 1; i++) printf("═");
    printf("╝\033[0m");
}

static int getX(const Window* this) { return this->x; }
static int getY(const Window* this) { return this->y; }
static void setPos(Window* this, int x, int y) {
    this->x = x;
    this->y = y;
}

static int getWidth(const Window* this) { return this->width; }
static int getHeight(const Window* this) { return this->height; }
static void setSize(Window* this, int width, int height) {
    this->width = width;
    this->height = height;
}

static int getID(const Window* this) { return this->id; }

static char* getTitle(const Window* this) {
    return (char*) this->title; // 返回标题的指针
}

static void setTitle(Window* this, const char* title) {
    strncpy(this->title, title, TITLE_MAX);
    this->title[TITLE_MAX - 1] = '\0'; // 确保截断后仍有终止符
}

static bool isActive(const Window* this) {
    return this->active;
}

static void setActive(Window* this, bool operation) {
    this->active = operation;
}