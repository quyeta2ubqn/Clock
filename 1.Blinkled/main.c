#include <iostm8s005k6.h>
#include <intrinsics.h>

#define led0  PD_ODR_ODR7        //30
#define led1  PD_ODR_ODR6        //32
#define led2  PD_ODR_ODR5        //25
#define led3  PD_ODR_ODR4        //27
#define led4  PD_ODR_ODR3
#define led5  PD_ODR_ODR2
#define led6  PD_ODR_ODR1
#define led7  PD_ODR_ODR0
////
#define led8  PC_ODR_ODR7   
#define led9  PC_ODR_ODR6     
#define led10 PC_ODR_ODR5  
#define led11 PC_ODR_ODR4  
#define led12 PC_ODR_ODR3  
#define led13 PC_ODR_ODR2  
#define led14 PC_ODR_ODR1  

#define SPI_SDI   PB_ODR_ODR2
#define SPI_SCK   PB_ODR_ODR0
#define SPI_LAT   PB_ODR_ODR1
#define HIGH 1
#define LOW  0

unsigned int duty[23];
unsigned char data_hc;
unsigned char maled[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};



void Init_all()
{       //doc phan clock
  CLK_ICKR_LSIEN        =1;     //internal clock control register// bat che do clock noi
  CLK_ECKR_HSEEN        =0;     //External clock control register// tat che do  thach anh ngoài
  CLK_CKDIVR_HSIDIV     =0x00;  // bo chia 2
  CLK_SWCR_SWEN         =1;     // thanh ghi dieu khien bat tat//cho phép bat tat sung clock nguon
  CLK_SWR               =0xE1;  //chon che do bo chia HSI // set thanh ghi SWCR truoc de bit thanh ghi này
  //GPIO port D
  PD_DDR_DDR7                 =1;  
  PD_CR1_C17                  =1;
  PD_DDR_DDR6                 =1;  
  PD_CR1_C16                  =1;
  PD_DDR_DDR5                 =1;  
  PD_CR1_C15                  =1;
  PD_DDR_DDR4                 =1;  
  PD_CR1_C14                  =1;
  PD_DDR_DDR3                 =1;  
  PD_CR1_C13                  =1;
  PD_DDR_DDR2                 =1;  
  PD_CR1_C12                  =1;
  PD_DDR_DDR1                 =1;  
  PD_CR1_C11                  =1;
  PD_DDR_DDR0                 =1;  
  PD_CR1_C10                  =1;
  //GPIO PORT C
  PC_DDR_DDR7                 =1;
  PC_CR1_C17                  =1; 
  PC_DDR_DDR6                 =1;
  PC_CR1_C16                  =1; 
  PC_DDR_DDR5                 =1;
  PC_CR1_C15                  =1; 
  PC_DDR_DDR4                 =1;
  PC_CR1_C14                  =1; 
  PC_DDR_DDR3                 =1;
  PC_CR1_C13                  =1; 
  PC_DDR_DDR2                 =1;
  PC_CR1_C12                  =1; 
  PC_DDR_DDR1                 =1;
  PC_CR1_C11                  =1;
  PC_DDR_DDR0                 =1;
  PC_CR1_C10                  =1;
  //SPI voi IC HC595
  PB_DDR_DDR0                 =1;
  PB_CR1_C10                  =1;
  
  PB_DDR_DDR1                 =1;
  PB_CR1_C11                  =1;
  
  PB_DDR_DDR2                 =1;
  PB_CR1_C12                  =1;
  
  

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
void sang_don(unsigned int delay)
{
  unsigned char n;
  unsigned char i,j;
  while(1)
  {  
    n=15;
    duty[0]=10;
   
   for(j=15;j>0;j--)
   {
     for(i=0;i<n-1;i++)
    {
      duty[i+1]=duty[i];
      duty[i]=0;
      delay_ms(delay);
    }
    n--;
   duty[j-1]=10;
   duty[0]=10;
   delay_ms(delay);
   }
   for(i=0;i<15;i++)// tat led
     duty[i]=0;
   
  }

}

void hieu_ung_sao_bang(unsigned int delay)
{
  duty[2]=90;
  duty[1]=5;
  duty[0]=5;
  while(1)
  {
   for(unsigned char i=0;i<22;i++)
   {
     duty[22-i]=duty[21-i];
   }
   duty[0]=duty[22];
   delay_ms(delay);
  }
}
void hieu_ung_led_vay()
{
  while(1)
  {
    duty[0]=77;
    duty[1]=79;
    duty[2]=68;
    duty[3]=28;
    duty[4]=39;
    duty[5]=40;
    duty[6]=40;
    duty[7]=48;
    duty[8]=47;
    duty[9]=47;
    duty[10]=43;
    duty[11]=42;
    duty[12]=41;
    duty[13]=48;
    duty[14]=47; 
  }
}
void SPI_RW(unsigned char data_out)
{
 // SPI_CS=0;
 // unsigned char data_in=0;
  for(unsigned char i=0;i<8;i++)
  {
    SPI_SDI=(data_out>>((7-i))&0x01);
    SPI_SCK=1;
   
  // data_in|=SPI_SDO;
    SPI_SCK=0;
 
   
  //  data_in=data_in<<1;
  }          
  //SPI_CS=1;
 // return data_in;
}
void HC_595(unsigned char data_out)
{
  SPI_RW(data_out);
  SPI_LAT=1;
  SPI_LAT=0;
  
}
void dig_write(unsigned char PIN,unsigned char status)
{
  if(status==HIGH)
  data_hc |=maled[PIN];
  else
    data_hc &=~maled[PIN];
}

int main(void)
{
  Init_all();
  duty[16]=50;
  duty[17]=50;
  duty[22]=50;
  while(1)
  {    
   
  hieu_ung_sao_bang(50);
  //sang_don(10);
 // hieu_ung_led_vay();
    
  }
  
}
// trinh phuc vu ngat
#pragma vector = TIM2_OVR_UIF_vector
  __interrupt void my_handler(void)
  { 
      static unsigned int dem=0;
    if(++dem==100) dem=0;
    if(dem<duty[0])
    led0=1;
    else 
    led0=0;
    
    if(dem<duty[1])
    led1=1;
    else 
    led1=0;
    
    if(dem<duty[2])
    led2=1;
    else 
    led2=0;
    
    if(dem<duty[3])
    led3=1;
    else 
    led3=0;
    
    if(dem<duty[4])
    led4=1;
    else 
    led4=0;
    
    if(dem<duty[5])
    led5=1;
    else 
    led5=0;
    
    if(dem<duty[6])
    led6=1;
    else 
    led6=0;
    
    if(dem<duty[7])
    led7=1;
    else 
    led7=0;
    
    if(dem<duty[8])
    led8=1;
    else 
    led8=0;
    
     if(dem<duty[9])
    led9=1;
    else 
    led9=0;
    
     if(dem<duty[10])
    led10=1;
    else 
    led10=0;
    
     if(dem<duty[11])
    led11=1;
    else 
    led11=0;
    
     if(dem<duty[12])
    led12=1;
    else 
    led12=0;
    
     if(dem<duty[13])
    led13=1;
    else 
    led13=0;
    
    if(dem<duty[14])
    led14=1;
    else 
    led14=0;

    if(dem<duty[15])
    dig_write(7,HIGH);
    else
    dig_write(7,LOW);
    
     if(dem<duty[16])
    dig_write(6,HIGH);
    else
    dig_write(6,LOW);
     if(dem<duty[17])
    dig_write(5,HIGH);
    else
    dig_write(5,LOW);
    
     if(dem<duty[18])
    dig_write(4,HIGH);
    else
    dig_write(4,LOW);
    
     if(dem<duty[19])
    dig_write(3,HIGH);
    else
    dig_write(3,LOW);
    
     if(dem<duty[20])
    dig_write(2,HIGH);
    else
    dig_write(2,LOW);
     
    if(dem<duty[21])
    dig_write(1,HIGH);
    else
    dig_write(1,LOW);
     
    if(dem<duty[22])
    dig_write(0,HIGH);
    else
    dig_write(0,LOW);
     
    HC_595(data_hc);
   
    TIM2_SR1_UIF =0; // xoa co ngat
    
  }
// hieu ung sang don, hieu ung sao bang
//bat duty led1=30,led 2=32,led 3=25 ,27,23,60,89 // bat tat 7 led, moi led mot duty khac nhau
// trinh phuc vu ngat
