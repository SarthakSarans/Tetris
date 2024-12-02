

#ifndef SPRITE_H_
#define SPRITE_H_

#include <stdint.h>

typedef enum
{
  dead,
  alive
} status_t;
typedef enum
{
  sq,
  rect,
  lshape,
  jshape
} shape_t;
struct sprite
{
  int32_t x;      // x coordinate
  int32_t y;      // y coordinate
  int32_t vx, vy; // pixels/30Hz
  shape_t shape;
  const unsigned short *image[4]; // ptr->image
  const unsigned short *black[4];
  status_t life;     // dead/alive
  int32_t w[4];      // width
  int32_t h[4];      // height
  uint32_t needDraw; // true if need to draw
  uint32_t orientation;
};
typedef struct sprite sprite_t;
extern int blocks[10][10];
extern void rotate(sprite_t *sprite);
extern int drop(sprite_t *sprite);
extern int validX(sprite_t sprite, int x);
extern int processGrid();
extern int clearBlocks(int xPos);
extern int score;
extern void placeBlock(sprite_t sprite);
extern void Square(sprite_t *sprite, uint32_t speed, const unsigned short *squareImage, const unsigned short *squareBlack);
extern void Rectangle(sprite_t *sprite, uint32_t speed, const unsigned short *rectangleImage1, const unsigned short *rectangleImage2, const unsigned short *rectangleBlack1, const unsigned short *rectangleBlack2);
extern void LPiece(sprite_t *sprite, uint32_t speed, const unsigned short *LPiece1, const unsigned short *LPiece2, const unsigned short *LPiece3, const unsigned short *LPiece4, const unsigned short *LPieceBlack1, const unsigned short *LPieceBlack2, const unsigned short *LPieceBlack3, const unsigned short *LPieceBlack4);
extern void JPiece(sprite_t *sprite, uint32_t speed, const unsigned short *JPiece1, const unsigned short *JPiece2, const unsigned short *JPiece3, const unsigned short *JPiece4, const unsigned short *JPieceBlack1, const unsigned short *JPieceBlack2, const unsigned short *JPieceBlack3, const unsigned short *JPieceBlack4);
#endif
