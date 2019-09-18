#include "graphicsdisplay.h"
#include "window.h"
#include "info.h"
#include "coor.h"
#include <string>
#include <sstream>
const int w_size = 640;
const int num_rc = 8;
const int cell_size = w_size / num_rc;
const int wide = 25;

// see graphicsdisplay.h for details

void GraphicsDisplay::graphic_init() {
    xw = std::make_unique<Xwindow>(w_size, w_size);
    for (int r = 0; r < num_rc; ++r) {
        for (int c = 0; c < num_rc; ++c) {
            if (r % 2 == 0) {
                if (c % 2 == 0) xw->fillRectangle(c * cell_size, r * cell_size, cell_size, cell_size, Xwindow::Orange);
                else xw->fillRectangle(c * cell_size, r * cell_size, cell_size, cell_size, Xwindow::Brown);
            }
            else if (r % 2 == 1) {
                if (c % 2 == 0) xw->fillRectangle(c * cell_size, r * cell_size, cell_size, cell_size, Xwindow::Brown);
                else xw->fillRectangle(c * cell_size, r * cell_size, cell_size, cell_size, Xwindow::Orange);
            }
        }
    }
    for (int r = 0; r < num_rc; ++r) {
        std::string num;
        std::ostringstream ss;
        ss << 8 - r;
        num = ss.str();
        xw->drawString(10, r * cell_size + 55, num, Xwindow::Yellow);
        char c = r + 'a';
        ss.str("");
        ss << c;
        num = ss.str();
        xw->drawString(r * cell_size + 55, w_size - 10, num, Xwindow::Yellow);
    }
}

void GraphicsDisplay::normInit() {
    for (int c = 0; c < num_rc; ++c) {
        std::string p;
        if ((c == 0) || (c == 7)) p = "R";
        else if ((c == 1) || (c == 6)) p = "N";
        else if ((c == 2) || (c == 5)) p = "B";
        else if (c == 3) p = "Q";
        else if (c == 4) p = "K";
        xw->drawBigString(cell_size * c + wide, 55, p, Xwindow::Black);
    }
    for (int c = 0; c < num_rc; ++c) {
        std::string p;
        xw->drawBigString(cell_size * c + wide, 55 + cell_size, "P", Xwindow::Black);
    }
    for (int c = 0; c < num_rc; ++c) {
        std::string p;
        if ((c == 0) || (c == 7)) p = "R";
        else if ((c == 1) || (c == 6)) p = "N";
        else if ((c == 2) || (c == 5)) p = "B";
        else if (c == 3) p = "Q";
        else if (c == 4) p = "K";
        xw->drawBigString(cell_size * c + wide, 55 + cell_size * 7, p, Xwindow::White);
    }
    for (int c = 0; c < num_rc; ++c) {
        std::string p;
        xw->drawBigString(cell_size * c + wide, 55 + cell_size * 6, "P", Xwindow::White);
    }
}

void GraphicsDisplay::draw_num(Coor coor) {
    if (coor.col == 0) {
        std::string num;
        std::ostringstream ss;
        ss << 8 - coor.row;
        num = ss.str();
        xw->drawString(10, coor.row * cell_size + 55, num, Xwindow::Yellow);
    }
}

void GraphicsDisplay::draw_letter(Coor coor) {
    if (coor.row == 7) {
        std::string letter;
        std::ostringstream ss;
        char c = coor.col + 'a';
        ss << c;
        letter = ss.str();
        xw->drawString(coor.col * cell_size + 55, w_size - 10, letter, Xwindow::Yellow);
    }
}

void GraphicsDisplay::getNotify(Coor was, Coor des, Type t, Colour colour) {
    if ((was.row == -1) && (was.col == -1)) { // add
        if (des.row % 2 == 0) { // remove the thing on the cell
            if (des.col % 2 == 0)  xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Orange);
            else if (des.col % 2 == 1)  xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Brown);
        }
        else {
            if (des.col % 2 == 0)  xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Brown);
            else if (des.col % 2 == 1) xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Orange);
        }
        draw_num(des);
        draw_letter(des);
        if (colour == Colour::White) {
            std::string p;
            switch (t) {
                case tRook: p = 'R';
                    break;
                case tKnight: p = 'N';
                    break;
                case tBishop: p = 'B';
                    break;
                case tQueen: p = 'Q';
                    break;
                case tKing: p = 'K';
                    break;
                case tPawn: p = 'P';
                    break;
                default:
                    break;
            }
            xw->drawBigString(cell_size * des.col + wide, 50 + cell_size * des.row, p, Xwindow::White);
        }
        else if (colour == Colour::Black) {
            std::string p;
            switch (t) {
                case tRook: p = 'R';
                    break;
                case tKnight: p = 'N';
                    break;
                case tBishop: p = 'B';
                    break;
                case tQueen: p = 'Q';
                    break;
                case tKing: p = 'K';
                    break;
                case tPawn: p = 'P';
                    break;
                default:
                    break;
            }
            xw->drawBigString(cell_size * des.col + wide, 50 + cell_size * des.row, p, Xwindow::Black);
        }
    }
    else if ((des.row == -1) && (des.col == -1) && (t == NonPiece) && (colour == Colour::NoneColour)) { // remove
        if (was.row % 2 == 0) {
            if (was.col % 2 == 0)  xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Orange);
            else if (was.col % 2 == 1)  xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Brown);
        }
        else {
            if (was.col % 2 == 0)  xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Brown);
            else if (was.col % 2 == 1) xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Orange);
        }
        draw_num(was);
        draw_letter(was);
    }
    
    else {
        if (was.row % 2 == 0) {
            if (was.col % 2 == 0)  xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Orange);
            else if (was.col % 2 == 1)  xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Brown);
        }
        else {
            if (was.col % 2 == 0)  xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Brown);
            else if (was.col % 2 == 1) xw->fillRectangle(was.col * cell_size, was.row * cell_size, cell_size, cell_size, Xwindow::Orange);
        }
        if (des.row % 2 == 0) {
            if (des.col % 2 == 0)  xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Orange);
            else if (des.col % 2 == 1)  xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Brown);
        }
        else {
            if (des.col % 2 == 0)  xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Brown);
            else if (des.col % 2 == 1) xw->fillRectangle(des.col * cell_size, des.row * cell_size, cell_size, cell_size, Xwindow::Orange);
        }
        draw_num(was);
        draw_letter(was);
        draw_num(des);
        draw_letter(des);
        if (colour == Colour::White) {
            std::string p;
            switch (t) {
                case tRook: p = 'R';
                    break;
                case tKnight: p = 'N';
                    break;
                case tBishop: p = 'B';
                    break;
                case tQueen: p = 'Q';
                    break;
                case tKing: p = 'K';
                    break;
                case tPawn: p = 'P';
                    break;
                default:
                    break;
            }
            xw->drawBigString(cell_size * des.col + wide, 50 + cell_size * des.row, p, Xwindow::White);
        }
        else if (colour == Colour::Black) {
            std::string p;
            switch (t) {
                case tRook: p = 'R';
                    break;
                case tKnight: p = 'N';
                    break;
                case tBishop: p = 'B';
                    break;
                case tQueen: p = 'Q';
                    break;
                case tKing: p = 'K';
                    break;
                case tPawn: p = 'P';
                    break;
                default:
                    break;
            }
            xw->drawBigString(cell_size * des.col + wide, 50 + cell_size * des.row, p, Xwindow::Black);
        }
    }
}


// see graphicsdisplay.h for details
/*
void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
	Info info = whoNotified.getInfo(); // the cell which was placed
	if (info.colour == Colour::Black) { // change the colour to black if the piece is black
		xw->fillRectangle(info.col * cell_size, info.row * cell_size,
				  cell_size, cell_size, Xwindow::Black);
	} else if (info.colour == Colour::White) {
		xw->fillRectangle(info.col * cell_size, info.row * cell_size,
				  cell_size, cell_size, Xwindow::White);
	} else { // info.colour == Colour::NoColour
		xw->fillRectangle(info.col * cell_size, info.row * cell_size,
				  cell_size, cell_size, Xwindow::Blue);
	}
}
*/
