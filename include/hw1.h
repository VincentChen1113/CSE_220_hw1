#ifndef __HW1_H
#define __HW1_H

#define INFO(...) do {fprintf(stderr, "[          ] [ INFO ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);} while(0)
#define ERROR(...) do {fprintf(stderr, "[          ] [ ERR  ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);} while(0) 

//Hint: We defined these constants, you dont need to.
#define OCCUPIED_ERROR 1
#define FOUR_IN_ROW_ERROR 2
#define BOARD_FULL 0
#define LEGAL_MOVE 4

#define FOUND_SOLUTION 1
#define COMPLETED_A_FOUR 5
#define HEURISTICS_FAILED 0
#define INITIAL_BOARD_FOUR_IN_A_ROW -1
#define INITIAL_BOARD_INVALID_CHARACTERS -2
#define INITIAL_BOARD_NO_SOLUTION -3


#define MAX_ROWS 20
#define MAX_COLS 20

void initialize_board(const char *initial_state, int num_rows, int num_cols);
int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o);
char* generate_medium(const char *final_state, int num_rows, int num_cols);
void printBoard(int row, int col);
int checkExist(int NUM_ROWS, int NUM_COLS);
void putPiece(int CURR_ROWS, int CURR_COLS, char gamePiece);
int checkFourInARow(int currRow, int currCol, int actualRow, int actualCol, char piece);
int checkWin(int actualRow, int actualCol);
int findFourInARowExist(int num_rows, int num_cols);
int invalidCharactersExist(int num_rows, int num_cols);
int findSolution(int num_rows, int num_cols);
void countPieces(int num_rows, int num_cols, int *num_x, int *num_o);


#endif // HW1_H