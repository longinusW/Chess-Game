#include "knight.h"
#include "piece.h"
#include "board.h"
#include "info.h"
#include <vector>

Knight::Knight (Colour colour, Type t, int weight, Coor c, Board * b):
    Piece{colour, t, weight, c, b} {}

bool Knight::canReach(Coor des) {
    Coor curr = getInfo().c;
    Colour myColour = getInfo().colour;
    if ((des.row < 0) || (des.row > 7) || (des.col < 0) || (des.col > 7)) return false;
    if ((des.row == curr.row) && (des.col == curr.col)) return false;
    if ((b->getPiece(des)->getInfo().type != NonPiece) &&
        (b->getPiece(des)->getInfo().colour == myColour)) {
        return false;
    }
    if (((curr.row + 2 == des.row) && (curr.col + 1 == des.col)) ||
        ((curr.row + 2 == des.row) && (curr.col - 1 == des.col)) ||
        ((curr.row - 2 == des.row) && (curr.col + 1 == des.col)) ||
        ((curr.row - 2 == des.row) && (curr.col - 1 == des.col)) ||
        ((curr.row + 1 == des.row) && (curr.col + 2 == des.col)) ||
        ((curr.row + 1 == des.row) && (curr.col - 2 == des.col)) ||
        ((curr.row - 1 == des.row) && (curr.col + 2 == des.col)) ||
        ((curr.row - 1 == des.row) && (curr.col - 2 == des.col))) {
        return true;
    }
    return false;
}


std::vector<Coor> Knight::nextMoveList() {
    std::vector<Coor> list;
    Coor curr = getInfo().c;
    Coor pos1 = {curr.row + 2, curr.col + 1};
    Coor pos2 = {curr.row + 2, curr.col - 1};
    Coor pos3 = {curr.row - 2, curr.col + 1};
    Coor pos4 = {curr.row - 2, curr.col - 1};
    Coor pos5 = {curr.row + 1, curr.col + 2};
    Coor pos6 = {curr.row + 1, curr.col - 2};
    Coor pos7 = {curr.row - 1, curr.col + 2};
    Coor pos8 = {curr.row - 1, curr.col - 2};
    if (validMove(pos1)) list.emplace_back(pos1);
    if (validMove(pos2)) list.emplace_back(pos2);
    if (validMove(pos3)) list.emplace_back(pos3);
    if (validMove(pos4)) list.emplace_back(pos4);
    if (validMove(pos5)) list.emplace_back(pos5);
    if (validMove(pos6)) list.emplace_back(pos6);
    if (validMove(pos7)) list.emplace_back(pos7);
    if (validMove(pos8)) list.emplace_back(pos8);
    return list;
}
