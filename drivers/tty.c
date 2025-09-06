#include "tty.h"

static const char scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', 0,
    0,'q','w','e','r','t','y','u','i','o','p','[',']',0,
    0, 'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const char scancode_to_ascii_shift[128] = {
    0,  27, '!','@','#','$','%','^','&','*','(',')','_','+',0,
    0,'Q','W','E','R','T','Y','U','I','O','P','{','}',0,0,
    'A','S','D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V',
    'B','N','M','<','>','?',0,'*',0,' ',0
};


static int cursor_x = 0;
static int cursor_y = 0;
static int prev_vga_index = 0;
static bool shift = false;

void handle_shift_press(void)  { 
    shift = true; 
}

void handle_shift_release(void){ 
    shift = false; 
}

void handle_enter(void) { 
    cursor_y++; 
    cursor_x = 0;
}

void handle_backspace() {
    // if at top left, dont do anything
    if (cursor_x == 0 && cursor_y == 0) return;
    
    // normal function, not at start of line just delete character to the left
    if (cursor_x > 0) {
        cursor_x--;
    //if at x = 0 go up one line
    } else if (cursor_y > 0) {
        cursor_y--;
        cursor_x = 79;

        // find the start of text in the line
        while (cursor_x > 0 && !(VGA_MEMORY[cursor_y * 80 + cursor_x] & 0xFF)) {
            cursor_x--;
        }
    }

    VGA_MEMORY[cursor_y * 80 + cursor_x] = 0;
    VGA_MEMORY[cursor_y * 80 + cursor_x - 1] = (0x70 << 8) | (VGA_MEMORY[cursor_y * 80 + cursor_x - 1] & 0xFF);
    prev_vga_index = cursor_y * 80 + cursor_x - 1;
}

key_handler_t handlers[SCANCODE_MAX];

void init_special_keys() {
    handlers[0x2A] = handle_shift_press;
    handlers[0x36] = handle_shift_press;
    handlers[0xAA] = handle_shift_release;
    handlers[0xB6] = handle_shift_release;
    handlers[0x1C] = handle_enter;
    handlers[0x0E] = handle_backspace;
}

void clear_vga_memory() {
    int i = 0;
	while(i < 80 * 25) {
		VGA_MEMORY[i] = 0;
		i++;
	}
    cursor_x = 0;
    cursor_y = 0;
}

char convert_scancode(unsigned char scancode) {
    if (handlers[scancode]) {
        handlers[scancode]();
        return 0;
    } else if (scancode < 0x80) {
        char c = shift ? scancode_to_ascii_shift[scancode] : scancode_to_ascii[scancode];
        return c;
    }

    return 0;
}

void putc(char c) {
    VGA_MEMORY[cursor_y * 80 + cursor_x] = (0x70 << 8) | c;        

    VGA_MEMORY[prev_vga_index] = (0x07 << 8) | (VGA_MEMORY[prev_vga_index] & 0xFF);
    prev_vga_index = cursor_y * 80 + cursor_x;

    cursor_x++;
    if (cursor_x >= 80) {
        cursor_y++;
        cursor_x = 0;
    }

}

void puts(const char *str) {
    while (*str) {
        putc(*str++);
    }
}
