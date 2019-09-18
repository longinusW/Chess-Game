#ifndef _COMPL3_H_
#define _COMPL3_H_

#include "computer.h"
#include "player.h"
#include "coor.h"
#include "info.h"

class CompL3: public Computer {
    public:
    CompL3(Colour co, Game* g):Computer(3, co, g) {}
    void goMove(Coor& src, Coor& dest) override;
};

#endif
