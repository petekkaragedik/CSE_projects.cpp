// to run: g++ -std=c++11 tictactoe_ai.cpp -o tictactoe_ai
//./tictactoe_ai
#include <iostream>
#include <vector>
#include <limits>
#include <climits> //for INT_MIN INT_MAX
using namespace std;

char playerSymbol, aiSymbol;
//not the most efficient when it comes to traverse through it because you need a nested loop of 2!
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
// ' ' -> empty cell, 'X' -> player, '0' -> AI
int nodesExplored; //nodes explored by ai
void displayBoardWithNumbers();

void chooseSymbol() {
    cout << "Do you want to play as X or O? (X goes first): ";
    cin >> playerSymbol;

    //what if the player enter lowercase?
    playerSymbol = toupper(playerSymbol);

    if(playerSymbol == 'X'){
        aiSymbol = 'O';
    }
    else if (playerSymbol == 'O'){
        aiSymbol = 'X';
    }
    else {
        cout << "Invalid choice! Defaulting to X." << endl;
        playerSymbol = 'X';
        aiSymbol = 'O';
    }
    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "You are playing as " << playerSymbol << "." << endl;
    cout << "The AI is playing as " << aiSymbol << "." << endl;
    cout << "Enter a number from 1-9 to make your move: " << endl;
    displayBoardWithNumbers();
}

void displayBoardWithNumbers(){
    cout << endl;
    cout << " 1 | 2 | 3 " << endl;
    cout << "---+---+---" << endl;
    cout << " 4 | 5 | 6 " << endl;
    cout << "---+---+---" << endl;
    cout << " 7 | 8 | 9 " << endl;
    cout << endl;
}

//function to display the curr. board
void displayBoard() {
    for(int i = 0; i < 3; i++){
        cout << " ";
        for(int j = 0; j < 3; j++){
            cout << board[i][j];
            if (j < 2) {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < 2) {
            cout << "---+---+---" << endl;
        }
    }
    cout << endl;
}

bool isBoardFull(char b[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j <3; j++){
            if(b[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}

//to check if player CAN play that move
bool isValidMove(int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

void playerMove() {
    int choice;
    while(true) {
        cout << "Your move (1-9): ";
        cin >> choice;
        if(choice < 1 || choice > 9) {
            cout << "Invalid choice! Choose a number between 1-9." << endl;
            continue; //continuing with the next iteration
        }
        
        int row = (choice - 1 ) / 3;
        int col = (choice - 1) % 3;

        if(!isValidMove(row, col)) {
            cout << "That position is already taken. Try again." << endl;
            continue; //continue with the next iteration of the loop
        }
        board[row][col] = playerSymbol;
        break;
    }
}

//10 means AI wins, -10 means player wins
int checkWin(char b[3][3], char playerSym, char aiSym){
    for( int i = 0; i < 3; i++) {
        if((b[i][0] == b[i][1]) && (b[i][1] == b[i][2]) && (b[i][0] != ' ')){
            if (b[i][0] == playerSym){
                return -10;
            } else if (b[i][0] == aiSym){
                return 10;
            }
        }
    }
    for( int i = 0; i < 3; i++) {
        if((b[0][i] == b[1][i]) && (b[1][i] == b[2][i]) && (b[0][i] != ' ')){
            if (b[0][i] == playerSym){
                return -10;
            } else if (b[0][i] == aiSym){
                return 10;
            }
        }
    }
    if((b[0][0] == b[1][1]) && (b[1][1] == b[2][2]) && (b[0][0] != ' ')) {
        if(b[0][0] == playerSym){
            return -10;
        }
        else if(b[0][0] == aiSym){
            return 10;
        }
    }
    if((b[0][2] == b[1][1]) && (b[1][1] == b[2][0]) && (b[0][2] != ' ')) {
        if(b[0][2] == playerSym){
            return -10;
        }
        else if(b[0][2] == aiSym){
            return 10;
        }
    }
    if(isBoardFull(b)){
        return 0; //draw
    } else {
        return -1; //not complete
    }
}

int checkCurrentWinnerSituation(){
        return checkWin(board, playerSymbol, aiSymbol);
}

//TREE NODE
struct TreeNode {
    char boardCopy[3][3]; //copy of the board
    int moveRow, moveCol; //moves that caused this condition
    vector <TreeNode*> children; //possible future moves' conditions
    int value; //score

    TreeNode (char b[3][3], int row, int col){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                boardCopy[i][j] = b[i][j]; //copying the curr. state of the board
            }
        }
        moveRow = row;
        moveCol = col;
        value = 0; //unknown initially so...
    }
};

void generateChildren(TreeNode * node, char player) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3 ; j++){
            if(node -> boardCopy[i][j] == ' '){ //empty spot detected
                TreeNode * child = new TreeNode(node->boardCopy, i, j);
                //generating all possible moves
                child->boardCopy[i][j] = player; //making the move
                node -> children.push_back(child);
            }
        }
    }
}

int AlphaBetaMinimax(TreeNode * node, int depth, int alpha, int beta, bool isMaximizing){
    nodesExplored++;
    
    int score = checkWin(node->boardCopy, playerSymbol, aiSymbol);
    //base case: terminal or depth 0
    if((score == 10) || (score == -10) || (isBoardFull(node -> boardCopy)) || (depth == 0)){
        node->value = score;
        return score;
    }
    //generate children if none exist yet
    if(node->children.empty()) {
        if(isMaximizing){
            generateChildren(node, aiSymbol);
        } else {
            generateChildren(node, playerSymbol);
        }
    }
    if(isMaximizing){ //maximizing player (AI)'s turn
        int maxEval = INT_MIN;
        for (TreeNode * child: node -> children){ //for each child node
            int eval = AlphaBetaMinimax(child, depth - 1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if(beta <= alpha) {
                break;
            }
        }
        node->value = maxEval;
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for(TreeNode * child : node -> children) {
            int eval = AlphaBetaMinimax(child, depth - 1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if(beta <= alpha){
                break;
            }
        }
        node -> value = minEval;
        return minEval;
    }
}

void deleteTree(TreeNode * node){
    for(TreeNode* child : node->children){
        deleteTree(child);
    }
    delete node;
}

//the best move choosing strategy for the AI
pair <int, int> bestMove(){
    nodesExplored = 1;
    TreeNode * root = new TreeNode(board, -1, -1);
    generateChildren(root, aiSymbol);
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for(TreeNode * child : root -> children) {
        int score = AlphaBetaMinimax(child, 9, INT_MIN, INT_MAX, false);
        child -> value = score;
        if(score > bestScore){
            bestScore = score;
            bestMove = {child -> moveRow, child ->moveCol};
        }
    }
    deleteTree(root);
    return bestMove;
}

void aiMove() {
    cout << "AI is making a move..." << endl;
    pair<int, int> move = bestMove();
    board[move.first][move.second] = aiSymbol;
    int position = (move.first * 3 + move.second + 1);
    cout << "AI chose position " << position << "." << endl;
    cout << "Nodes explored: " << nodesExplored << endl;
    cout << endl;
}

void playGame() {
    chooseSymbol();
    // if ai is X then goes first

    bool isPlayersTurn = (playerSymbol == 'X'); //to see who goes first, x goes first though
    while (true) {
        if(isPlayersTurn){
            playerMove();
            cout << endl;
            displayBoard();
            int result = checkCurrentWinnerSituation();
            if (result == -10) {
                cout << "Congratulations! You win!" << endl;
                break;
            } else if (result == 0) {
                cout << "It's a draw!" << endl;
                break;
            }
        }
        else{
            aiMove();
            displayBoard();
            int result = checkCurrentWinnerSituation();
            if (result == 10) {
                cout << "The AI wins!" << endl;
                break;
            } else if (result == 0) {
                cout << "It's a draw!" << endl;
                break;
            }
        }
        isPlayersTurn = !isPlayersTurn; //to switch between players in each round
    }
}

int main() {
    playGame();
    return 0;
}
