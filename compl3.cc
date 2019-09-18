#include "compl3.h"
#include "coor.h"
#include "info.h"
#include "computer.h"
#include "game.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <memory>

void CompL3::goMove(Coor& retSrc, Coor& retDest) {
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
    bool foundSafe = 0, foundButNotSafe = 0;
    /* If we can find any moves(in a order as check, capture, others moves) that can avoid capturing, then foundSafe = 1
     * Otherwise, we will be captured anyway. So we select a move as CompL2 do
     */
    if (!check.empty()) {
        bool flag = 0;
        for (auto& im:check) {
            if (safeTest(im)) {// if dest will not be captured
                if (!flag) {
                    flag = 1;
                    intent = im;// set the intent move to this one
                }
                else if (randInt(0, 3) < 1) {
                    intent = im;
                }
            }
        }
        if (flag) foundSafe = 1;
        else intent = check[randInt(0, check.size())], foundButNotSafe = 1;//randomly pick a move that is not safe though
    }
    if (!foundSafe && !capture.empty()) {//same as previous code
        bool flag = 0;
        for (auto& im:capture) {
                if (safeTest(im)) {
                if (!flag) {
                    flag = 1;
                    intent = im;
                }
                else if (randInt(0, 3) < 1) {
                    intent = im;
                }
            }
        }
        if (flag) foundSafe = 1;
        else if (!foundButNotSafe) intent = capture[randInt(0, capture.size())], foundButNotSafe=1;
    }
    if (!foundSafe && !others.empty()) {//same as previous code
        bool flag = 0;
        for (auto& im:others) {
            if (safeTest(im)) {
                if (!flag) {
                    flag = 1;
                    intent = im;
                }
                else if (randInt(0, 3) < 1) {
                    intent = im;
                }
            }
        }
        if (flag) foundSafe = 1;
        else if (!foundButNotSafe) {
            intent = others[randInt(0, others.size())];
            foundButNotSafe = 1;
            
        }
        
    }
    //return the infomation
    retSrc = intent.first;
    retDest = intent.second;
}
