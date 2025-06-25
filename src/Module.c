#include "Module.h"
#include <stdlib.h>
#include <string.h>

void modSetSize(Module* this, int newWidth, int newHeight) {
    if (this != NULL) {
        this->width = newWidth;
        this->height = newHeight;
    }
}

int modGetWidth(Module* this) {
    return (this != NULL) ? this->width : 0;
}

int modGetHeight(Module* this) {
    return (this != NULL) ? this->height : 0;
}

void modSetPos(Module* this, int newX, int newY) {
    if (this != NULL) {
        this->x = newX;
        this->y = newY;
    }
}

int modGetX(Module* this) {
    return (this != NULL) ? this->x : 0;
}

int modGetY(Module* this) {
    return (this != NULL) ? this->y : 0;
}

int modGetID(Module* this) {
    return (this != NULL) ? this->id : -1;
}

char* modGetShape(Module* this) {
    return (this != NULL) ? this->shape : NULL;
}

void modSetShape(Module* this, char* newShape) {
    if (newShape != NULL) {
        this->shape = newShape;
    }
}

Module* newModule(int newWidth, int newHeight, int newX, int newY, int newID, char* newShape, Module* up, Module* down) {
    Module* newMod = (Module*)malloc(sizeof(Module));
    if (newMod == NULL) return NULL;
    newMod->width = newWidth;
    newMod->height = newHeight;
    newMod->x = newX;
    newMod->y = newY;
    newMod->id = newID;
    char* shape = newShape;
    newMod->up = up;
    newMod->down = down;
    return newMod;
}
