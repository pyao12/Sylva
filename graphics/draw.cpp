#include <graphics/draw.h>

void draw_pixel(unsigned int x, unsigned int y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color) {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = g_gfx.base + (g_gfx.hr * y) + x;

    p->Blue = color.Blue;
    p->Green = color.Green;
    p->Red = color.Red;
    p->Reserved = color.Reserved;
}