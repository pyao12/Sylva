#pragma once

#define ASM asm volatile

static unsigned int strlen(const char* arr) { // 获取string长度
    int i = 0;
    while (arr[i++] != '\0');
    return i - 1;
}