#pragma once

#include <efi.h>
#include <graphics/context.h>

void draw_pixel(unsigned int x, unsigned int y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);