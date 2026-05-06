#include <msp430.h>

// Exercício 1: Configuração dos pinos
// Escreva um programa que faça o LED verde imitar o estado da chave S1. Se S1
// estiver pressionado o LED deverá estar aceso, se estiver solto, o LED deve
// apagar.

void io_config(void);

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs

  io_config();

  while (1) {
    /*
    if (P2IN & BIT1){
        P4OUT &= ~BIT7;
    }else {
        P4OUT |= BIT7;
    }*/

    while (P2IN & BIT1); // esta solto, so mudará de estado quando precionado
    P4OUT |= BIT7;

    while (P2IN & BIT1 == 0);
    P4OUT &= ~BIT7;
  }
}

void io_config() {
  P2DIR &= ~BIT1; // chave s1, é do tipo entrada
  P2REN |= BIT1;  // s1, precisa de um resistor
  P2OUT |= BIT1;  // Resistor de pull up

  // prepara led verde
  P4DIR |= BIT7; // saida no p4.7
  P4OUT &= ~BIT7;
}
