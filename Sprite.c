
#include "Sprite.h"

void Square(sprite_t *sprite, uint32_t speed, const unsigned short *squareImage, const unsigned short *squareBlack)
{
    sprite->x = 52;
    sprite->y = 0;
    // Set velocity to zero
    sprite->vx = 0;
    sprite->vy = speed;
    sprite->black = squareBlack;
    // Assuming `square` is defined in your images.h
    for (int i = 0; i < 4; i++)
    {
        sprite->image[i] = squareImage;
        sprite->w[i] = 24;
        sprite->h[i] = 24;
    }
    sprite->life = alive;
    sprite->orientation = 0;
    sprite->needDraw = 1;
}

void Rectangle(sprite_t *sprite, uint32_t speed, const unsigned short *rectangleImage1, const unsigned short *rectangleImage2)
{
    sprite->x = 58;
    sprite->y = 0;
    // Set velocity to zero
    sprite->vx = 0;
    sprite->vy = speed;
    // Assuming `square` is defined in your images.h
    for (int i = 0; i < 4; i++)
    {
        if (i % 2 == 0)
        {
            sprite->image[i] = rectangleImage1;
            sprite->w[i] = 12;
            sprite->h[i] = 48;
        }
        else
        {
            sprite->image[i] = rectangleImage2;
            sprite->w[i] = 48;
            sprite->h[i] = 12;
        }
    }
    sprite->life = alive;
    sprite->orientation = 0;
    sprite->needDraw = 1;
}
