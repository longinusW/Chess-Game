#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"
#include <vector>

class Bishop: public Piece {
	
	public:
    
    Bishop(Colour colour, Type t, int weight, Coor c, Board * b);
    
    bool canReach(Coor des) override;
    
	std::vector<Coor> nextMoveList() override;
	
};

#endif
