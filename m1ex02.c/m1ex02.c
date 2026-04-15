#include <msp430.h>

// Exercício 2: Ruído (rebotes) de chaves mecânicas
// Escreva na função main() uma rotina que alterne o estado do LED vermelho toda
// vez que o usuário apertar o botão S1. Não remova os rebotes.

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs

  P2DIR &= ~BIT1;
  P2REN |= BIT1;
  P2OUT |= BIT1;

  P1DIR |= BIT0;
  P1OUT &= ~BIT0;

  while (1) {
    // TEM QUE ser igual a 0, pois o botão solto, gera bit 1 & 1 =1
    while (P2IN & BIT1);
    P1OUT ^= BIT0;
    while (~P2IN & BIT1);
  }
}
