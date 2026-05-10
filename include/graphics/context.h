#pragma once

// 这个文件存在的目的是让graphics的draw功能不用每次传 GOP hr vr base

#include <efi.h>

struct gfx_context {
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    unsigned int hr;
    unsigned int vr;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base;
};

extern gfx_context g_gfx;

void gfx_init(EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP); // 初始化 GFX
void gfx_clear(void);                             // 清空 GFX（相当于重置）