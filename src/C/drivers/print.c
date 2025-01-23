#include "print.h"
#include "ports.h"

#include "mem.h"

//**************HELPERS***************//
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

//********IMPLIMENTATION**********//
void clear_screen()
{
    int screenSize = ROWS*COLS;
    char* VGA = (char*)VIDEO_MEMORY;

    for(int i = 0; i < screenSize; i++)
    {
        VGA[2*i] = ' ';
        VGA[2*i + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}

void kprint_at(char *message, int col, int row)
{
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);

        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message)
{
    kprint_at(message, -1, -1);
}

void kprint_backspace()
{
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, WHITE_ON_BLACK);
}


//********PRIVATE**********//

int get_cursor_offset()
{
    int pos;

    WB_port(REG_SCREEN_CTRL, 14);
    pos = RB_port(REG_SCREEN_DATA) << 8;


    WB_port(REG_SCREEN_CTRL, 15);
    pos += RB_port(REG_SCREEN_DATA);

    return pos*2;
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    WB_port(REG_SCREEN_CTRL, 14);
    WB_port(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    WB_port(REG_SCREEN_CTRL, 15);
    WB_port(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int print_char(char c, int col, int row, char attr)
{
    if(!attr) attr = WHITE_ON_BLACK;
    unsigned char* VGA = (unsigned char*)VIDEO_MEMORY;

    //ERROR CHECKING
    if (col >= COLS || row >= ROWS) {
        VGA[2*(COLS)*(ROWS)-2] = 'E';
        VGA[2*(COLS)*(ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();
    
    if(c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    }else if(c == 0x08) {
        VGA[offset] = ' ';
        VGA[offset+1] = attr;        
    }else {
        VGA[offset] = c;
        VGA[offset+1] = attr;
        offset += 2;
    }

    // SCROLLING:
    if(offset >= 2*COLS*ROWS)
    {
        for(int i = 0; i < ROWS-1; i++)
        {
            unsigned char* src = (unsigned char*)(VIDEO_MEMORY + get_offset(0, i+1));
            unsigned char* dst = (unsigned char*)(VIDEO_MEMORY + get_offset(0, i));

            memory_copy(src, dst, COLS*2);
        }
        char* last_line = (char*)(VIDEO_MEMORY + get_offset(0, ROWS-1));
        for(int i = 0; i < COLS*2; i++) last_line[i] = 0;

        offset -= 2*COLS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_offset(int col, int row)
{
    return 2*(row*COLS + col);
}

int get_offset_row(int offset)
{
    return offset/(COLS*2);
}

int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset)*2*COLS))/2;
}