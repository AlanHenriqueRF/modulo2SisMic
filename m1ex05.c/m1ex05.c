#include <msp430.h>

// EXEMPLO TIMER

// ACLK = 32768 Hz (cristal do Launchpad)
// Modo Up: Timer conta de 0 até CCR0, reseta, repete
// 32768 ticks = 1 segundo exato

#define LED     BIT0
#define UM_SEG  32767       // CCR0 = 32768 - 1

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= LED;
    P1OUT &= ~LED;

    // --- Configura o Timer_A0 ---
    TA0CCR0 = UM_SEG;           // Topo: conta até aqui e reseta
    TA0CTL  = TASSEL_1          // Clock: ACLK (32768 Hz)
            | ID_0              // Divisor: /1 (sem dividir)
            | MC_1              // Modo Up: 0 → CCR0 → 0 → ...
            | TACLR;            // Limpa o contador agora

    while (1) {
        // TAIFG = flag que acende quando o timer "transborda" (chegou no CCR0)
        while (!(TA0CTL & TAIFG));  // fica parado esperando a flag
        TA0CTL &= ~TAIFG;           // apaga a flag manualmente (obrigatório!)
        P1OUT ^= LED;               // pisca o LED
    }
}
