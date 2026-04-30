#include <math.h>
#include <msp430.h>


// Exercício 7: Medindo tempo.
// Meça o tempo de execução das duas linhas de código abaixo.
// volatile double hardVar = 128.43984610923f;
// hardVar = (sqrt(hardVar * 3.14159265359) + 30.3245)/1020.2331556 – 0.11923;

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs

  TA0CTL = TASSEL_2 | MC_2 | TACLR;

  unsigned int t_antes = TA0R;

  volatile double hardVar = 128.43984610923f;
  hardVar = (sqrt(hardVar * 3.14159265359) + 30.3245) / 1020.2331556 - 0.11923;

  unsigned int t_depois = TA0R;

  unsigned int t_total = t_depois - t_antes;

  // Tempo em µs: ticks / 1.048576
  // (deixa aqui pra você ver no debugger)
  volatile float tempo_us = t_total / 1.048576f;

  while (1);
}
