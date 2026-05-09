#include <efi.h>
#include <efilib.h>

extern "C" void kernel_main();

void kernel_main() {
    // uefi_call_wrapper((void*)ST->ConOut->ClearScreen, 1, ST->ConOut);
    uefi_call_wrapper((void*)ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 5);
    uefi_call_wrapper((void*)ST->ConOut->OutputString, 2, ST->ConOut, L"Kernel is running!\n");

    while (1);
}