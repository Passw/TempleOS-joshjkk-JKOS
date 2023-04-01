#include "stdio.h"
#include "stdint.h"

vidchar_t *vidmem = (vidchar_t *)0xb8000;

uint8_t row = 0;
uint8_t col = 0;
uint8_t color = COLOR_WHITE | (COLOR_BLACK << 4);

void set_color(uint8_t fore, uint8_t back) {
    color = fore | (back << 4);
}

void _clear_row(uint8_t row) {
    vidchar_t empty = { (uint8_t)' ', color };
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

void newline() {
    col = 0;
    if (row < ROWS - 1) {
        row++;
        return;
    }
    scroll();
    _clear_row(ROWS - 1);
}

void putc(char c) {
    if (c == '\n') {
        newline();
        return;
    }
    vidchar_t scr_c = { (uint8_t)c, color };
    vidmem[col + COLS * row] = scr_c;
    col++;
}

void puts(const char *str) {
    while (*str) {
        putc(*str);
        str++;
    }
}