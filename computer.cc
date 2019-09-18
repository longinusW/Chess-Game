#include "computer.h"
#include "board.h"
#include "game.h"
#include "piece.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <utility>


int Computer::randInt(int l, int r) {
    return int(rand())%(r-l) + l;
}

bool Computer::checkTest(std::pair<Coor, Coor> im) {//check if the intent move can check the opponent's king
    auto& b = g->board->board;
    auto src = im.first, dest = im.second;
    auto moveList = b[src.col][src.row]->assumeMoveList(dest);//get move list if we put the piece at dest
    Colour opc = getOpc();//get opponent's color
    for (auto newDest:moveList){//scan the move list and search for the king
        auto& piece = b[newDest.col][newDest.row];
        if (piece->getInfo().colour == opc && piece->getInfo().type == Type::tKing) {
            return true;//king found. We can check the enemy with this move
        }
    }
    return false;// did not find any move useful
}

void Computer::oneCanReach(std::vector<Coor>& ret, Colour c) {//get all positions one with colour c can reach
    ret.clear();
    auto& b = g->board->board;
    for (auto& row: b) {
        for (auto& piece : row) {
            if (piece->getInfo().type == NonPiece || piece->getInfo().colour != c) continue;
            auto moveList = piece->nextMoveList();
            for (auto x:moveList) {
                ret.push_back(x);
            }
        }
    }
    //Note that we have vector ret sorted so we can use lower_bound and unique later
    std::stable_sort(ret.begin(), ret.end());
    ret.resize(std::unique(ret.begin(), ret.end()) - ret.begin());
}
bool Computer::safeTest(std::pair<Coor, Coor> im) {// test if the piece will be captured after we take the move
    
    auto src = im.first, dest = im.second;
    
    auto p = g->board->getPiece(dest);
    
    g->board->getPiece(src)->setPosn(dest);
    
    g->board->board[dest.row][dest.col] = g->board->board[src.row][src.col];
    
    g->board->board[src.row][src.col] = std::make_shared<Piece> (Colour::NoneColour, NonPiece, 0, src, g->board.get());
    
    //g->board->move(src, dest);
    
    std::vector<Coor> danger;
    
    oneCanReach(danger, getOpc());
    
    auto it = std::lower_bound(danger.begin(), danger.end(), dest);
    
    bool unsafe = it != danger.end() && *it == dest;// if we find the position existing in the danger vector, which means that it maybe captured
    
    
    g->board->getPiece(dest)->setPosn(src);
    
    g->board->board[src.row][src.col] = g->board->board[dest.row][dest.col];
    
    g->board->board[dest.row][dest.col] = p;
    
    //g->board->undo();
    return !unsafe;
}
bool Computer::safeTest(Coor src) {// return if src will be captured if your opponent take the next move
    std::vector<Coor> danger;
    oneCanReach(danger, getOpc());
    auto it = std::lower_bound(danger.begin(), danger.end(), src);
    bool unsafe = it != danger.end() && *it == src;
    return !unsafe;
}

int Computer::pieceValue(Type t) {// some magic numbers. You can modify it as you want, which will have an influence on how AI consider its pieces
    const int w_Rook = 500;
    const int w_Bishop = 330;
    const int w_Knight = 320;
    const int w_Queen = 900;
    const int w_Pawn = 100;
    const int w_King = 20000;
    const int w_Non = 0;
    if (t == Type::NonPiece) return w_Non;
    else if (t==Type::tBishop) return w_Bishop;
    else if (t==Type::tKing) return w_King;
    else if (t==Type::tKnight) return w_Knight;
    else if (t==Type::tPawn) return w_Pawn;
    else if (t==Type::tQueen) return w_Queen;
    else if (t==Type::tRook) return w_Rook;
    return 0;
}


