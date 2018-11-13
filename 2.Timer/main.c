#include <iostm8s003f3.h>
#include <intrinsics.h>

#define SPI_LAT         PA_ODR_ODR3
#define OC6             PA_ODR_ODR1
#define OC5             PA_ODR_ODR2

#define I2C_SCL         PB_ODR_ODR4
#define I2C_SDA         PB_ODR_ODR5

#define BTN             PC_ODR_ODR3
#define IR              PC_ODR_ODR4
#define SPI_CLK         PC_ODR_ODR5
#define SPI_DATA        PC_ODR_ODR6
#define OC1             PC_ODR_ODR7

#define OC2             PD_ODR_ODR1
#define OC3             PD_ODR_ODR2
#define OC4             PD_ODR_ODR3
#define BEEP            PD_ODR_ODR4
#define OC8             PD_ODR_ODR5
#define OC7             PD_ODR_ODR6
//config pin
//define pin
//setup timer -> ngat timer-> quet tung cot
unsigned char data_hc;
unsigned char cot[8];
unsigned char maled[40];

void Init_all(void)
{       // Xung Clock
  CLK_ICKR_LSIEN        =1;     //internal clock control register// bat che do clock noi
  CLK_ECKR_HSEEN        =0;     //External clock control register// tat che do  thach anh ngoài
  CLK_CKDIVR_HSIDIV     =0x00;  // bo chia 2
  CLK_SWCR_SWEN         =1;     // thanh ghi dieu khien bat tat//cho phép bat tat sung clock nguon
  CLK_SWR               =0xE1;
  //Timer
  
  
  // PORTA
  PA_DDR_DDR3=1;
  PA_CR1_C13=1;
  
  PA_DDR_DDR2=1;
  PA_CR1_C12=1;
  
  PA_DDR_DDR1=1;
  PA_CR1_C11=1;
  // PORTC
  PC_DDR_DDR3=1;
  PC_CR1_C13=1;
  
  PC_DDR_DDR4=1;
  PC_CR1_C14=1;
  
  PC_DDR_DDR5=1;
  PC_CR1_C15=1;
  
  PC_DDR_DDR6=1;
  PC_CR1_C16=1;
  
  PC_DDR_DDR7=1;
  PC_CR1_C17=1;
  //PORT B
  PB_DDR_DDR4=1;
  PB_CR1_C14=1;
  
  PB_DDR_DDR5=1;
  PB_CR1_C15=1;
  //PORT D
  PD_DDR_DDR1=1;
  PD_CR1_C11=1;
  
  PD_DDR_DDR2=1;
  PD_CR1_C12=1;
  
  PD_DDR_DDR3=1;
  PD_CR1_C13=1;
  
  PD_DDR_DDR4=1;
  PD_CR1_C14=1;
  
  PD_DDR_DDR5=1;
  PD_CR1_C15=1;
  
  PD_DDR_DDR6=1;
  PD_CR1_C16=1;
  
  OC8=cot[7];
  OC7=cot[6];
  OC6=cot[5];
  OC5=cot[4];
  OC4=cot[3];
  OC3=cot[2];
  OC2=cot[1];
  OC1=cot[0];
  
    //Timer
  //timer 1 la tim advand dung dk dong co, con lai timer basic
  TIM2_PSCR             =2; // chia cho 2 mu x, x=2
  TIM2_ARRH             =(300>>8);// ghi 8 bit thap cua 300 nen phai dich
  TIM2_ARRL             =(300&0xFF);
  TIM2_CR1_ARPE         =1;
  TIM2_IER_UIE          =1; // cho phep ngat
  TIM2_CR1_CEN          =1; // kich hoat timmer
   __enable_interrupt();
 
}
void SPI_RW(unsigned int data_out)
{
  for(unsigned char j=0;j<1;j++)
  {
 for(unsigned char i=0;i<40;i++)
   {
  SPI_DATA= (data_out>>(39-i))&(0x01);
  SPI_CLK=1;
  
  SPI_CLK=0;
  
    }
  }
}
void delay_us(unsigned int time)
{
  while(time--)
  {
    asm("NOP");// ton 2 chu ki may.
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    
  }
}
void delay_ms(unsigned int time)
{
  while(time--)
    delay_us(1000);
 
}
void HC_595(unsigned int data_out)
{
  SPI_RW(data_out);
  SPI_LAT=1;
  SPI_LAT=0;
}
void write_code(unsigned int code)
{

}

main()
{
  Init_all();

 while(1)
 {

 }
  
 
}

// trinh phuc vu ngat
#pragma vector = TIM2_OVR_UIF_vector
  __interrupt void my_handler(void)
  { 
    
  
    HC_595(0x00);
    OC8=1;
    delay_us(10);
    OC8=0;
 

    HC_595(0x3F);
    OC7=1;
    delay_us(10);
    OC7=0;
    

    HC_595(0x7F);
    OC6=1;
    delay_us(10);
    OC6=0;
    
    HC_595(0xCC);
    OC5=1;
    delay_us(10);
    OC5=0;
    
    HC_595(0xCC);
    OC3=1;
    delay_us(10);
    OC3=0;
    
    HC_595(0x7F);
    OC4=1;
    delay_us(10);
    OC4=0;
    
     HC_595(0x3F);
    OC2=1;
    delay_us(10);
    OC2=0;
    
     HC_595(0x00);
    OC1=1;
    delay_us(10);
    OC1=0;
 

    


  
    
  
   
    TIM2_SR1_UIF =0; // xoa co ngat
    
  }