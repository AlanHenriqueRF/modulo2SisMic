#include <msp430.h>

// Exercício 3: Remoção de rebotes
// Refaça o exercício 2 removendo os rebotes das chaves. Para isso, defina uma
// função debounce() que consome tempo do processador através de um loop que
// decremente uma variável. Não deixe de declará-la como volatile para evitar
// que o recurso de otimização do compilador a remova.

void debounce(int a);

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
    debounce(5000);
    while (~P2IN & BIT1);
    debounce(5000);
  }
}

void debounce(int a) {
  volatile int i;
  for (i = 0; i < a; i++)
    ;
}
