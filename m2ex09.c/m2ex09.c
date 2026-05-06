#include <msp430.h>

// Exercício 9: PWM por hardware
// Repita o programa anterior usando a saída do timer. Procure no datasheet qual pino está
// conectado à saída do canal desejado. Ligue a saída do timer no LED vermelho com um cabo
// removendo o jumper JP8 e conectando a saída do timer no pino de baixo do jumper (pino mais
// próximo da extremidade da placa). Não conecte no outro pino! Você irá queimar a porta do
// seu MSP.

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    TA0CTL = TASSEL__ACLK | MC__UP;

    P1DIR |= BIT5;
    P1SEL |= BIT5; // CONFIGURA O CABO CONECTADO NO P1.5, A USAR O TA0.4

    TA0CCR0 = 255; 
    TA0CCR4 = TA0CCR0 >> 1; // 50%

    TA0CCTL4 = OUTMOD_7; // RESET/SET // ERROUUUUUU TA0CCTL

    while(1) {}
}
