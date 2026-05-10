#include <serial.h>
#include <efilib.h>
#include <fonts/pixel_font.h>
#include <BUILD_INFOS.h>

serial_context g_serial;

void serial_init(EFI_SERIAL_IO_PROTOCOL *SerialIo) {
    g_serial.SerialIo = SerialIo;
    uefi_call_wrapper((void*)SerialIo->Reset, 1, SerialIo);
}

void serial_write_char(char c) {
    // 不要直接调用，ENABLE_SERIAL_PRINTS有问题，因此不会打印DEBUG
    if (!g_serial.SerialIo) {
        uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"serial: null io\n");
        return;
    }
    UINTN size = 1;
    EFI_STATUS status = uefi_call_wrapper((void*)g_serial.SerialIo->Write, 3, g_serial.SerialIo, &size, &c);
    // if (ENABLE_SERIAL_PRINTS) pf_print((const char*) c);
    if (status != EFI_SUCCESS) {
        uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"serial: write failed\n");
    }
}

void serial_write(const char *str) {
    if (!g_serial.SerialIo) {
        uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"serial: null io\n");
        return;
    }
    if (ENABLE_SERIAL_PRINTS) pf_print(str);
    while (*str) {
        serial_write_char(*str++);
    }
}

char serial_read_char() {
    // 后面可能用的上，比如远程调试？
    if (!g_serial.SerialIo) return 0;
    char c = 0;
    UINTN size = 1;
    EFI_STATUS status = uefi_call_wrapper((void*)g_serial.SerialIo->Read, 3, g_serial.SerialIo, &size, &c);
    if (status != EFI_SUCCESS || size == 0) return 0;
    return c;
}