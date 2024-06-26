#include <msp430.h>

#include "switches.h"

#include "stateMachines.h"

#include "led.h"



char switch_pressed = 3;



/* Switch on P2 (S2) */

void

__interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */

    P2IFG &= ~SWITCHES;  /* clear pending sw interrupts */

    switch_interrupt_handler_p2();/* single handler for all switches */

  }

}
