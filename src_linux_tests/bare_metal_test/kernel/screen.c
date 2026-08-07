#include "screen.h"

#include "com.h"
#include "vga.h"

static vga_state_t vga_state;

void screen_clear(void) { vga_clear(&vga_state); }

void screen_puts(bstring_view sv) {
    vga_puts(&vga_state, sv.data, (u16)sv.len);
    com_puts(sv.data, sv.len);
}