#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#define segmenty_DDR DDRA
#define segmenty PORTA
#define wybor_DDR DDRB
#define wybor PORTB
uint8_t seg7[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
uint8_t dane[] = {1, 2, 3, 4}

ISR(TIMER0_OVF_vect)
{
    static uint8_t i=0;
    wybor |= (1<<i);
    if(i++==3) i=0;
    segmenty = seg7[dane[i]];
    wybor &= ~(1<<i);
}
ISR(TIMER1_OVF_vect)
{
    if(date[3]++==9)
    {
        dane[3]=0;
        if(dane[2]++==9)
        {
            dane[2]=0;
            if (dane[1]++==9)
            {
                dane[1]=0;
                if(dane[0]++==9)
                {
                    dane[0]=0;
                }
            }
        }
    }
}

int main(void)
{
    segmenty_DDR = 0xff;
    wybor_DDR |= 0x0ff;
    wybor |= 0x0ff;
    segmenty = 0xff;
    TCCR0 = (1<<CS02);
    TCCR1B = (1<<CS12)|(1<<WGM12);
    TIMSK = (1<<TOIE0)|(1<<OCIE1A);
    OCR1A = 31250;
    sei();
    while (1)
    {

    }


}
