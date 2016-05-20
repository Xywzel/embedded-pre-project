/*
 * This program takes input from switches and turns LEDs
 * and servo motor to correct setting based on the buttons.
 * LEDs will be turned on for 3s after corresponding button
 * is pressed.
 */
#include <inttypes.h> /* definitions for uint8_t */
#include <avr/io.h>   /* definitions for all PORT* and other registers */
#include <avr/interrupt.h>

/* LEDs are uset with portC and output mode */
#define LEDS_PORT PORTC
#define LEDS_DDR  DDRC
/* Buttons are used with bins and input mode */
#define BUTTONS_DDR DDRA
#define BUTTONS_PIN PINA

// Timer and bin for servo
#define SERVO_PIN PB5
#define SERVO_TIMER TCCR2B

// First free timer counter for other use
#define FREE_TIMER_A TCCR3A
#define FREE_TIMER_B TCCR3B

volatile uint8_t reading = 1;

void setup(void) {
    LEDS_DDR = 0xff;
    BUTTONS_DDR = 0x00;
    // setup timer
    cli();
    TCCR3A = 0;
    TCCR3B = 0 | (1 << WGM32) | (1 << CS30) | (1 << CS32);
    TIMSK3 |= (1 << OCIE3A);
    OCR3A = 15624;
    sei();
}

void reset_timer(void) {
    TCNT3 = 0;
}

void start_pwm(int val){
   DDRB = 0xff;
   TCCR1A |= (1 << COM1A0) | (1 << COM1A1) | (1 << WGM11);
   TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
   ICR1 = 4999;
   OCR1A = ICR1 - val;
}


void start_turning(uint8_t n){
    uint16_t length = 313;
    switch (n) {
        case 0b00000001:
            length += (0 * 17);
            break;
        case 0b00000010:
            length += (1 * 17);
            break;
        case 0b00000100:
            length += (2 * 17);
            break;
        case 0b00001000:
            length += (3 * 17);
            break;
        case 0b00010000:
            length += (4 * 17);
            break;
        case 0b00100000:
            length += (5 * 17);
            break;
        case 0b01000000:
            length += (6 * 17);
            break;
        case 0b10000000:
            length += (7 * 17);
            break;
        default:
            reading = 1;
            LEDS_PORT = 0;
    }
    if (n > 0) {
        reading = 0; // Don't read while controlling
        LEDS_PORT = n; // Set leds to correct value
        reset_timer();
        start_pwm(length);
    }
}

int main(void) {
    setup();
    uint8_t buttons = 0x00;
    for (;;) {
        buttons = ~BUTTONS_PIN;
        if (reading > 0 && buttons > 0) {
            start_turning(buttons);
        }
    }
    return 0;
}

uint16_t max_counter = 3;
volatile uint16_t counter = 0;

ISR(TIMER3_COMPA_vect){
    if ((counter++) >= max_counter) {
        counter = 0;
        reading = 1;
        LEDS_PORT = 0;
        TCCR1A &= ~_BV(COM1A1); // END PWM
    }
}
