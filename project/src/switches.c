#include <msp430.h>

#include "switches.h"

#include "led.h"

#include "stateMachines.h"


char switch_state_down, switch_state_changed; /* effectively boolean */

char switch_pressed;



static char

switch_update_interrupt_sense_p2()

{

  char p2val = P2IN;

  /* update switch interrupt to detect changes from current buttons */

  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */

  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}

static char

switch_update_interrupt_sense()

{

  char p1val = P1IN;

  /* update switch interrupt to detect changes from current buttons */

  P1IES |= (p1val & SWITCH);/* if switch up, sense down */

  P1IES &= (p1val | ~SWITCH);/* if switch down, sense up */

  return p1val;

}



void switch_init(){

  P1REN |= SWITCH;/* enables resistors for switches */

  P1IE |= SWITCH;/* enable interrupts from switches */

  P1OUT |= SWITCH;/* pull-ups for switches */

  P1DIR &= ~SWITCH;/*set switches' bits for input */

  P2REN |= SWITCHES;

  P2IE |= SWITCHES;

  P2OUT |= SWITCHES;

  P2DIR &= ~SWITCHES;

  switch_update_interrupt_sense();
  
  switch_update_interrupt_sense_p2();

  led_update();

}



void

switch_interrupt_handler()

{

  char p1val = switch_update_interrupt_sense();

  // switch_state_down = (p1val & SW1) ? 0 : 1; /* 0 when SW1 is up */

  if((p1val & SW1) == 0) state_advance(4);

  //state_advance(4);
  
  switch_state_down = !switch_state_down;
  
  switch_state_changed = switch_state_changed;

  led_update();

}
void

switch_interrupt_handler_p2(){

  char p2val = switch_update_interrupt_sense_p2();

  if ((p2val & S1) == 0) switch_pressed = 0; 

  if ((p2val & S2) == 0) switch_pressed = 1; 

  if ((p2val & S3) == 0) switch_pressed = 2; 

  if ((p2val & S4) == 0) switch_pressed = 3;

  state_advance(switch_pressed);
  
  switch_state_down = !switch_state_down;

  switch_state_changed = switch_state_changed;

  led_update();

}
