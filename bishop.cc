#include "piece.h"
#include "board.h"
#include "info.h"
#include "bishop.h"
#include <vector>

Bishop::Bishop (Colour colour, Type t, int weight, Coor c, Board * b):
    Piece{colour, t, weight, c, b} {}

std::vector<Coor> Bishop::nextMoveList() {
    std::vector<Coor> list;
    Coor curr = getInfo().c;
    Colour myColour = getInfo().colour;
    
    for (int r = curr.row, co = curr.col; ((r >= 0) && (co >= 0)); --r, --co) {
        Coor pos{r,co};
        if (b->getPiece(pos)->getInfo().type == NonPiece) {
            if (!checkMyKing(pos)) list.emplace_back(pos);
        } else if (b->getPiece(pos)->getInfo().colour != myColour) { // can capture
            if (!checkMyKing(pos)) list.emplace_back(pos);
            break;
        } else break; // been blocked
    }
    
    for (int r = curr.row, co = curr.col; ((r <= 7) && (co >= 0)); ++r, --co) {
        Coor pos{r,co};
        if (b->getPiece(pos)->getInfo().type == NonPiece) {
            if (!checkMyKing(pos)) list.emplace_back(pos);
        } else if (b->getPiece(pos)->getInfo().colour != myColour) { // can capture
            if (!checkMyKing(pos)) list.emplace_back(pos);
            break;
        } else break; // been blocked
    }
    
    for (int r = curr.row, co = curr.col; ((r <= 7) && (co <= 7)); ++r, ++co) {
        Coor pos{r,co};
        if (b->getPiece(pos)->getInfo().type == NonPiece) {
            if (!checkMyKing(pos)) list.emplace_back(pos);
        } else if (b->getPiece(pos)->getInfo().colour != myColour) { // can capture
            if (!checkMyKing(pos)) list.emplace_back(pos);
            break;
        } else break; // been blocked
    }
    
    for (int r = curr.row, co = curr.col; ((r >= 0) && (co <= 7)); --r, ++co) {
        Coor pos{r,co};
        if (b->getPiece(pos)->getInfo().type == NonPiece) {
            if (!checkMyKing(pos)) list.emplace_back(pos);
        } else if (b->getPiece(pos)->getInfo().colour != myColour) { // can capture
            if (!checkMyKing(pos)) list.emplace_back(pos);
            break;
        } else break; // been blocked
    }
    return list;
}

bool Bishop::canReach(Coor des) {
	Coor curr = getInfo().c;
    Colour myColour = getInfo().colour;
    if ((des.row < 0) || (des.row > 7) || (des.col < 0) || (des.col > 7)) return false;
    if ((des.row == curr.row) && (des.col == curr.col)) {
        return false;
    }
    if ((b->getPiece(des)->getInfo().type != NonPiece) && (b->getPiece(des)->getInfo().colour == myColour)) return false;
    
    if ((curr.row > des.row) && (curr.col > des.col)) {
        for (int r = curr.row - 1, co = curr.col - 1; ((r >= des.row) && (co >= des.col)); --r, --co) {
            Coor pos = {r, co};
            if ((b->getPiece(pos)->getInfo().type != NonPiece) && (r > des.row) && (co > des.col)) { // pieces on the path
                return false;
            } else if (((b->getPiece(pos)->getInfo().type == NonPiece) ||
                        (b->getPiece(pos)->getInfo().colour != myColour)) &&
                        ((r == des.row) && (co == des.col))) {
                return true; // the destination has no piece or different colour piece
            } else if ((b->getPiece(pos)->getInfo().type == NonPiece) && ((r > des.row) && (co > des.col))) {
                continue; // on the path, no piece
            }
        }
        return false;
        
    } else if ((curr.row > des.row) && (curr.col < des.col)) {
        for (int r = curr.row - 1, co = curr.col + 1; ((r >= des.row) && (co <= des.col)); --r, ++co) {
            Coor pos = {r, co};
            if ((b->getPiece(pos)->getInfo().type != NonPiece) && ((r > des.row) && (co < des.col))) { // pieces on the path
                return false;
            } else if (((b->getPiece(pos)->getInfo().type == NonPiece) ||
                        (b->getPiece(pos)->getInfo().colour != myColour)) &&
                       ((r == des.row) && (co == des.col))) {
                return true; // the destination has no piece or different colour piece
            } else if ((b->getPiece(pos)->getInfo().type == NonPiece) && ((r > des.row) && (co < des.col))) {
                continue; // on the path, no piece
            }
        }
        return false;
    } else if ((curr.row < des.row) && (curr.col > des.col)) {
        for (int r = curr.row + 1, co = curr.col - 1; ((r <= des.row) && (co >= des.col)); ++r, --co) {
            Coor pos = {r, co};
            if ((b->getPiece(pos)->getInfo().type != NonPiece) && ((r < des.row) && (co > des.col))) { // pieces on the path
                return false;
            } else if (((b->getPiece(pos)->getInfo().type == NonPiece) ||
                        (b->getPiece(pos)->getInfo().colour != myColour)) &&
                       ((r == des.row) && (co == des.col))) {
                return true; // the destination has no piece or different colour piece
            } else if ((b->getPiece(pos)->getInfo().type == NonPiece) && ((r < des.row) && (co > des.col))) {
                continue; // on the path, no piece
            }
        }
        return false;
    } else if ((curr.row < des.row) && (curr.col < des.col)) {
        for (int r = curr.row + 1, co = curr.col + 1; ((r <= des.row) && (co <= des.col)); ++r, ++co) {
            Coor pos = {r, co};
            if ((b->getPiece(pos)->getInfo().type != NonPiece) && ((r < des.row) && (co < des.col))) { // pieces on the path
                return false;
            } else if (((b->getPiece(pos)->getInfo().type == NonPiece) ||
                        (b->getPiece(pos)->getInfo().colour != myColour)) &&
                       ((r == des.row) && (co == des.col))) {
                return true; // the destination has no piece or different colour piece
            } else if ((b->getPiece(pos)->getInfo().type == NonPiece) && ((r < des.row) && (co < des.col))) {
                continue; // on the path, no piece
            }
        }
        return false;
    } else { // curr.row == des.row or curr.col == des.col
        return false;
    }
}



                
    
