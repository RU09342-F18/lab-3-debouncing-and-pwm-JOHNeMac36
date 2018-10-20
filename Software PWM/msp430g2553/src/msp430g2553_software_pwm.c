#include <msp430.h>

/**
 * @file msp430g2553_software_pwm.c
 * @author John McAvoy
 * @date 10 Oct 2018
 */
#define LED BIT0 // P1.0
#define BTN BIT3 // P1.3
#define STATUS BIT6 // P1.3

void setup_status_led(){
    P1SEL &= ~STATUS;
    P1DIR |=  STATUS;
    P1OUT &= ~STATUS;
}

void setup_led(){
    P1SEL &= ~LED;
    P1DIR |= LED;
    P1OUT &= ~LED;
}

void setup_btn(){
    P1SEL &= ~BTN;
    P1DIR &= ~BTN;
    P1OUT &= ~BTN;

    P1IES |= BTN;
    P1IE |= BTN;
}

// drives LED
void setup_timera0(){
    TA0CCR0 = 9999;
    TA0CCR1 = 1000;

    TA0CTL = TASSEL_2 + ID_3 + MC_1;
    TA0CCTL0 = OUTMOD_3 | CCIE;

}

// debouncing delay
void setup_timera1(){
    TA1CCR0 = 9999;

    TA1CTL = TASSEL_2 + ID_0 + MC_0;
    TA1CCTL0 = CCIE;

    TA1R = 0; // clear timer
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer

    setup_led();
    setup_status_led();

    setup_btn();
    setup_timera0();
    setup_timera1();
    __bis_SR_register(GIE);

    // infinite loop
    while(1) {

    }

    return 0;
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= STATUS;
    P1IE &= ~BTN; // disable BTN intterupt
    TA1CTL |= MC_1; // start debouncing timer
    TA0CCR1 += 1000; // increment 10% duty cycle
    TA0CCR1 %= 10000; // handle overflow
    TA0R = 0;
    P1IFG &= ~(BTN); // BTN IFG cleared
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A0(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer0_A0 (void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= LED;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) Timer1_A0 (void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= LED;
    P1IE |= BTN; // enable BTN intterupt
    TA1CTL |= MC_0; // stop timer
}
