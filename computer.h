#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"
#include "coor.h"
#include "info.h"
#include <utility>
#include <vector>

class Computer: public Player {
    
    protected:
    void oneCanReach(std::vector<Coor>&, Colour);
    bool safeTest(std::pair<Coor, Coor>);
    bool safeTest(Coor);
    int pieceValue(Type);
    int randInt(int l, int r);
    bool checkTest(std::pair<Coor, Coor> im); //check if the intent move can check the opponent's king
    public:
    Computer(int level, Colour colour, Game* g):Player(level, colour, g) {}
};

#endif

