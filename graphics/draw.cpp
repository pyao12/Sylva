#include <efi.h>

void draw_pixel(unsigned int x, unsigned int y, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color, 
        EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP, unsigned int hr, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base) {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x;

    p->Blue = color.Blue;
    p->Green = color.Green;
    p->Red = color.Red;
    p->Reserved = color.Reserved;
}
