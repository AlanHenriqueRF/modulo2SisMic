#include <msp430.h>

// Exercício 3: Remoção de rebotes
// Refaça o exercício 2 removendo os rebotes das chaves. Para isso, defina uma
// função debounce() que consome tempo do processador através de um loop que
// decremente uma variável. Não deixe de declará-la como volatile para evitar
// que o recurso de otimização do compilador a remova.

void debounce(int a);

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs

}

void debounce(int a) {
  volatile int i;
  for (i = 0; i < a; i++)
    ;
}
