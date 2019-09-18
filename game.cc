#include "game.h"
#include "player.h"
#include "board.h"
#include "human.h"
#include "piece.h"
#include "computer.h"
#include "compl1.h"
#include "compl2.h"
#include "compl3.h"
#include "compl4.h"
#include <memory>
#include <string>
using namespace std;

// see details in game.h
void Game::setUp() {
    board = make_unique<Board>();
}

void Game::addPiece(Coor des, Colour colour, Type type) {
    board->add(des, colour, type);
}

void Game::removePiece(Coor was) {
    board->remove(was);
}

void Game::setUpPlayer(playerType pt, Colour colour) {
    if (colour == Colour::White) {
        if (pt == pHuman) { 
            wPlayer = make_unique<Human>(Colour::White, this);
        }
        else if (pt == pComputer1) {
            wPlayer = make_unique<CompL1>(Colour::White, this);
        }
        else if (pt == pComputer2) {
            wPlayer = make_unique<CompL2>(Colour::White, this);
        }
        else if (pt == pComputer3) {
            wPlayer = make_unique<CompL3>(Colour::White, this);
        }
        else if (pt == pComputer4) {
            wPlayer = make_unique<CompL4>(Colour::White, this);
        }
    }
    if (colour == Colour::Black) {
        if (pt == pHuman) {
            bPlayer = make_unique<Human>(Colour::Black, this);
        }
        else if (pt == pComputer1) {
            bPlayer = make_unique<CompL1>(Colour::Black, this);
        }
        else if (pt == pComputer2) {
            bPlayer = make_unique<CompL2>(Colour::Black, this);
        }
        else if (pt == pComputer3) {
            bPlayer = make_unique<CompL3>(Colour::Black, this);
        }
        else if (pt == pComputer4) {
            bPlayer = make_unique<CompL4>(Colour::Black, this);
        }
    }
}

void Game::gameStart() {
    board = make_unique<Board>();
    board->normInit();
}

void Game::move(Coor was, Coor des, Colour c) {
    if (board->getPiece(was)->getInfo().colour != c) {
        std::cout <<  was.row << was.col << des.row << des.col << std::endl;
        string s;
        throw s;
    }
    board->move(was, des);
}

void Game::computerMove(Coor & scr, Coor & dest, Colour c) {
    if (c == Colour::White) {
        wPlayer->goMove(scr, dest);
    } else if (c == Colour::Black) {
        bPlayer->goMove(scr, dest);
    }
}

bool Game::validMove(Coor was, Coor des, Colour c) {
    if (board->getPiece(was)->getInfo().colour != c) return false;
    return board->validMove(was, des);
}

void Game::resign(Colour c) {
    if (c == Colour::Black) bPlayer->addScore(10);
    if (c == Colour::White) wPlayer->addScore(10);
}

int Game::getScore(Colour c) {
    if (c == Colour::Black) return bPlayer->getScore();
    else return wPlayer->getScore();
}

bool Game::checkSetup() {
    return board->validSetup();
}

bool Game::isCheckmate(Colour c) {
    if (board->kingInCheck(c) && board->noValidMove(c)) {
        if (c == Colour::Black) wPlayer->addScore(10);
        else if (c == Colour::White) bPlayer->addScore(10);
        return true;
    }
    return false;
}

bool Game::isStalemate(Colour c) {
    if ((!board->kingInCheck(c)) && board->noValidMove(c)) {
        wPlayer->addScore(5);
        bPlayer->addScore(5);
        return true;
    }
    return false;
}

void Game::promote(Coor c, Type t) {
    board->promote(c, t);
}

void Game::undo() {
    board->undo();
    board->undo();
}


std::pair<Coor, Coor> Game::hint(Colour colour) const {
    return board->getHint(colour);
}

std::ostream & operator<<(std::ostream & out, const Game & g) {
    out << *(g.board);
    return out;
}




