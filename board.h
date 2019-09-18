#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include "info.h"
#include "coor.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Piece; // or include ?

class Board {
    std::vector<std::vector<std::shared_ptr<Piece> > > board;
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<GraphicsDisplay> gd;
    std::vector<std::pair<std::shared_ptr<Piece>, std::pair<Coor, Coor> > > undolist;
public:
    Board();
    friend class CompL1;
    friend class CompL2;
    friend class CompL3;
    friend class CompL4;
    friend class Computer;
    //void setUpWindows(GraphicDisplay * wd);
    void notifyDisplays(Coor was, Coor des, Type t, Colour colour); // notify display classes a change of a piece
    Coor findKing(Colour colour) const; // return colour king's location
    bool kingInCheck(Colour colour) const; // return true if colour's king is in check
    bool noValidMove(Colour colour) const; // return true if colour has no valid move
    void normInit(); // initialize board as a normal way
    bool validSetup(); // check if the board is valid for setup conditions
    std::vector<Coor> validDes(Coor c); // return a list of pos that the c is able to move to
    bool validMove(Coor was, Coor des); // check if a move is valid
    void add(Coor c, Colour colour, Type t); // add a new piece at c
    void remove(Coor c); // remove a piece at c
    void move(Coor was, Coor des); // move a cell at <was> to <des> // add sepcial move here
    void add_noNotify(Coor c, Colour colour, Type t); // add a new piece at c
    void remove_noNotify(Coor c); // remove a piece at c
    void move_noNotify(Coor was, Coor des); // move a cell at <was> to <des> // add sepcial move here
    int totalWeight(Colour colour); // return the total weight of c in the board (c's - opponents)
    std::shared_ptr<Piece> getPiece(Coor c); // return the piece at c
    std::vector<std::pair<Coor, std::vector<Coor> > > validMoveList(Colour colour) const; // return a list of pair of (piece, movelist) for a colour
    void promote(Coor des, Type t); // promote the pawn at des to be t
    void promote_noNotify(Coor des, Type t); // promote the pawn at des to be t
    bool checkMyKing(Coor was, Coor des); // return true if a move from mc to des will make mc's King in check
    void undo(); // undo a move
    void undo_noNotify(); // undo a move with no notify to displays
    std::pair<Coor, Coor> getHint(Colour colour) const; //get hint for next move
    friend std::ostream & operator<< (std::ostream & out, const Board & b);
    
};

#endif
