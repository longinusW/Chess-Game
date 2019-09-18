# Chess-Game
you are supposed to open uml as first :)

# Introduction 
  Once we touched the chess game, we considered how do we think for the next move while playing this game? How we can create an algorithm to make AI to consider as human? How can computer learn anything by itself without any other commands? Technology and automation, are exactly the direction of world revolution.

# Overview 
  The general structure of the project consists of a Board contains 64 (8 * 8) pieces. Each piece has different types based on the rules of the game. Based on their types, the pieces have similarities and differences. Through commands from the client’s input, the Board will execute the transformation on the location of the pieces, and the pieces who were involved in the transformation will update their information as well. At the same time, the Board will notify the class, who is responsible for output, that the transformation’s information and the class who handles output will update its information as well. This part is following the observer pattern. In the computer player part, the computer players can get information from the Board and use different algorithms (based on their level) to compute a most appropriate move. To connect the Board, computer players and the client (main), we create a Game class, which behaves followed the bridge design pattern. So the computer player can access Board from Game and can execute transformations by calling methods of Game. 

# Design
Our program consists mainly four classes, Game, Board, Piece and Player (which contains AI’s algorithms)

Game

  Game acts like a controller to connect Board, Players and Clients. It owns a Board, and two Players which represents white and black players respectively. Based on client’s input commands, it will execute different methods to modify the information of Board and update information in Players, and do transformations on Pieces. The purpose of designing a Game class is provide bridges between the client, Board, and Players, and it can hide the information inside the game (Pieces’ location, players’ scores) from client, and provide the program with security and information hiding. 

Board and Piece

Board contains 64 Pieces objects which are stored in a 2D vector. Each Piece is different with their types (King, Queen, Bishop, Knight, Rook, Pawn, NoPiece (which means this piece is not a valid movable piece)). We use the parent class, Piece to represent the type NoPiece and its subclasses are the 6 valid movable piece types. Each valid movable Piece class contains different algorithms to determine its move behaviour. Since a main part of the chess game to execute a move, where our move method, which is a method in board, will determine if a move is valid and execute the transformation by updating the 2D vector that stores the pieces and updating the information in the relevant piece (the piece which is moved), if a move a valid. The move method will call the validCheck method in pieces, which is different dynamically, where each Piece class has its own validCheck conditions. In order to check if a move is valid, there are three main cases: 

1. If the piece that you want to move can actually move to the destination based on its moving behavior. For example, if you want to move a rook diagonally, that is invalid. 

2. If the move is a special move. For example, if we want to execute castling , the king’s destination is two squares from it horizontally and we need to check the conditions to determine if the castling is valid (ex. one condition can be, if there are pieces between the king and the rook you want to castle with). 

3. If the move will cause your king in check. If a move is valid by passing both 1 and 2, we still need to check if the move will make your king be checked by the opponent, if yes, it is an invalid move. To achieve this goal, we try to move the piece to its destination, and we search the whole board to see if an opponent’s piece can capture the king after the move. After trying, we need to move the piece back to its original location.

After we execute the transformation on the board, we need to notify the displays(graphic and text) with the updated information so they can modify the display. Here we used the strategy of Observer Pattern but we did not follow it exactly because there will be only two observers, where the board is the subject and it will tell displays the information of a piece including type, old location, new location. Moverever, in Piece class, we designed a method to return a valid move destinations of the Piece, intend to provide information for the AI players.

AI

The basic idea to implement high-level AI is to give every piece a weight(eg. King = 10000, Queen = 80, Rook = 50…) and calculate the total weight of all pieces of one colour and minus opponent’s total weight to measure the board. Upon our discussion, we decide our attack plan should depend upon <next_move_list> of all pieces. For the “AI” of level 1 and 2, we only need to calculate all available move in one step for the white player or the black one. We will give all available moves a weight. For Level 1, we would set up them in the same after satisfying the condition that such a move will not make king in check. For Level 2, we will increase up the weight of cell with kind or other pieces of the opponent. For Level 3, in order to avoid being captured, we just need to calculate the next move list of the opponent and whether it will overlap with that of this player in turn, which means we have to anticipate one more turn compared to Level 1 and 2. Similarly, we just need to increase up the anticipating range for Level 4. More specifically, for Level 4, we can simulate every possible location that the player can move. We assign weight into each piece to indicate how important they are. For some specific condition, if level 3 has already fulfilled the features of preferring to capture, then we need to create level 4 based upon level 3, adding the function of calculate the total weight on the board. Weight of each piece of opponent would be viewed as the negative, otherwise would be viewed as the positive.  We  assume the opponent will move the piece to make my worst situation (i.e. total weight least), then we can use recursion to find the most total weight and corresponding move. 

# Resilience to Change
In our design, we stored pieces’ information in their classes, where also includes the corresponding capture and transformation rules related to the piece. If we wish to change the information  or change the move behavior of a piece in the future, we can easily go to the piece’s class to modify the move behavior method (determine if it is a valid move and a special move) There will be no change in the Board class or Game class since the two classes only call Piece’s methods. This design brings us benefit in this case by putting the basic information at the basis hence achieved high cohesion low coupling goal.

Another example that demonstrates our program’s adaptability to the possible various changes that might occur afterwards is that we stored the weight of every piece type, which is considered to be the magic number, in integer constants. Since we depend on every piece’s weight to calculate the value of a specific move and then decide for the computer which move to make, the best choice of the weight can be subjective to different person’s view. By using constants, if some other choice of the piece’s weight is found to be more reasonable than the choice that we currently adopt, we just need to make a slight change to the data stored in those constants. This demonstrates our program’s design of flexibility and maintainability. Besides, it also makes the code more readable.

What is more, say we want to change the scale of the board and add some new pieces with new types. Using our design, we only need to add subclasses under Piece and add them into the board, <with some simple change in the Type enum>. There will be no extra work to do with the Game class or Player class since they are just calling the methods in Board. For the old(original) piece classes, we do not need to change them unless a new rule change their behaviour (Then we have to change no matter what design!). In this case, our design brings us a lot efficiency if there needs to be modified in the future. And of course, demonstrates our program’s design of flexibility and maintainability.

# Special Features

Opening

For those available moves in the standard book, we will just add them into player as if condition by hardcoding. And tell the AIs to follow the opening in certain turns of the game. (ex. For the first three steps, follow the opening style) If we are accessible to use deep learning, we can use these opens as a training case for AI.

Undo

We actually implement the undo feature in our program, and it can handle any kinds of moves, including regular captures, castling, en passant, or promote. To implement this feature, we create a vector which can contain the information in every move (old position, destination, the original piece at destination). Once a valid move is executed, we push the information as an element of this move in the vector. And if we want to undo a move, we pop out an element in the vector, we put the current piece at <destination> to its original position(i.e. <old position>), and put the original piece, which stored in the vector, to <destination>. We also need to build some conditions to check if a move is a special move (en passant, castling, promote…). The strategy to implement the feature is actually in the last section. For normal moves (regular capture or regular move without capturing), we only need to pop out one element from the vector which we use to store every move’s information(We call it undoList). The challenging part is about the special moves, since we need to update the relevant piece’s information to its old values, which were the values before the move is executed. For example, if a pawn just move two squares forward, we store a boolean in Pawn class to track this message (to determine if one can en passant). If we undo a move where a pawn just moved two squares forward, and the relevant boolean was updated to true, we have to change it back to false and decrease the number of moves of the piece.  Moreover, we have to check that if the move is a special move. Since in our implementation for transformation, castling is move but contains two transformations (a transformation of the king and a transformation of the rook). In order to determine if an element in undoList is a part of such a special move like castling, we need to peak the second last elements in the undoList and see if the information(Piece, original location, destination) stored in last two elements follow the rule of the special move. (For castling, it is obvious because a king can only move 2 squares in a row if and only if it is castiling). 
  
Four-handed Game

For four-handed chess game, we will firstly change the layout of the board. The board will contain 14*14, 2D vector instead of 8*8, where the four 3*3 squares at the four corner will be empty (We can define a special class for the empty cell which means one cannot move to this location). We will change attack rule of different pieces if necessary based upon the rules of four-handed chess games. But the pieces behavior will be mostly the same. We will change the number of players of 2 to 4 in the class of game and the condition of ending game since we cannot assign win as the end of game. Thus, in the class of player, all of isWin, inCheck, stalemate, checkmate or move functions should depend upon all players. On the other hand, we will have to expand AI anticipating next move list into at least the future 4 steps in the level of 3 and above. We also need to consider the condition that whether all AIs need to combine as an ally if the game is one human player and all of the rest is computer player.

History

Presenting the history of all moves made: For this feature, we used one of the STL containers vector to store every step’s move, including its previous position and its destination position expressed in 2-D coordinates. By making use of vector, we do not need to explicitly managing our own memory. In order to take another extra feature “undo” step into account in history, we implemented with the thoughts of the stack’s feature by emplacing the moves from the back of the vector when adding new moves and popping out the move from the back of the vector twice(since we actually need to first undo the opponent’s move and then undo the current player’s move) when an “undo” occurs.
