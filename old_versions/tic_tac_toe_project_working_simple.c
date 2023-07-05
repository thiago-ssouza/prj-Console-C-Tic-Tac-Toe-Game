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

struct tic_tac_toe_data{
    char tic_toc_toe_m[ROW][COLUMN];
};

// Fuction Declaration

// VALIDATE REPEAT OPERATION
char validate_repeat_operation(int);

// Play the game
// void play_game(char[3][3], int, int);
// void play_game(char[ROW][COLUMN]);
void play_game();

// Initialize reset Tic-Tac-Toe
struct tic_tac_toe_data initialize_reset_tic_tac_toe(struct tic_tac_toe_data);

// Print Tic-Toc-Toe
// void printf_tic_tac_toe(char[3][3], int, int);
// void printf_tic_tac_toe(char[ROW][COLUMN]);
void printf_tic_tac_toe(struct tic_tac_toe_data);

// Check with there is a winner
bool checkWinner(struct tic_tac_toe_data tic_tac_toe_s, int player_movement_row, int player_movement_column/*, int player*/);

int main(){

    int choice = -1;
    char repeat_operation = '\n';

    // int const ROW = 3;
    // int const COLUMN = 3;

    // char tic_toc_toe[ROW][COLUMN];

    // struct tic_tac_toe_data{
    //     char tic_toc_toe_m[ROW][COLUMN]
    // };

    // struct tic_tac_toe_data tic_tac_toe_s;
    
    
    do{
        system("cls");
        choice = -1;

        do{
            // printf("\n\t      NUMERIC CALCULATOR\n\t  Main Menu Operators Choice\n\t  --------------------------\n\n    1 - ADDITION\n    2 - DIVISION\n    3 - MULTIPLICATION\n    4 - SUBTRACTION\n    5 - QUIT\n\n   Make your choice (1 - 5) : ");
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
                    // system("cls");
                    
                    // play_game(tic_toc_toe, ROW, COLUMN);
                    // play_game(tic_toc_toe);
                    play_game();

                    repeat_operation = validate_repeat_operation(choice);

                }while(repeat_operation == 'y');

                break;
            case 2:
                printf("\nQuitting...");
                sleep(2);
                system("cls");
                exit(0);
                //break;
            default:
                printf("Operation not found. Please try to enter the operation again.\n");
        }


    }while(choice != 5);

    return 0;

}

// Fuction Definition

// void play_game(char tic_toc_toe[3][3], int row, int column){
// void play_game(char tic_toc_toe[ROW][COLUMN]){
void play_game(){

    struct tic_tac_toe_data tic_tac_toe_s;

    tic_tac_toe_s = initialize_reset_tic_tac_toe(tic_tac_toe_s);

    printf_tic_tac_toe(tic_tac_toe_s);

    bool hasWinner = false;
    bool isValidRound = false;
    int player_movement_row, player_movement_column;
    int player = PLAYER_1;
    int count_movements = 1;


    while(hasWinner == false && count_movements <= ROW * COLUMN){
        isValidRound = false;
        while(isValidRound == false){
            
            do{
                printf("\nPlayer %d Movement: Please enter your movement (row (0 - %d) column (0 - %d)) maximum (%d, %d): ", player,ROW - 1, COLUMN - 1, ROW - 1, COLUMN - 1);
                scanf("%d%d", &player_movement_row, &player_movement_column);
                fflush(stdin);
            }while(player_movement_row < 0 || player_movement_row > ROW - 1 || player_movement_column < 0 || player_movement_column > COLUMN - 1);
            
            if(tic_tac_toe_s.tic_toc_toe_m[player_movement_row][player_movement_column] != ' '){
                printf("\nMoviment already made. Please choose another movement.\n");
            }else{
                if(player == PLAYER_1){
                    tic_tac_toe_s.tic_toc_toe_m[player_movement_row][player_movement_column] = 'X';
                    hasWinner = checkWinner(tic_tac_toe_s, player_movement_row, player_movement_column);
                    if(!hasWinner){
                        player = PLAYER_2;
                    }
                }else{
                    tic_tac_toe_s.tic_toc_toe_m[player_movement_row][player_movement_column] = 'O';
                    hasWinner = checkWinner(tic_tac_toe_s, player_movement_row, player_movement_column);
                    if(!hasWinner){
                        player = PLAYER_1;
                    }
                }
                count_movements++;
                isValidRound = true;
            }
        }
        printf_tic_tac_toe(tic_tac_toe_s);
    }

    if(hasWinner){
        printf("\nPlayer %d wins!\n", player);
    }else{
        printf("\nDraw. No Winners!\n");
    }

    // printf_tic_tac_toe(tic_tac_toe_s);

}

struct tic_tac_toe_data initialize_reset_tic_tac_toe(struct tic_tac_toe_data tic_tac_toe_s){

    for(int i = 0 ; i < ROW ; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            tic_tac_toe_s.tic_toc_toe_m[i][j] = ' ';
        }
        printf("\n");
    }    

    return tic_tac_toe_s;

}

// void printf_tic_tac_toe(char tic_toc_toe[3][3], int row, int column){
// void printf_tic_tac_toe(char tic_toc_toe[ROW][COLUMN]){
void printf_tic_tac_toe(struct tic_tac_toe_data tic_tac_toe_s){
    
    // for(int i = 0 ; i < ROW ; i++){
    //     for(int j = 0 ; j < COLUMN ; j++){
    //         printf("%c ", tic_tac_toe_s.tic_toc_toe_m[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("\n");

    for(int i = 0 ; i < ROW ; i++){
        // printf("|");
        for(int j = 0 ; j < COLUMN ; j++){
            if(j > 0){
                printf("| ");
            }else{
                printf(" ");
            }
            printf("%c", tic_tac_toe_s.tic_toc_toe_m[i][j]);
            printf(" ");
        }
        // printf("|");
        printf("\n");
    }

    printf("\n");

    // printf("\n%d", sizeof(tic_toc_toe[3][3]));
}

bool checkWinner(struct tic_tac_toe_data tic_tac_toe_s, int player_movement_row, int player_movement_column/*, int player*/){

    int count_x = 0;
    int count_0 = 0;

    // if(player == 1){
        // if(player_movement_row = player_movement_column){
            
            // if(player_movement_row == 0 && player_movement_column == 0){
                
                for(int i = 0 ; i < ROW ; i++){
                    if(tic_tac_toe_s.tic_toc_toe_m[i][player_movement_column] == 'X'){
                        count_x++;
                    }else if(tic_tac_toe_s.tic_toc_toe_m[i][player_movement_column] == 'O'){
                        count_0++;
                    }
                }
                
                if(count_x == ROW || count_0 == COLUMN){
                    return true;
                }

                count_x = 0;
                count_0 = 0;

                for(int j = 0 ; j < COLUMN ; j++){
                    if(tic_tac_toe_s.tic_toc_toe_m[player_movement_row][j] == 'X'){
                        count_x++;
                    }else if(tic_tac_toe_s.tic_toc_toe_m[player_movement_row][j] == 'O'){
                        count_0++;
                    }
                }
                
                if(count_x == ROW || count_0 == COLUMN){
                    return true;
                }

                count_x = 0;
                count_0 = 0;

                for(int i = 0, j = 0 ; i < ROW ; i++, j++){
                    if(tic_tac_toe_s.tic_toc_toe_m[i][j] == 'X'){
                        count_x++;
                    }else if(tic_tac_toe_s.tic_toc_toe_m[i][j] == 'O'){
                        count_0++;
                    }
                }
                
                if(count_x == ROW || count_0 == COLUMN){
                    return true;
                }

                count_x = 0;
                count_0 = 0;

                for(int i = 0, j = COLUMN - 1 ; i < ROW && j >= 0 ; i++, j--){
                    if(tic_tac_toe_s.tic_toc_toe_m[i][j] == 'X'){
                        count_x++;
                    }else if(tic_tac_toe_s.tic_toc_toe_m[i][j] == 'O'){
                        count_0++;
                    }
                }
                
                if(count_x == ROW || count_0 == COLUMN){
                    return true;
                }

            // }else if(player_movement_row == ROW - 1 && player_movement_column == COLUMN - 1){



            // }else{

            // }
        // }else if(player_movement_row + player_movement_column == player_movement_row - 1){


        // }else{

        // }   

    // }else{

    // }

    // if(player_movement_row = player_movement_column){
    //     if(player_movement_row == 0 && player_movement_column == 0){
    //         for(int i = 0 ; i < player_movement_row ; i++){
    //             if(tic_tac_toe_s.tic_toc_toe_m[i][player_movement_row]){

    //             }
    //         }
    //     }else if(player_movement_row == ROW - 1 && player_movement_column == COLUMN - 1){

    //     }else{

    //     }
    // }else if(player_movement_row + player_movement_column == player_movement_row - 1){

    // }else{

    // }

    return false;

}

// VALIDATE REPEAT OPERATION
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

    