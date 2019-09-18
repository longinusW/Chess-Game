#ifndef _COMPL1_H_
#define _COMPL1_H_

#include "computer.h"
#include "player.h"
#include "coor.h"
#include "info.h"

class Game;

class CompL1: public Computer {
    public:
    CompL1(Colour co, Game* g):Computer(1, co, g) {}
    void goMove(Coor& src, Coor& dest) override;
};

#endif
