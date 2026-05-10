#pragma once

#include <graphics/context.h>

void pf_print_char(char c, unsigned int basex, unsigned int basey, 
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL color = {255, 255, 255, 255});                         // Pixel Font 打印字符
void pf_print(const char* text, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color = {255, 255, 255, 255}); // Pixel Font 打印string
void pf_reset_position(void);                                                                // 重设Pixel Font Cursor位置