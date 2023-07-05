/******************************************************************************
thiago.soares_de_souza @ lcieducation.net
ap1, Tic-Tac-Toe project
winter 2022 LaSalle College

Instructions: 

Do a tic tac toe game 



******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#define ROW 3
#define COLUMN 3
#define PLAYER_1 1
#define PLAYER_2 2

// Fuction Declaration

// Validate repeat opetation
char validate_repeat_operation(int);

// Initialize reset Tic-Tac-Toe Passing a Matrix
void initialize_reset_tic_tac_toe(char[ROW][COLUMN]);

// Play the game Passing a Matrix
void play_game(char tic_tac_toe[ROW][COLUMN]);

// Print Tic-Toc-Toe Passing a Matrix
void printf_tic_tac_toe(char tic_tac_toe[ROW][COLUMN]);

// Check with there is a winner Passing matrix and last moviments
bool check_winner(char tic_tac_toe[ROW][COLUMN], int player_movement_row, int player_movement_column);


int main(){

    int choice = -1;
    char repeat_operation = '\n';

    // int const ROW = 3;
    // int const COLUMN = 3;

    char tic_tac_toe[ROW][COLUMN];    
    
    do{
        system("cls");
        choice = -1;

        do{
            printf("\t\t\t      TIC-TAC-TOE GAME\n");
            printf("\t\t\t Main Menu Operators Choice\n");
            printf("\t\t\t----------------------------\n\n");

            printf("  1 - PLAY GAME\n");
            printf("  2 - QUIT\n\n\n");

            printf("Make your choice (1 - 2) : ");
            scanf(" %d", &choice);
            fflush(stdin);
            
            if(choice < 1 || choice > 2){
                printf("\nInvalid choice. Choice should be between 1 - 2.\n");
                choice = -1;
                sleep(2);
                system("cls");
            }

        }while(choice < 1 || choice > 5);

        switch(choice){
            case 1:
                do{
                    system("cls");

                    printf("\t\t\t      TIC-TAC-TOE GAME\n");
                    printf("\t\t\t   Player 1 vs Player 2\n");
                    printf("\t\t\t --------------------------\n\n");

                    initialize_reset_tic_tac_toe(tic_tac_toe);

                    printf_tic_tac_toe(tic_tac_toe);

                    play_game(tic_tac_toe);

                    repeat_operation = validate_repeat_operation(choice);

                }while(repeat_operation == 'y');

                break;

            case 2:
                printf("\nQuitting...");
                sleep(2);
                system("cls");
                exit(0);

            default:
                printf("Operation not found. Please try to enter the operation again.\n");
        }

    }while(choice != 5);

    return 0;

}

// Fuction Definition

// Validate repeat opetation
char validate_repeat_operation(int choice){

    char repeat_operation;

    do{
        if(choice == 1){
            printf("\nDo you want to play again ? (y/n) : ");
        }
        // else if(choice == 2){
        //     printf("\n Do you want to do another division ? (y/n) : ");
        // }else if(choice == 3){
        //     printf("\n Do you want to do another multiplication ? (y/n) : ");
        // }else{
        //     printf("\n Do you want to do another subtraction ? (y/n) : ");
        // }
        
        scanf(" %c", &repeat_operation);
        fflush(stdin);
        repeat_operation = tolower(repeat_operation);
        
        if(repeat_operation != 'y' && repeat_operation != 'n'){
            printf("\nInvalid option.\n");
            sleep(2);
        }

    }while(repeat_operation != 'y' && repeat_operation != 'n');

    return repeat_operation;
}

// Initialize reset Tic-Tac-Toe Passing a Matrix
void initialize_reset_tic_tac_toe(char tic_tac_toe[ROW][COLUMN]){

    for(int i = 0 ; i < ROW ; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            tic_tac_toe[i][j] = ' ';
        }
    }
}

// Play the game Passing a Matrix
void play_game(char tic_tac_toe[ROW][COLUMN]){

    bool hasWinner = false;
    bool isValidRound = false;
    int player_movement_row, player_movement_column;
    int player = PLAYER_1;
    int count_movements = 1;

    // initialize_reset_tic_tac_toe_matrix(tic_tac_toe_m);

    // printf_tic_tac_toe_matrix(tic_tac_toe_m);

    while(hasWinner == false && count_movements <= ROW * COLUMN){
        
        isValidRound = false;
        
        while(isValidRound == false){
            
            do{
                printf("\nPlayer %d Movement: Please enter your movement (row (0 - %d) column (0 - %d)) maximum (%d, %d): ", player, ROW - 1, COLUMN - 1, ROW - 1, COLUMN - 1);
                scanf("%d%d", &player_movement_row, &player_movement_column);
                fflush(stdin);
            }while(player_movement_row < 0 || player_movement_row > ROW - 1 || player_movement_column < 0 || player_movement_column > COLUMN - 1);
            
            if(tic_tac_toe[player_movement_row][player_movement_column] != ' '){
                printf("\nMoviment already made. Please choose another movement.\n");
            }else{
                
                if(player == PLAYER_1){
                    tic_tac_toe[player_movement_row][player_movement_column] = 'X';
                    
                    hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
                    
                    if(!hasWinner){
                        player = PLAYER_2;
                    }
                }else{
                    tic_tac_toe[player_movement_row][player_movement_column] = 'O';
                    hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
                    if(!hasWinner){
                        player = PLAYER_1;
                    }
                }
                count_movements++;
                isValidRound = true;
            }
        }
        printf_tic_tac_toe(tic_tac_toe);
    }

    if(hasWinner){
        printf("\nPlayer %d wins!\n", player);
    }else{
        printf("\nDraw. No Winners!\n");
    }

}

// Print Tic-Toc-Toe Passing a Matrix
void printf_tic_tac_toe(char tic_tac_toe[ROW][COLUMN]){
    
    printf("\n");

    for(int i = 0 ; i < ROW ; i++){
        // printf("|");
        for(int j = 0 ; j < COLUMN ; j++){
            if(j > 0){
                printf("| ");
            }else{
                printf(" ");
            }
            printf("%c", tic_tac_toe[i][j]);
            printf(" ");
        }
        // printf("|");
        printf("\n");
    }

    // printf("\n");

}

// Check with there is a winner Passing matrix and last moviments
bool check_winner(char tic_tac_toe[ROW][COLUMN], int player_movement_row, int player_movement_column){

    int count_x = 0;
    int count_0 = 0;

    // verifying row
    for(int i = 0 ; i < ROW ; i++){
        if(tic_tac_toe[i][player_movement_column] == 'X'){
            count_x++;
        }else if(tic_tac_toe[i][player_movement_column] == 'O'){
            count_0++;
        }
    }
    
    if(count_x == ROW || count_0 == COLUMN){
        return true;
    }

    count_x = 0;
    count_0 = 0;

    // verifying column
    for(int j = 0 ; j < COLUMN ; j++){
        if(tic_tac_toe[player_movement_row][j] == 'X'){
            count_x++;
        }else if(tic_tac_toe[player_movement_row][j] == 'O'){
            count_0++;
        }
    }
    
    if(count_x == ROW || count_0 == COLUMN){
        return true;
    }

    count_x = 0;
    count_0 = 0;

    // verifying primary diagonal
    for(int i = 0, j = 0 ; i < ROW ; i++, j++){
        if(tic_tac_toe[i][j] == 'X'){
            count_x++;
        }else if(tic_tac_toe[i][j] == 'O'){
            count_0++;
        }
    }
    
    if(count_x == ROW || count_0 == COLUMN){
        return true;
    }

    count_x = 0;
    count_0 = 0;


    // verifying secundary diagonal
    for(int i = 0, j = COLUMN - 1 ; i < ROW && j >= 0 ; i++, j--){
        if(tic_tac_toe[i][j] == 'X'){
            count_x++;
        }else if(tic_tac_toe[i][j] == 'O'){
            count_0++;
        }
    }
    
    if(count_x == ROW || count_0 == COLUMN){
        return true;
    }

    return false;

}

    