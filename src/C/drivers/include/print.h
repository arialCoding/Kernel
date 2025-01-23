#ifndef PRINT_H
#define PRINT_H

#define VIDEO_MEMORY 0xb8000

#define ROWS 25
#define COLS 80

#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void kprint_backspace();

#endif // PRINT_H