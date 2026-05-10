#include <fonts/hankaku.h>
#include <fonts/pixel_font.h>
#include <graphics/draw.h>
#include <common.h>

static unsigned int pf_x = 0;
static unsigned int pf_y = 1;

void pf_reset_position(void) {
    // 其实应该还要清一下屏，后面思考一个安全的做法
    pf_x = 0;
    pf_y = 1;
}

void pf_print_char(char c, unsigned int basex, unsigned int basey, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color) {
    for (unsigned int y = 0; y < 16; y++) {
        unsigned char data = hankaku_pixels[c][y];
        for (int x = 7; x >= 0; x--) {
            // 解码Hankaku字体
            /*
            既然都在这了，就讲一下Hankaku字体是如何解码的
            比如一个
            {0x00, 0x82, 0x82, 0x44, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00}
            每一个Hex代表一行，比如0x82就是一行，转换成Bin得到10000010，1代表有像素，0代表没像素
            */
            unsigned int current = data & 1;
            data >>= 1;
            if (current)
                draw_pixel(basex + x, basey + y, color);
        }
    }
}

void pf_print(const char* text, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color) {
    for (unsigned int i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (c == '\n') {
            pf_x = 0;
            pf_y++;
            if ((pf_y - 1) * 16 >= g_gfx.vr) {
                gfx_clear();
                pf_y = 1;
            }
            continue;
        }
        if (pf_x * 9 + 9 > g_gfx.hr) {
            pf_x = 0;
            pf_y++;
            if ((pf_y - 1) * 16 >= g_gfx.vr) {
                gfx_clear();
                pf_y = 1;
            }
        }
        pf_print_char(c, pf_x * 9, (pf_y - 1) * 16, color);
        pf_x++;
    }
}