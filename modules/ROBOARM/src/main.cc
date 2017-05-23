#include <sam3x8e.h>
#include "wrap-hwlib.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;



    return 0;
}
