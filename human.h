#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"
#include "info.h"

class Game;

class Human: public Player {
    
    public:
    Human(Colour colour, Game * game);
    void goMove(Coor & src, Coor & dest) override; // get hints
};

#endif
