#ifndef BISMUTH_MODULE_H
#define BISMUTH_MODULE_H

typedef struct Module Module;
struct Module {
    int width, height;
    int x, y;
    int id;
    char* shape;
    Module* up;
    Module* down;
};

void modSetSize(Module* this, int newWidth, int newHeight);
int modGetWidth(Module* this);
int modGetHeight(Module* this);

void modSetPos(Module* this, int newX, int newY);
int modGetX(Module* this);
int modGetY(Module* this);

int modGetID(Module* this);

char* modGetShape(Module* this);
void modSetShape(Module* this, char* newShape);

Module* newModule(int newWidth, int newHeight, int newX, int newY, int id, char* shape, Module* up, Module* down);

#endif //BISMUTH_MODULE_H
