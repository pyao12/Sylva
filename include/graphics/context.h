#pragma once

#include <efi.h>

struct gfx_context {
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    unsigned int hr;
    unsigned int vr;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base;
};

extern gfx_context g_gfx;

void gfx_init(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP);