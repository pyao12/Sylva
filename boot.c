#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    InitializeLib(ImageHandle, ST);

    // 不能直接ST->ConOut之类的，会GP，不知道为什么
    // uefi_call_wrapper可以解决，而且比较安全（不过就是宏）
    // 看着挺长，反正就在boot这里用到UEFI Out，后面不用，也就算了
    uefi_call_wrapper(ST->ConOut->ClearScreen, 1, ST->ConOut);
    uefi_call_wrapper(ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 1);
    uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"Welcome to SYLVA OS!\n");
    uefi_call_wrapper(ST->ConOut->SetCursorPosition, 3, ST->ConOut, 0, 2);
    uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"* The system has booted successfully.\n");
    while (1); // 否则会直接跳到QEMU Setup
    return EFI_SUCCESS;
}