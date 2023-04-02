#include "mouse.h"
#include "../../x86/stdio.h"
#include "../../x86/stdlib.h"

#define MOUSE_IRQ 12
#define STATUS_PORT 0x64
#define DATA_PORT 0x60

int ms_enabled = FALSE;

void init_mouse() {
    outb(0xA8, STATUS_PORT);

    outb(0x20, STATUS_PORT);
    uint8_t status = inb(DATA_PORT);

    status |= 0x02;

    outb(0x60, STATUS_PORT);
    outb(status, DATA_PORT);

    outb(0xD4, STATUS_PORT);
    outb(0xF4, DATA_PORT);

    log_msg("DRIVERS", "Mouse enabled", COLOR_GREEN);
    ms_enabled = TRUE;
}