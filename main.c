//  @see: https://www.facebook.com/groups/cprogramming123/posts/5703993666355550/
//  @author: Bishnu Chalise - https://www.facebook.com/groups/133000920121547/user/100021969948366

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//  MARK: - Definitions
#define NUM_ROWS 3
#define NUM_COLS 5
#define NUM_CELLS 9

#define cint(n) n-'0'

void instruction(void);
void initialize_attrs(void);
void display_board(void);
void initialize_board(void);
int * allocate_position(char ch);
bool is_valid_pos(int row, int col);
void ai_play(void);
void play(void);
bool cmp_cell_r(int r, int c1, int c2, int c3);
bool cmp_cell_c(int c, int r1, int r2, int r3);
bool cmp_cell_diag(void);
void check_win_status(void);

//  MARK: - Implimentation
static
char board[NUM_ROWS][NUM_COLS] = {
  { '_', '|', '_', '|', '_', },
  { '_', '|', '_', '|', '_', },
  { ' ', '|', ' ', '|', ' ', },
};

static
char ch;

static
int space, player_score, ai_score, ai_win_count, player_win_count;

/*
 *  MARK:  main()
 */
int main() {
  srand((unsigned) time(NULL));
  instruction();
  play();
  display_board();
  return 0;
}

/*
 *  MARK:  instruction()
 */
void instruction(void) {
  printf("%60s","Enter respective numbers to fill....\n");

  char board_temp[NUM_ROWS][NUM_COLS] = {
    { '1', '|', '2', '|', '3', },
    { '4', '|', '5', '|', '6', },
    { '7', '|', '8', '|', '9', },
  };

  for (int i = 0; i < NUM_ROWS; i++) {
    printf("%35s", " ");
    for (int j = 0; j < NUM_COLS; j++) {
      printf("%c", board_temp[i][j]);
    }
    putchar('\n');
  }
  printf("\n\n");
}

/*
 *  MARK:  initialize_board()
 */
void initialize_board(void) {
  int i, j;
  for (i = 0; i < NUM_ROWS - 1; i++) {
    for (j = 0; j < NUM_COLS; j++) {
      if (j % 2 == 0) {
        board[i][j] = '_';
      }
      else {
        board[i][j] = '|';
      }
    }
  }
  board[2][0] = ' ';
  board[2][2] = ' ';
  board[2][4] = ' ';
}

/*
 *  MARK:  initialize_attrs()
 */
void initialize_attrs(void) {
  space = 8;
  player_score = ai_score = ai_win_count = player_win_count = 0;
}

/*
 *  MARK:  display_board()
 */
void display_board(void) {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      printf("%c", board[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
}

/*
 *  MARK:  allocate_position()
 */
int * allocate_position(char ch) {
  static int position[2];
  int row, col;

  switch(ch) {
    case '1':
    case '2':
    case '3':
      row = 0; col = 2*(ch-'1');
      break;

    case '4':
    case '5':
    case '6':
      row = 1; col = 2*(ch-'4');
      break;

    case '7':
    case '8':
    case '9':
      row = 2; col = 2*(ch-'7');
      break;
  }

  position[0] = row;
  position[1] = col;

  return position;
}

/*
 *  MARK:  is_valid_pos()
 */
bool is_valid_pos(int row, int col) {
  if (board[row][col] == '_' || board[row][col] == ' ') {
    return true;
  }
  return false;
}

/*
 *  MARK:  ai_play()
 */
void ai_play(void) {
  char avilable_moves[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', };
  char move = avilable_moves[rand() % NUM_CELLS];
  int * pos = allocate_position(move);
  int row = pos[0];
  int col = pos[1];

  while (!is_valid_pos(row, col) && space >= 0) {
    move = avilable_moves[rand() % NUM_CELLS];
    pos  = allocate_position(move);
    row = pos[0];
    col = pos[1];
  }

  board[row][col] = 'X';
  space--;

  printf("AI play: \n");
  display_board();
}

/*
 *  MARK:  play()
 */
void play(void) {
  initialize_attrs();
  initialize_board();
  int row, col, * pos;
  int src;

  while (space >= 0) {
    printf("your play: ");
    src = scanf("%c", &ch);
    getchar();
    if (ch - '0' >= 1 && ch - '0' <= 9) {
      pos = allocate_position(ch);
      row = pos[0];
      col = pos[1];
      if (is_valid_pos(row, col)) {
        board[row][col] = 'O';
        display_board();
        space--;
      }
      ai_play();
      check_win_status();
    }
    else {
      printf("%c is invalid entry..\n", ch);
    }
  }
}

/*
 *  MARK:  cmp_cell_r()
 */
bool cmp_cell_r(int r, int c1, int c2, int c3) {
  return (board[r][c1] == board[r][c2] &&
          board[r][c2] == board[r][c3]);
}

/*
 *  MARK:  cmp_cell_c()
 */
bool cmp_cell_c(int c, int r1, int r2, int r3) {
  return (board[r1][c] == board[r2][c] &&
          board[r2][c] == board[r3][c]);
}

/*
 *  MARK:  cmp_cell_diag()
 */
bool cmp_cell_diag(void) {
  return (
         (board[0][0] == board[1][2] &&
          board[1][2] == board[2][4]) ||
         (board[0][4] == board[1][2] &&
          board[1][2] == board[2][0])
         );
}

/*
 *  MARK:  check_win_status()
 */
void check_win_status(void) {
  int src;
  char choice;
  [[maybe_unused]] int row;
  [[maybe_unused]] int col;
  char winner = ' ';

  if (cmp_cell_r(0, 0, 2, 4)) {
    winner = board[0][0];
  }
  else if (cmp_cell_r(1, 0, 2, 4)) {
    winner = board[1][0];
  }
  else if (cmp_cell_r(2, 0, 2, 4)) {
    winner = board[2][2];
  }
  else if (cmp_cell_c(0, 0, 1, 2)) {
    winner = board[0][0];
  }
  else if (cmp_cell_c(2, 0, 1, 2)) {
    winner = board[0][2];
  }
  else if (cmp_cell_c(4, 0, 1, 2)) {
    winner = board[0][4];
  }
  else if (cmp_cell_diag()) {
    winner = board[1][2];
  }

  if (winner == 'X') {
    printf("AI won!");
    printf("Do you want to continue (y/n)");
    src = scanf("%c", &choice);
    getchar();
    if (toupper(choice) == 'Y') {
      play();
    }
    else {
      exit(EXIT_SUCCESS);
    }
  }
  else if (winner == 'O') {
    printf("Player won\n");
    printf("Do you want to continue (y/n)");
    src = scanf("%c", &choice);
    getchar();
    if (toupper(choice) == 'Y') {
      play();
    }
    else {
      exit(EXIT_SUCCESS);
    }
  }
}
