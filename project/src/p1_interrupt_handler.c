#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"



/* Switch on P1 (S2) */

void

__interrupt_vec(PORT1_VECTOR) Port_1(){

  if (P1IFG & SWITCH) {      /* did a button cause this interrupt? */

    P1IFG &= ~SWITCH;      /* clear pending sw interrupts */

    switch_interrupt_handler();/* single handler for all switches */

  }

}

