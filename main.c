#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"


void btn_init(){
	GPIO0->PIN_CNF[13]=(3<<2);
	// GPIO0->PIN_CNF[14]=(3<<2);
	// GPIO0->PIN_CNF[15]=(3<<2);
	// GPIO0->PIN_CNF[16]=(3<<2);
}
void led_init(){
	  GPIO0->PIN_CNF[17] = 1;
	  GPIO0->PIN_CNF[18] = 1;
	  GPIO0->PIN_CNF[19] = 1;
	  GPIO0->PIN_CNF[20] = 1;
};

int isBtnPressed(int placement) {
	return (!(GPIO0->IN & (1 << placement)));
}

void led_off(int placement){
	GPIO0->OUTSET |= (1<<placement);
};

void led_on(int placement){
	GPIO0->OUTCLR &= (1<<placement);
};

// ssize_t _write(int fd, const void *buf, size_t count){
// 	char * letter = (char *)(buf);
// 	for(int i = 0; i < count; i++){
// 		uart_send(*letter);
// 		letter++;
// 	}
// return count;

// }


int main(){
    // led_init();
    btn_init();
	// // int lightAON=1;
    // // int sleep=0;
    // for(int i=17; i<21;i++){
	// 	led_off(i);
	// 	// lightAON=0;
	// }
    PPI->CHENSET|=(1<<0);
    PPI->CHENSET|=(1<<1);
    PPI->CHENSET|=(1<<2);
    PPI->CHENSET|=(1<<3);
    PPI->CHENSET|=(1<<4);

    GPIOTE->CONFIG[0]=(13 <<8 ) | (1<<0) | (2 << 16);

    GPIOTE->CONFIG[1]=(17 << 8) | (3<<0) | (3 << 16) | (1<<20);
    GPIOTE->CONFIG[2]=(18 << 8) | (3<<0) | (3 << 16) | (1<<20);
    GPIOTE->CONFIG[3]=(19 << 8) | (3<<0) | (3 << 16) | (1<<20);
    GPIOTE->CONFIG[4]=(20 << 8) | (3<<0) | (3 << 16) | (1<<20);

   

    PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[1]);

    PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[2]);

    PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[3]);

    PPI->PPI_CH[3].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[3].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[4]);

     for (int i = 17; i <= 20; i++)
	{
		GPIO0->DIRSET = (1 << i);
		GPIO0->OUTSET = (1 << i);
	}

    while(1){

    
           
            
        }

        
		
        
        

    }


    // if(isBtnPressed(13)){
    //         if (!lightAON)
    //         {
    //         led_on(17);
    //         led_on(18);
    //         led_on(19);
    //         led_on(20);
    //         lightAON=1;
    //         }

    //          if (lightAON)
    //         {
    //         led_off(17);
    //         led_off(18);
    //         led_off(19);
    //         led_off(20);
    //         lightAON=0;
    //         }

// sleep = 10000;
		// while(--sleep);