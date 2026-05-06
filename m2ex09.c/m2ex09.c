#include <msp430.h>

// Exercício 9: PWM por hardware
// Repita o programa anterior usando a saída do timer. Procure no datasheet qual pino está
// conectado à saída do canal desejado. Ligue a saída do timer no LED vermelho com um cabo
// removendo o jumper JP8 e conectando a saída do timer no pino de baixo do jumper (pino mais
// próximo da extremidade da placa). Não conecte no outro pino! Você irá queimar a porta do
// seu MSP.

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    while(1) {}
}
