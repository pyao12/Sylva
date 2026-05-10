#include <fonts/sylva_sd.h>
#include <fonts/pixel_font.h>
#include <graphics/draw.h>
#include <common.h>

void pf_print_char(char c, unsigned int basex, unsigned int basey, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color) {
    for (unsigned int y = 0; y < 16; y++) {
        unsigned char data = hankaku_pixels[c][y];
        for (int x = 7; x >= 0; x--) {
            unsigned int current = data & 1;
            data >>= 1;
            if (current)
                draw_pixel(basex + x, basey + y, color);
        }
    }
}

void pf_print(char* text, unsigned int basex, unsigned int basey, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color) {
    for (unsigned int i = 0; i < strlen(text); i++) {
        pf_print_char(text[i], basex + 9 * i, basey, color);
    }
}