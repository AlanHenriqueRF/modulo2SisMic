#include <msp430.h>

int main(void){
    WDTCTL = WDTPW | WDTHOLD; // interrompe whatdogs
  
}
