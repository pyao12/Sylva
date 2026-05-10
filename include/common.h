#pragma once

unsigned int strlen(char* arr) {
    int i = 0;
    while (arr[i++] != '\0');
    return i - 1;
}