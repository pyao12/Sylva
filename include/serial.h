#pragma once

#include <efi.h>
#include <efiser.h>

struct serial_context { // 串行内容结构体
    EFI_SERIAL_IO_PROTOCOL *SerialIo;
};

extern serial_context g_serial;

void serial_init(EFI_SERIAL_IO_PROTOCOL *SerialIo); // 初始化串行驱动
void serial_write(const char *str);                 // 往串行写string
void serial_write_char(char c);                     // 往串行写char（不推荐使用）
char serial_read_char();                            // 读串行