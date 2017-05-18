#include <sam3x8e.h>

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    return 0;
}
