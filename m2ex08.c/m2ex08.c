#include <msp430.h>

// Exercício 8: PWM com duty cycle fixo
// 128Hz, 50% duty cycle usando interrupções de overflow (TAIFG) e CCR1
//
// ACLK = 32768 Hz
// Período: 32768 / 128 = 256 ticks → CCR0 = 255
// 50% duty cycle: CCR1 = 128

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    TA0CTL = TASSEL__ACLK | MC__UP | TAIE;

    TA0CCR0 = 255;  // período = 256 ticks → 32768/256 = 128 Hz
    TA0CCR1 = 128;  // 50% duty cycle

    TA0CCTL1 = CCIE;                              // interrupção do CCR1
    
    __enable_interrupt();

    while(1) {}
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void isr_toggle() {
    switch (TA0IV) {
        case TA0IV_TA0CCR1:           // CCR1: metade do período → desliga LED
            P1OUT &= ~BIT0;
            break;
        case TA0IV_TAIFG:            // TAIFG: overflow, início do período → liga LED
            P1OUT |= BIT0;
            break;
    }
}
