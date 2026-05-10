#include <graphics/context.h>

gfx_context g_gfx;

void gfx_init(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP) {
    g_gfx.GOP = GOP;
    g_gfx.hr = GOP->Mode->Info->HorizontalResolution;
    g_gfx.vr = GOP->Mode->Info->VerticalResolution;
    g_gfx.base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) GOP->Mode->FrameBufferBase;
}

void gfx_clear(void) {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL black = {0, 0, 0, 0};
    g_gfx.GOP->Blt(g_gfx.GOP, &black, EfiBltVideoFill, 0, 0, 0, 0, g_gfx.hr, g_gfx.vr, 0);
}