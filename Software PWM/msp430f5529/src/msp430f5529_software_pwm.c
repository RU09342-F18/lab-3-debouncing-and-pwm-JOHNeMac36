#include <msp430.h>

/**
 * @file msp430f5529_software_pwm.c
 * @author John McAvoy
 * @date 10 Oct 2018
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer

    // infinite loop
    while(1) {

    }

    return 0;
}
