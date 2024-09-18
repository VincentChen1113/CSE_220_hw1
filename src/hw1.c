#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"


char board[MAX_ROWS][MAX_COLS] = {0};

/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/

void initialize_board(const char *initial_state, int num_rows, int num_cols) {
    int index = 0;
    for(int i = 0; i < num_rows; i++ ){
        for(int j = 0; j < num_cols; j++){
            board[i][j] = initial_state[index++];
        }
    }
}
void printBoard(int NUM_ROWS, int NUM_COLS){
    for(int row = 0; row < NUM_ROWS; row++){
        for(int column = 0; column < NUM_COLS; column++){
            printf("%c ", board[row][column]);
        }
        printf("\n");
    }
}

int checkExist(int NUM_ROWS, int NUM_COLS){
    if(board[NUM_ROWS][NUM_COLS] == 'x' || board[NUM_ROWS][NUM_COLS] == 'o'){
        return 1;
    }
    return 0;
}

void putPiece(int CURR_ROWS, int CURR_COLS, char gamePiece){
    board[CURR_ROWS][CURR_COLS] = gamePiece;
}

int checkFourInARow(int currRow, int currCol, int actualRow, int actualCol, char piece){
    int horizonCounter = 1;
    for(int i = currCol + 1; i < actualCol; i++){
        if(board[currRow][i] == piece){
            horizonCounter++;
        }
        else{
            break;
        }
    }
    for(int j = currCol - 1; j > -1; j--){
        if(board[currRow][j] == piece){
            horizonCounter++;
        }
        else{
            break;
        }
    }

    int verticalCounter = 1;
    for(int i = currRow + 1; i < actualRow; i++){
        if(board[i][currCol] == piece){
            verticalCounter++;
        }
        else{
            break;
        }
    }
    for(int j = currRow - 1; j > -1; j--){
        if(board[j][currCol] == piece){
            verticalCounter++;
        }
        else {
            break;
        }
    }

    int diagonalCounter1 = 1;
    for(int i = currRow + 1, j = currCol + 1; i < actualRow && j < actualCol; i++, j++){
        if(board[i][j] == piece){
            diagonalCounter1++;
        }
        else{
            break;
        }
    }
    for(int i = currRow - 1, j = currCol - 1; i > -1 && j > -1; i--, j--){
        if(board[i][j] == piece){
            diagonalCounter1++;
        }
        else{
            break;
        }
    }

    int diagonalCounter2 = 1;
    for(int i = currRow + 1, j = currCol - 1; i < actualRow && j < actualCol; i++, j--){
        if(board[i][j] == piece){
            diagonalCounter2++;
        }
        else{
            break;
        }
    }
    for(int i = currRow - 1, j = currCol + 1; i > -1 && j > -1; i--, j++){
        if(board[i][j] == piece){
            diagonalCounter2++;
        }
        else{
            break;
        }
    }


    if (horizonCounter >= 4 || verticalCounter >= 4 || diagonalCounter1 >= 4 || diagonalCounter2 >= 4) {
        return 1;
    }
    return 0;
}

int checkWin(int actualRow, int actualCol){
    for(int i = 0; i < actualRow; i++){
        for(int j = 0; j < actualCol; j++){
            if(board[i][j] == '-'){
                return 0;
                break;
            }
            else if(checkFourInARow(i, j, actualRow, actualCol, board[i][j])){
                return 0;
                break;
            }
        }
    }

    return 1;
}

int findFourInARowExist(int num_rows, int num_cols){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            if(checkFourInARow(i, j, num_rows, num_cols, board[i][j])){
                return INITIAL_BOARD_FOUR_IN_A_ROW;
            }
        }
    }
    return 0;
}

int invalidCharactersExist(int num_rows, int num_cols){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            if(board[i][j] != 'o' && board[i][j] != 'x'){
                if(board[i][j] != '-'){
                    return INITIAL_BOARD_INVALID_CHARACTERS;
                }
            }
        }
    }
    return 0;
}

int findSolution(int num_rows, int num_cols){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            if(board[i][j] == '-'){
               if(checkFourInARow(i, j, num_rows, num_cols, 'x')){
                if(checkFourInARow(i, j, num_rows, num_cols, 'o')){
                    return INITIAL_BOARD_NO_SOLUTION;
                }
                else{
                    return FOUND_SOLUTION;
                }
               }

               if(checkFourInARow(i, j, num_rows, num_cols, 'o')){
                if(checkFourInARow(i, j, num_rows, num_cols, 'x')){
                    return INITIAL_BOARD_NO_SOLUTION;
                }
                else{
                    return FOUND_SOLUTION;
                }
               }
            }
        }
    }
    return HEURISTICS_FAILED;
}

int pieceCounter(int num_rows, int num_cols, char piece){
    int counter = 0;
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            if(board[i][j] == piece){
                counter++;
            }
        }
    }
    return counter;
}


int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o) {
    initialize_board(initial_state, num_rows, num_cols);
    *num_x = pieceCounter(num_rows, num_cols, 'x');
    *num_o = pieceCounter(num_rows, num_cols, 'o');

    if(findFourInARowExist(num_rows, num_cols) == -1){
        if(invalidCharactersExist(num_rows, num_cols) == -2){
        return INITIAL_BOARD_INVALID_CHARACTERS;
        }
        return INITIAL_BOARD_FOUR_IN_A_ROW;
    }

    if(invalidCharactersExist(num_rows, num_cols) == -2){
        return INITIAL_BOARD_INVALID_CHARACTERS;
    }

    if(findSolution(num_rows, num_cols) == 1){
        return FOUND_SOLUTION;
    }
    else if(findSolution(num_rows, num_cols) == -3){
        return INITIAL_BOARD_NO_SOLUTION;
    }
    else if(findSolution(num_rows, num_cols) == 0){
        return HEURISTICS_FAILED;
    }
    return 0;
}

char* generate_medium(const char *final_state, int num_rows, int num_cols) { 

    return 0;
    (void) final_state;
    (void) num_rows; 
    (void) num_cols;
}
