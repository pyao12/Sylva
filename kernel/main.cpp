#include <efi.h>
#include <efilib.h>
#include <graphics/draw.h>

extern "C" void kernel_main() {
    EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};

    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    uefi_call_wrapper((void*)ST->BootServices->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper((void*)ST->BootServices->LocateProtocol, 3, &gop_guid, NULL, (void **)&GOP);

    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) GOP->Mode->FrameBufferBase;

    uefi_call_wrapper((void*)ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 5);
    uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"Kernel is running!\n");
    
    for (unsigned int i = 1; i <= 100; i++) {
        // uefi_call_wrapper((void*)ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, i + 6);
        // uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"hello!");
        for (unsigned int j = 1; j <= 100; j++) {   
            draw_pixel(i, j, {255, 255, 255, 255}, GOP, hr, base);
        }
    }
    while (1);
}