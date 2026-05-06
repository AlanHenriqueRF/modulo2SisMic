#include <msp430.h>

// Exercício 4: Trava de execução com condições mais elaboradas.
// Escreva na função main() uma rotina que alterne o estado do LED vermelho toda vez que o
// usuário acionar a chave S1 ou S2. Por acionamento de uma chave, entende-se sua passagem
// do estado aberta para o estado fechada (A à F).

#define led_red_on (P1OUT |= BIT0)
#define led_red_off (P1OUT &= ~(BIT0))

#define s1_clicked (~P2IN & BIT1)
#define s1_nonClicked (P2IN & BIT1)

#define s2_clicked (~P1IN & BIT1)
#define s2_nonClicked (P1IN & BIT1)

void debounce(int a);

void io_config();

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs

  io_config();

  while (1) {
    while (P2IN & BIT1 && P1IN & BIT1 );
    P1OUT ^= BIT0;
    debounce(5000);
    while (~P2IN & BIT1 || ~P1IN & BIT1);
    debounce(5000);
  }
}

void debounce(int a) {
  volatile int i;
  for (i = 0; i < a; i++);
}

void io_config(){
  // led vermelho
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;

  // chave s2
  P1DIR &= ~BIT1;
  P1REN |= BIT1;
  P1OUT |= BIT1;

  // chave s1
  P2DIR &= ~BIT1;
  P2REN |= BIT1;
  P2OUT |= BIT1;
}
