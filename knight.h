#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"
#include <vector>

class Knight: public Piece {
    
    
    protected:
    
   // std::vector<Coor> MoveList() const override;
    
	public:
    
    Knight(Colour colour, Type t, int weight, Coor c, Board * b);

    bool canReach(Coor des) override;

    std::vector<Coor> nextMoveList() override;

};

#endif
