#include <iostream>
#include <string>
#include "info.h"
#include "game.h"
#include "player.h"
using namespace std;

// print the score of colour
void printScore(Colour colour, Game & g) {
    int s = g.getScore(colour);
    if (s % 10 == 0) {
        if (colour == Colour::Black) {
            cout << "Black: " << s / 10 << endl;
        } else {
            cout << "White: " << s / 10 << endl;
        }
    } else {
        if (colour == Colour::Black) {
            cout << "Black: " << s / 10 << '.' << s % 10 << endl;
        } else {
            cout << "White: " << s / 10 << '.' << s % 10 << endl;
        }
    }
}

int main() {
    Game game;
    Colour turn = Colour::White;
    string cmd;
    vector<pair<Coor, Coor>> history;
    cin >> cmd;
    bool normal_game = true; // game will start a normal (default) game if is true
    if ("setup" == cmd) {  // enters setup mode to customize the board
        normal_game = false;
        game.setUp();
        cout << game;
        while (cin >> cmd) {
            if ("+" == cmd) { // add piece on the board
                char t,col;
                int row;
                cin >> t >> col >> row;
                
                Type type;
                if (('p' == t) || ('P' == t)) type = tPawn;
                else if (('r' == t) || ('R' == t)) type = tRook;
                else if (('n' == t) || ('N' == t)) type = tKnight;
                else if (('b' == t) || ('B' == t)) type = tBishop;
                else if (('q' == t) || ('Q' == t)) type = tQueen;
                else if (('k' == t) || ('K' == t)) type = tKing;
                else cout << "invalid type" << endl;
                
                if ((row < 1) && (row > 8)) cerr << "invlid row" << endl;
                Coor add_c;
                if ((col >= 'a') && (col <= 'h')) add_c = {8 - row, col - 'a'};
                else cout << "invalid column" << endl;
                
                if (t >= 'a') game.addPiece(add_c, Colour::Black, type);
                else game.addPiece(add_c, Colour::White, type);
            }
            
            else if ("-" == cmd) { // remove the piece from the board
                char col;
                int row;
                cin >> col >> row;
                if ((col < 'a') || (col > 'h') || (row < 1) || (row > 8)) {
                    cout << "invalid row and line! \n";
                    continue;
                }
                Coor rm_c = {8 - row, col - 'a'};
                game.removePiece(rm_c);
            }
            
            else if ("clear" == cmd) { // clear all the pieces on the board
                game.setUp();
            }
            
            else if ("basic" == cmd) { // create a normal board
                game.gameStart();
            }
            
            else if ("done" == cmd) { // setup is finished
                if (game.checkSetup()) {
                    break;
                } else {
                    cout << "illegal board setting" << endl;
                }
            }
            
            else if ("=" == cmd) { // decide which colour's player plays next
                cin >> cmd;
                if ("white" == cmd) {
                    turn = Colour::White;
                } else if ("black" == cmd) {
                    turn = Colour::Black;
                }
            }
            cout << game;
        }
        cin >> cmd;
    }
    if ("game" == cmd) { // start the game
        bool whuman = true; // true if white player is a human
        bool bhuman = true;
        string p;
        cin >> p;
        if ("human" == p) game.setUpPlayer(pHuman, Colour::White);
        else if ("computer[1]" == p) game.setUpPlayer(pComputer1, Colour::White);
        else if ("computer[2]" == p) game.setUpPlayer(pComputer2, Colour::White);
        else if ("computer[3]" == p) game.setUpPlayer(pComputer3, Colour::White);
        else if ("computer[4]" == p) game.setUpPlayer(pComputer4, Colour::White);
        if (p != "human") whuman = false;
        cin >> p;
        if ("human" == p) game.setUpPlayer(pHuman, Colour::Black);
        else if ("computer[1]" == p) game.setUpPlayer(pComputer1, Colour::Black);
        else if ("computer[2]" == p) game.setUpPlayer(pComputer2, Colour::Black);
        else if ("computer[3]" == p) game.setUpPlayer(pComputer3, Colour::Black);
        else if ("computer[4]" == p) game.setUpPlayer(pComputer4, Colour::Black);
        if (p != "human") bhuman = false;
        if (normal_game) {
            turn = Colour::White;
            game.gameStart();
        }
        cout << game;
        if (turn == Colour::White) cout << "White player's turn now: \n";
        else cout << "Black player's turn now: \n";
        while(cin >> cmd) {
            if ("resign" == cmd) { // the current player resigns, the opponent will win
                switch (turn) {
                    case Colour::White: {
                        game.resign(Colour::Black);
                        cout << "Black wins!" << endl;
                        cout << "White player's score: " << game.getScore(Colour::White) << endl;
                        cout << "Black player's score: " << game.getScore(Colour::Black) << endl;
                        turn = Colour::White;
                        game.gameStart();
                        cout << game;
                        cout << "White player's turn now: \n";
                        continue;
                    }
                    case Colour::Black: {
                        game.resign(Colour::White);
                        cout << "White wins!" << endl;
                        cout << "White player's score: " << game.getScore(Colour::White) << endl;
                        cout << "Black player's score: " << game.getScore(Colour::Black) << endl;
                        turn = Colour::White;
                        game.gameStart();
                        cout << game;
                        cout << "White player's turn now: \n";
                        continue;
                    }
                    default: break;
                }
                break;
            }
            else if ("history" == cmd) { // print the history of all moves made
                bool turn_ = true;
                for (unsigned int i = 0; i < history.size(); ++i) {
                    int was_r = 8 - history[i].first.row;
                    char was_c = history[i].first.col + 'a';
                    int des_r = 8 - history[i].second.row;
                    char des_c = history[i].second.col + 'a';
                    if (turn_) {
                        cout << "White: " << was_c << was_r;
                        cout << " " << des_c << des_r << endl;
                    }
                    else {
                        cout << "Black: " << was_c << was_r;
                        cout << " " << des_c << des_r << endl;
                    }
                    turn_ = !turn_;
                }
            }
            else if ("hint" == cmd) { // give the current player a hint for next move
                pair <Coor, Coor> foo;
                foo = game.hint(turn);
                int was_r = 8 - foo.first.row;
                char was_c = foo.first.col + 'a';
                int des_r = 8 - foo.second.row;
                char des_c = foo.second.col + 'a';
                cout << "Hint: " << was_c << was_r;
                cout << " -> " << des_c << des_r << endl;
            }
            else if ("move" == cmd) { // move a piece
                Coor was, des;
                if ((turn == Colour::White) && (whuman == false)) { // white is a computer
                    game.computerMove(was, des, Colour::White);
                } else if ((turn == Colour::Black) && (bhuman == false)) {
                    game.computerMove(was, des, Colour::Black);
                }
                else {
                    char was_c, was_r, new_c, new_r;
                    cin >> was_c >> was_r >> new_c >> new_r;
                    was = {8 - (was_r - '0'), was_c - 'a'};
                    des = {8 - (new_r - '0'), new_c - 'a'};
                }
                try {
                    game.move(was, des, turn);
                    pair <Coor, Coor> foo;
                    foo = make_pair (was, des);
                    history.emplace_back(foo);
                    turn = (turn == Colour::White)? Colour::Black : Colour::White;
                    if (game.isStalemate(turn)) {
                        cout << game;
                        cout << "Stalemate!\n";
                        printScore(Colour::White, game);
                        printScore(Colour::Black, game);
                        turn = Colour::White;
                        game.gameStart();
                        cout << game;
                        cout << "White player's turn now: \n";
                        continue;
                    }
                    if (game.isCheckmate(turn)) {
                        cout << game;
                        cout << "Checkmate! ";
                        (turn == Colour::White)? cout<<"Black wins!"<<endl : cout<<"White wins!"<<endl;
                        printScore(Colour::White, game);
                        printScore(Colour::Black, game);
                        turn = Colour::White;
                        game.gameStart();
                        cout << game;
                        cout << "White player's turn now: \n";
                        continue;
                    }

                }
                catch (string &) {
                    cout << "invalid move, please enter a valid move\n";
                }
                catch (Type) { // promote
                    if ((turn == Colour::White) && (whuman == false)) {
                        game.promote(des, tQueen);
                    } else if ((turn == Colour::Black) && (bhuman == false)) {
                        game.promote(des, tQueen);
                    } else {
                        char t;
                        cin >> t;
                        if (('q' == t) || ('Q' == t)) {
                            game.promote(des, tQueen);
                        } else if (('r' == t) || ('R' == t)) {
                            game.promote(des, tRook);
                        } else if (('b' == t) || ('B' == t)) {
                            game.promote(des, tBishop);
                        } else if (('n' == t) || ('N' == t)) {
                            game.promote(des, tKnight);
                        }
                    }
                    turn = (turn == Colour::White)? Colour::Black : Colour::White;
                    if (game.isStalemate(turn)) {
                        cout << game;
                        cout << "Stalemate!\n"; 
                        printScore(Colour::White, game);
                        printScore(Colour::Black, game);
                        turn = Colour::White;
                        game.gameStart();
                        cout << game;
                        cout << "White player's turn now: \n";
                        continue;
                    }
                    if (game.isCheckmate(turn)) {
                        cout << game;
                        cout << "Checkmate! ";
                        (turn == Colour::White)? cout<<"Black wins!"<<endl : cout<<"White wins!"<<endl;
                        printScore(Colour::White, game);
                        printScore(Colour::Black, game);
                        turn = Colour::White;
                        game.gameStart();
                        cout << game;
                        cout << "White player's turn now: \n";
                        continue;
                    }
                }
            }
            else if ("undo" == cmd) { //undo the previous two moves
                try {
                    game.undo();
                    history.pop_back();
                    history.pop_back();
                }
                catch (char) {
                    cout << "No move yet, cannot undo! \n ";
                }
            }
            cout << game;
            if (turn == Colour::White) cout << "White player's turn now: \n";
            else cout << "Black player's turn now: \n";
        }
    }
    cout << "Final Score:" << endl;
    printScore(Colour::White, game);
    printScore(Colour::Black, game);
}
