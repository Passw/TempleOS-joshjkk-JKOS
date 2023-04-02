#include "drivers.h"
#include "keyboard.h"
#include "mouse.h"
#include "../../x86/stdio.h"
#include "../../x86/stdint.h"

extern int kbd_enabled;
extern int ms_enabled;

void start_drivers() {
    log_msg("DRIVERS", "Starting drivers...", COLOR_YELLOW);

    init_keyboard();
    init_mouse();
    
    if (kbd_enabled == TRUE && ms_enabled == TRUE) return;
    else
        log_msg("DRIVERS", "Failed to start keyboard and mouse drivers", COLOR_RED);
}