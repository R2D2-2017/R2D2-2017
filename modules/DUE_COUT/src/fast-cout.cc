//
// Created by Robert on 5/24/17.
//
#include "fast-cout.hh"

namespace hwlib {
bool uart_char_available() {
    return (bool) (UART->UART_SR & UART_SR_RXRDY);
}
char getc() {
    return (char) (UART->UART_RHR & UART_RHR_RXCHR_Msk);
}
void putc(char c) {
    while (!(UART->UART_SR & UART_SR_TXRDY));
    UART->UART_THR = static_cast<uint32_t>(c);
}
void init(unsigned int baudrate) {
    WDT->WDT_MR = WDT_MR_WDDIS;
    PIOA->PIO_PDR = PIO_PA8A_URXD | PIO_PA9A_UTXD;
    UART->UART_BRGR = 84000000 / 16 / baudrate;
    UART->UART_MR = UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO;
    UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
    PMC->PMC_PCER0 = 1 << ID_UART; // PID for uart
}
}

