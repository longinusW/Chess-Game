#ifndef _KING_H_
#define _KING_H_

#include "piece.h"

class King: public Piece {
	public:
    King(Colour colour, Type t, int weight, Coor c, Board * b);
    bool canReach(Coor des) override;
    bool checkCastle(Coor des) override;
    std::vector<Coor> nextMoveList() override;
};


#endif
