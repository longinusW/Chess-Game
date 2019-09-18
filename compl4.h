#ifndef _COMPL4_H_
#define _COMPL4_H_

#include "computer.h"
#include "player.h"
#include "coor.h"
#include "info.h"


class CompL4: public Computer {
    int calcValue(std::pair<Coor, Coor>);
    public:
    CompL4(Colour co, Game* g):Computer(4, co, g) {}
    void goMove(Coor& src, Coor& dest) override;
};

#endif
