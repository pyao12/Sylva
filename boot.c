#include <efi.h>
#include <efilib.h>

extern void kernel_main();

EFI_STATUS EFIAPI efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    InitializeLib(ImageHandle, ST);

    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    uefi_call_wrapper(ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 1);
    uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"Welcome to SYLVA OS!\n");
    uefi_call_wrapper(ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 2);
    uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"* The system has booted successfully.\n");
    uefi_call_wrapper(ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 3);
    uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"* Jumping to kernel...\n");

    kernel_main();

    return EFI_SUCCESS;
}