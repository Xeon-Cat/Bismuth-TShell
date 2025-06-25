#ifndef BISMUTH_TERMWIN_H
#define BISMUTH_TERMWIN_H

#include <stdbool.h>
#include "Module.h"


#define MAX_WINDOWS 128
#define TITLE_MAX 32


/* 窗口结构体 */
typedef struct BWinManager BWinManager;
typedef struct Window Window;
struct Window {
    int x, y;           // 窗口位置
    int (*getX)(const Window* this); int (*getY)(const Window* this);
    void (*setPos)(Window* this, int x, int y);

    int width, height;  // 尺寸
    int (*getWidth)(const Window* this); int (*getHeight)(const Window* this);
    void (*setSize)(Window* this, int width, int height);

    int id;
    int (*getID)(const Window* this);

    char title[TITLE_MAX];
    char* (*getTitle)(const Window* this);
    void (*setTitle)(Window* this, const char* title);

    bool active;
    bool (*isActive)(const Window* this); // 是否活动窗口
    void (*setActive)(Window* this, bool operation);


    void (*drawWindow)(Window *this);
    Module* mods;
};
Window* newWindow(int x, int y, int w, int h, const char* title, BWinManager* master);



#endif //BISMUTH_TERMWIN_H
