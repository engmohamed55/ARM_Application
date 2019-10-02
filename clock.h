#ifndef clock
#define clock


#define RIS_CLOCK_REG   (*((volatile unsigned long *)0x400FE050))
#define RCC_CLOCK_REG   (*((volatile unsigned long *)0x400FE060))
#define RCC2_CLOCK_REG  (*((volatile unsigned long *)0x400FE070))

typedef enum{   EXTERNAL_CRYSTAL = 0x0,INTERNAL_OSC = 0x1}Data_type_clock;
typedef enum{MH_3_579545=0x4,MH_3_6864=0x5,MH_4 = 0x6,MH_4_096= 0x7,MH_16 = 0x15}Crystall_no;  //there are more crystall see 10.1 shape the world
typedef struct{
    Data_type_clock source_clock;
    Crystall_no crystal;
    unsigned char required_freq;

}Clock_struct;


extern Clock_struct clock_data;

void CLOCK_Init(void);
#endif
