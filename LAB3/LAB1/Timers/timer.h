
#ifndef TIMER_H_
#define TIMER_H_

#define PRESCALE 5 // 1024
#define PRESCALE_VALUE 1024
//#define PRESCALE 4 // 1024
//#define PRESCALE_VALUE 256
//#define PRESCALE 3 // 128
//#define PRESCALE_VALUE 128
//#define PRESCALE 2 // 64
//#define PRESCALE_VALUE 64
//#define PRESCALE 1 // 0
//#define PRESCALE_VALUE 0

void Timer0_cmp_start(uint8_t porovnani);
void Timer0_ovf_start();
void Timer0_fastpwm_start(uint8_t strida);
void Timer0_Stop();

void Timer1_cmp_B_start(uint16_t porovnani);
void Timer1_cmp_A_start(uint16_t porovnani);
void Timer1_ovf_start(uint16_t zbytek);
void Timer1_fastpwm_start(uint8_t strida);
void Timer1_phasepwm_start(uint8_t strida);
void Timer1_Stop();

void Timer2_cmp_start(uint8_t porovnani);
void Timer2_ovf_start();
void Timer2_fastpwm_start(uint8_t strida);
void Timer2_Stop();

void Timer3_cmp_start(uint16_t porovnani);
void Timer3_ovf_start(uint16_t zbytek);
void Timer3_Stop();




#endif /* TIMER_H_*/