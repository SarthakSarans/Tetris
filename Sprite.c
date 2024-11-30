
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
        if(clearBlocks(sprite.y / 12)){return;}
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
            if(clearBlocks(sprite.y / 12)){return;}
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 2] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 3] = 1;
           
        }
    }
}
int clearBlocks(int yPos)
{
    if (yPos != 0)
    {
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            blocks[i][j] = 0;
        }
    }
    return 1;
}

void rotate(sprite_t *sprite)
{
    sprite->orientation = (sprite->orientation + 1) % 4;
}
int drop(sprite_t *sprite) // return 1 if not valid position, retun 0 if valid drop
{
    int dropping = (sprite->y + 12) % 120;
    if (sprite->shape == sq)
    {
        if (blocks[sprite->x / 12][dropping / 12] || blocks[sprite->x / 12 + 1][dropping / 12])
        {
            return 2;
        }
    }
    else if (sprite->shape == rect)
    {
        if (sprite->orientation % 2)
        {
            if (blocks[sprite->x / 12][dropping / 12] || blocks[sprite->x / 12 + 1][dropping / 12] || blocks[sprite->x / 12 + 2][dropping / 12] || blocks[sprite->x / 12 + 3][dropping / 12])
            {
                return 2;
            }
        }
        else
        {
            if (blocks[sprite->x / 12][dropping / 12])
            {
                return 2;
            }
        }
    }

    sprite->y = dropping;
    if (dropping)
    {
        return 0;
    }

    return 1;
}

int validX(sprite_t sprite, int x)
{
    if (sprite.shape == sq)
    {
        if (x > 96)
        {
            return 100;
        }
        return x;
    }
    if (sprite.shape == rect)
    {
        if (sprite.orientation % 2)
        {
            if (x > 72)
                return 76;
        }
        return x;
    }
    return 4;
}

int processGrid()
{
    int changed = 0;
    for (int row = 0; row < 10; row++)
    {
        int isFull = 1; // Assume the row is full
        for (int col = 0; col < 10; col++)
        {
            if (blocks[col][row] == 0)
            {
                isFull = 0; // Row is not full
                break;
            }
        }
        if (isFull)
        {
            changed = 1;
            // Shift rows above the full row down
            for (int r = row; r > 0; r--)
            {
                for (int col = 0; col < 10; col++)
                {
                    blocks[col][r] = blocks[col][r - 1];
                }
            }

            // Clear the top row
            for (int col = 0; col < 10; col++)
            {
                blocks[col][0] = 0;
            }
            // Recheck the same row after shifting
            row--;
        }
    }
    return changed;
}