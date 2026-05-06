#include <msp430.h>

/*
 * Relógio de 1 minuto — Servo SG90
 *
 * TA0 (SMCLK) → PWM do servo em P1.2
 * TA1 (ACLK)  → base de tempo de 1 segundo exato
 *
 * S1 (P2.1): pausado → reinicia | rodando → pausa
 * LED verde  P4.7: aceso = rodando
 * LED verm.  P1.0: aceso = pausado
 */

/* ── Pinos ─────────────────────────────── */
#define SERVO           BIT2    // P1.2 = TA0.1
#define S1              BIT1    // P2.1
#define LED_VERDE       BIT7    // P4.7
#define LED_VERMELHO    BIT0    // P1.0

/* ── Servo: SMCLK = 1.048.576 Hz ───────── */
#define SMCLK       1048576UL 
#define PERIODO     (SMCLK / 50 - 1)           // 20ms = 50Hz
#define PULSO_MIN   (SMCLK *  6 / 10000)       // 0.6ms →   0°
#define PULSO_MAX   (SMCLK * 24 / 10000)       // 2.4ms → 180°

/* ── Relógio ────────────────────────────── */
#define PASSO       3           // graus por segundo
#define ANGULO_MAX  180         // reinicia ao atingir

/* ── Variáveis compartilhadas com ISR ───── */
volatile unsigned char tick    = 0;     // 1 = passou 1 segundo
volatile unsigned char rodando = 1;     // estado atual

unsigned int angulo = 0;

/* ── Protótipos ─────────────────────────── */
void servo_angulo(unsigned int grau);

/* ═══════════════════════════════════════════
 *  MAIN
 * ═══════════════════════════════════════════ */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    /* --- LEDs --- */
    P4DIR |=  LED_VERDE;
    P1DIR |=  LED_VERMELHO;
    P4OUT |=  LED_VERDE;        // começa rodando → verde aceso
    P1OUT &= ~LED_VERMELHO;

    /* --- Servo: TA0 com SMCLK --- */
    P1DIR |=  SERVO;
    P1SEL |=  SERVO;
    TA0CCR0  = PERIODO;
    TA0CCR1  = PULSO_MIN;       // posição inicial: 0°
    TA0CCTL1 = OUTMOD_7;        // Reset/Set
    TA0CTL   = TASSEL_2 | MC_1 | TACLR;

    /* --- Timer 1 segundo: TA1 com ACLK ---
     * ACLK = 32.768 Hz
     * CCR0 = 32.767 → conta 32.768 ticks = 1s exato
     */
    TA1CCR0  = 32767;
    TA1CCTL0 = CCIE;
    TA1CTL   = TASSEL_1 | MC_1 | TACLR;

    /* --- Botão S1 --- */
    P2DIR &= ~S1;
    P2REN |=  S1;
    P2OUT |=  S1;   // pull-up

    __enable_interrupt();

    servo_angulo(0);            // posição inicial

    /* ═══════════════════════════════════════
     *  Loop principal
     * ═══════════════════════════════════════ */
    while (1) {

        /* ── Botão S1: polling com debounce ── */
        if (!(P2IN & S1)) {
            volatile unsigned int d;
            for (d = 0; d < 15000; d++);        // aguarda estabilizar

            if (!(P2IN & S1)) {                 // confirma pressionado

                if (rodando) {
                    /* RODANDO → PAUSA */
                    rodando = 0;
                    P4OUT &= ~LED_VERDE;
                    P1OUT |=  LED_VERMELHO;

                } else {
                    /* PAUSADO → REINICIA do zero */
                    angulo  = 0;
                    servo_angulo(0);

                    TA1CTL |= TACLR;            // zera o timer de 1s
                    tick    = 0;
                    rodando = 1;

                    P1OUT &= ~LED_VERMELHO;
                    P4OUT |=  LED_VERDE;
                }

                while (!(P2IN & S1));           // aguarda soltar
            }
        }

        /* ── Avança servo a cada segundo ─── */
        if (tick && rodando) {
            tick = 0;

            angulo += PASSO;

            if (angulo >= ANGULO_MAX) {
                angulo = 0;         // minuto completo → reinicia
            }

            servo_angulo(angulo);
        }
    }
}

/* ═══════════════════════════════════════════
 *  ISR: 1 segundo (TA1, CCR0 — ACLK)
 *
 *  Só levanta a flag — o processamento
 *  acontece no main, nunca na ISR
 * ═══════════════════════════════════════════ */
#pragma vector = TIMER1_A0_VECTOR
__interrupt void isr_1segundo(void) {
    tick = 1;
}

/* ═══════════════════════════════════════════
 *  servo_angulo — converte graus em CCR1
 * ═══════════════════════════════════════════ */
void servo_angulo(unsigned int grau) {
    if (grau > 180) grau = 180;
    TA0CCR1 = PULSO_MIN
            + (unsigned long)grau * (PULSO_MAX - PULSO_MIN) / 180;
}
