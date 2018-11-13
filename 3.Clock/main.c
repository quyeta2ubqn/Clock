/*
############################
### Code Led Matrix########
### write by: NTD  #########

*/
  
#include <iostm8s003F3.h>
#include <intrinsics.h>
#define COT_LED_0       PC_ODR_ODR7
#define COT_LED_1       PD_ODR_ODR1
#define COT_LED_2       PD_ODR_ODR3
#define COT_LED_3       PD_ODR_ODR2
#define COT_LED_4       PA_ODR_ODR2
#define COT_LED_5       PA_ODR_ODR1
#define COT_LED_6       PD_ODR_ODR6
#define COT_LED_7       PD_ODR_ODR5

#define LATCH           PA_ODR_ODR3
#define QL0             0x01
#define QL1             0x02
#define QL2             0x04
#define QL3             0x08
#define QL4             0x10
#define QL5             0x20
#define QL6             0x40
#define QL7             0x80
#define mang_dem          0
#define mang_chinh        1

unsigned char matrix_led[40];
unsigned char matrix_led_dem[40];
unsigned char bien[255];
unsigned char bat_coi,TIME_COI;
unsigned char ma_quet[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

const unsigned char FONT_5X7[95][5] = {
{0x00, 0x00, 0x00, 0x00, 0x00}, // SPACE
{0x00, 0x00, 0x5F, 0x00, 0x00}, // !
{0x00, 0x03, 0x00, 0x03, 0x00},// "
{0x14, 0x3E, 0x14, 0x3E, 0x14},// #
{0x24, 0x2A, 0x7F, 0x2A, 0x12},// $
{0x43, 0x33, 0x08, 0x66, 0x61},// %
{0x36, 0x49, 0x55, 0x22, 0x50},// &
{0x00, 0x05, 0x03, 0x00, 0x00},// '
{0x00, 0x1C, 0x22, 0x41, 0x00},// (
{0x00, 0x41, 0x22, 0x1C, 0x00},// )
{0x14, 0x08, 0x3E, 0x08, 0x14},// *
{0x08, 0x08, 0x3E, 0x08, 0x08},// +
{0x00, 0x50, 0x30, 0x00, 0x00},// ,
{0x08, 0x08, 0x08, 0x08, 0x08},// -
{0x40, 0x00, 0x00, 0x00, 0x00},// .
{0x20, 0x10, 0x08, 0x04, 0x02},// /
{0x3E, 0x51, 0x49, 0x45, 0x3E},// 0
{0x00, 0x04, 0x02, 0x7F, 0x00},// 1
{0x42, 0x61, 0x51, 0x49, 0x46},// 2
{0x22, 0x41, 0x49, 0x49, 0x36},// 3
{0x18, 0x14, 0x12, 0x7F, 0x10},// 4
{0x27, 0x45, 0x45, 0x45, 0x39},// 5
{0x3E, 0x49, 0x49, 0x49, 0x32},// 6
{0x01, 0x01, 0x71, 0x09, 0x07},// 7
{0x36, 0x49, 0x49, 0x49, 0x36},// 8
{0x26, 0x49, 0x49, 0x49, 0x3E},// 9
{0x24, 0x00, 0x00, 0x00, 0x00},// :
{0x00, 0x56, 0x36, 0x00, 0x00},// ;
{0x08, 0x14, 0x22, 0x41, 0x00},// <
{0x14, 0x14, 0x14, 0x14, 0x14},// =
{0x00, 0x41, 0x22, 0x14, 0x08},// >
{0x02, 0x01, 0x51, 0x09, 0x06},// ?
{0x3E, 0x41, 0x59, 0x55, 0x5E},// @
{0x7E, 0x09, 0x09, 0x09, 0x7E},// A
{0x7F, 0x49, 0x49, 0x49, 0x36},// B
{0x3E, 0x41, 0x41, 0x41, 0x22},// C
{0x7F, 0x41, 0x41, 0x41, 0x3E},// D
{0x7F, 0x49, 0x49, 0x49, 0x41},// E
{0x7F, 0x09, 0x09, 0x09, 0x01},// F
{0x3E, 0x41, 0x41, 0x49, 0x3A},// G
{0x7F, 0x08, 0x08, 0x08, 0x7F},// H
{0x00, 0x41, 0x7F, 0x41, 0x00},// I
{0x30, 0x40, 0x40, 0x40, 0x3F},// J
{0x7F, 0x08, 0x14, 0x22, 0x41},// K
{0x7F, 0x40, 0x40, 0x40, 0x40},// L
{0x7F, 0x02, 0x0C, 0x02, 0x7F},// M
{0x7F, 0x02, 0x04, 0x08, 0x7F},// N
{0x3E, 0x41, 0x41, 0x41, 0x3E},// O
{0x7F, 0x09, 0x09, 0x09, 0x06},// P
{0x1E, 0x21, 0x21, 0x21, 0x5E},// Q
{0x7F, 0x09, 0x09, 0x09, 0x76},// R
{0x26, 0x49, 0x49, 0x49, 0x32},// S
{0x01, 0x01, 0x7F, 0x01, 0x01},// T
{0x3F, 0x40, 0x40, 0x40, 0x3F},// U
{0x1F, 0x20, 0x40, 0x20, 0x1F},// V
{0x7F, 0x20, 0x10, 0x20, 0x7F},// W
{0x41, 0x22, 0x1C, 0x22, 0x41},// X
{0x07, 0x08, 0x70, 0x08, 0x07},// Y
{0x61, 0x51, 0x49, 0x45, 0x43},// Z
{0x00, 0x7F, 0x41, 0x00, 0x00},// [
{0x02, 0x04, 0x08, 0x10, 0x20},// 
{0x00, 0x00, 0x41, 0x7F, 0x00},// ]
{0x04, 0x02, 0x01, 0x02, 0x04},// ^
{0x40, 0x40, 0x40, 0x40, 0x40},// _
{0x00, 0x01, 0x02, 0x04, 0x00},// `
{0x20, 0x54, 0x54, 0x54, 0x78},// a
{0x7F, 0x44, 0x44, 0x44, 0x38},// b
{0x38, 0x44, 0x44, 0x44, 0x44},// c
{0x38, 0x44, 0x44, 0x44, 0x7F},// d
{0x38, 0x54, 0x54, 0x54, 0x18},// e
{0x04, 0x04, 0x7E, 0x05, 0x05},// f
{0x08, 0x54, 0x54, 0x54, 0x3C},// g
{0x7F, 0x08, 0x04, 0x04, 0x78},// h
{0x00, 0x44, 0x7D, 0x40, 0x00},// i
{0x20, 0x40, 0x44, 0x3D, 0x00},// j
{0x7F, 0x10, 0x28, 0x44, 0x00},// k
{0x00, 0x41, 0x7F, 0x40, 0x00},// l
{0x7C, 0x04, 0x78, 0x04, 0x78},// m
{0x7C, 0x08, 0x04, 0x04, 0x78},// n
{0x38, 0x44, 0x44, 0x44, 0x38},// o
{0x7C, 0x14, 0x14, 0x14, 0x08},// p
{0x08, 0x14, 0x14, 0x14, 0x7C},// q
{0x00, 0x7C, 0x08, 0x04, 0x04},// r
{0x48, 0x54, 0x54, 0x54, 0x20},// s
{0x04, 0x04, 0x3F, 0x44, 0x44},// t
{0x3C, 0x40, 0x40, 0x20, 0x7C},// u
{0x1C, 0x20, 0x40, 0x20, 0x1C},// v
{0x3C, 0x40, 0x30, 0x40, 0x3C},// w
{0x44, 0x28, 0x10, 0x28, 0x44},// x
{0x0C, 0x50, 0x50, 0x50, 0x3C},// y
{0x44, 0x64, 0x54, 0x4C, 0x44},// z
{0x00, 0x08, 0x36, 0x41, 0x41},// {
{0x00, 0x00, 0x7F, 0x00, 0x00},// |
{0x41, 0x41, 0x36, 0x08, 0x00},// }
{0x02, 0x01, 0x02, 0x04, 0x02},
};

void Spi_write(unsigned char byte);
void Day_Data_Led(unsigned char cot);
void set_pixel(unsigned char x,unsigned char y,unsigned char status,unsigned char select);

void Init_all()
{
  CLK_ICKR_LSIEN                = 1;          
  CLK_ECKR_HSEEN                = 0;
  CLK_CKDIVR_HSIDIV             = 0x00;             
  CLK_SWCR_SWEN                 = 1;        
  CLK_SWR                       = 0xE1;
  __disable_interrupt();
   
 
  /*Cau hinh pin cho Cot Led5*/
  PA_DDR_DDR1    =1;    //Cot Led5
  PA_CR1_C11     =1;
  PA_ODR_ODR1    =0;
  
  /*Cau hinh pin cho Cot Led4*/
  PA_DDR_DDR2    =1;    //Cot Led4
  PA_CR1_C12     =1;
  PA_ODR_ODR2    =0;
  
  /*Cau hinh pin cho chan chot HC595*/
  PA_DDR_DDR3    =1;    
  PA_CR1_C13     =1;
  PA_ODR_ODR3    =0;
  
  /*Cau hinh pin cho Cot Led0*/
  PC_DDR_DDR7    =1;    //Cot Led0
  PC_CR1_C17     =1;
  PC_ODR_ODR7    =0;
  
  /*Cau hinh pin cho Cot Led1*/
  PD_DDR_DDR1    =1;    //Cot LED1
  PD_CR1_C11     =1;
  PD_ODR_ODR1    =0;

  /*Cau hinh pin cho Cot Led2*/
  PD_DDR_DDR2    =1;    //Cot Led2
  PD_CR1_C12     =1;
  PD_ODR_ODR2    =0;
  
  /*Cau hinh pin cho Cot Led3*/
  PD_DDR_DDR3    =1;    //Cot Led3
  PD_CR1_C13     =1;
  PD_ODR_ODR3    =0;
  
  /*Cau hinh pin cho Cot Led6*/
  PD_DDR_DDR6    =1;    //Cot Led6
  PD_CR1_C16     =1;
  PD_ODR_ODR6    =0;
  
  /*Cau hinh pin cho Cot Led7*/
  PD_DDR_DDR5    =1;    //Cot Led1
  PD_CR1_C15     =1;
  PD_ODR_ODR5    =0;
  
  /*Cau hinh SPI day HC595     */
  SPI_CR1       =0x44;
  SPI_CR2       =0x43;
  /*Cau hinh Coi                    */
  BEEP_CSR_BEEPEN       =1;
  BEEP_CSR_BEEPDIV      =31;
  
  TIM2_PSCR                     = 2;              
  TIM2_ARRH                     = (1000>>8);        
  TIM2_ARRL                     = (1000&0xFF);
  TIM2_CR1_ARPE                 = 1;          
  TIM2_IER_UIE                  = 1;         
  TIM2_CR1_CEN                  = 1; 
  
 
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

void reset_data()
{
  bien[QL0]=0;
  bien[QL1]=1;
  bien[QL2]=2;
  bien[QL3]=3;
  bien[QL4]=4;
  bien[QL5]=5;
  bien[QL6]=6;
  bien[QL7]=7;
  
   __enable_interrupt();
}

void Spi_write
(
unsigned char byte
)
{
  SPI_DR=byte;
  while( ! (SPI_SR & 0x02));
}
void Day_Data_Led
(
unsigned char cot
)
{
  unsigned char bien_cot=0;
  bien_cot=bien[cot];
  
 Spi_write(matrix_led[32+bien_cot]);
 Spi_write(matrix_led[24+bien_cot]);
 Spi_write(matrix_led[16+bien_cot]);
 Spi_write(matrix_led[8+bien_cot]);
 Spi_write(matrix_led[0+bien_cot]);
 LATCH =0;
 LATCH =1;
}
void quet_led
(
  unsigned char stt_cot
)
{
  COT_LED_0=0;
  COT_LED_1=0;
  COT_LED_2=0;
  COT_LED_3=0;
  COT_LED_4=0;
  COT_LED_5=0;
  COT_LED_6=0;
  COT_LED_7=0;  
  
  Day_Data_Led(stt_cot);

  COT_LED_0=stt_cot ;
  COT_LED_1=stt_cot>>1;
  COT_LED_2=stt_cot>>2;
  COT_LED_3=stt_cot>>3;
  COT_LED_4=stt_cot>>4;
  COT_LED_5=stt_cot>>5;
  COT_LED_6=stt_cot>>6;
  COT_LED_7=stt_cot>>7;
}
//------------------------------
void set_pixel
(
unsigned char x,
unsigned char y,
unsigned char status,
unsigned char select  //select =1 ghi vao mang chinh
)
{
  if(select==1)
  {
    if(status== 1)
      matrix_led[x] |= ma_quet[y];
    else
      matrix_led[x] &= ~ma_quet[y];
  }
  if(select==0)
  
   if(status== 1)
      matrix_led_dem[x] |= ma_quet[y];
    else
      matrix_led_dem[x] &= ~ma_quet[y];
  
    
}

//------------------------------------
void show_char
(
unsigned char x,
unsigned char data,
unsigned char select
)
{
  unsigned char num;
  num=data-32;
  for (unsigned char i=0;i<5;i++)
  {
    for (unsigned char j=0;j<8;j++)
    {
          if((FONT_5X7[num][i]>>j)& 0x01)
          set_pixel(i+x,j,1,select);
          else
          set_pixel(i+x,j,0,select);
 
     }
  }
}

//---------------------------------------------
void show_string
(
unsigned char x,
unsigned char *data,
unsigned char select

)
{
  while(*data!=0)
  {
    show_char(x,*data,select);
    x=x+6;
    data++;
  } 
}

//-------------------------------------
void chay_sang_phai(unsigned char delay)
{
  unsigned char i;
  unsigned char data;

  data=matrix_led[39];
  for(i=0;i<39;i++)
  matrix_led[39-i]=matrix_led[38-i];
  matrix_led[0]=data;
  delay_ms(delay);
}
//-----------------------------------------------

void chay_sang_trai(unsigned char delay)
{
  unsigned char i;
  unsigned char data;

  data=matrix_led[0];
  for(i=0;i<40;i++)
  {
  matrix_led[i]=matrix_led[i+1];
  }
  matrix_led[39]=data;
  delay_ms(delay);
  
}

//-------------------------------

void Xoa_mang
(
   
  
  unsigned char select
)
{
  unsigned char i;
  for(unsigned char k=0;k<8;k++)
  {
    for(i=0;i<8;i++)
  {
    if(select==mang_chinh)
    {
    matrix_led[0+i]=matrix_led[0+i]<<1;
    matrix_led[8+i]=matrix_led[8+i]<<1;
    matrix_led[16+i]=matrix_led[16+i]<<1;
    matrix_led[24+i]=matrix_led[24+i]<<1;
    matrix_led[32+i]=matrix_led[32+i]<<1;
    }
    else
    {
        matrix_led_dem[0+i]=matrix_led_dem[0+i]<<1;
        matrix_led_dem[8+i]=matrix_led_dem[8+i]<<1;
        matrix_led_dem[16+i]=matrix_led_dem[16+i]<<1;
        matrix_led_dem[24+i]=matrix_led_dem[24+i]<<1;
        matrix_led_dem[32+i]=matrix_led_dem[32+i]<<1;
    }
    
  }
  
  }
}

//-------------------------

void ghi_mang
(
  unsigned char delay
)
{
  unsigned char i;
  for(unsigned char k=0;k<8;k++)
  {
    for(i=0;i<8;i++)
  {
      matrix_led[0+i]=matrix_led[0+i]<<1;
      matrix_led[8+i]=matrix_led[8+i]<<1;
      matrix_led[16+i]=matrix_led[16+i]<<1;
      matrix_led[24+i]=matrix_led[24+i]<<1;
      matrix_led[32+i]=matrix_led[32+i]<<1;
  }
    for(i=0;i<8;i++)
    {                                                  
    matrix_led[0+i]  |= matrix_led_dem[0+i]  >>(7-k) &0x01 ;
    matrix_led[8+i]  |= matrix_led_dem[8+i]  >>(7-k) &0x01 ;
    matrix_led[16+i] |= matrix_led_dem[16+i] >>(7-k) &0x01 ;
    matrix_led[24+i] |= matrix_led_dem[24+i] >>(7-k) &0x01 ;
    matrix_led[32+i] |= matrix_led_dem[32+i] >>(7-k) &0x01 ;
    }
     delay_ms(delay);
  }
 
  }

int main(void)
{
  
  Init_all();
  reset_data();
  TIME_COI=10;
  bat_coi=0;
 
  while(1)
  { 


//chay_sang_phai(100);
//chay_sang_trai(70);
//chay_xuong_duoi(100);

  }

}
#pragma vector = TIM2_OVR_UIF_vector 
__interrupt void my_hanler(void)
{  
  static unsigned char scan_led=0x01;
  static unsigned char dem_coi=0;
  if(bat_coi==1)
  {
  dem_coi++;
  if(dem_coi==1)
    BEEP_CSR_BEEPEN=1;
  if(dem_coi==TIME_COI)
    BEEP_CSR_BEEPEN=0;
  if(dem_coi==TIME_COI*3)
    BEEP_CSR_BEEPEN=1;
  if(dem_coi==TIME_COI*4)
    BEEP_CSR_BEEPEN=0;
  }
  else
  {
    BEEP_CSR_BEEPEN=0;
  }
  
  scan_led=scan_led<<1;
  if(scan_led==0) 
  scan_led=0x01;
  quet_led(scan_led);
 
  TIM2_SR1_UIF =0;   
}