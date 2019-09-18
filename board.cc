#include "board.h"
#include "piece.h"
#include "info.h"
#include "textdisplay.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "graphicsdisplay.h"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;
const int wRook = 500;
const int wBishop = 330;
const int wKnight = 320;
const int wQueen = 900;
const int wPawn = 100;
const int wKing = 20000;
const int grid_size = 8;
Board::Board() {
    for (int i = 0; i < grid_size; ++i) {
        vector< shared_ptr <Piece> > lis;
        for (int j = 0; j < grid_size; ++j) {
            Coor pos = {i, j};
            auto p = std::make_shared<Piece>(Colour::NoneColour, NonPiece, 0, pos, this);
            lis.emplace_back(p);
        }
        board.emplace_back(lis);
    }
    td = make_unique<TextDisplay>();
    gd = make_unique<GraphicsDisplay>();
    gd->graphic_init();
}

void Board::notifyDisplays(Coor was, Coor des, Type t, Colour colour) {
    td->getNotify(was, des, t, colour);
    gd->getNotify(was, des, t, colour);
}

Coor Board::findKing(Colour colour) const {
    Coor loca;
    for (auto & r : board) {
        for (auto & co : r) {
            if ((co->getInfo().colour == colour) && (co->getInfo().type == tKing)) {
                loca = co->getInfo().c;
                break;
            }
        }
    }
    return loca;
}

bool Board::kingInCheck(Colour colour) const {
    Coor kingLoc = findKing(colour);
    for (auto r : board) {
        for (auto co : r) {
            if ((co->getInfo().type != NonPiece) && (co->getInfo().colour != Colour::NoneColour) && (co->getInfo().colour != colour)) {
                if(co->canReach(kingLoc)) return true; // some piece can capture king
            }
        }
    }
    return false;
}

bool Board::noValidMove(Colour colour) const {
    for (auto & r: board) {
        for (auto & co : r) {
            if (co->getInfo().type == NonPiece) continue;
            std::vector<Coor> moveLis = co->nextMoveList();
            if ((co->getInfo().colour == colour) && (!(moveLis.empty()))) return false;
        }
    }
    return true;
}

void Board::normInit() {
    std::vector<Coor> initlist;
    for (int i = 0; i < grid_size; ++i) {
        Coor pos = {0, i};
        initlist.emplace_back(pos);
    }
    board[0][0] = make_shared<Rook> (Colour::Black, tRook, wRook, initlist[0], this);
    board[0][1] = make_shared<Knight> (Colour::Black, tKnight, wKnight, initlist[1], this);
    board[0][2] = make_shared<Bishop> (Colour::Black, tBishop, wBishop, initlist[2], this);
    board[0][3] = make_shared<Queen> (Colour::Black, tQueen, wQueen, initlist[3], this);
    board[0][4] = make_shared<King> (Colour::Black, tKing, wKing, initlist[4], this);
    board[0][5] = make_shared<Bishop> (Colour::Black, tBishop, wBishop, initlist[5], this);
    board[0][6] = make_shared<Knight> (Colour::Black, tKnight, wKnight, initlist[6], this);
    board[0][7] = make_shared<Rook> (Colour::Black, tRook, wRook, initlist[7], this);
    initlist.clear();
    
    for (int i = 0; i < grid_size; ++i) {
        Coor pos = {7, i};
        initlist.emplace_back(pos);
    }
    board[7][0] = make_shared<Rook> (Colour::White, tRook, wRook, initlist[0], this);
    board[7][1] = make_shared<Knight> (Colour::White, tKnight, wKnight, initlist[1], this);
    board[7][2] = make_shared<Bishop> (Colour::White, tBishop, wBishop, initlist[2], this);
    board[7][3] = make_shared<Queen> (Colour::White, tQueen, wQueen, initlist[3], this);
    board[7][4] = make_shared<King> (Colour::White, tKing, wKing, initlist[4], this);
    board[7][5] = make_shared<Bishop> (Colour::White, tBishop, wBishop, initlist[5], this);
    board[7][6] = make_shared<Knight> (Colour::White, tKnight, wKnight, initlist[6], this);
    board[7][7] = make_shared<Rook> (Colour::White, tRook, wRook, initlist[7], this);
    initlist.clear();
    
    for (int j = 0; j < grid_size; ++j) {
        board[1][j] = make_shared<Pawn> (Colour::Black, tPawn, wPawn, Coor{1,j}, this);
    }
    for (int j = 0; j < grid_size; ++j) {
        board[6][j] = make_shared<Pawn> (Colour::White, tPawn, wPawn, Coor{6,j}, this);
    }
    td->normInit();
    gd->normInit();
}

bool Board::validSetup() {
    int numBlackKing = 0;
    int numWhiteKing = 0;
    for(auto r : board) {
        for (auto co : r) {
            if (co->getInfo().type != NonPiece) {
                Info info = co->getInfo();
                if ((info.colour == Colour::Black) && (info.type == tKing)) {
                    numBlackKing++;
                } else if ((info.colour == Colour::White) && (info.type == tKing)) {
                    numWhiteKing++;
                } else if (info.type == tPawn) {
                    if ((info.c.row == 0) || (info.c.row == 7)) {
                        return false;
                    }
                }
            }
        }
    }
    if ((numWhiteKing != 1) || (numBlackKing != 1)) return false;
    if (kingInCheck(Colour::White) || kingInCheck(Colour::Black)) return false;
    return true;
};


std::vector<Coor> Board::validDes(Coor c) {
    return getPiece(c)->nextMoveList();
}

bool Board::validMove(Coor was, Coor des) {
    return board[was.row][was.col]->validMove(des);
}

void Board::add(Coor c, Colour colour, Type t) {
    if (t == tKing) board[c.row][c.col] = make_shared<King> (colour, t, wKing, c, this);
    else if (t == tQueen) board[c.row][c.col] = make_shared<Queen> (colour, t, wQueen, c, this);
    else if (t == tKnight) board[c.row][c.col] = make_shared<Knight> (colour, t, wKnight, c, this);
    else if (t == tBishop) board[c.row][c.col] = make_shared<Bishop> (colour, t, wBishop, c, this);
    else if (t == tRook) board[c.row][c.col] = make_shared<Rook> (colour, t, wRook, c, this);
    else if (t == tPawn) board[c.row][c.col] = make_shared<Pawn> (colour, t, wPawn, c, this);
    Coor pos = {-1, -1};
    notifyDisplays(pos, c, t, colour);
}

void Board::move(Coor was, Coor des) {
    Colour my_colour = getPiece(was)->getInfo().colour;
    if  ((was.row > 7) || (was.row < 0) || (was.col > 7) || (was.col < 0) ||
         (des.row > 7) || (des.row < 0) || (des.col > 7) || (des.col < 0)) {
        cout << was.row << was.col << des.row << des.col << endl;
        string s;
        throw s;
    }
    if (validMove(was, des)) {
        auto p = make_pair(was, des);
        auto movep = make_pair(getPiece(des), p);
        undolist.emplace_back(movep);
        if (board[was.row][was.col]->getInfo().type == tPawn) { // check enpassant
            if (board[was.row][was.col]->checkPassant(des)) {
                if (board[was.row][was.col]->getInfo().colour == Colour::White) {
                    Coor pos = {des.row + 1, des.col};
                    remove(pos);
                }
                
                 else if (board[was.row][was.col]->getInfo().colour == Colour::Black) {
                    Coor pos = {des.row - 1, des.col};
                    remove(pos);
                 }
            }
        }
        
        else if (board[was.row][was.col]->getInfo().type == tKing) { // check castling
            if (board[was.row][was.col]->checkCastle(des)) {
                if (des.col >  was.col) {
                    Coor movedRook = {des.row, 7};
                    Coor rookNew = {des.row, des.col - 1};
                    move(movedRook, rookNew);
                } else if (des.col < was.col) {
                    Coor movedRook = {des.row, 0};
                    Coor rookNew = {des.row, des.col + 1};
                    move(movedRook, rookNew);
                }
            }
        }
        Type tpiece = getPiece(was)->getInfo().type;
        board[was.row][was.col]->setPosn(des);
        getPiece(was)->incMove();

        if ((tpiece == tPawn) && ((des.row + 2 == was.row) || (des.row - 2 == was.row))) {
                dynamic_pointer_cast<Pawn>(getPiece(was))->changeMoveTwo(true);
            }
        
        board[des.row][des.col] = board[was.row][was.col];
        board[was.row][was.col] = make_shared<Piece> (Colour::NoneColour, NonPiece, 0, was, this);
        for (auto & r : board) {
            for (auto & c : r) {
                if ((c->getInfo().type == tPawn) && (c->getInfo().colour != my_colour)) {
                    dynamic_pointer_cast<Pawn>(c)->changeMoveTwo(false); // waited a round, cannot en passent
                }
            }
        }
        notifyDisplays(was, des, board[des.row][des.col]->getInfo().type, board[des.row][des.col]->getInfo().colour);
        if (getPiece(des)->getInfo().type == tPawn) {
            if ((getPiece(des)->getInfo().colour == Colour::White) && (getPiece(des)->getInfo().c.row == 0)) {
                Type t = tPawn;
                throw t; // tell main there is another input to promote
            }
            if ((getPiece(des)->getInfo().colour == Colour::Black) && (getPiece(des)->getInfo().c.row == 7)) {
                Type t = tPawn;
                throw t; // tell main there is another input to promote
            }
        }
    } else {
        cout << was.row << was.col << des.row << des.col << endl;
        string s;
        throw s;
    }
}


void Board::remove(Coor c) {
    Coor pos = {-1, -1};
    auto p = make_pair(c, pos);
    auto movep = make_pair(getPiece(c), p);
    undolist.emplace_back(movep);
    board[c.row][c.col] = make_shared<Piece> (Colour::NoneColour, NonPiece, 0, c, this);
    notifyDisplays(c, pos, NonPiece, Colour::NoneColour);
}


int Board::totalWeight(Colour colour) {
    int total = 0;
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            if (board[i][j]->getInfo().type != NonPiece) {
                if (board[i][j]->getInfo().colour == colour) total += board[i][j]->getInfo().weight;
                else if (board[i][j]->getInfo().colour != colour) total -= board[i][j]->getInfo().weight;
            }
        }
    }
    return total;
}

std::shared_ptr<Piece> Board::getPiece(Coor c) {
    return board[c.row][c.col];
}

std::vector<std::pair<Coor, std::vector<Coor> > > Board::validMoveList(Colour colour) const {
    std::vector< std::pair <Coor, std::vector <Coor> > > list;
    for (auto r : board) {
        for (auto c : r) {
            if (c->getInfo().colour == colour) {
                auto p = std::make_pair(c->getInfo().c, c->nextMoveList());
                list.emplace_back(p);
            }
        }
    }
    return list;
}

void Board::promote(Coor des, Type t) {
    Coor pos = {-1, -1};
    auto p = make_pair(pos, des);
    auto movep = make_pair(getPiece(des), p);
    undolist.emplace_back(movep);
    if (getPiece(des)->getInfo().type == tPawn) { // double check
        switch (t) {
            case tQueen: board[des.row][des.col] = std::make_shared<Queen> (getPiece(des)->getInfo().colour, t, wQueen, des, this);
                break;
            case tRook: board[des.row][des.col] = std::make_shared<Rook> (getPiece(des)->getInfo().colour, t, wRook, des, this);
                break;
            case tBishop: board[des.row][des.col] = std::make_shared<Bishop> (getPiece(des)->getInfo().colour, t, wBishop, des, this);
                break;
            case tKnight: board[des.row][des.col] = std::make_shared<Knight> (getPiece(des)->getInfo().colour, t, wKnight, des, this);
                break;
            default: return; // should never call this
        }
    }
    notifyDisplays(pos, des, t, getPiece(des)->getInfo().colour);
}




bool Board::checkMyKing(Coor was, Coor des) {
    Colour my_colour = getPiece(was)->getInfo().colour;
    std::shared_ptr<Piece> p = getPiece(des);
    board[was.row][was.col]->setPosn(des);
    board[des.row][des.col] = board[was.row][was.col];
    board[was.row][was.col] = make_shared<Piece> (Colour::NoneColour, NonPiece, 0, was, this);
    bool inCheck = kingInCheck(my_colour);
    board[des.row][des.col]->setPosn(was); // undo
    board[was.row][was.col] = board[des.row][des.col];
    board[des.row][des.col] = p;
    return inCheck;
}

void Board::undo() {
    if (undolist.empty()) throw 'e';
    auto movep = undolist.back();
    Coor oldp = movep.second.second; // now the piece is here
    Coor newp = movep.second.first; // it should go here
    if ((oldp.row == -1) && (oldp.col == -1)) { // removed only option is en passant
        board[newp.row][newp.col] = movep.first;
        notifyDisplays(oldp, newp, getPiece(newp)->getInfo().type, getPiece(newp)->getInfo().colour);
        undolist.pop_back();
        undo();
        return;
    } else if ((newp.row == -1) && (newp.col == -1)) { // promoted (only option)
        board[oldp.row][oldp.row] = movep.first;
        notifyDisplays(newp, oldp, (movep.first)->getInfo().type, (movep.first)->getInfo().colour);
        undolist.pop_back();
        undo();
        return;
    }
    board[newp.row][newp.col] = getPiece(oldp);
    getPiece(newp)->decMove();
    getPiece(newp)->setPosn(newp);
    if ((getPiece(newp)->getInfo().type == tPawn) &&
        (dynamic_pointer_cast<Pawn>(getPiece(newp))->checkMoveTwo())) {
        dynamic_pointer_cast<Pawn>(getPiece(newp))->changeMoveTwo(false);
    }
    board[oldp.row][oldp.col] = movep.first;
    Coor addp = {-1, -1};
    undolist.pop_back();
    notifyDisplays(oldp, newp, getPiece(newp)->getInfo().type, getPiece(newp)->getInfo().colour);
    notifyDisplays(addp, oldp, getPiece(oldp)->getInfo().type, getPiece(oldp)->getInfo().colour);
    if ((oldp.row == newp.row) && (getPiece(newp)->getInfo().type == tRook)) { // check castling
        auto backp = undolist.back();
        if ((backp.second.second.row == backp.second.first.row) &&
            ((backp.second.second.col - backp.second.first.col == 2) ||
             (backp.second.second.col - backp.second.first.col == -2))) {
                undo(); // undo another move since it is castling
            }
    }
}


std::pair<Coor, Coor> Board::getHint(Colour colour) const {
    std::vector<std::pair<Coor, std::vector<Coor> > > list1 = validMoveList(colour);
    int v1 = rand() % list1.size();
    while (list1[v1].second.size() == 0) {
        v1 = rand() % list1.size();
    }
    int v2 = rand () % list1[v1].second.size();
    std::pair<Coor, Coor> foo;
    foo = std::make_pair(list1[v1].first, (list1[v1].second)[v2]);
    return foo;
}

std::ostream & operator<< (std::ostream & out, const Board & b) {
    out << *(b.td);
    return out;
}
