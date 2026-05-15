#include <stdio.h>
#include <string.h>

/*
    -[GRID LAYOUT]-
     ╭───┬───┬───╮
     │ O │ X │ O │
     ├───┼───┼───┤
     │ X │ O │ X │
     ├───┼───┼───┤
     │ 7 │ 8 │ O │
     ╰───┴───┴───╯
    (game example)
*/


// aesthetic things
void prompt(){
  printf("\e[32m");
  printf(">> ");
  printf("\e[0m");
}

void Player1(char* str){
  printf("\e[33m");
  printf("%s", str);
  printf("\e[0m");
}

void Player2(char* str){
  printf("\e[34m");
  printf("%s", str);
  printf("\e[0m");
}

void EmptySlot(char symbol){
  printf("\e[37m");
  printf("%c", symbol);
  printf("\e[0m");
}

void PrintError(char *str){
  printf("\e[31m");
  printf("%s", str);
  printf("\e[0m");
}
// END aesthetic

int GetInt(){
  int check, num;

  do{
    prompt();
    check = scanf("%d", &num);
    // clear keyboard buffer
    while(getchar() != '\n');

    if (check != 1)
      PrintError("Not an integer!\n");
  } while(check != 1);

  return num;
}

int GetQuadrant(){
  int quadrant;
  do{
    quadrant = GetInt();
    if(quadrant < 1 || quadrant > 9){
      PrintError("Not a valid quadrant!\n");
    }
  } while(quadrant < 1 || quadrant > 9);

  return quadrant;
}

void PrintSymbol(char symbol){
  if (symbol == 'X'){
    Player1("X");
  }
  else if(symbol == 'O'){
    Player2("O");
  }
  else{
    EmptySlot(symbol);
  }
}

void PrintGrid(char grid[3][3]){
  printf("╭───┬───┬───╮\n");
  printf("│ ");
  PrintSymbol(grid[0][0]);
  printf(" │ ");
  PrintSymbol(grid[0][1]);
  printf(" │ ");
  PrintSymbol(grid[0][2]);
  printf(" │\n");
  printf("├───┼───┼───┤\n");
  printf("│ ");
  PrintSymbol(grid[1][0]);
  printf(" │ ");
  PrintSymbol(grid[1][1]);
  printf(" │ ");
  PrintSymbol(grid[1][2]);
  printf(" │\n");
  printf("├───┼───┼───┤\n");
  printf("│ ");
  PrintSymbol(grid[2][0]);
  printf(" │ ");
  PrintSymbol(grid[2][1]);
  printf(" │ ");
  PrintSymbol(grid[2][2]);
  printf(" │\n");
  printf("╰───┴───┴───╯");
}

int CheckWin(char grid[3][3]){
  // to win, variable must be 0
  int i;
  // rows and columns
  for(i = 0; i < 3; i++){
    if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]){
      return 0;
    }
    else if(grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]){
      return 0;
    }
  }
  // diagonals
  if((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) || (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])){
    return 0;
  }
  return 1;
}

int main(int argc, char* argv[]){
  // help flag
  if(strcmp(argv[argc-1], "-h") == 0 || strcmp(argv[argc-1], "--help") == 0){
      printf("\n-[HOW TO PLAY]-\n");
      printf("You are given a 3x3 grid with numbered quadrant where you can place your symbol.");
      printf("Player 1 is the orange 'X' while Player 2 is the blue 'O'.\n");
      printf("First one to fill a row, column or diagonal with their symbol wins.\n");
      return 0;
  }
  else if(argc > 1){
    PrintError("Not a valid command! Run without flags or with -h / --help\n");
    return 1;
  }

  // counter
  int i, j, turn;
  // main
  int quadrant, width, height;
  char grid[3][3];
  char symbol;
  // fills grid with the quadrant numbers
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      // ascii 48 = number 0
      grid[i][j] = 3*i+j+49;
    }
  }

  for(turn = 0; turn < 9; turn++){
    PrintGrid(grid);
    printf("\nTurn: ");
    if (turn % 2 == 0){
      symbol = 'X';
      Player1("Player 1\n");
    }
    else{
      symbol = 'O';
      Player2("Player 2\n");
    }

    do{
      quadrant = GetQuadrant();
      height = (quadrant-1)%3;
      width = (quadrant-1)/3;
      if (grid[width][height] < '1' || grid[width][height] > '9'){
        PrintError("That space is taken!\n");
      }
    } while(grid[width][height] < '1' || grid[width][height] > '9');

    grid[width][height] = symbol;
    printf("\n");

    // if there's a win, turn is set to 10 to indicate exit without a tie (turn = 9 is a tie)
    if(CheckWin(grid) == 0){
      turn = 10;
    }
  }

  PrintGrid(grid);
  printf("\n");
  if(turn > 9){
    if(symbol == 'X'){
      Player1("Player 1 ");
    }
    else {
      Player2("Player 2! ");
    }
    printf("wins!\n");
  }
  
  else{
    printf("Oh! It's a tie!\n");
  }

  return 0;
}
