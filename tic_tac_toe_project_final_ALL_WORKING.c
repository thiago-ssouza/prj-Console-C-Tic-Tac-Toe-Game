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
#define PLAYER_X 'X'
#define PLAYER_O 'O'

// Fuction Declaration

// Validate repeat opetation
char validate_repeat_operation(int);

// Initialize reset Tic-Tac-Toe Passing a Matrix
void initialize_reset_tic_tac_toe(char[ROW][COLUMN]);

// Play the game Passing a Matrix
void play_game(char[ROW][COLUMN], int);

// Print Tic-Toc-Toe Passing a Matrix
void printf_tic_tac_toe(char[ROW][COLUMN]);

// Check with there is a winner Passing matrix and last moviments
bool check_winner(char[ROW][COLUMN], int, int);

// // Get and validate if the number is a valid integer (Inspired in camilo's code in the calculator program, presented during the class)
// int get_validate_integer(int, int);


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

            printf("  1 - Player X vs Player O\n");
            printf("  2 - Player X vs Machine O\n");
            printf("  3 - Machine X vs Machine O\n");
            printf("  4 - QUIT\n\n\n");

            printf("Make your choice (1 - 4) : ");
            scanf(" %d", &choice);
            fflush(stdin);
            
            if(choice < 1 || choice > 4){
                printf("\nInvalid choice. Choice should be between 1 - 4.\n");
                choice = -1;
                sleep(2);
                system("cls");
            }

        }while(choice < 1 || choice > 4);

        switch(choice){
            case 1:
                do{
                    system("cls");

                    printf("\t\t\t      TIC-TAC-TOE GAME\n");
                    printf("\t\t\t   Player X vs Player O\n");
                    printf("\t\t\t --------------------------\n\n");

                    initialize_reset_tic_tac_toe(tic_tac_toe);

                    printf_tic_tac_toe(tic_tac_toe);

                    play_game(tic_tac_toe, choice);

                    repeat_operation = validate_repeat_operation(choice);

                }while(repeat_operation == 'y');

                break;

            case 2:
                do{
                    system("cls");

                    printf("\t\t\t      TIC-TAC-TOE GAME\n");
                    printf("\t\t\t   Player X vs Machine O\n");
                    printf("\t\t\t --------------------------\n\n");

                    initialize_reset_tic_tac_toe(tic_tac_toe);

                    printf_tic_tac_toe(tic_tac_toe);

                    play_game(tic_tac_toe, choice);

                    repeat_operation = validate_repeat_operation(choice);

                }while(repeat_operation == 'y');

                break;

            case 3:
                do{
                    system("cls");

                    printf("\t\t\t      TIC-TAC-TOE GAME\n");
                    printf("\t\t\t   Machine X vs Machine O\n");
                    printf("\t\t\t --------------------------\n\n");

                    initialize_reset_tic_tac_toe(tic_tac_toe);

                    printf_tic_tac_toe(tic_tac_toe);

                    play_game(tic_tac_toe, choice);

                    repeat_operation = validate_repeat_operation(choice);

                }while(repeat_operation == 'y');

                break;

            case 4:
                printf("\nQuitting...");
                sleep(2);
                system("cls");
                exit(0);

            default:
                printf("Operation not found. Please try to enter the operation again.\n");
        }

    }while(choice != 4);

    return 0;

}

// Fuction Definition

// Validate repeat opetation
char validate_repeat_operation(int choice){

    char repeat_operation;

    do{
        if(choice == 1){
            printf("\nDo you want to play again Player X vs Player O ? (y/n) : ");
        }else if(choice == 2){
            printf("\nDo you want to play again Player X vs Machine O ? (y/n) : ");
        }else if(choice == 3){
            printf("\nDo you want to play again Machine X vs Machine O ? (y/n) : ");
        }
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

    int num_1_ascii = 49; // value of 1 (ascii = 49) in the ascii table and increment until read all the matrix 9 times (ascii = 57) 

    for(int i = 0 ; i < ROW ; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            tic_tac_toe[i][j] = num_1_ascii;
            num_1_ascii++;
        }
    }
}

// Play the game Passing a Matrix
void play_game(char tic_tac_toe[ROW][COLUMN], int choice){

    bool hasWinner = false;
    bool isValidRound = false;
    int player_movement_row, player_movement_column;
    char player_movement_choice;
    // int player = PLAYER_X;
    char player = PLAYER_X;
    int count_movements = 1;
    int count_movements_x = 0;
    int count_movements_o = 0;
    int machine_number;

    // initialize_reset_tic_tac_toe_matrix(tic_tac_toe_m);

    // printf_tic_tac_toe_matrix(tic_tac_toe_m);

    while(hasWinner == false && count_movements <= ROW * COLUMN){
        
        isValidRound = false;
        
        while(isValidRound == false){
            
            do{
                
                if(choice == 1 || (choice == 2 && player == PLAYER_X)){
                    printf("\nPlayer %c Movement: Please enter your movement (1 - 9): ", player);
                    // scanf("%d%d", &player_movement_row, &player_movement_column);
                    scanf("%c", &player_movement_choice);
                    fflush(stdin);
                }else{ // ((choice == 2 && player == PLAYER_O) || choice == 3){
                    printf("\nMachine %c time...\n", player);
                    sleep(2);
                    machine: // label to be used in the goto to enter again the position
                    machine_number = (rand() % 9) + 1;
                    player_movement_choice = machine_number + '0';
                    // switch(machine_number){
                    //     case 1:
                    //         player_movement_choice = '1';
                    //         break;
                    //     case 2:
                    //         player_movement_choice = '2';
                    //         break;
                    //     case 3:
                    //         player_movement_choice = '3';
                    //         break;
                    //     case 4:
                    //         player_movement_choice = '4';
                    //         break;
                    //     case 5:
                    //         player_movement_choice = '5';
                    //         break;
                    //     case 6:
                    //         player_movement_choice = '6';
                    //         break;
                    //     case 7:
                    //         player_movement_choice = '7';
                    //         break;
                    //     case 8:
                    //         player_movement_choice = '8';
                    //         break;
                    //     case 9:
                    //         player_movement_choice = '9';
                    //         break;
                    //     default:
                    //         printf("Invalid movement!");
                    // }
                    // player_movement_choice = (char)(rand() % 9) + 1;

                }
            }while(player_movement_choice < '1' || player_movement_choice > '9');
            // }while(player_movement_row < 0 || player_movement_row > ROW - 1 || player_movement_column < 0 || player_movement_column > COLUMN - 1);
                
            switch(player_movement_choice){
                case '1':
                    player_movement_row = 0;
                    player_movement_column = 0;
                    break;
                case '2':
                    player_movement_row = 0;
                    player_movement_column = 1;
                    break;
                case '3':
                    player_movement_row = 0;
                    player_movement_column = 2;
                    break;
                case '4':
                    player_movement_row = 1;
                    player_movement_column = 0;
                    break;
                case '5':
                    player_movement_row = 1;
                    player_movement_column = 1;
                    break;
                case '6':
                    player_movement_row = 1;
                    player_movement_column = 2;
                    break;
                case '7':
                    player_movement_row = 2;
                    player_movement_column = 0;
                    break;
                case '8':
                    player_movement_row = 2;
                    player_movement_column = 1;
                    break;
                case '9':
                    player_movement_row = 2;
                    player_movement_column = 2;
                    break;
                default:
                    printf("Invalid movement!");
            }

            // if(tic_tac_toe[player_movement_row][player_movement_column] != ' '){
            if(tic_tac_toe[player_movement_row][player_movement_column] < '1' || tic_tac_toe[player_movement_row][player_movement_column] > '9'){
                if(choice == 1 || (choice == 2 && player == PLAYER_X)){
                    printf("\nMoviment already made. Please choose another movement.\n");
                }else{
                    goto machine;
                }
            }else{
                
                if(player == PLAYER_X){
                    tic_tac_toe[player_movement_row][player_movement_column] = 'X';
                    
                    count_movements_x++;

                    if(count_movements_x >= ROW){
                        hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
                    }
                    
                    if(!hasWinner){
                        player = PLAYER_O;
                    }
                }else{
                    tic_tac_toe[player_movement_row][player_movement_column] = 'O';

                    count_movements_o++;

                    if(count_movements_o >= ROW){ // Row or columns (3). At least 3 movement to check if the player O is the winner
                        hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
                    }

                    if(!hasWinner){
                        player = PLAYER_X;
                    }
                }
                count_movements++;
                isValidRound = true;
            }
        }

        system("cls");

        printf("\t\t\t      TIC-TAC-TOE GAME\n");
        if(choice == 1){
            printf("\t\t\t   Player X vs Player O\n");
        }else if(choice == 2){
            printf("\t\t\t   Player X vs Machine O\n");
        }else if(choice == 3){
            printf("\t\t\t   Machine X vs Machine O\n");
        }
        printf("\t\t\t --------------------------\n\n");

        printf_tic_tac_toe(tic_tac_toe);
    }

    if(hasWinner){
        if(choice == 1){
            printf("\nPlayer %c wins!\n", player);
        }else if(choice == 2){
            player == PLAYER_X ? printf("\nPlayer %c wins!\n", player) : printf("\nMachine %c wins!\n", player);
            // if(player = PLAYER_X){
            //     printf("\nPlayer %c wins!\n", player);
            // }else{
            //     printf("\nMachine %c wins!\n", player);
            // }
        }else if(choice == 3){
            printf("\nMachine %c wins!\n", player);
        }

    }else{
        printf("\nDraw. No Winners!\n");
    }

}

// Print Tic-Toc-Toe Passing a Matrix
void printf_tic_tac_toe(char tic_tac_toe[ROW][COLUMN]){
    
    printf("\n");

    for(int i = 0 ; i < ROW ; i++){
        for(int j = 0 ; j < COLUMN ; j++){
            if(j > 0){
                printf("|  ");
            }else{
                printf("  ");
            }
            printf("%c", tic_tac_toe[i][j]);
            printf("  ");
        }
        if(i != ROW - 1){
            printf("\n");
            printf("_____|_____|_____");
            printf("\n");
        }else{
            printf("\n");
            printf("     |     |     ");
            printf("\n");
        }
    }

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

// // Get and validate if the number is a valid integer (Inspired in camilo's code in the calculator program, presented during the class)
// int get_validate_integer(int min, int limit){

//     int number = false;
//     int valid;
//     bool error = true;

//     do{
//         valid = scanf("%d", &number);
//         getchar();

//         if(valid != 0 && number >= min && number <= limit){
//             error = false;
//         }else{
//             printf("Please enter a valid number between 1 - 100: ");
//         }

//     }while(error);

//     printf("\n");

//     return number;
// }

    