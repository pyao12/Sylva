#include <efi.h>
#include <efilib.h>
#include <graphics/context.h>
#include <graphics/draw.h>
#include <fonts/pixel_font.h>
#include <serial.h>

inline void init_gop() {
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    uefi_call_wrapper((void*)ST->BootServices->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper((void*)ST->BootServices->LocateProtocol, 3, &gop_guid, NULL, (void **)&GOP);
    gfx_init(GOP);
}

inline void init_serial() {
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

    uefi_call_wrapper((void*)ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 5);
    uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"Kernel is running!\n");

    uefi_call_wrapper((void*)ST->ConOut->ClearScreen, 1, ST->ConOut);
    serial_write("\n\n"); // 防止和前面串了

    // pf_print_char('k', 10, 10);
    pf_print("Welcome to Sylva OS!", 10, 10);
    serial_write("Hello from serial!\n");
    serial_write("Hello from serial line 2!");
    while (1);
}