/***************************************
 * Module: Timer Driver Header File
 *
 * Date: 1st October 2019
 *
 * Author: Mohamed AbdElkader
 */

#ifndef TIMER_H_
#define TIMER_H_



#define Timer0_16_32_base       ((unsigned long) 0x40030000)
#define Timer0_32_64_base       ((unsigned long) 0x40036000)
#define RCGC1                   ((unsigned long) 0x400FE000)


#define RCGC1OFFSET         ((unsigned long) 0x104)
#define GPTMCTL             ((unsigned long) 0x00C)
#define GPTMCFG             ((unsigned long) 0x000)
#define GPTMTAMR            ((unsigned long) 0x004)
#define GPTMTAPR            ((unsigned long) 0x038)
#define GPTMTAMATCHR        ((unsigned long) 0x030)
#define GPTMTAILR           ((unsigned long) 0x028)
#define GPTMTAPMR           ((unsigned long) 0x040)
#define GPTMIMR             ((unsigned long) 0x018)
#define GPTMRIS             ((unsigned long) 0x01C)
#define GPTMICR             ((unsigned long) 0x024)
#define GPTMMIS             ((unsigned long) 0x020)
#define GPTMTAR             ((unsigned long) 0x048)



#define PRI4_INTERRUPT_PRIORITY (*((volatile unsigned long *)0xE000E410))
#define EN0_INTERRUPT_ENABLE    (*((volatile unsigned long *)0xE000E100))


#define TIMER0_A_INT_NO       19
#define TIMER0_B_INT_NO       20





#define REG(BASE,OFFSET)   (*((volatile unsigned long *)((BASE)+(OFFSET))))
#define SET_BIT(REG,BIT) ((REG) |= (1<<(BIT)))
#define CLEAR_BIT(REG,BIT) ((REG) &= (~(1<<(BIT))))



typedef enum { TIMER0=16 , TIMER1=17}TIMER_RCGC;
typedef enum { TBPWML=14, TBOTE=13, TBEVENT=10, TBSTALL=9, TBEN=8, TAPWML=6, TAOTE=5, RTCEN=4, TAEVENT=2, TASTALL=1, TAEN=0 }GPTMCTL_BITS;
typedef enum { GTAPLO=11, TAMRSU=10, TAPWMIE=9, TAILD=8, TASNAPS=7, TAWOT=6, TAMIE=5, TACDIR=4, TAAMS =3, TACMR=2, TAMR=0}GPTMTAMR_BITS;
typedef enum { ONE_SHOT = 0X1, PERIODIC= 0X2, CAPTURE = 0X3}TAMR_MODES;
typedef enum { TBMIM = 11, CBEIM = 10, CBMIM=9, TBTOIM=8, TAMIM=4, RTCIM=3, CAEIM=2, CAMIM=1, TATOIM=0}GPTMIMR_BITS;
typedef enum { TBMRIS= 11, CBERIS= 10, CBMRIS=9, TBTORIS=8, TAMRIS=4, RTCRIS=3, CAERIS=2, CAMRIS=1, TATORIS=0}GPTMRIS_BITS;
typedef enum { TTBMCINT= 11, CBECINT= 10, CBMCINT=9, TBTOCINT=8, TAMCINT=4, RTCCINT=3, CAECINT=2, CAMCINT=1, TATOCINT=0}GPTMICR_BITS;
typedef enum { TBMMIS= 11, CBEMIS= 10, CBMMIS=9, TBTOMIS=8, TAMMIS=4, RTCMIS=3, CAEMIS=2, CAMMIS=1, TATOMIS=0}GPTMMIS_BITS;




void TIMER0_Init(void);
void TIMER0_deInit(void);



#endif
