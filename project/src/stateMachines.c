#include <msp430.h>

#include "stateMachines.h"

#include "led.h"

#include "buzzer.h"

static char sb = 1;
static short x = 500;

void toggle_red()

{

  static char state = 0;



  switch (state) {

  case 0:

    red_on = 1;

    state = 1;

    break;

  case 1:

    red_on = 0;

    state = 0;

    break;

  }

}



void toggle_green()

{

  static char state = 0;



  switch (state) {

  case 0:

    green_on = 1;

    state = 1;

    break;

  case 1:

    green_on = 0;

    state = 0;

    break;

  }

}



void state_advance(char state)

{

  switch (state) {

  case 0:

    red_on = 1;

    green_on = 0;

    buzzer_set_period(4000);
    

    break;

  case 1:

    red_on = 0;

    green_on = 1;

    buzz_tone();

    break;

  case 2:

    red_on = 1;

    green_on = 1;
    
    buzzer_set_period(1000);

    break;

  case 3:

    red_on = 0;

    green_on = 0;

    buzzer_set_period(0);

    break;

  }

  led_changed = 1;

  led_update();
}

  void main_state(){
    static char state = 0;

    switch (state)

      {

      case 0:

      case 1:

	button_up_state();

	state++;

      case 2:

	button_down_state();

	state = 0;

      default: break;

      }
  }
  void button_up_state(){
    char changed = 0;

    sb = 1;

    red_on = 0;

    green_on = 1;


    led_changed = 1;

    led_update();

  }
void button_down_state(){
  char changed = 0;

  sb = 0;

  green_on = 0;

  red_on = 1;

  led_changed = 1;

  led_update();

}
/*
void button1_state(){
  state_advance(1);
}
void button2_state(){
  state_advance(2);
}
void button3_state(){
  state_advance(3);
}
void button4_state(){
  state_advance(4);
  }*/
  
void buzz_tone(){
  if(!sb){
    for(int i = x; i > 2000; i+=10){
      x = i;
      buzzer_set_period(x);
    }
  }else{
    buzzer_set_period(0);
  }
}

void buzzer_advance()

{

  static int frequency = 1000; // Initial frequency

  static int increment = 225;  // Increment/Decrement value



  // Increase or decrease frequency based on sb

  if (sb) {

    frequency += increment;

  } else {

    frequency -= increment;

  }



  // Ensure frequency stays within a reasonable range

  if (frequency < 100) {

    frequency = 100;

    sb = 1; // Set sb to 1 to start increasing frequency again

  } else if (frequency > 5000) {

    frequency = 5000;

    sb = 0; // Set sb to 0 to start decreasing frequency again

  }



  short cycles = 2000000 / frequency;

  buzzer_set_period(cycles);

}


