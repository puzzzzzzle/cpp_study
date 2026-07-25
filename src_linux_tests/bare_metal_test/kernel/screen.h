#ifndef SCREEN_H
#define SCREEN_H

/* VGA 文本模式（80x25，灰度属性）写字符到 0xB8000 */
void screen_clear(void);
void screen_puts(const char *s);

#endif /* SCREEN_H */
