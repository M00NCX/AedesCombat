#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Texture.h"

class GameScreen {
public:
    GameScreen();
    void render();
private:
    Texture background;
};

#endif