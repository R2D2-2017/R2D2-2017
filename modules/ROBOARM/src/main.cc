#include <sam3x8e.h>
#include "wrap-hwlib.hh"
#include "parser.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    parseCommand("left 42");


    return 0;
}
