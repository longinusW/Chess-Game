#include "coor.h"
#include "info.h"
#include "compl2.h"
#include "computer.h"
#include "game.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <memory>

void CompL2::goMove(Coor& retSrc, Coor& retDest) {
    std::vector<std::pair<Coor, Coor>> capture, check, others;// store moves that can capture or check or do nothing..
    auto& b = g->board->board;
    Colour opc = getOpc();//get opponent's color
    for (auto& row: b) {
        for (auto& piece : row) {
            auto src = piece->getInfo().c;//get source piece coordinate
            if (piece->getInfo().type == NonPiece || piece->getInfo().colour != side) continue;
            auto moveList = piece->nextMoveList();
            if (moveList.empty()) continue;
            for(auto& dest : moveList) {// for every possible move of this piece
                std::pair<Coor, Coor> im = std::pair<Coor, Coor>(src, dest);
                if (checkTest(im)) {// if this move can check the opponent's king
                    check.push_back(im);// add the move to the check list
                    //                    std::cerr << "check found\n";
                }
                else if (b[dest.row][dest.col]->getInfo().colour == opc) {// if there is a piece of your opponent in the destnation
                    capture.push_back(im);// add the move to the capture list
                    //                    std::cerr << "capture found\n";
                }
                else {// other moves
                    others.push_back(im);
                }
            }
        }
    }
    std::pair<Coor, Coor> intent;
    if (!check.empty()) {//select the check move if there is any
        intent = check[randInt(0, check.size())];
    }
    else if (!capture.empty()) {// select the capture move if there is no check move
        intent = capture[randInt(0, capture.size())];
    }
    else {// select other moves if there is no moves above
        intent = others[randInt(0, others.size())];
    }
    //return the infomation
    retSrc = intent.first;
    retDest = intent.second;
}
