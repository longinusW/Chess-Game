#ifndef _COMPL2_H_
#define _COMPL2_H_

#include "computer.h"
#include "player.h"
#include "coor.h"
#include "info.h"

class Game;

class CompL2: public Computer {
    public:
    CompL2 (Colour co, Game* g): Computer(2, co, g) {}
    void goMove(Coor& src, Coor& dest) override;
};

#endif
