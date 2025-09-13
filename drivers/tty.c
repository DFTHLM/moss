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

key_handler_t handlers[SCANCODE_MAX];
static ring_buffer_t input_buffer;

static int cursor_x = 0;
static int cursor_y = 0;
static bool shift = false;

void handle_shift_press(void)  { 
    shift = true; 
}

void handle_shift_release(void){ 
    shift = false; 
}

void handle_enter(void) { 
    // could have done just memroy_index + 80 but this seems cleaner tbh
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
}

void clear_vga_memory() {
    // just sets the entire vga memory too 0 and resets the cursor position
    // effectively clearing it
    int i = 0;
	while(i < 80 * 25) {
		VGA_MEMORY[i] = 0;
		i++;
	}
    cursor_x = 0;
    cursor_y = 0;
}


void putc(char c) {
    VGA_MEMORY[cursor_y * 80 + cursor_x] = (0x70 << 8) | c;        
    rb_put(&input_buffer, c);

    // keeping track of cursor x and y if i need it in the future
    // (just increments the y based on whether we are at the end of line)
    cursor_x++;
    if (cursor_x >= 80) {
        cursor_y++;
        cursor_x = 0;
    }

}

void puts(const char *str, int len) {
    int i = 0;
    while (*str && i < len) {
        putc(*str++);
        i++;
    }
}

// the only functions exposed outside of this file are here

char convert_scancode(unsigned char scancode) {
    // if the key pressed is a special key handle it properly (so far only enter, shift and backspace work)
    if (handlers[scancode]) {
        handlers[scancode]();
        return 0;
        // else if the key is a normal key and not a break code, print it according to whether shift is pressed
    } else if (scancode < 0x80) {
        char c = shift ? scancode_to_ascii_shift[scancode] : scancode_to_ascii[scancode];
        return c;
    }

    return 0;
}

// TODO: add either clearing the screen at bottom right or scrolling
int tty_write(const char *str, int len) {
    puts(str, len);
    return len;
}

int tty_read(char *buf, int maxlen) {
    int i = 0;
    while(!rb_is_empty(&input_buffer) && i < maxlen) {
        rb_get(&input_buffer, &buf[i]);
        i++;
    }
    return i; // number of chars read
}

void init_tty() {
    clear_vga_memory();
    rb_init(&input_buffer);

    handlers[0x2A] = handle_shift_press;
    handlers[0x36] = handle_shift_press;
    handlers[0xAA] = handle_shift_release;
    handlers[0xB6] = handle_shift_release;
    handlers[0x1C] = handle_enter;
    handlers[0x0E] = handle_backspace;
}
