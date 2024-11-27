
#include "Sprite.h"

void Square(sprite_t *sprite, uint32_t speed, const unsigned short *squareImage, const unsigned short *squareBlack)
{
    sprite->shape = sq;
    sprite->x = 52;
    sprite->y = 0;
    // Set velocity to zero
    sprite->vx = 0;
    sprite->vy = speed;

    // Assuming `square` is defined in your images.h
    for (int i = 0; i < 4; i++)
    {
        sprite->image[i] = squareImage;
        sprite->black[i] = squareBlack;
        sprite->w[i] = 24;
        sprite->h[i] = 24;
    }
    sprite->life = alive;
    sprite->orientation = 0;
    sprite->needDraw = 1;
}

void Rectangle(sprite_t *sprite, uint32_t speed, const unsigned short *rectangleImage1, const unsigned short *rectangleImage2, const unsigned short *rectangleBlack1, const unsigned short *rectangleBlack2)
{
    sprite->shape = rect;
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
            sprite->black[i] = rectangleBlack1;
            sprite->w[i] = 12;
            sprite->h[i] = 48;
        }
        else
        {
            sprite->image[i] = rectangleImage2;
            sprite->black[i] = rectangleBlack2;
            sprite->w[i] = 48;
            sprite->h[i] = 12;
        }
    }
    sprite->life = alive;
    sprite->orientation = 0;
    sprite->needDraw = 1;
}

void placeBlock(sprite_t sprite)
{
    if (sprite.shape == sq)
    {
        blocks[sprite.x / 12][sprite.y / 12] = 1;
        blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
        blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
        blocks[sprite.x / 12 + 1][sprite.y / 12 - 1] = 1;
    }
    if (sprite.shape == rect)
    {
        if ((sprite.orientation % 2))
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 2][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 3][sprite.y / 12] = 1;
        }
        else
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 2] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 3] = 1;
        }
    }
}

void rotate(sprite_t *sprite)
{
    sprite->orientation = (sprite->orientation + 1) % 4;
}
int drop(sprite_t *sprite)
{
    int dropping = (sprite->y + 12) % 120;
    sprite->y = dropping;
    if (dropping != 0)
    {
        return 0;
    }

    return 1;
}

int validX(sprite_t* sprite)
{
    if (sprite.shape == sq)
    {
        if (sprite.x > 96)
        {
            return 100;
        }
    }
    if (sprite.shape == rect)
    {
        if (sprite.orientation % 2)
        {
            if (sprite.x > 72)
                return 76;
        }
        return sprite.x;
    }
    return 4;
}
