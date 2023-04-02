#include "../x86/stdio.h"
#include "../x86/stdlib.h"
#include "../x86/stdint.h"
#include "../x86/string.h"
#include "../x86/graphics.h"
#include "drivers/keyboard.h"

void kernel_main() {
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear();
    log_msg("SYSTEM", "Welcome to JKOS!", COLOR_GREEN);
}