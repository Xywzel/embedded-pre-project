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

void setup_timer(void)
{
  // TCCR1B Timer/Counter 1 control register B
  TCCR1B |= (1 << WGM12); // use hw timer comparison
  // TIMSK1 Timer/Counter 1 Interrupt Mask Register
  // TIMER1_COMPA
  TIMSK1 |= (1 << OCIE1A);  // enable ctc interrupt
  // http://www.gnu.org/savannah-checkouts/non-gnu/avr-libc/user-manual/group__avr__interrupts.html#ogaad5ebd34cb344c26ac87594f79b06b73
  sei();
  // Define the address for the comparison value
  OCR1A = 49999;
  TCCR1B |= ((1 << CS10) | (1 << CS11)); // timer 1 control register B w prescaler
}

uint8_t toggle_leds(uint8_t);
uint8_t check_switch_state();

int main(void)
{
  setup_ddr();
  setup_timer();
  LEDS_PORT = 0;

  for(;;)
  {

  }
}

uint8_t toggle_leds(uint8_t state) {
  return state;
}

uint8_t check_switch_state() {
  uint8_t state = SWITCH_PORT;
  return state;
}

// Setting TIMSK1 to what it is sets a listener for TIMER1_COMPA_vect
ISR(TIMER1_COMPA_vect) {
  // TODO: this is called when the the timer counter hits the value 49999
}
