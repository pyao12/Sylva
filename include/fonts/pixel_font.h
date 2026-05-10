#pragma once

#include <graphics/context.h>

void pf_print_char(char c, unsigned int basex, unsigned int basey, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color = {255, 255, 255, 255});
void pf_print(char* text, unsigned int basex, unsigned int basey, EFI_GRAPHICS_OUTPUT_BLT_PIXEL color = {255, 255, 255, 255});