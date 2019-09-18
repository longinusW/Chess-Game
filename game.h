#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include "info.h"
#include "coor.h"
#include "board.h"
class Player;
class Board;
enum playerType {pHuman, pComputer1, pComputer2, pComputer3, pComputer4, pComputer5};
class Game {
    std::unique_ptr<Player> wPlayer;
    std::unique_ptr<Player> bPlayer;
    std::unique_ptr<Board> board;
    friend class Player;
    friend class CompL1;
    friend class CompL2;
    friend class CompL3;
    friend class CompL4;
    friend class Computer;
    public:
    void setUp(); // setup an empty board
    void addPiece(Coor des, Colour colour, Type type); // add a piece
    void removePiece(Coor was); // remove a piece
    void setUpPlayer(playerType pt, Colour colour); // set up players
    void gameStart(); // normal intialize the board
    void move(Coor was, Coor des, Colour c);
    void computerMove(Coor & scr, Coor & dest, Colour c);
    bool validMove(Coor was, Coor des, Colour c); // return true if is a valid move
    void resign(Colour c); // increment scores
    int getScore(Colour c); // return c player's score
    bool checkSetup(); // return true if the board setup is valid
    bool isCheckmate(Colour c); // return true if c is checkmated by its opponents
    bool isStalemate(Colour c); // return true if c is stalemated by its opponents
    void promote(Coor c, Type t); // promote the pawn at c to be t
    void undo(); // undo a move
     std::pair<Coor, Coor> hint(Colour colour) const; //get hint for next move
    friend std::ostream & operator<<(std::ostream & out, const Game & g); // print the board
};
#endif
