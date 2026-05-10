#include <efi.h>
#include <efilib.h>
#include <graphics/context.h>
#include <graphics/draw.h>
#include <fonts/pixel_font.h>
#include <serial.h>
#include <common.h>

inline void init_gop() {
    // 初始化 GOP
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    uefi_call_wrapper((void*)ST->BootServices->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper((void*)ST->BootServices->LocateProtocol, 3, &gop_guid, NULL, (void **)&GOP);
    gfx_init(GOP);
}

inline void init_serial() {
    // 初始化串行驱动
    EFI_SERIAL_IO_PROTOCOL *SerialIo = NULL;
    EFI_GUID gEfiSerialIoProtocolGuid = EFI_SERIAL_IO_PROTOCOL_GUID;
    EFI_HANDLE *SerialHandles = NULL;
    UINTN NumSerials = 0;
    EFI_STATUS status = uefi_call_wrapper((void*)ST->BootServices->LocateHandleBuffer, 5,
        ByProtocol,
        &gEfiSerialIoProtocolGuid,
        NULL,
        &NumSerials,
        &SerialHandles
    );
    if (status == EFI_SUCCESS && NumSerials > 0) {
        status = uefi_call_wrapper((void*)ST->BootServices->HandleProtocol, 3,
            SerialHandles[0], &gEfiSerialIoProtocolGuid, (void **)&SerialIo);
        if (status == EFI_SUCCESS) {
            serial_init(SerialIo);
        }
    }
    if (SerialHandles) {
        ST->BootServices->FreePool(SerialHandles);
    }
}

extern "C" void kernel_main() {
    init_gop();
    init_serial();

    // 都用uefi_call_wrapper，不用会PF，不知道为什么
    uefi_call_wrapper((void*)ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 5);
    uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"Kernel is running!\n");

    uefi_call_wrapper((void*)ST->ConOut->ClearScreen, 1, ST->ConOut);
    serial_write("\n\n"); // 防止和前面串了serial.log看不清

    pf_print("Welcome to Sylva OS!\n");
    serial_write(" Kernel prepared well, start loop.\n");

    while (1) ASM ("hlt"); // 《30天》看多了 (doge
}