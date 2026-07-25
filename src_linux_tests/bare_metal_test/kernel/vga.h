#ifndef VGA_H
#define VGA_H

/* VGA 文本模式（80x25，黑底白字）写字符到 0xB8000 帧缓冲 */
void vga_clear(void);
void vga_puts(const char *s);

#endif /* VGA_H */
