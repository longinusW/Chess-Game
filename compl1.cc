#include "coor.h"
#include "info.h"
#include "compl1.h"
#include "computer.h"
#include "game.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <memory>


void CompL1::goMove(Coor& src, Coor& dest) {// AI for Computer[1]: random legal moves. The intent move is stored void CompL1::goMove(Coor& src, Coor& dest) {// AI for Computer[1]: random legal moves. The intent move is stored in variables src and dest
    //following code collects all coordinates of pieces that that computer get and that have valid moves
    auto& b = g->board->board;
    std::vector<Coor> pieceRec;
    for (auto& row: b) {
        for (auto& piece : row) {
            if (piece->getInfo().type == NonPiece || piece->getInfo().colour != side) continue;
            auto moveList = piece->nextMoveList();
            if (moveList.empty() == false) {// only consider the piece that has valid moves
                pieceRec.push_back(piece->getInfo().c);
            }
        }
    }
    src = pieceRec[randInt(0, pieceRec.size())];// and at random pick one piece and then store it so that the move information can be returned in this way
    auto& nowp = b[src.row][src.col];//find the piece that picked above
    auto moveList = nowp->nextMoveList();//get its move list
    dest = moveList[randInt(0, moveList.size())];//randomly pick a valid move of it and then store it so that the infomration can be returned in this way
}
