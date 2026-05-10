#include <efi.h>
#include <efilib.h>

extern void kernel_main();

EFI_STATUS EFIAPI efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);

    uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut);
    uefi_call_wrapper(SystemTable->ConOut->SetCursorPosition, 3, SystemTable->ConOut, 0, 1);
    uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"Welcome to SYLVA OS!\n");
    uefi_call_wrapper(SystemTable->ConOut->SetCursorPosition, 3, SystemTable->ConOut, 0, 2);
    uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"* The system has booted successfully.\n");


    uefi_call_wrapper(SystemTable->ConOut->SetCursorPosition, 3, SystemTable->ConOut, 0, 3);
    uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"* Jumping to kernel...\n");

    kernel_main();

    return EFI_SUCCESS;
}