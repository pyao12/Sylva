#pragma once

#include <efi.h>

void draw_pixel(unsigned int x, unsigned int y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color,
        EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP, unsigned int hr, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base);