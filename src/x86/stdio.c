#include "stdio.h"
#include "stdint.h"

typedef struct VidChar {
    uint8_t c;
    uint8_t color;
} vidchar_t;

vidchar_t *vidmem = (vidchar_t *)0xb8000;

uint8_t g_row = 0;
uint8_t g_col = 0;
uint8_t g_color = COLOR_WHITE | (COLOR_BLACK << 4);

void set_color(uint8_t fore, uint8_t back) {
    g_color = fore | (back << 4);
}

void _clear_row(uint8_t row) {
    vidchar_t empty = { (uint8_t)' ', g_color };
    for (uint8_t col = 0; col < COLS; col++)
        vidmem[col + COLS * row] = empty;
}

void clear() {
    for (uint8_t row = 0; row < ROWS; row++)
        _clear_row(row);
}

void scroll() {
    for (uint8_t row = 1; row < ROWS; row++) {
        for (uint8_t col = 0; col < COLS; col++) {
            vidchar_t vc = vidmem[col + COLS * row];
            vidmem[col + COLS * (row - 1)] = vc;
        }
    }
}

void _newline() {
    g_col = 0;
    if (g_row < ROWS - 1) {
        g_row++;
        return;
    }
    scroll();
    _clear_row(ROWS - 1);
}


void putc(char c) {
    if (c == '\n') {
        _newline();
        return;
    }
    vidchar_t scr_c = { (uint8_t)c, g_color };
    vidmem[g_col + COLS * g_row] = scr_c;
    g_col++;
}

void puts(const char *str) {
    while (*str) {
        putc(*str);
        str++;
    }
}

void mvputc(uint8_t row, uint8_t col, char c) {
    if (c == '\n') {
        _newline();
        return;
    }
    vidchar_t scr_c = { (uint8_t)c, g_color };
    vidmem[col + COLS * row] = scr_c;
    g_col++;
}

void mvputs(uint8_t row, uint8_t col, const char *str) {
    uint8_t i = 0;
    while (*str) {
        mvputc(row, col + i, *str);
        i++;
        str++;
    }
}

void log_msg(const char *sender, char *msg, uint8_t fore) {
    set_color(COLOR_WHITE, COLOR_BLACK);
    puts("[ ");
    set_color(fore, COLOR_BLACK);
    puts(sender);
    set_color(COLOR_WHITE, COLOR_BLACK);
    puts(" ] ");
    puts(msg);
    putc('\n');
}