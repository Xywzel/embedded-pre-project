#include <inttypes.h> /* definitions for uint8_t and others */
#include <avr/io.h>   /* definitions for all PORT* and other registers. You absolutely will need this one */
#include <avr/interrupt.h>

/* Needed only when the _delay_ms is used
 * TODO: delete when no need for _delay_ms
 */
#include <util/delay.h>

#define LEDS_PORT PORTC
#define LEDS_DDR  DDRC
#define LEDS_PIN  PINC

#define SWITCH_PORT PORTA
#define SWITCH_DDR DDRA
#define SWITCH_PIN PINA

#define BLINK_LED PC2
#define OTHER_LED PC0

void setup_ddr(void) {
  /* Configure the leds port as output
   * DDR* registers define GPIO pin direction (1 means output and 0 input)
   * Refer atmega 2560 datasheet for more about this
   */
  LEDS_DDR   = 0xff;
  SWITCH_DDR = 0x0;
}

void reset_timer(void) {
  TCNT1 = 0;
}

void setup_timer(void) {
  // TCCR1B Timer/Counter 1 control register B
  TCCR2B |= (1 << WGM22); // use hw timer comparison
  // TIMSK1 Timer/Counter 1 Interrupt Mask Register
  // TIMER1_COMPA
  TIMSK2 |= (1 << OCIE2A);  // enable ctc interrupt
  // http://www.gnu.org/savannah-checkouts/non-gnu/avr-libc/user-manual/group__avr__interrupts.html#ogaad5ebd34cb344c26ac87594f79b06b73
  sei();
  // Define the address for the comparison value
  OCR2A = 120;
  TCCR2B |= ((1 << CS20) | (1 << CS21)); // timer 1 control register B w prescaler
}

uint8_t check_switch_state();

volatile int buttons_ready = 1;

int main(void) {
  setup_ddr();
  setup_timer();
  LEDS_PORT = 0;
  int buttons_down;

  for(;;) {
    buttons_down = ~SWITCH_PIN;

    if (buttons_ready && buttons_down > 0) {
      buttons_ready = 0;
      LEDS_PORT = buttons_down;
      reset_timer();
    }
  }
}

uint8_t check_switch_state() {
  uint8_t state = SWITCH_PORT;
  return state;
}

// Setting TIMSK1 to what it is sets a listener for TIMER1_COMPA_vect
ISR(TIMER2_COMPA_vect) {
  LEDS_PORT = 0b00000000;
  buttons_ready = 1;
  // TODO: this is called when the the timer counter hits the value 49999
}
