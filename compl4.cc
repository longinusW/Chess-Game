#include "compl4.h"
#include "coor.h"
#include "info.h"
#include "computer.h"
#include "game.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <memory>


int CompL4::calcValue(std::pair<Coor, Coor> im) {
    int value = 0;
    Coor src = im.first, dest = im.second;
    value = pieceValue(g->board->getPiece(dest)->getInfo().type);// add the value of opponent's piece that we can capture by this move
    if (!safeTest(src)) value += pieceValue(g->board->getPiece(src)->getInfo().type);// add the value of this piece if it will be captured by our opponent in the next move because by this move we can escape
    if (!safeTest(im)) value -= pieceValue(g->board->getPiece(src)->getInfo().type); // susbtract the value of this piece if it will be captured in the new possition
    return value;
}
void CompL4::goMove(Coor& retSrc, Coor& retDest) {// mostly same with CompL1 but it will pick the move with the highest value(considering capture and being capture)
    auto& b = g->board->board;
    bool moveSet=0;
    std::pair<Coor, Coor> nowMove;//the move with highest value
    int nowValue=0;//the highest value that  nowMove holds
    for (auto& row: b) {
        for (auto& piece : row) {
            if (piece->getInfo().type == NonPiece || piece->getInfo().colour != side) continue;//only consider our pieces
            auto src = piece->getInfo().c;//get source piece coordinate
            auto moveList = piece->nextMoveList();
            if (moveList.empty()) continue;
            for (auto& dest: moveList) {
                if (!moveSet) {// the first move we found
                    moveSet = 1;
                    nowMove = std::pair<Coor, Coor>(src, dest);
                    nowValue = calcValue(nowMove);
                }
                else {
                    auto thisMove = std::pair<Coor, Coor>(src, dest);
                    int thisValue = calcValue(thisMove);
                    if (thisValue > nowValue || (thisValue == nowValue && randInt(0, 3) > 1)) {// add some random if we have mutiple choices
                        nowMove = thisMove;
                        nowValue = thisValue;
                    }
                }
            }
        }
    }
    //returne the information
    retSrc = nowMove.first;
    retDest = nowMove.second;
}
