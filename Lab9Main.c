// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Sarthak Sarans
// Last Modified: 8/21/2024

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
#include "Sprite.h"

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void)
{ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0); // run this line for 80MHz
}
int blocks[10][10] = {0};
int score = 0;
Arabic_t ArabicAlphabet[] = {
    alif, ayh, baa, daad, daal, dhaa, dhaal, faa, ghayh, haa, ha, jeem, kaaf, khaa, laam, meem, noon, qaaf, raa, saad, seen, sheen, ta, thaa, twe, waaw, yaa, zaa, space, dot, null};
Arabic_t Hello[] = {alif, baa, ha, raa, meem, null};                                   // hello
Arabic_t WeAreHonoredByYourPresence[] = {alif, noon, waaw, ta, faa, raa, sheen, null}; // we are honored by your presence
int main0(void)
{ // main 0, demonstrate Arabic output
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_REDTAB);
  ST7735_FillScreen(ST7735_WHITE);
  Arabic_SetCursor(0, 15);
  Arabic_OutString(Hello);
  Arabic_SetCursor(0, 31);
  Arabic_OutString(WeAreHonoredByYourPresence);
  Arabic_SetCursor(0, 63);
  Arabic_OutString(ArabicAlphabet);
  while (1)
  {
  }
}
uint32_t M = 1;
uint32_t Random32(void)
{
  M = 1664525 * M + 1013904223;
  return M;
}
uint32_t Random(uint32_t n)
{
  return (Random32() >> 16) % n;
}
int swap();
int BlockMove(int posi);
// games  engine runs at 30Hz
sprite_t piece;
uint32_t Data, Position, Flag, Switch; // Global Variables
uint32_t stored = 4;
void TIMG12_IRQHandler(void)
{
  uint32_t pos, msg;
  if ((TIMG12->CPU_INT.IIDX) == 1)
  {                             // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
                                // game engine goes here
    // 1) sample slide pot
    Data = ADCin();
    // returns 0 - 2000
    // 2) read input switches
    Switch = Switch_In();

    // 3) move sprites
    Position = Convert(Data);
    int pos = BlockMove(Position);
    piece.x = validX(piece, pos);
    // 4) start sounds
    // 5) set semaphore
    Flag = 1;
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void)
{
  return (0x80 | ((GPIOB->DOUT31_0 >> 26) & 0x03));
}

void drawShape(sprite_t sprite)
{
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if (blocks[i][j])
      {
        ST7735_DrawBitmap(i * 12 + 4, j * 12 + 52, singleBlock, 12, 12);
      }
      else
      {
        ST7735_DrawBitmap(i * 12 + 4, j * 12 + 52, singleBlack, 12, 12);
      }
    }
  }
}

int swap()
{
  if (stored == 4)
  {
    stored = piece.shape;
    // go to next piece in array
    return 1;
  }
  else
  {
    int temp = stored;
    stored = piece.shape;
    piece.shape = temp;
    // call construstor of new shape;
    if (temp == 0)
    {
      Square(&piece, 1, squareImage, squareBlack);
    }
    else if (temp == 1)
    {
      Rectangle(&piece, 1, rectangleImage1, rectangleImage2, rectangleBlack1, rectangleBlack2);
    }
    else if (temp == 2)
    {
      LPiece(&piece, 1, LPiece1, LPiece2, LPiece3, LPiece4, LJBlack1, LJBlack2);
    }
    else
    {
      JPiece(&piece, 1, JPiece1, JPiece2, JPiece3, JPiece4, LJBlack1, LJBlack2);
    }
  }
  return 0;
}

void RandomPiece()
{
  int rand = Random(4);
  // int rand = 3;

  if (rand == 0)
  {
    Square(&piece, 1, squareImage, squareBlack);
  }
  else if (rand == 1)
  {
    Rectangle(&piece, 1, rectangleImage1, rectangleImage2, rectangleBlack1, rectangleBlack2);
  }
  else if (rand == 2)
  {
    LPiece(&piece, 1, LPiece1, LPiece2, LPiece3, LPiece4, LJBlack1, LJBlack2);
  }
  else
  {
    JPiece(&piece, 1, JPiece1, JPiece2, JPiece3, JPiece4, LJBlack1, LJBlack2);
  }
}

typedef enum
{
  English,
  Spanish,
  Portuguese,
  French
} Language_t;
Language_t myLanguage = English;
typedef enum
{
  HELLO,
  GOODBYE,
  LANGUAGE
} phrase_t;
const char Hello_English[] = "Hello";
const char Hello_Spanish[] = "\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] = "All\x83";
const char Goodbye_English[] = "Goodbye";
const char Goodbye_Spanish[] = "Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[] = "English";
const char Language_Spanish[] = "Espa\xA4ol";
const char Language_Portuguese[] = "Portugu\x88s";
const char Language_French[] = "Fran\x87"
                               "ais";
const char *Phrases[3][4] = {
    {Hello_English, Hello_Spanish, Hello_Portuguese, Hello_French},
    {Goodbye_English, Goodbye_Spanish, Goodbye_Portuguese, Goodbye_French},
    {Language_English, Language_Spanish, Language_Portuguese, Language_French}};
// use main1 to observe special characters
int main1(void)
{ // main1
  char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000); // set screen to black
  for (phrase_t myPhrase = HELLO; myPhrase <= GOODBYE; myPhrase++)
  {
    for (Language_t myL = English; myL <= French; myL++)
    {
      ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
      ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000); // set screen to black
  l = 128;
  while (1)
  {
    Clock_Delay1ms(2000);
    for (int j = 0; j < 3; j++)
    {
      for (int i = 0; i < 16; i++)
      {
        ST7735_SetCursor(7 * j + 0, i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7 * j + 4, i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void)
{ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ADCinit();
  TimerG12_IntArm(2666664, 0);
  TIMG12_IRQHandler();
  __enable_irq();
  Flag = 1;
  // note: if you colors are weird, see different options for
  //  ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  sprite_t rect;
  Rectangle(&rect, 1, rectangleImage1, rectangleImage2, rectangleBlack1, rectangleBlack2);
  // ST7735_DrawBitmap(10, 24, l, 24, 36); // player ship bottom
  // ST7735_DrawBitmap(50, 79, j, 24, 36);
  /// ST7735_DrawBitmap(23, 48, squareImage, 24, 24); // player ship bottom

  // ST7735_DrawBitmap(62, 48, rect.image[0], rect.w[0], rect.h[0]); // player ship bottom

  // for (uint32_t t = 500; t > 0; t = t - 5)
  // {
  //       int x=0;
  //        ST7735_DrawBitmap(x, 140, squareImage, 24, 24);
  //        Clock_Delay1ms(10);
  //        x=x+5%128;            // delay 50 msec
  // }
  //  ST7735_FillScreen(0x0000); // set screen to black
  //  ST7735_SetCursor(1, 1);
  //  ST7735_OutString("GAME OVER");
  //  ST7735_SetCursor(1, 2);
  //  ST7735_OutString("Nice try,");
  //  ST7735_SetCursor(1, 3);
  //  ST7735_OutString("Earthling!");
  //  ST7735_SetCursor(2, 4);
  //  ST7735_OutUDec(1234);
  int y = 0;
  while (1)
  {
    if (Flag)
    {
      Flag = 0;
      int posi = Position;
      ST7735_DrawBitmap(BlockMove(posi), y + 52, squareImage, 24, 24);
      Clock_Delay1ms(500);
      ST7735_DrawBitmap(BlockMove(posi), y + 52, squareBlack, 24, 24);
      y = (y + 12) % 120;
    }
  }
}

// use main3 to test switches and LEDs
int main(void)
{ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  ADCinit();
  TimerG12_IntArm(2666664, 0);
  TIMG12_IRQHandler();
  __enable_irq();
  ST7735_FillScreen(ST7735_BLACK);
  Rectangle(&piece, 1, rectangleImage1, rectangleImage2, rectangleBlack1, rectangleBlack2);
  int count = 0;
  ST7735_SetCursor(0, 0);

  int language = 0;

  ST7735_DrawBitmap(0, 160, startPage, 128, 160);
  printf("Rect\xE1ngulo");
  while (1)
  {
    if (Switch_In() & 0x1)
    {
      language = 1;
    }
    else if (Switch_In())
    {
      break;
    }
  }

  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetCursor(0, 0);

  if (!language)
  {
    printf("Nothing  ");
  }
  else
  {
    printf("Nada     ");
  }

while (1)
{
  if (Switch & 0x1)
  {
    rotate(&piece);
  }
  if (Switch & 0x2)
  {
    ST7735_SetCursor(0, 0);
    if (!language)
    {
      if (piece.shape == 0)
      {
        printf("Square   ");
      }
      if (piece.shape == 1)
      {
        printf("Rectangle");
      }
      if (piece.shape == 2)
      {
        printf("J        ");
      }
      if (piece.shape == 3)
      {
        printf("L        ");
      }
    }
    else
    {
      if (piece.shape == 0)
      {
        printf("Cuadrado  ");
      }
      if (piece.shape == 1)
      {
        printf("Rect\xE1ngulo");
      }
      if (piece.shape == 2)
      {
        printf("J         ");
      }
      if (piece.shape == 3)
      {
        printf("L         ");
      }
    }
    if (swap())
    {
      // call random piece function?
      RandomPiece();
      continue;
    }
  }
  int xPos = piece.x;
  ST7735_DrawBitmap(xPos, piece.y + 40, piece.image[piece.orientation], piece.w[piece.orientation], piece.h[piece.orientation]);
  Clock_Delay1ms(500);
  ST7735_DrawBitmap(xPos, piece.y + 40, piece.black[piece.orientation], piece.w[piece.orientation], piece.h[piece.orientation]);
  if (piece.y / 12 == 9)
  {
    if (clearBlocks(piece.y / 12))
    {
      break;
    }
    placeBlock(piece);
  }
  int dropped = drop(&piece);
  if (dropped) // check if being placed down
  {
    if (dropped == 2)
    {
      if (clearBlocks(piece.y / 12))
      {
        break;
      }
      if (placeBlock(piece))
      {
        break;
      }
    }
    drawShape(piece);
    if (processGrid())
    { // if full row then shift everyting down
      Clock_Delay1ms(50);
      drawShape(piece);
    } // replace with random piece function / array?
    RandomPiece();
  }
  // write code to test switches and LEDs
}
ST7735_FillScreen(ST7735_BLACK);
ST7735_SetCursor(0, 0);
if(!language){
printf("Game Over! \n");
printf("Score:%d \n", score);
}else{
  printf("\xADJuego terminado! \n");
printf("Puntaje:%d \n", score);
}
while (1)
{
}
}

// use main4 to test sound outputs
int main4(void)
{
  uint32_t last = 0, now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init();          // initialize switches
  LED_Init();             // initialize LED
  Sound_Init();           // initialize sound
  TExaS_Init(ADC0, 6, 0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while (1)
  {
    now = Switch_In(); // one of your buttons
    if ((last == 0) && (now == 1))
    {
      Sound_Shoot(); // call one of your sounds
    }
    if ((last == 0) && (now == 2))
    {
      Sound_Killed(); // call one of your sounds
    }
    if ((last == 0) && (now == 4))
    {
      Sound_Explosion(); // call one of your sounds
    }
    if ((last == 0) && (now == 8))
    {
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void)
{ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  // note: if you colors are weird, see different options for
  //  ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();                                       // PB18 = ADC1 channel 5, slidepot
  Switch_Init();                                   // initialize switches
  LED_Init();                                      // initialize LED
  Sound_Init();                                    // initialize sound
  TExaS_Init(0, 0, &TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  TimerG12_IntArm(2666664, 0);                     // initialize interrupts on TimerG12 at 30 Hz
  TIMG12_IRQHandler();
  // initialize all data structures
  __enable_irq();

  while (1)
  {
    // wait for semaphore
    // clear semaphore
    // update ST7735R
    // check for end game or level switch
  }
}
