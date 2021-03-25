#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void multPlayerGame(string&, int&, string&, int&, int&); //lets two players play through a game
void singlePlayerGame(string&, int&, int&, int&); //lets one player play against a computer generated player that plays randomly
void noPlayerGame(); //lets two computers generated players play against each-other
int compPlay(const vector<char>&);
int EcompPlay(const vector <char>&);
int McompPlay(const vector <char>&);
int SinglePlayercompPlay(const vector<char> &); //computer player for single game (hard mode)
void drawBoard(const vector < char >&);//draws and updates board as game progresses, placed within loop for updating
void initVector(vector <char> &);//creates the initial vector, only called once
int convertPosition(char);//converts input to a spot on the board
bool validPlacement(const vector<char>&, int);//checks if input is within parameters/hasn't been used yet
int getPlay(const vector<char> &); //gets the play from the user
bool gameWon(const vector<char> &);
bool boardFull(const vector<char> &);

   const int PLAYER1 = 0; //'X' goes first
   const int PLAYER2 = 1; //'O' goes second

int main() {
    char userInput;
    int userval;
    int Play1Win = 0, Play2Win = 0;
    int HumPlayWin = 0, CompPlayWin = 0, tie = 0;

    string Player1Name;
    string Player2Name;
cout << "How many players will be playing today? (0-2)" << endl;
    cin >> userval;
    while(userval < 0 || userval > 2){
        cout << "Please enter a proper number of players\n";
        cin >> userval;
    }
    if (userval == 1){
        cout << "Please enter your name:\n";
        cin >> Player1Name;
        cout << endl;
    }
    else if (userval == 2){
        cout << "Please enter Player1's name:\n";
        cin >> Player1Name;
        cout << "Please enter Player2's name:\n";
        cin >> Player2Name;
    }
do{
    if( userval == 0){
        noPlayerGame();
    }
    else if(userval == 1){
        singlePlayerGame(Player1Name, HumPlayWin, CompPlayWin, tie);
    }
    else{
            multPlayerGame(Player1Name, Play1Win, Player2Name, Play2Win, tie);
    }
   cout << "Play again? (y/n)" << endl;
   cin >> userInput;
   userInput = tolower(userInput);
   while(userInput != 'y' && userInput != 'n'){
    cout << "Please decide.\n";
    cin >> userInput;
   }
  }while(userInput == 'y');
   return 0;
}

void singlePlayerGame(string& Player1Name, int& playWin, int& compWin, int& tie){

    vector<char> gameBoard(9);
    int curPlay;
    int whosTurn = PLAYER1;
    char eMode;

    srand(time(0));

    initVector(gameBoard); //creates the initial vector

    cout << "Easy(e), Medium (m), or Hard (h) mode?\n";
        cin >> eMode;
        eMode = tolower(eMode);
        while(eMode != 'e'&& eMode != 'm' && eMode != 'h'){
            cout <<"Please enter a difficulty\n";
            cin >> eMode;
        }
           drawBoard(gameBoard); //draws the empty board

    while(!gameWon(gameBoard) && !boardFull(gameBoard)){ //continues game while the game hasn't been won and there are spots available
      if(whosTurn == PLAYER1) { //places the proper character at chosen spot (player 1)
         curPlay = getPlay(gameBoard);
         gameBoard.at(curPlay) = 'X';
         whosTurn = PLAYER2; //switches turns
      }
      else { //places proper character at chosen spot (player 2)
            if(eMode == 'e'){
            curPlay = EcompPlay(gameBoard);
             gameBoard.at(curPlay) = 'O';
             whosTurn = PLAYER1;
            }
            else if(eMode == 'm'){
            curPlay = McompPlay(gameBoard);
             gameBoard.at(curPlay) = 'O';
             whosTurn = PLAYER1;
            }
            else{
            curPlay = SinglePlayercompPlay(gameBoard);
             gameBoard.at(curPlay) = 'O';
             whosTurn = PLAYER1; //switches turns
            }
      }

      drawBoard(gameBoard); //updates board
  }

// checks who, if either, won
   if(gameWon(gameBoard) && whosTurn == PLAYER2) { //checks player2 because swap happens immediately
      cout <<Player1Name << " Wins!!" << endl;
      ++playWin;
   }
   else if(gameWon(gameBoard) && whosTurn == PLAYER1){//checks player2 because swap happens immediately
      cout << "Computer Wins!!" << endl;
      ++compWin;
   }
   else {
      cout << "No one wins" << endl; //no one was victorious
   ++tie;
   }
   cout << Player1Name << ": " << playWin << "   Computer: " << compWin << "   Tie: " << tie << endl;
}
void multPlayerGame(string& Player1Name, int& Play1Win, string& Player2Name, int& Play2Win, int& tie){
    vector<char> gameBoard(9);
    int curPlay;
    int whosTurn = PLAYER1;

    initVector(gameBoard); //creates the initial vector

   drawBoard(gameBoard); //draws the empty board

        while(!gameWon(gameBoard) && !boardFull(gameBoard)){ //continues game while the game hasn't been won and there are spots available

      curPlay = getPlay(gameBoard); //user input

      if(whosTurn == PLAYER1) { //places the proper character at chosen spot (player 1)
         gameBoard.at(curPlay) = 'X';
         whosTurn = PLAYER2; //switches turns
      }
      else { //places proper character at chosen spot (player 2)
         gameBoard.at(curPlay) = 'O';
         whosTurn = PLAYER1; //switches turns
      }

      drawBoard(gameBoard); //updates board
  }

// checks who, if either, won
   if(gameWon(gameBoard) && whosTurn == PLAYER2) { //checks player2 because swap happens immediately
      cout <<Player1Name <<" Wins!!" << endl;
      ++Play1Win;
   }
   else if(gameWon(gameBoard) && whosTurn == PLAYER1){//checks player2 because swap happens immediately
      cout << Player2Name << " Wins!!" << endl;
      ++Play2Win;
   }
   else {
      cout << "No one wins" << endl; //no one was victorious
   ++tie;
   }
   cout << Player1Name << ": " << Play1Win << "   " << Player2Name << ": " << Play2Win << "   Tie: " << tie << endl;
}
void noPlayerGame(){
  vector<char> gameBoard(9);
    int curPlay;
    int whosTurn = PLAYER1;
    initVector(gameBoard); //creates the initial vector
    srand(time(0));
   drawBoard(gameBoard); //draws the empty board

    while(!gameWon(gameBoard) && !boardFull(gameBoard)){ //continues game while the game hasn't been won and there are spots available

      if(whosTurn == PLAYER1) { //places the proper character at chosen spot (player 1)
         curPlay = compPlay(gameBoard);
         gameBoard.at(curPlay) = 'X';
         whosTurn = PLAYER2; //switches turns
      }
      else { //places proper character at chosen spot (player 2)
            curPlay = compPlay(gameBoard);
         gameBoard.at(curPlay) = 'O';
         whosTurn = PLAYER1; //switches turns
      }

      drawBoard(gameBoard); //updates board
  }

// checks who, if either, won
   if(gameWon(gameBoard) && whosTurn == PLAYER2) { //checks player2 because swap happens immediately
      cout <<"Computer1 Wins!!" << endl;
   }
   else if(gameWon(gameBoard) && whosTurn == PLAYER1){//checks player2 because swap happens immediately
      cout << "Computer2 Wins!!" << endl;
   }
   else {
      cout << "No one wins" << endl; //no one was victorious
   }
}
void drawBoard(const vector < char >&gameBoard) { //draws and updates board as game progresses, placed within loop for updating
   for (int i = 0; i < 9; i += 3) {
      cout << "  " << gameBoard.at(i) << "  |  " << gameBoard.at(i + 1) << "  |  "
         << gameBoard.at(i + 2) << "  " << endl;
      if (i < 6) {
         cout << "-----|-----|-----" << endl;
      }
   }
   cout << endl;

   return;
}
void initVector(vector <char> &v) { //creates the initial vector, only called once
    char character = 'a';

    for (unsigned i = 0; i <v.size(); ++i) {
       v.at(i) = character;
       ++character;
    }
   return;
}
int convertPosition(char boardPosition) {//converts input to a spot on the board
   boardPosition = tolower(boardPosition); //enables game to continue if uppercase value used
   switch (boardPosition){ //converts input
      case 'a':
         return 0;
      case 'b':
         return 1;
      case 'c':
         return 2;
      case 'd':
         return 3;
      case 'e':
         return 4;
      case 'f':
         return 5;
      case 'g':
         return 6;
      case 'h':
         return 7;
      case 'i':
         return 8;
      default:
         return -1;
   }
}
bool validPlacement(const vector<char>  &gameBoard, int positionIndex) { //checks if input is within parameters/hasn't been used yet

   if (positionIndex >-1 && positionIndex < 9 &&
      (gameBoard.at(positionIndex) != 'X' && gameBoard.at(positionIndex) != 'O')) {
         return true;
      }
   return false;
}
int getPlay(const vector<char> &gameBoard) { //gets the play from the user

   char boardPosition = ' ';
   int play;
   cout << "Please choose a position: " << endl;
   cin >> boardPosition;
   play = convertPosition(boardPosition);
   while(!validPlacement(gameBoard, play)){
      cout << "Please choose a position: " << endl;
      cin >> boardPosition;
      play = convertPosition(boardPosition);
   }

   return play;
}
bool gameWon(const vector<char> &gameBoard) {

   for (int i = 0; i < 9; i += 3) {
      if((gameBoard.at(i) == 'O' && gameBoard.at(i+1) == 'O' && gameBoard.at(i+2) == 'O') ||
         (gameBoard.at(i) == 'X' && gameBoard.at(i+1) == 'X' && gameBoard.at(i+2) == 'X')){ //checks rows
            return true;
        }
   }
   for( int j = 0; j <3; ++j){
      if((gameBoard.at(j) == 'O' && gameBoard.at(j +3) == 'O' && gameBoard.at(j + 6) == 'O') ||
         (gameBoard.at(j) == 'X' && gameBoard.at(j +3) == 'X' && gameBoard.at(j + 6) == 'X')) { //checks columns
         return true;
      }
   }
   if((gameBoard.at(0) == 'O' && gameBoard.at(4) == 'O' && gameBoard.at(8) == 'O') ||
         (gameBoard.at(0) == 'X' && gameBoard.at(4) == 'X' && gameBoard.at(8) == 'X')) { //checks forward diagonal
            return true;
   }
   else if ((gameBoard.at(2) == 'O' && gameBoard.at(4) == 'O' && gameBoard.at(6) == 'O') ||
         (gameBoard.at(2) == 'X' && gameBoard.at(4) == 'X' && gameBoard.at(6) == 'X')) { //checks backwards diagonal
            return true;
   }

   return false;
}
bool boardFull(const vector<char> &gameBoard) { //checks that any position is available

   char characterVal = 'a';
   for(unsigned i = 0; i <gameBoard.size(); ++i){

      if (gameBoard.at(i) == characterVal){
         return false;
      }
      ++characterVal;
   }
   return true;
}
int compPlay(const vector<char> & gameBoard){
   int play;

    for (int i = 0; i < 9; i += 3) {
      if((gameBoard.at(i) == 'O' && gameBoard.at(i+1) == 'O' && (gameBoard.at(i+2) != 'O' && gameBoard.at(i+2) != 'X')) ||
         (gameBoard.at(i) == 'X' && gameBoard.at(i+1) == 'X' && (gameBoard.at(i+2) != 'X' && gameBoard.at(i+2) != 'O'))){ //checks rows
            play = i+2;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
        if((gameBoard.at(i) == 'O'  && (gameBoard.at(i+1) != 'O' && gameBoard.at(i+1) != 'X') && gameBoard.at(i+2) == 'O') ||
         (gameBoard.at(i) == 'X' && (gameBoard.at(i+1) != 'X' && gameBoard.at(i+1) != 'O') && gameBoard.at(i+2) == 'X' )){ //checks rows
            play = i+1;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
        if(((gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') && gameBoard.at(i + 1) == 'O' && gameBoard.at(i+2) == 'O' ) ||
         ((gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') && gameBoard.at(i + 1) == 'X' && gameBoard.at(i+2) == 'X' )){ //checks rows
            play = i;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
   }
    for( int j = 0; j <3; ++j){
      if((gameBoard.at(j) == 'O' && gameBoard.at(j +3) == 'O' && (gameBoard.at(j + 6) != 'O' && gameBoard.at(j + 6)  != 'X')) ||
         (gameBoard.at(j) == 'X' && gameBoard.at(j +3) == 'X' && (gameBoard.at(j + 6) != 'O' && gameBoard.at(j + 6)  != 'X'))) { //checks columns
         play = j+6;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
      if((gameBoard.at(j) == 'O' && (gameBoard.at(j + 3) != 'O' && gameBoard.at(j + 3)  != 'X')&& gameBoard.at(j +6) == 'O') ||
         (gameBoard.at(j) == 'X' && (gameBoard.at(j + 3) != 'O' && gameBoard.at(j + 3)  != 'X') && gameBoard.at(j +6) == 'X')) { //checks columns
         play = j+3;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
      if(((gameBoard.at(j) != 'O' && gameBoard.at(j)  != 'X') && gameBoard.at(j + 3) == 'O' && gameBoard.at(j + 6) == 'O') ||
         ((gameBoard.at(j) != 'O' && gameBoard.at(j)  != 'X') && gameBoard.at(j + 3) == 'X' && gameBoard.at(j + 6) == 'X')) { //checks columns
         play = j;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
   }
   if((gameBoard.at(0) == 'O' && gameBoard.at(4) == 'O' && (gameBoard.at(8) != 'O' && gameBoard.at(8)  != 'X')) ||
         (gameBoard.at(0) == 'X' && gameBoard.at(4) == 'X' && (gameBoard.at(8) != 'O' && gameBoard.at(8)  != 'X'))) { //checks forward diagonal
            play = 8;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
   else if((gameBoard.at(0) == 'O' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(8) == 'O') ||
         (gameBoard.at(0) == 'X' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(8) == 'X')) { //checks forward diagonal
            play = 4;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
   else if(((gameBoard.at(0) != 'O' && gameBoard.at(0)  != 'X') && gameBoard.at(4) == 'O' && gameBoard.at(8) == 'O') ||
         ((gameBoard.at(0) != 'O' && gameBoard.at(0)  != 'X') && gameBoard.at(4) == 'X' && gameBoard.at(8) == 'X')) { //checks forward diagonal
            play = 0;
            if(validPlacement(gameBoard, play)){
                    return play;
   }
         }
   if ((gameBoard.at(2) == 'O' && gameBoard.at(4) == 'O' && (gameBoard.at(6) != 'O' && gameBoard.at(6)  != 'X')) ||
         (gameBoard.at(2) == 'X' && gameBoard.at(4) == 'X' && (gameBoard.at(6) != 'O' && gameBoard.at(6)  != 'X'))) { //checks backwards diagonal
            play = 6;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    else if ((gameBoard.at(2) == 'O' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(6) == 'O') ||
         (gameBoard.at(2) == 'X' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(6) == 'X')) { //checks backwards diagonal
            play = 4;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    else if (((gameBoard.at(2) != 'O' && gameBoard.at(2)  != 'X') && gameBoard.at(4) == 'O' && gameBoard.at(6) == 'O') ||
            ((gameBoard.at(2) != 'O' && gameBoard.at(2)  != 'X') && gameBoard.at(4) == 'X' && gameBoard.at(6) == 'X')) {
            play = 2;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }


   do{
        switch((rand()%9)){
            case 0:
                play = 0;
                break;
            case 1:
               play = 1;
               break;
            case 2:
               play = 2;
               break;
            case 3:
               play = 3;
               break;
            case 4:
               play = 4;
               break;
            case 5:
               play = 5;
               break;
            case 6:
               play = 6;
               break;
            case 7:
               play = 7;
               break;
            case 8:
               play = 8;
               break;
           }
       }while(!validPlacement(gameBoard, play));

   return play;

}
int EcompPlay(const vector <char>& gameBoard){
int play;
do{
        switch((rand()%9)){
            case 0:
                play = 0;
                break;
            case 1:
               play = 1;
               break;
            case 2:
               play = 2;
               break;
            case 3:
               play = 3;
               break;
            case 4:
               play = 4;
               break;
            case 5:
               play = 5;
               break;
            case 6:
               play = 6;
               break;
            case 7:
               play = 7;
               break;
            case 8:
               play = 8;
               break;
           }
       }while(!validPlacement(gameBoard, play));

   return play;

}
int McompPlay(const vector <char>& gameBoard){
int play;

    if(rand()%2 == 1){
        for (int i = 0; i < 9; i += 3) {
          if((gameBoard.at(i) == 'O' && gameBoard.at(i+1) == 'O' && (gameBoard.at(i+2) != 'O' && gameBoard.at(i+2) != 'X')) ||
             (gameBoard.at(i) == 'X' && gameBoard.at(i+1) == 'X' && (gameBoard.at(i+2) != 'X' && gameBoard.at(i+2) != 'O'))){ //checks rows
                play = i+2;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
            }
            if((gameBoard.at(i) == 'O'  && (gameBoard.at(i+1) != 'O' && gameBoard.at(i+1) != 'X') && gameBoard.at(i+2) == 'O') ||
             (gameBoard.at(i) == 'X' && (gameBoard.at(i+1) != 'X' && gameBoard.at(i+1) != 'O') && gameBoard.at(i+2) == 'X' )){ //checks rows
                play = i+1;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
            }
            if(((gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') && gameBoard.at(i + 1) == 'O' && gameBoard.at(i+2) == 'O' ) ||
             ((gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') && gameBoard.at(i + 1) == 'X' && gameBoard.at(i+2) == 'X' )){ //checks rows
                play = i;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
            }
       }
        for( int j = 0; j <3; ++j){
          if((gameBoard.at(j) == 'O' && gameBoard.at(j +3) == 'O' && (gameBoard.at(j + 6) != 'O' && gameBoard.at(j + 6)  != 'X')) ||
             (gameBoard.at(j) == 'X' && gameBoard.at(j +3) == 'X' && (gameBoard.at(j + 6) != 'O' && gameBoard.at(j + 6)  != 'X'))) { //checks columns
             play = j+6;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
          }
          if((gameBoard.at(j) == 'O' && (gameBoard.at(j + 3) != 'O' && gameBoard.at(j + 3)  != 'X')&& gameBoard.at(j +6) == 'O') ||
             (gameBoard.at(j) == 'X' && (gameBoard.at(j + 3) != 'O' && gameBoard.at(j + 3)  != 'X') && gameBoard.at(j +6) == 'X')) { //checks columns
             play = j+3;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
          }
          if(((gameBoard.at(j) != 'O' && gameBoard.at(j)  != 'X') && gameBoard.at(j + 3) == 'O' && gameBoard.at(j + 6) == 'O') ||
             ((gameBoard.at(j) != 'O' && gameBoard.at(j)  != 'X') && gameBoard.at(j + 3) == 'X' && gameBoard.at(j + 6) == 'X')) { //checks columns
             play = j+6;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
          }
       }
       if((gameBoard.at(0) == 'O' && gameBoard.at(4) == 'O' && (gameBoard.at(8) != 'O' && gameBoard.at(8)  != 'X')) ||
             (gameBoard.at(0) == 'X' && gameBoard.at(4) == 'X' && (gameBoard.at(8) != 'O' && gameBoard.at(8)  != 'X'))) { //checks forward diagonal
                play = 8;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
        }
       else if((gameBoard.at(0) == 'O' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(8) == 'O') ||
             (gameBoard.at(0) == 'X' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(8) == 'X')) { //checks forward diagonal
                play = 4;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
        }
       else if(((gameBoard.at(0) != 'O' && gameBoard.at(0)  != 'X') && gameBoard.at(4) == 'O' && gameBoard.at(8) == 'O') ||
             ((gameBoard.at(0) != 'O' && gameBoard.at(0)  != 'X') && gameBoard.at(4) == 'X' && gameBoard.at(8) == 'X')) { //checks forward diagonal
                play = 0;
                if(validPlacement(gameBoard, play)){
                        return play;
       }
             }
       if ((gameBoard.at(2) == 'O' && gameBoard.at(4) == 'O' && (gameBoard.at(6) != 'O' && gameBoard.at(6)  != 'X')) ||
             (gameBoard.at(2) == 'X' && gameBoard.at(4) == 'X' && (gameBoard.at(6) != 'O' && gameBoard.at(6)  != 'X'))) { //checks backwards diagonal
                play = 6;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
        }
        else if ((gameBoard.at(2) == 'O' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(6) == 'O') ||
             (gameBoard.at(2) == 'X' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(6) == 'X')) { //checks backwards diagonal
                play = 4;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
        }
        else if (((gameBoard.at(2) != 'O' && gameBoard.at(2)  != 'X') && gameBoard.at(4) == 'O' && gameBoard.at(6) == 'O') ||
                ((gameBoard.at(2) != 'O' && gameBoard.at(2)  != 'X') && gameBoard.at(4) == 'X' && gameBoard.at(6) == 'X')) {
                play = 2;
                if(validPlacement(gameBoard, play)){
                        return play;
                }
        }
    }


   do{
        switch((rand()%9)){
            case 0:
                play = 0;
                break;
            case 1:
               play = 1;
               break;
            case 2:
               play = 2;
               break;
            case 3:
               play = 3;
               break;
            case 4:
               play = 4;
               break;
            case 5:
               play = 5;
               break;
            case 6:
               play = 6;
               break;
            case 7:
               play = 7;
               break;
            case 8:
               play = 8;
               break;
           }
       }while(!validPlacement(gameBoard, play));

   return play;

}
int SinglePlayercompPlay(const vector<char> & gameBoard){//checks for any possible two in a rows before playing
   int play;
   for (int i = 0; i < 9; i += 3) {
      if(gameBoard.at(i) == 'O' && gameBoard.at(i+1) == 'O' && (gameBoard.at(i+2) != 'O' && gameBoard.at(i+2) != 'X')){ //checks rows
            play = i+2;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
        if(gameBoard.at(i) == 'O'  && (gameBoard.at(i+1) != 'O' && gameBoard.at(i+1) != 'X') && gameBoard.at(i+2) == 'O'){ //checks rows
            play = i+1;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
        if((gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') && gameBoard.at(i + 1) == 'O' && gameBoard.at(i+2) == 'O' ){ //checks rows
            play = i;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
   }
    for( int j = 0; j <3; ++j){
      if(gameBoard.at(j) == 'O' && gameBoard.at(j +3) == 'O' && (gameBoard.at(j + 6) != 'O' && gameBoard.at(j + 6)  != 'X')){ //checks columns
         play = j+6;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
      if(gameBoard.at(j) == 'O' && (gameBoard.at(j + 3) != 'O' && gameBoard.at(j + 3)  != 'X')&& gameBoard.at(j +6) == 'O') { //checks columns
         play = j+3;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
      if((gameBoard.at(j) != 'O' && gameBoard.at(j)  != 'X') && gameBoard.at(j + 3) == 'O' && gameBoard.at(j + 6) == 'O') { //checks columns
         play = j;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
   }
   if(gameBoard.at(0) == 'O' && gameBoard.at(4) == 'O' && (gameBoard.at(8) != 'O' && gameBoard.at(8)  != 'X')) { //checks forward diagonal
            play = 8;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
   else if(gameBoard.at(0) == 'O' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(8) == 'O') { //checks forward diagonal
            play = 4;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
   else if((gameBoard.at(0) != 'O' && gameBoard.at(0)  != 'X') && gameBoard.at(4) == 'O' && gameBoard.at(8) == 'O'){ //checks forward diagonal
            play = 0;
            if(validPlacement(gameBoard, play)){
                    return play;
   }
         }
   if (gameBoard.at(2) == 'O' && gameBoard.at(4) == 'O' && (gameBoard.at(6) != 'O' && gameBoard.at(6)  != 'X')){ //checks backwards diagonal
            play = 6;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    else if (gameBoard.at(2) == 'O' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(6) == 'O'){ //checks backwards diagonal
            play = 4;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    else if ((gameBoard.at(2) != 'O' && gameBoard.at(2)  != 'X') && gameBoard.at(4) == 'O' && gameBoard.at(6) == 'O'){
            play = 2;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    for (int i = 0; i < 9; i += 3) {
      if(gameBoard.at(i) == 'X' && gameBoard.at(i+1) == 'X' && (gameBoard.at(i+2) != 'X' && gameBoard.at(i+2) != 'O')){ //checks rows
            play = i+2;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
        if(gameBoard.at(i) == 'X' && (gameBoard.at(i+1) != 'X' && gameBoard.at(i+1) != 'O') && gameBoard.at(i+2) == 'X' ){ //checks rows
            play = i+1;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
        if((gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') && gameBoard.at(i + 1) == 'X' && gameBoard.at(i+2) == 'X' ){ //checks rows
            play = i;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
        }
   }
    for( int j = 0; j <3; ++j){
      if (gameBoard.at(j) == 'X' && gameBoard.at(j +3) == 'X' && (gameBoard.at(j + 6) != 'O' && gameBoard.at(j + 6)  != 'X')) { //checks columns
         play = j+6;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
      if(gameBoard.at(j) == 'X' && (gameBoard.at(j + 3) != 'O' && gameBoard.at(j + 3)  != 'X') && gameBoard.at(j +6) == 'X') { //checks columns
         play = j+3;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
      if((gameBoard.at(j) != 'O' && gameBoard.at(j)  != 'X') && gameBoard.at(j + 3) == 'X' && gameBoard.at(j + 6) == 'X') { //checks columns
         play = j;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
      }
   }
   if(gameBoard.at(0) == 'X' && gameBoard.at(4) == 'X' && (gameBoard.at(8) != 'O' && gameBoard.at(8)  != 'X')){ //checks forward diagonal
            play = 8;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
   else if(gameBoard.at(0) == 'X' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(8) == 'X') { //checks forward diagonal
            play = 4;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
   else if((gameBoard.at(0) != 'O' && gameBoard.at(0)  != 'X') && gameBoard.at(4) == 'X' && gameBoard.at(8) == 'X') { //checks forward diagonal
            play = 0;
            if(validPlacement(gameBoard, play)){
                    return play;
   }
         }
   if (gameBoard.at(2) == 'X' && gameBoard.at(4) == 'X' && (gameBoard.at(6) != 'O' && gameBoard.at(6)  != 'X')) { //checks backwards diagonal
            play = 6;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    else if (gameBoard.at(2) == 'X' && (gameBoard.at(4) != 'O' && gameBoard.at(4)  != 'X') && gameBoard.at(6) == 'X') { //checks backwards diagonal
            play = 4;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }
    else if ((gameBoard.at(2) != 'O' && gameBoard.at(2)  != 'X') && gameBoard.at(4) == 'X' && gameBoard.at(6) == 'X') {
            play = 2;
            if(validPlacement(gameBoard, play)){
                    return play;
            }
    }


   do{
        switch((rand()%9)){
            case 0:
                play = 0;
                break;
            case 1:
               play = 1;
               break;
            case 2:
               play = 2;
               break;
            case 3:
               play = 3;
               break;
            case 4:
               play = 4;
               break;
            case 5:
               play = 5;
               break;
            case 6:
               play = 6;
               break;
            case 7:
               play = 7;
               break;
            case 8:
               play = 8;
               break;
           }
       }while(!validPlacement(gameBoard, play));

   return play;

}
