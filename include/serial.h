#pragma once

#include <efi.h>
#include <efiser.h>

struct serial_context {
    EFI_SERIAL_IO_PROTOCOL *SerialIo;
};

extern serial_context g_serial;

void serial_init(EFI_SERIAL_IO_PROTOCOL *SerialIo);
void serial_write(const char *str);
void serial_write_char(char c);
char serial_read_char();