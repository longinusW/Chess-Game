#ifndef _COOR_H_
#define _COOR_H_

#include <iostream>
struct Coor {
	int row; // keep int temporarily
	int col;
    bool operator<(const Coor& rhs)const {
        return row < rhs.row ? 1 : (col < rhs.col);
    }
    bool operator==(const Coor& rhs)const {
        return row == rhs.row && col == rhs.col;
    }
};


#endif
