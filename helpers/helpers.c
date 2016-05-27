#include "helpers.h"
#include <stdio.h>
#include <string.h>

#define DEBOUNCE_COUNT   1000

void Debounce(bool rawPinValue, bool* oldStableValue, uint16_t* debounceCount) {
    if (rawPinValue == *oldStableValue && *debounceCount > 0)
        (*debounceCount)--;
    else if (rawPinValue != *oldStableValue)
        (*debounceCount)++;

    // If the Input has shown the same value for long enough let's switch it
    if (*debounceCount >= DEBOUNCE_COUNT) {
        *debounceCount = 0;
        *oldStableValue = rawPinValue;
    }
}

bool startsWith(const char *str, const char *pre) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

uint16_t ASCIIToNibble(uint8_t nib) {
    uint16_t n;

    n = nib - '0';
    if (n > 48)
        n -= 39;
    else if (n > 9)
        n -= 7;

    return n;
}

uint16_t ASCIIToHex16(uint8_t* hexStr) {
    return ASCIIToNibble(*hexStr++) << 12 |
            ASCIIToNibble(*hexStr++) << 8 |
            ASCIIToNibble(*hexStr++) << 4 |
            ASCIIToNibble(*hexStr);
}

// For some reason, results are corrupted if casted to uint8_t on function return
uint16_t ASCIIToHex8(uint8_t* hexStr) {
    return (ASCIIToNibble(*hexStr++) << 4) | (ASCIIToNibble(*hexStr));
}
