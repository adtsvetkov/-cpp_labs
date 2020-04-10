#pragma once

#define COLOR_PAR 3
#define MAX_LOADSTRING 100
#define B_SIZE 50
#define B_Y 17
#define W_X 974
#define W_Y 367
void SystemInit(const char* file_name);
int  SystemUpdate(HWND hWnd, UINT message, WPARAM wParam, char * name);
void SystemClose();