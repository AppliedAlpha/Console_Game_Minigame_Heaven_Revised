#pragma once
#define WIDTH 80
#define HEIGHT 40
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define FUNCTION_KEY -32
#define ESC 27
#define ENTER 13
#define A 65
#define S 83
#define D 68
#define W 87
#define J 74
#define K 75
#define L 76
#define I 73
#define c_black 0
#define c_blue 1
#define c_green 2
#define c_cyan 3
#define c_red 4
#define c_purple 5
#define c_yellow 6
#define c_white 7
#define c_gray 8
#define cc_blue 9
#define cc_green 10
#define cc_cyan 11
#define cc_red 12
#define cc_purple 13
#define cc_yellow 14
#define cc_white 15

void gotoxy(int x, int y);
void tc(int color);

void print_score(int score1, int score2);
void normalbound(int color);
void halfbound(int color, int type);
void border(int y);

void mt_start(int color);
void mt_quit(int color);
void sm_np(int color);
void sm_sp(int color);

void winner(int a, int b);
void print_halfmoon(int a, int b);
void print_Heart(int a);
void remove_Heart(int a);

void p1_win();
void p2_win();
void tie();

void print_bike(int x, int y, int c);
void print_line(int y, int* line, int move);
void print_hand(int x, int y, int rd);