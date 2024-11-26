

#ifndef SPRITE_H_
#define SPRITE_H_

#include <stdint.h>

typedef enum {dead,alive} status_t;
struct sprite {
  int32_t x;      // x coordinate
  int32_t y;      // y coordinate
  int32_t vx,vy;  // pixels/30Hz

  const unsigned short *image [4]; // ptr->image
  const unsigned short *black ;
  status_t life;        // dead/alive
  int32_t w [4]; // width
  int32_t h [4]; // height
  uint32_t needDraw; // true if need to draw
  uint32_t orientation; 
};
typedef struct sprite sprite_t;

extern void Square(sprite_t *sprite, uint32_t speed, const unsigned short *squareImage, const unsigned short *squareBlack);
extern void Rectangle(sprite_t *sprite, uint32_t speed, const unsigned short *rectangleImage1, const unsigned short *rectangleImage2);
#endif 
