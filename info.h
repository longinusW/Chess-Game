#ifndef _INFO_H_
#define _INFO_H_

#include "coor.h"

enum class Colour {NoneColour, Black, White};
enum Type {NonPiece, tPawn, tKing, tRook, tQueen, tBishop, tKnight};

struct Info {
    Colour colour;
    Type type;
    Coor c;
    int weight;
    bool alive = false;
    Info(Colour colour, Type type, Coor c, int weight):
        colour{colour}, type{type}, c{c}, weight{weight} {}
    
    Info(const Info & other):
    colour{other.colour}, type{other.type}, c{other.c}, weight{other.weight} {}
};

#endif
