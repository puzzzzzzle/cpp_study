#include "screen.h"

#include "com.h"
#include "str.h"
#include "vga.h"

static vga_state_t vga_state;

void screen_clear(void) { vga_clear(&vga_state); }

void screen_putsn(const char* s, size_t len) {
  vga_puts(&vga_state, s, len);
  com_puts(s, len);
}
void screen_puts(const char* s) { screen_putsn(s, strlen(s, ~(size_t)0)); }