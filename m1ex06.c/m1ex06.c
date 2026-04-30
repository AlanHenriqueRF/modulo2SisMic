#include <msp430.h>

// Exercício 6: Amostrando flags do timer
// Escreva um programa em C que faça piscar o LED verde (P4.7) em exatamente 1Hz
// (0,5s apagado e 0,5s aceso). Use a técnica de amostragem (polling) da flag de
// overflow (TAIFG) ou a flag do canal 0 (CCIFG) para saber quando o timer
// atingiu o valor máximo.

#define led_verde (P4OUT |= BIT7)
#define non_led_verde (P4OUT &= ~BIT7)

#define UM_SEG 32767 // CCR0 = 32768 - 1

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs

  P4DIR |= BIT7; // LED VERDE CONFIGURADO

  TA0CCR0 = UM_SEG/2;
  TA0CTL = TASSEL_1 // TIPO DE CLOCK, NO CASO O ACLK
           | MC_1   // MODO UP, 0->1->3->...->32767
           | TACLR; // LIMPA O CONTADOR

  while (1) {
    while (!(TA0CTL & TAIFG));
    TA0CTL &= ~TAIFG;
    P4OUT ^= BIT7;
  }
}
