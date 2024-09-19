#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"



int main(int argc, char **argv) {
    assert(argc == 4);

    int num_rows = (int)strtoul(argv[1], NULL, 10);
    int num_cols = (int)strtoul(argv[2], NULL, 10);
    const char *initial_state = argv[3];

    initialize_board(initial_state, num_rows, num_cols);
    
	bool endGame = true;
    char piece = 'x';
    int rowPut = 0;
    int colPut = 0;

    while(endGame){
        printBoard(num_rows, num_cols);

        do{
            printf("Choose a piece (x or o) or q to quit: ");
            scanf(" %c", &piece);
             if(piece != 'x' && piece != 'o' && piece != 'q'){
                printf("Invalid choice. ");
             }
            
        }
        while(piece != 'x' && piece != 'o' && piece != 'q');

        if(piece == 'q'){
                break; 
             }

        do{
            printf("Choose a row (0-%d): ", num_rows - 1);
            scanf("%d", &rowPut);
            if(rowPut < 0 || rowPut > num_rows - 1){
                printf("Invalid choice. ");
            }
            
        }
        while(rowPut < 0 || rowPut > num_rows - 1);

        do{
            printf("Choose a column (0-%d): ", num_cols - 1);
            scanf("%d", &colPut);
            if(colPut < 0 || colPut > num_cols - 1){
                printf("Invalid choice. ");
            }
            
        }
        while(colPut < 0 || colPut > num_cols - 1);

        if(checkExist(rowPut, colPut)){
            printf("Invalid choice. That space is already occupied.\n");
        }
        else if(checkFourInARow(rowPut, colPut, num_rows, num_cols, piece)){
            printf("Invalid choice. You have created 4-in-a-row.\n");
        }
        else{
            putPiece(rowPut, colPut, piece);
        }

        if(checkWin(num_rows, num_cols)){
            endGame = false;
            printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
            printBoard(num_rows, num_cols);
        }

    }
    
    return 0;
}
