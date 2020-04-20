#pragma once
#include "../src/action.h"

int check_snake(chrpos* snake, chrpos* snake2, int len);
void move_snake(chrpos* p1_snake, chrpos* p2_snake, int len1, int len2);
void tail_n8(int* total1, int* total2, int* dwID);