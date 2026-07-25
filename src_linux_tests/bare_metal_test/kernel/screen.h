#ifndef SCREEN_H
#define SCREEN_H

/* VGA 文本模式（80x25，灰度属性）写字符到 0xB8000 */
void screen_clear(void);
void screen_puts(const char *s);

/* 从 COM1 串口阻塞读取一个字符（已含 LSR 就绪判断） */
int serial_getc(void);

#endif /* SCREEN_H */
