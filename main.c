#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#define segmenty_DDR DDRA
#define segmenty PORTA
#define wybor_DDR DDRB
#define wybor PORTB
#define klawiatura_DDR DDRC
#define klawiatura_PULLUP PORTC
#define klawiatura_PIN PINC
#define klawisz1 0
volatile uint8_t przycisk1=0;

uint8_t seg7[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
volatile uint8_t dane[] = {1, 2, 3, 4}

ISR(TIMER0_OVF_vect)
{
    static uint8_t i=0;
    wybor |= (1<<i);
    if(i++==3) i=0;
    segmenty = seg7[dane[i]];
    wybor &= ~(1<<i);

    if (!(klawiatura_PIN & (1<<klawisz1)))
    {

        switch(przycisk1)
        {
            case 0:
            przycisk1=1;
            break;
            case 1:
            przycisk1=2;
            break;
            case 2:
            przycisk1=3
            break;
        }

    } else {

            switch(przycisk1)
        {
            case 3:
            przycisk1=4;
            break;
            case 4:
            przycisk1=5;
            break;
            case 5:
            przycisk1=0
            break;
        }



    }

}


ISR(TIMER1_OVF_vect)
{

}

int main(void)
{
    klawiatura_PULLUP |= (1<<klawisz1);
    klawiatura_DDR &= ~(1<<klawisz1);
    segmenty_DDR = 0xff;
    wybor_DDR |= 0x0ff;
    wybor |= 0x0ff;
    segmenty = 0xff;
    TCCR0 = (1<<CS02);
    TCCR1B = (1<<CS12)|(1<<WGM12);
    TIMSK = (1<<TOIE0)|(1<<OCIE1A);
    OCR1A = 62500;
    sei();
    while (1)
    {
        if(przycisk1==3)

        if (dane[3]++==9)
        {
            dane[3]=0;
            if (dane[2]++==6)
            {
                dane[2]=0;
                if (dane[1]++==9)
                {
                    dane[1]=0;
                    if (dane[0]++==9)
                    {
                        dane[0]=0;
                    }
                }
            }
        }
    }
    }


}


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
