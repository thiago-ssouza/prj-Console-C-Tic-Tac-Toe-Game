/******************************************************************************
thiago.soares_de_souza @ lcieducation.net
ap1, Tic-Tac-Toe project
winter 2022 LaSalle College

Instructions: 

Do a tic tac toe game

#10. [TIC TAC TOE]

Write a program that allows a user to play tic tac toe. The program should ask for moves alternating between player X and player O. 
Alternatively, the second player can be the machine, or the machine can play against itself. This will require the use of the built-in 
function random or your own customized version. The program displays the game positions (1-9) and when a player selects a position, their 
move is entered, and the new board configuration is displayed. The board on the left is the original board. The board on the right shows 
the configuration after 4 moves.

     1    |     2    |     3                   X    |     X    |     O
          |          |                              |          |
__________|__________|__________          __________|__________|__________
     4    |     5    |     6                   4    |     5    |     6    
          |          |                              |          |
__________|__________|__________          __________|__________|__________
     7    |     8    |     9                   O    |     8    |     9      
          |          |                              |          |  
          |          |                              |          |  

The game ends when a player has 3 Xs or 3 Os spanning across the board (horizontally, vertically, or diagonally), or there are no more 
moves that can be made. When the game is over, ask the player if he/she would like to play again. You will need multiple functions. 
Can you identify them first?


******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

// #define ROW 10
// #define COLUMN 10
#define PLAYER_X 'X'
#define PLAYER_O 'O'
// #define MINIMUM 1
// #define LIMIT (ROW * COLUMN)
#define MAXIMUM_SIZE 10
#define MINIMUM_SIZE 3

int row;
int column;

int player_x_score = 0;
int player_o_score = 0;

int count_play_games = 0;

bool wasPlayedX = false;
bool wasPlayedO = false;

int idx_i_x_played = -1;
int idx_j_x_played = -1;
int idx_i_o_played = -1;
int idx_j_o_played = -1;



// int row = 0;
// int column = 0;

// Fuction Declaration

// Validate repeat opetation
char validate_repeat_operation(int);

// Initialize reset Tic-Tac-Toe Passing a Matrix
void initialize_reset_tic_tac_toe(char[row][column]);

// Play the game Passing a Matrix
void play_game(char[row][column], int);

// Print Tic-Toc-Toe Passing a Matrix
void printf_tic_tac_toe(char[row][column]);

// Check with there is a winner Passing matrix and last moviments
bool check_winner(char[row][column], int, int);

// Print the title of the user choice (Player vs Player, Player vs Machine, Machine vs Machine)
void print_title_user_choice(int);

// Get and validate if the number is a valid integer (Inspired in camilo's code in the calculator program, presented during the class)
int get_validate_integer(int, int);

// Choose / Change Tic Tac Toe size
void change_size_tic_tac_toe();


int main(){

    int choice = -1;
    char repeat_operation = '\n';

    // int player_x_score = 0;
    // int player_o_score = 0;

    // printf("Please enter");


    // int const ROW = 3;
    // int const COLUMN = 3;

    // printf("\t\t\t      TIC-TAC-TOE GAME\n");
    // printf("\t\t\t Main Menu Operators Choice\n");
    // printf("\t\t\t----------------------------\n\n");

    // printf("Please enter the size of the Tic Tac Toe that you wanna play (%d - (%dx%d), %d - (%dx%d), ..., %d - (%dx%d)): ",MINIMUM_SIZE, MINIMUM_SIZE, MINIMUM_SIZE, MINIMUM_SIZE + 1, MINIMUM_SIZE + 1, MINIMUM_SIZE + 1, MAXIMUM_SIZE, MAXIMUM_SIZE, MAXIMUM_SIZE);
    // row = get_validate_integer(MINIMUM_SIZE, MAXIMUM_SIZE);
    // column = row;

    // row = 3;
    // column = 3;

    change_size_tic_tac_toe();

    char tic_tac_toe[row][column];    
    
    do{
        system("cls");
        choice = -1;

        player_x_score = 0;
        player_o_score = 0;
        count_play_games = 0;

        do{
            printf("\t\t\t      TIC-TAC-TOE GAME\n");
            printf("\t\t\t Main Menu Operators Choice\n");
            printf("\t\t\t----------------------------\n\n");

            printf("  1 - Player X vs Player O\n");
            printf("  2 - Player X vs Machine O\n");
            printf("  3 - Machine X vs Machine O\n");
            printf("  4 - Change Tic Tac Toe size\n");
            printf("  5 - QUIT\n\n\n");

            printf("Make your choice (1 - 5) : ");
            scanf(" %d", &choice);
            fflush(stdin);
            
            if(choice < 1 || choice > 5){
                printf("\nInvalid choice. Choice should be between 1 - 5.\n");
                choice = -1;
                sleep(2);
                system("cls");
            }

        }while(choice < 1 || choice > 5);

        switch(choice){
            case 1:
            case 2:
            case 3:
                do{
                    system("cls");

                    printf("\t\t\t      TIC-TAC-TOE GAME\n");
                    // if(choice == 1){
                    //     printf("\t\t\t   Player X vs Player O\n");
                    // }else if(choice == 2){
                    //     printf("\t\t\t   Player X vs Machine O\n");
                    // }else if(choice == 3){
                    //     printf("\t\t\t   Machine X vs Machine O\n");
                    // }

                    print_title_user_choice(choice);

                    printf("\t\t\t -----------------------------\n\n");

                    initialize_reset_tic_tac_toe(tic_tac_toe);

                    printf_tic_tac_toe(tic_tac_toe);

                    play_game(tic_tac_toe, choice);

                    repeat_operation = validate_repeat_operation(choice);

                }while(repeat_operation == 'y');

                break;

            case 4:
                system("cls");

                change_size_tic_tac_toe();

                // printf("\nSize changed to: %d - (%dx%d)\n", row, row, column);
                
                // sleep(2);
                
                break;
            
            case 5:
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

// // Initialize reset Tic-Tac-Toe Passing a Matrix
// void initialize_reset_tic_tac_toe(char tic_tac_toe[ROW][COLUMN]){

//     int num_1_ascii = 49; // value of 1 (ascii = 49) in the ascii table and increment until read all the matrix 9 times (ascii = 57) 

//     for(int i = 0 ; i < ROW ; i++){
//         for(int j = 0 ; j < COLUMN ; j++){
//             tic_tac_toe[i][j] = num_1_ascii;
//             num_1_ascii++;
//         }
//     }
// }

// Initialize reset Tic-Tac-Toe Passing a Matrix
void initialize_reset_tic_tac_toe(char tic_tac_toe[row][column]){

    // int num_1_ascii = 49; // value of 1 (ascii = 49) in the ascii table and increment until read all the matrix 9 times (ascii = 57)

    wasPlayedX = false;
    wasPlayedO = false;

    idx_i_x_played = -1;
    idx_j_x_played = -1;
    idx_i_o_played = -1;
    idx_j_o_played = -1;

    int num = 1;

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            if(num == PLAYER_X){
                idx_i_x_played = i;
                idx_j_x_played = j;
            }
            if(num == PLAYER_O){
                idx_i_o_played = i;
                idx_j_o_played = j;
            }
            tic_tac_toe[i][j] = num;
            num++;
        }
    }

    // printf("index_x i = %d\n", idx_i_x_played);
    // printf("index_x j = %d\n", idx_j_x_played);
    // printf("index_o i = %d\n", idx_i_o_played);
    // printf("index_o j = %d\n", idx_j_o_played);
    
}

// Play the game Passing a Matrix
// void play_game(char tic_tac_toe[ROW][COLUMN], int choice){

//     bool hasWinner = false;
//     bool isValidRound = false;
//     int player_movement_row, player_movement_column;
//     char player_movement_choice;
//     // int player = PLAYER_X;
//     char player = PLAYER_X;
//     int count_movements = 1;
//     int count_movements_x = 0;
//     int count_movements_o = 0;
//     int machine_number;

//     // initialize_reset_tic_tac_toe_matrix(tic_tac_toe_m);

//     // printf_tic_tac_toe_matrix(tic_tac_toe_m);

//     while(hasWinner == false && count_movements <= ROW * COLUMN){
        
//         isValidRound = false;
        
//         while(isValidRound == false){
            
//             do{
                
//                 if(choice == 1 || (choice == 2 && player == PLAYER_X)){
//                     printf("\nPlayer %c Movement: Please enter your movement (1 - 9): ", player);
//                     // scanf("%d%d", &player_movement_row, &player_movement_column);
//                     scanf("%c", &player_movement_choice);
//                     fflush(stdin);
//                 }else{ // ((choice == 2 && player == PLAYER_O) || choice == 3){
//                     printf("\nMachine %c time...\n", player);
//                     // sleep(2);
//                     sleep(1);
//                     machine: // label to be used in the goto to enter again the position
//                     machine_number = (rand() % 9) + 1;
//                     // printf("%d\n", machine_number);
//                     // sleep(2);
//                     player_movement_choice = machine_number + '0'; // Convert the int into char
//                     // printf("\n%d\n", player_movement_choice);
//                     // switch(machine_number){
//                     //     case 1:
//                     //         player_movement_choice = '1';
//                     //         break;
//                     //     case 2:
//                     //         player_movement_choice = '2';
//                     //         break;
//                     //     case 3:
//                     //         player_movement_choice = '3';
//                     //         break;
//                     //     case 4:
//                     //         player_movement_choice = '4';
//                     //         break;
//                     //     case 5:
//                     //         player_movement_choice = '5';
//                     //         break;
//                     //     case 6:
//                     //         player_movement_choice = '6';
//                     //         break;
//                     //     case 7:
//                     //         player_movement_choice = '7';
//                     //         break;
//                     //     case 8:
//                     //         player_movement_choice = '8';
//                     //         break;
//                     //     case 9:
//                     //         player_movement_choice = '9';
//                     //         break;
//                     //     default:
//                     //         printf("Invalid movement!");
//                     // }
//                     // player_movement_choice = (char)(rand() % 9) + 1;

//                 }
//             }while(player_movement_choice < '1' || player_movement_choice > '9');
//             // }while(player_movement_row < 0 || player_movement_row > ROW - 1 || player_movement_column < 0 || player_movement_column > COLUMN - 1);
                
//             switch(player_movement_choice){
//                 case '1':
//                     player_movement_row = 0;
//                     player_movement_column = 0;
//                     break;
//                 case '2':
//                     player_movement_row = 0;
//                     player_movement_column = 1;
//                     break;
//                 case '3':
//                     player_movement_row = 0;
//                     player_movement_column = 2;
//                     break;
//                 case '4':
//                     player_movement_row = 1;
//                     player_movement_column = 0;
//                     break;
//                 case '5':
//                     player_movement_row = 1;
//                     player_movement_column = 1;
//                     break;
//                 case '6':
//                     player_movement_row = 1;
//                     player_movement_column = 2;
//                     break;
//                 case '7':
//                     player_movement_row = 2;
//                     player_movement_column = 0;
//                     break;
//                 case '8':
//                     player_movement_row = 2;
//                     player_movement_column = 1;
//                     break;
//                 case '9':
//                     player_movement_row = 2;
//                     player_movement_column = 2;
//                     break;
//                 default:
//                     printf("Invalid movement!");
//             }

//             // if(tic_tac_toe[player_movement_row][player_movement_column] != ' '){
//             if(tic_tac_toe[player_movement_row][player_movement_column] < '1' || tic_tac_toe[player_movement_row][player_movement_column] > '9'){
//                 if(choice == 1 || (choice == 2 && player == PLAYER_X)){
//                     printf("\nMoviment already made. Please choose another movement.\n");
//                 }else{
//                     goto machine;
//                 }
//             }else{
                
//                 if(player == PLAYER_X){
                    
//                     if((choice == 2 && player == PLAYER_O) || choice == 3){
//                         printf("%c\n", player_movement_choice);
//                         // sleep(2);
//                     }
//                     sleep(1);

//                     tic_tac_toe[player_movement_row][player_movement_column] = 'X';
                    
//                     count_movements_x++;

//                     if(count_movements_x >= ROW){
//                         hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
//                     }
                    
//                     if(!hasWinner){
//                         player = PLAYER_O;
//                     }
//                 }else{
                    
//                     if((choice == 2 && player == PLAYER_O) || choice == 3){
//                         printf("%c\n", player_movement_choice);
//                         // sleep(2);
//                     }
//                     sleep(1);

//                     tic_tac_toe[player_movement_row][player_movement_column] = 'O';

//                     count_movements_o++;

//                     if(count_movements_o >= ROW){ // Row or columns (3). At least 3 movement to check if the player O is the winner
//                         hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
//                     }

//                     if(!hasWinner){
//                         player = PLAYER_X;
//                     }
//                 }
//                 count_movements++;
//                 isValidRound = true;
//             }
//         }

//         if(hasWinner){
//             if(player == PLAYER_X){
//                 player_x_score++;
//             }else{
//                 player_0_score++;
//             }
//         }

//         system("cls");

//         printf("\t\t\t      TIC-TAC-TOE GAME\n");
//         // if(choice == 1){
//         //     printf("\t\t\t   Player X vs Player O\n");
//         // }else if(choice == 2){
//         //     printf("\t\t\t   Player X vs Machine O\n");
//         // }else if(choice == 3){
//         //     printf("\t\t\t   Machine X vs Machine O\n");
//         // }
//         print_title_user_choice(choice);
//         printf("\t\t\t -----------------------------\n\n");

//         printf_tic_tac_toe(tic_tac_toe);
//     }

//     if(hasWinner){
//         if(choice == 1){
//             printf("\nPlayer %c wins!\n", player);
//             // if(player == PLAYER_X){
//             //     player_x_score++;
//             // }else{
//             //     player_0_score++;
//             // }
//         }else if(choice == 2){
//             player == PLAYER_X ? printf("\nPlayer %c wins!\n", player) : printf("\nMachine %c wins!\n", player);
//             // if(player = PLAYER_X){
//             //     printf("\nPlayer %c wins!\n", player);
//             //     player_x_score++;
//             // }else{
//             //     printf("\nMachine %c wins!\n", player);
//             //     player_0_score++;
//             // }
//         }else if(choice == 3){
//             printf("\nMachine %c wins!\n", player);
//             // if(player == PLAYER_X){
//             //     player_x_score++;
//             // }else{
//             //     player_0_score++;
//             // }
//         }

//     }else{
//         printf("\nDraw. No Winners!\n");
//     }

// }

// Play the game Passing a Matrix
void play_game(char tic_tac_toe[row][column], int choice){

    bool hasWinner = false;
    bool isValidRound = false;
    int player_movement_row, player_movement_column;
    char player_movement_choice;
    // int player = PLAYER_X;
    char player = PLAYER_X;
    int count_movements = 0;
    int count_movements_x = 0;
    int count_movements_o = 0;
    int player_number_prompt;
    int count_choice = 0;
    int minimum = 1;
    int limit = row * column;

    // initialize_reset_tic_tac_toe_matrix(tic_tac_toe_m);

    // printf_tic_tac_toe_matrix(tic_tac_toe_m);

    count_play_games++;

    if(count_play_games % 2 == 0){
        player = PLAYER_O;
    }else{
        player = PLAYER_X;
    }

    while(hasWinner == false && count_movements <= (row * column) - 1){
        
        isValidRound = false;

        // count_choice = 0;
        
        while(isValidRound == false){
            
            do{

                if(choice == 1 || (choice == 2 && player == PLAYER_X)){
                    // printf("\nPlayer %c Movement: Please enter your movement (1 - 9): ", player);
                    printf("\nPlayer %c Movement: Please enter your movement (1 - %d): ", player, row * column);

                    // scanf("%d%d", &player_movement_row, &player_movement_column);
                    player_number_prompt = get_validate_integer(minimum, limit);

                    // scanf(" %d", &player_number_prompt);
                    
                    // fflush(stdin);
                    player_movement_choice = player_number_prompt;
                
                }else{ // ((choice == 2 && player == PLAYER_O) || choice == 3){
                    printf("\nMachine %c time...\n", player);
                    // sleep(2);
                    sleep(1);
                    machine: // label to be used in the goto to enter again the position
                    // machine_number = (rand() % 9) + 1;
                    
                    
                    // player_movement_choice = (rand() % 9) + 1;
                    
                    // srand(time(0));
                    
                    player_movement_choice = (rand() % (row * column)) + 1;
                    // player_movement_choice = (rand() % ( ((row * column) - 1) + 1) ) + 1;



                    // printf("%d\n", machine_number);
                    // sleep(2);
                    // player_movement_choice = machine_number + '0'; // Convert the int into char
                    // player_movement_choice = machine_number;
                    // printf("\n%d\n", player_movement_choice);
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
            // }while(player_movement_choice < '1' || player_movement_choice > '9');
            }while(player_movement_choice < 1 || player_movement_choice > row * column);
            // }while(player_movement_row < 0 || player_movement_row > ROW - 1 || player_movement_column < 0 || player_movement_column > COLUMN - 1);
                
            // switch(player_movement_choice){
            //     case '1':
            //         player_movement_row = 0;
            //         player_movement_column = 0;
            //         break;
            //     case '2':
            //         player_movement_row = 0;
            //         player_movement_column = 1;
            //         break;
            //     case '3':
            //         player_movement_row = 0;
            //         player_movement_column = 2;
            //         break;
            //     case '4':
            //         player_movement_row = 1;
            //         player_movement_column = 0;
            //         break;
            //     case '5':
            //         player_movement_row = 1;
            //         player_movement_column = 1;
            //         break;
            //     case '6':
            //         player_movement_row = 1;
            //         player_movement_column = 2;
            //         break;
            //     case '7':
            //         player_movement_row = 2;
            //         player_movement_column = 0;
            //         break;
            //     case '8':
            //         player_movement_row = 2;
            //         player_movement_column = 1;
            //         break;
            //     case '9':
            //         player_movement_row = 2;
            //         player_movement_column = 2;
            //         break;
            //     default:
            //         printf("Invalid movement!");
            // }

            // int cont_test = 0;

            count_choice = 0;

            // printf("CHoice: %d\n", player_movement_choice);

            for(int i = 0 ; i < row ; i++){
                for(int j = 0 ; j < column ; j++){
                    count_choice++;
                    if(count_choice == player_movement_choice){
                        // printf("count_choice: %d\n", count_choice);
                        // printf("count_choice: %d\n", player_movement_choice);
                        player_movement_row = i;
                        player_movement_column = j;
                        break;
                    }
                }
            }

            // printf("player i: %d\n", player_movement_row);
            // printf("player j: %d\n", player_movement_column);

            // cont_test = 0;

            // switch(player_movement_choice){
            //     case 1:
            //         player_movement_row = 0;
            //         player_movement_column = 0;
            //         break;
            //     case 2:
            //         player_movement_row = 0;
            //         player_movement_column = 1;
            //         break;
            //     case 3:
            //         player_movement_row = 0;
            //         player_movement_column = 2;
            //         break;
            //     case 4:
            //         player_movement_row = 1;
            //         player_movement_column = 0;
            //         break;
            //     case 5:
            //         player_movement_row = 1;
            //         player_movement_column = 1;
            //         break;
            //     case 6:
            //         player_movement_row = 1;
            //         player_movement_column = 2;
            //         break;
            //     case 7:
            //         player_movement_row = 2;
            //         player_movement_column = 0;
            //         break;
            //     case 8:
            //         player_movement_row = 2;
            //         player_movement_column = 1;
            //         break;
            //     case 9:
            //         player_movement_row = 2;
            //         player_movement_column = 2;
            //         break;
            //     default:
            //         printf("Invalid movement!");
            // }

            // if(tic_tac_toe[player_movement_row][player_movement_column] != ' '){
            // if(tic_tac_toe[player_movement_row][player_movement_column] < '1' || tic_tac_toe[player_movement_row][player_movement_column] > '9'){
            // if(tic_tac_toe[player_movement_row][player_movement_column] < 1 || tic_tac_toe[player_movement_row][player_movement_column] > ROW * COLUMN){
            // if(tic_tac_toe[player_movement_row][player_movement_column] == 'X'  || tic_tac_toe[player_movement_row][player_movement_column] == 'O'){
            if( (tic_tac_toe[player_movement_row][player_movement_column] == 'X' && (idx_i_x_played != player_movement_row || idx_j_x_played != player_movement_column) ) || (tic_tac_toe[player_movement_row][player_movement_column] == 'O' && (idx_i_o_played != player_movement_row || idx_j_o_played != player_movement_column)) || (tic_tac_toe[player_movement_row][player_movement_column] == 'X' && idx_i_x_played == player_movement_row && idx_j_x_played == player_movement_column  && wasPlayedX == true) || (tic_tac_toe[player_movement_row][player_movement_column] == 'O' && idx_i_o_played == player_movement_row && idx_j_o_played == player_movement_column && wasPlayedO == true)){
                if(choice == 1 || (choice == 2 && player == PLAYER_X)){
                    printf("\nMoviment already made. Please choose another movement.\n");
                }else{
                    // printf("count_movements: %d\n", count_movements);
                    // if(count_movements == (ROW * COLUMN) - 1){
                    //     printf("count_movements: %d\n", count_movements);
                    //     sleep(4);
                    // }
                    goto machine;
                }
            }else{
                
                if(player == PLAYER_X){
                    
                    if(player_movement_choice == PLAYER_X){
                        wasPlayedX = true;
                    }

                    if((choice == 2 && player == PLAYER_O) || choice == 3){
                        // printf("%c\n", player_movement_choice);
                        printf("%d\n", player_movement_choice);
                        // sleep(2);
                    }
                    sleep(1);

                    tic_tac_toe[player_movement_row][player_movement_column] = 'X';
                    
                    count_movements_x++;

                    if(count_movements_x >= row){
                        hasWinner = check_winner(tic_tac_toe, player_movement_row, player_movement_column);
                    }
                    
                    if(!hasWinner){
                        player = PLAYER_O;
                    }
                }else{
                    
                    if(player_movement_choice == PLAYER_O){
                        wasPlayedO = true;
                    }

                    if((choice == 2 && player == PLAYER_O) || choice == 3){
                        // printf("%c\n", player_movement_choice);
                        printf("%d\n", player_movement_choice);
                        // sleep(2);
                    }
                    sleep(1);

                    tic_tac_toe[player_movement_row][player_movement_column] = 'O';

                    count_movements_o++;

                    if(count_movements_o >= column){ // Row or columns (3). At least 3 movement to check if the player O is the winner
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

        if(hasWinner){
            if(player == PLAYER_X){
                player_x_score++;
            }else{
                player_o_score++;
            }
        }

        system("cls");

        printf("\t\t\t      TIC-TAC-TOE GAME\n");
        // if(choice == 1){
        //     printf("\t\t\t   Player X vs Player O\n");
        // }else if(choice == 2){
        //     printf("\t\t\t   Player X vs Machine O\n");
        // }else if(choice == 3){
        //     printf("\t\t\t   Machine X vs Machine O\n");
        // }
        print_title_user_choice(choice);
        printf("\t\t\t -----------------------------\n\n");

        printf_tic_tac_toe(tic_tac_toe);
    }

    // printf("count_movements: %d\n", count_movements);

    if(hasWinner){
        if(choice == 1){
            printf("\nPlayer %c wins!\n", player);
            // if(player == PLAYER_X){
            //     player_x_score++;
            // }else{
            //     player_0_score++;
            // }
        }else if(choice == 2){
            player == PLAYER_X ? printf("\nPlayer %c wins!\n", player) : printf("\nMachine %c wins!\n", player);
            // if(player = PLAYER_X){
            //     printf("\nPlayer %c wins!\n", player);
            //     player_x_score++;
            // }else{
            //     printf("\nMachine %c wins!\n", player);
            //     player_0_score++;
            // }
        }else if(choice == 3){
            printf("\nMachine %c wins!\n", player);
            // if(player == PLAYER_X){
            //     player_x_score++;
            // }else{
            //     player_0_score++;
            // }
        }

    }else{
        printf("\nDraw. No Winners!\n");
    }

}



// // Print Tic-Toc-Toe Passing a Matrix
// void printf_tic_tac_toe(char tic_tac_toe[ROW][COLUMN]){
    
//     printf("\n");

//     for(int i = 0 ; i < ROW ; i++){
//         for(int j = 0 ; j < COLUMN ; j++){
//             if(j > 0){
//                 printf("|  ");
//             }else{
//                 printf("  ");
//             }
//             printf("%c", tic_tac_toe[i][j]);
//             printf("  ");
//         }
//         if(i != ROW - 1){
//             printf("\n");
//             printf("_____|_____|_____");
//             printf("\n");
//         }else{
//             printf("\n");
//             printf("     |     |     ");
//             printf("\n");
//         }
//     }

// }

// Print Tic-Toc-Toe Passing a Matrix
void printf_tic_tac_toe(char tic_tac_toe[row][column]){
    
    // int count = 1;

    printf("\n");

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            
            // if(tic_tac_toe[i][j] != 'X' && tic_tac_toe[i][j] != 'O' && tic_tac_toe[i][j] >= 10){
            // if( ( (tic_tac_toe[i][j] != 'X' && tic_tac_toe[i][j] != 'O') || (tic_tac_toe[i][j] == 'X' && (idx_i_x_played != i || idx_j_x_played != j)) || (tic_tac_toe[i][j] == 'O' && (idx_i_o_played != i || idx_j_o_played != j)) || (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == false) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == false)) && tic_tac_toe[i][j] >= 10){
            if( ( (tic_tac_toe[i][j] != 'X' && tic_tac_toe[i][j] != 'O') || (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == false) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == false)) && tic_tac_toe[i][j] >= 10){
                // if(tic_tac_toe[i][j] == 87){
                //     printf("ENTROU!!!");
                //     sleep(4);
                // }

            // if((tic_tac_toe[i][j] != 'X' || (i != idx_i_x_played && j != idx_j_x_played)) && (tic_tac_toe[i][j] != 'O' || (i != idx_i_o_played && j != idx_j_o_played)) && tic_tac_toe[i][j] >= 10){
            // if((tic_tac_toe[i][j] != 'X' && wasPlayedX != true) && (tic_tac_toe[i][j] != 'O' && wasPlayedO != true) || tic_tac_toe[i][j] >= 10){
            // if((tic_tac_toe[i][j] != 'X' && wasPlayedX == false) || (tic_tac_toe[i][j] != 'O' && wasPlayedO == false) || tic_tac_toe[i][j] >= 10){
                if(j > 0){
                    printf("|  ");
                }else{
                    printf("  ");
                }
            }else{
                if(j > 0){
                    printf("|   ");
                }else{
                    printf("   ");
                }
            }
            // // if(tic_tac_toe[i][j] == 88 || tic_tac_toe[i][j] == 79){
            // if( (tic_tac_toe[i][j] == 'X' && (i == idx_i_x_played && j == idx_j_x_played) ) || tic_tac_toe[i][j] == 'O' && (i == idx_i_o_played && j == idx_j_o_played)){
            // // if( (tic_tac_toe[i][j] == 'X' && wasPlayedX == true) || (tic_tac_toe[i][j] == 'O' && wasPlayedO == true) ){
            //     printf("%c", tic_tac_toe[i][j]);
            // }else if((tic_tac_toe[i][j] == 'X' && (i != idx_i_x_played && j != idx_j_x_played) ) || tic_tac_toe[i][j] == 'O' && (i != idx_i_o_played && j != idx_j_o_played)){
            //     printf("%c", tic_tac_toe[i][j]);
            // }
            // else{
            //     printf("%d", tic_tac_toe[i][j]);
            // }

            // if(tic_tac_toe[i][j] == 88 || tic_tac_toe[i][j] == 79){
            if(  ( (tic_tac_toe[i][j] == 'X' && (idx_i_x_played != i || idx_j_x_played != j)) || (tic_tac_toe[i][j] == 'O'  && (idx_i_o_played != i || idx_j_o_played != j)) ) || ( (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == true) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == true) ) ){
            // if( (tic_tac_toe[i][j] == 'X' && wasPlayedX == true) || (tic_tac_toe[i][j] == 'O' && wasPlayedO == true) ){
                printf("%c", tic_tac_toe[i][j]);
            }else{
                printf("%d", tic_tac_toe[i][j]);
            }
            
            // printf("%c", tic_tac_toe[i][j]);
            printf("  ");
            // count++;
        }
        // if(count > 9){
        if(i != row - 1){
            // printf("\n");
            // printf("          |          |          ");
            // printf("\n");
            // printf("__________|__________|__________");
            // printf("\n");

            // printf("\n");

            // for(int c = 1 ; c <= COLUMN ; c++){
            //     if(c == 1){
            //         printf("          ");
            //     }else{
            //         printf("|          ");
            //     }
            // }
            
            printf("\n");

            for(int c = 1 ; c <= column ; c++){
                if(c == 1){
                    printf("______");
                }else{
                    printf("|______");
                }
            }

            printf("\n");

        }else{
            // printf("\n");
            // printf("          |          |          ");
            // printf("\n");
            // printf("          |          |          ");
            // printf("\n");

            // printf("\n");

            // for(int c = 1 ; c <= COLUMN ; c++){
            //     if(c == 1){
            //         printf("          ");
            //     }else{
            //         printf("|          ");
            //     }
            // }

            printf("\n");

            for(int c = 1 ; c <= column ; c++){
                if(c == 1){
                    printf("      ");
                }else{
                    printf("|      ");
                }
            }

            printf("\n");

        }
        // }else{
        //     if(i != ROW - 1){
        //         printf("\n");
        //         printf("          |          |          ");
        //         printf("\n");
        //         printf("__________|__________|__________");
        //         printf("\n");
        //     }else{
        //         printf("\n");
        //         printf("          |          |          ");
        //         printf("\n");
        //         printf("          |          |          ");
        //         printf("\n");
        //     }
        // }
        
    }

}

// Check with there is a winner Passing matrix and last moviments
bool check_winner(char tic_tac_toe[row][column], int player_movement_row, int player_movement_column){

    int count_x = 0;
    int count_o = 0;

    // verifying row
    for(int i = 0 ; i < row ; i++){
        // if(tic_tac_toe[i][player_movement_column] == 'X'){
        if( (tic_tac_toe[i][player_movement_column] == 'X' && (idx_i_x_played != i || idx_j_x_played != player_movement_column)) || (tic_tac_toe[i][player_movement_column] == 'X' && idx_i_x_played == i && idx_j_x_played == player_movement_column && wasPlayedX == true)){
            count_x++;
        // }else if(tic_tac_toe[i][player_movement_column] == 'O'){
        //     count_o++;
        // }
        }
        // if(tic_tac_toe[i][player_movement_column] == 'O'){
        if( (tic_tac_toe[i][player_movement_column] == 'O' && (idx_i_o_played != i || idx_j_o_played != player_movement_column)) || (tic_tac_toe[i][player_movement_column] == 'O' && idx_i_o_played == i && idx_j_o_played == player_movement_column && wasPlayedO == true)){
            count_o++;
        }
    }
    
    if(count_x == row || count_o == column){
        return true;
    }

    count_x = 0;
    count_o = 0;

    // verifying column
    for(int j = 0 ; j < column ; j++){
        // if(tic_tac_toe[player_movement_row][j] == 'X'){
        if( (tic_tac_toe[player_movement_row][j] == 'X' && (idx_i_x_played != player_movement_row || idx_j_x_played != j)) || (tic_tac_toe[player_movement_row][j] == 'X' && idx_i_x_played == player_movement_row && idx_j_x_played == j && wasPlayedX == true)){
            count_x++;
        // }else if(tic_tac_toe[player_movement_row][j] == 'O'){
        //     count_o++;
        // }
        }
        // if(tic_tac_toe[player_movement_row][j] == 'O'){
        if( (tic_tac_toe[player_movement_row][j] == 'O' && (idx_i_o_played != player_movement_row || idx_j_o_played != j)) || (tic_tac_toe[player_movement_row][j] == 'O' && idx_i_o_played == player_movement_row && idx_j_o_played == j && wasPlayedO == true)){
            count_o++;
        }
    }
    
    if(count_x == row || count_o == column){
        return true;
    }

    count_x = 0;
    count_o = 0;

    // verifying primary diagonal
    for(int i = 0, j = 0 ; i < row ; i++, j++){
        // if(tic_tac_toe[i][j] == 'X'){
        if( (tic_tac_toe[i][j] == 'X' && (idx_i_x_played != i || idx_j_x_played != j)) || (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == true) ){
            count_x++;
        // }else if(tic_tac_toe[i][j] == 'O'){
        //     count_o++;
        // }
        }
        // if(tic_tac_toe[i][j] == 'O'){
        if( (tic_tac_toe[i][j] == 'O' && (idx_i_o_played != i || idx_j_o_played != j)) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == true) ){
            count_o++;
        }
    }
    
    if(count_x == row || count_o == column){
        return true;
    }

    count_x = 0;
    count_o = 0;


    // verifying secundary diagonal
    for(int i = 0, j = column - 1 ; i < row && j >= 0 ; i++, j--){
        // if(tic_tac_toe[i][j] == 'X'){
        if( (tic_tac_toe[i][j] == 'X' && (idx_i_x_played != i || idx_j_x_played != j)) || (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == true) ){
            count_x++;
        // }else if(tic_tac_toe[i][j] == 'O'){
        //     count_o++;
        // }
        }
        // if(tic_tac_toe[i][j] == 'O'){
        if( (tic_tac_toe[i][j] == 'O' && (idx_i_o_played != i || idx_j_o_played != j)) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == true) ){
            count_o++;
        }
    }
    
    if(count_x == row || count_o == column){
        return true;
    }

    return false;

}

// Print the title of the user choice (Player vs Player, Player vs Machine, Machine vs Machine)
void print_title_user_choice(int choice){
    
    if(choice == 1){
        printf("\t\t\t   Player X %d vs %d Player O\n", player_x_score, player_o_score);
    }else if(choice == 2){
        printf("\t\t\t   Player X %d vs %d Machine O\n", player_x_score, player_o_score);
    }else if(choice == 3){
        printf("\t\t\t   Machine X %d vs %d Machine O\n", player_x_score, player_o_score);
    }
}

// Get and validate if the number is a valid integer (Inspired in camilo's code in the calculator program, presented during the class)
int get_validate_integer(int min, int limit){

    int number = false;
    int valid;
    bool error = true;

    do{
        valid = scanf("%d", &number);
        getchar();

        if(valid != 0 && number >= min && number <= limit){
            error = false;
        }else{
            printf("\nPlease enter a valid number between %d - %d: ", min, limit);
        }

    }while(error);

    printf("\n");

    return number;
}

// Choose / Change Tic Tac Toe size
void change_size_tic_tac_toe(){
    printf("\t\t\t      TIC-TAC-TOE GAME\n");
    printf("\t\t\t Main Menu Operators Choice\n");
    printf("\t\t\t----------------------------\n\n");

    printf("Please enter the size of the Tic Tac Toe that you wanna play (%d - (%dx%d), %d - (%dx%d), ..., %d - (%dx%d)): ",MINIMUM_SIZE, MINIMUM_SIZE, MINIMUM_SIZE, MINIMUM_SIZE + 1, MINIMUM_SIZE + 1, MINIMUM_SIZE + 1, MAXIMUM_SIZE, MAXIMUM_SIZE, MAXIMUM_SIZE);
    row = get_validate_integer(MINIMUM_SIZE, MAXIMUM_SIZE);
    column = row;

    printf("\nOption selected: %d - (%dx%d)\n", row, row, column);
                
    sleep(2);
}
