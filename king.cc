#include "king.h"
#include "piece.h"
#include "board.h"
#include "info.h"
#include <vector>

King::King (Colour colour, Type t, int weight, Coor c, Board * b):
    Piece{colour, t, weight, c, b} {}

bool King::checkCastle(Coor des) {
    Coor curr = getInfo().c;
    if (move) return false;
    if ((des.row == curr.row) && ((des.col == curr.col - 2) || (des.col == curr.col + 2))) {
        if (des.col == curr.col - 2) {
            Coor pos = {curr.row, 0};
            for (int i = 1; i < curr.col; ++i) {
                Coor cpos = {curr.row, i};
                if (b->getPiece(cpos)->getInfo().type != NonPiece) return false;
            }
            Coor trypos = {curr.row, curr.col - 1};
            if (b->checkMyKing(curr, trypos)) return false;
            if ((b->getPiece(pos)->getInfo().type == tRook) &&
                (b->getPiece(pos)->checkMoved() == false)) {
                return true;
            }
        } else if (des.col == curr.col + 2) {
            Coor pos = {curr.row, 7};
            for (int i = curr.col + 1; i < 7; ++i) {
                Coor cpos = {curr.row, i};
                if (b->getPiece(cpos)->getInfo().type != NonPiece) return false;
            }
            Coor trypos = {curr.row, curr.col + 1};
            if (b->checkMyKing(curr, trypos)) return false;
            if ((b->getPiece(pos)->getInfo().type == tRook) &&
                (b->getPiece(pos)->checkMoved() == false)) {
                return true;
            }
        }
    }
    return false;
}

bool King::canReach(Coor des) {
    if ((des.row < 0) || (des.row > 7) || (des.col < 0) || (des.col > 7)) return false;
    Coor curr = getInfo().c;
    Colour myColour = getInfo().colour;
    if (checkCastle(des) == true) return true; // check is des is a castling
    if ((des.row == curr.row) && (des.col == curr.col)) return false;
    if ((b->getPiece(des)->getInfo().type != NonPiece) && (b->getPiece(des)->getInfo().colour == myColour)) {
        return false; 
    }
    if (((des.row == curr.row) && (des.col == curr.col + 1)) ||
        ((des.row == curr.row) && (des.col == curr.col - 1)) ||
        ((des.row == curr.row + 1) && (des.col == curr.col)) ||
        ((des.row == curr.row - 1) && (des.col == curr.col)) ||
        ((des.row == curr.row + 1) && (des.col == curr.col + 1)) ||
        ((des.row == curr.row + 1) && (des.col == curr.col - 1)) ||
        ((des.row == curr.row - 1) && (des.col == curr.col + 1)) ||
        ((des.row == curr.row - 1) && (des.col == curr.col - 1))) {
        return true;
    }
    return false;
}

std::vector<Coor> King::nextMoveList() {
    std::vector<Coor> list;
    Coor curr = getInfo().c;
    Coor pos1 = {curr.row, curr.col + 1};
    Coor pos2 = {curr.row, curr.col - 1};
    Coor pos3 = {curr.row + 1, curr.col};
    Coor pos4 = {curr.row - 1, curr.col};
    Coor pos5 = {curr.row + 1, curr.col + 1};
    Coor pos6 = {curr.row + 1, curr.col - 1};
    Coor pos7 = {curr.row - 1, curr.col + 1};
    Coor pos8 = {curr.row - 1, curr.col - 1};
    Coor pos9 = {curr.row, curr.col - 2};
    Coor pos10 = {curr.row, curr.col + 2};
    if (validMove(pos1)) list.emplace_back(pos1);
    if (validMove(pos2)) list.emplace_back(pos2);
    if (validMove(pos3)) list.emplace_back(pos3);
    if (validMove(pos4)) list.emplace_back(pos4);
    if (validMove(pos5)) list.emplace_back(pos5);
    if (validMove(pos6)) list.emplace_back(pos6);
    if (validMove(pos7)) list.emplace_back(pos7);
    if (validMove(pos8)) list.emplace_back(pos8);
    if (validMove(pos9)) list.emplace_back(pos9);
    if (validMove(pos10)) list.emplace_back(pos10);
    return list;
}
