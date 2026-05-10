#include <efi.h>
#include <efilib.h>
#include <graphics/context.h>
#include <graphics/draw.h>
#include <fonts/pixel_font.h>

extern "C" void kernel_main() {
    EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};

    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    uefi_call_wrapper((void*)ST->BootServices->SetWatchdogTimer, 4, 0, 0, 0, NULL);
    uefi_call_wrapper((void*)ST->BootServices->LocateProtocol, 3, &gop_guid, NULL, (void **)&GOP);

    gfx_init(GOP);

    uefi_call_wrapper((void*)ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 5);
    uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"Kernel is running!\n");

    uefi_call_wrapper((void*)ST->ConOut->ClearScreen, 1, ST->ConOut);

    // pf_print_char('k', 10, 10);
    pf_print("Welcome to Sylva OS!", 10, 10);
    while (1);
}