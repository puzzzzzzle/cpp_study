#pragma once

/* 从 COM1 串口阻塞读取一个字符（已含 LSR 就绪判断） */
int com_getc(void);

/* 向 COM1 串口写入一个字符（已含 LSR 空判断） */
void com_putc(char c);
