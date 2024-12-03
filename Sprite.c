
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

void LPiece(sprite_t *sprite, uint32_t speed, const unsigned short *LPiece1, const unsigned short *LPiece2, const unsigned short *LPiece3, const unsigned short *LPiece4, const unsigned short *LPieceBlack1, const unsigned short *LPieceBlack2)
{
    sprite->shape = lshape;

    // setting starting position (set some random x value, y = 0 to start from top)
    sprite->x = 56;
    sprite->y = 0;

    // velocity = 0 to put block in original orientation
    sprite->vx = 0;
    sprite->vy = speed;
    for (int i = 0; i < 4; i++)
    {
        if ((i % 4) == 0)
        {
            sprite->image[i] = LPiece1;
            sprite->black[i] = LPieceBlack1;
            sprite->w[i] = 24;
            sprite->h[i] = 36;
        }
        else if ((i % 4) == 1)
        {
            sprite->image[i] = LPiece2;
            sprite->black[i] = LPieceBlack2;
            sprite->w[i] = 36;
            sprite->h[i] = 24;
        }
        else if ((i % 4) == 2)
        {
            sprite->image[i] = LPiece3;
            sprite->black[i] = LPieceBlack1;
            sprite->w[i] = 24;
            sprite->h[i] = 36;
        }
        else
        {
            sprite->image[i] = LPiece4;
            sprite->black[i] = LPieceBlack2;
            sprite->w[i] = 36;
            sprite->h[i] = 24;
        }
    }
    sprite->life = alive;
    sprite->orientation = 0;
    sprite->needDraw = 1;
}

void JPiece(sprite_t *sprite, uint32_t speed, const unsigned short *JPiece1, const unsigned short *JPiece2, const unsigned short *JPiece3, const unsigned short *JPiece4, const unsigned short *JPieceBlack1, const unsigned short *JPieceBlack2)
{
    sprite->shape = jshape;

    // setting starting position (set some random x value, y = 0 to start from top)
    sprite->x = 56;
    sprite->y = 0;

    // velocity = 0 to put block in original orientation
    sprite->vx = 0;
    sprite->vy = speed;

    for (int i = 0; i < 4; i++)
    {
        if ((i % 4) == 0)
        {
            sprite->image[i] = JPiece1;
            sprite->black[i] = JPieceBlack1;
            sprite->w[i] = 24;
            sprite->h[i] = 36;
        }
        else if ((i % 4) == 1)
        {
            sprite->image[i] = JPiece2;
            sprite->black[i] = JPieceBlack2;
            sprite->w[i] = 36;
            sprite->h[i] = 24;
        }
        else if ((i % 4) == 2)
        {
            sprite->image[i] = JPiece3;
            sprite->black[i] = JPieceBlack1;
            sprite->w[i] = 24;
            sprite->h[i] = 36;
        }
        else
        {
            sprite->image[i] = JPiece4;
            sprite->black[i] = JPieceBlack2;
            sprite->w[i] = 36;
            sprite->h[i] = 24;
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

    if (sprite.shape == lshape)
    {
        if ((sprite.orientation % 4) == 0)
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 2] = 1;
        }
        else if ((sprite.orientation % 4) == 1)
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12 + 2][sprite.y / 12 - 1] = 1;
        }
        else if ((sprite.orientation % 4) == 2)
        {
            blocks[sprite.x / 12][sprite.y / 12 - 2] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12 - 2] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
        }
        else
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 2][sprite.y / 12] = 1;
        }
    }

    if (sprite.shape == jshape)
    {
        if ((sprite.orientation % 4) == 0)
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12 - 2] = 1;
        }
        else if ((sprite.orientation % 4) == 1)
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 2][sprite.y / 12] = 1;
        }
        else if ((sprite.orientation % 4) == 2)
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 1] = 1;
            blocks[sprite.x / 12][sprite.y / 12 - 2] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12 - 2] = 1;
        }
        else
        {
            blocks[sprite.x / 12][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 1][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 2][sprite.y / 12] = 1;
            blocks[sprite.x / 12 + 2][sprite.y / 12 + 1] = 1;
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
int drop(sprite_t *sprite)
{
    int dropping = (sprite->y + 12) % 120;

    // Square piece (already implemented)
    if (sprite->shape == sq)
    {
        if (blocks[sprite->x / 12][dropping / 12] ||
            blocks[sprite->x / 12 + 1][dropping / 12])
        {
            return 2;
        }
    }
    // Rectangle piece (already implemented)
    else if (sprite->shape == rect)
    {
        if (sprite->orientation % 2)
        {
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12] ||
                blocks[sprite->x / 12 + 2][dropping / 12] ||
                blocks[sprite->x / 12 + 3][dropping / 12])
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
    // L piece
    else if (sprite->shape == lshape)
    {
        switch (sprite->orientation % 4)
        {
        case 0:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12])
            {
                return 2;
            }
            break;
        case 1:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12] ||
                blocks[sprite->x / 12 + 2][dropping / 12])
            {
                return 2;
            }
            break;
        case 2:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12])
            {
                return 2;
            }
            break;
        case 3:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12] ||
                blocks[sprite->x / 12 + 2][dropping / 12])
            {
                return 2;
            }
            break;
        }
    }
    // J piece
    else if (sprite->shape == jshape)
    {
        switch (sprite->orientation % 4)
        {
        case 0:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12])
            {
                return 2;
            }
            break;
        case 1:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12] ||
                blocks[sprite->x / 12 + 2][dropping / 12])
            {
                return 2;
            }
            break;
        case 2:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12])
            {
                return 2;
            }
            break;
        case 3:
            if (blocks[sprite->x / 12][dropping / 12] ||
                blocks[sprite->x / 12 + 1][dropping / 12] ||
                blocks[sprite->x / 12 + 2][dropping / 12])
            {
                return 2;
            }
            break;
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
    if (sprite.shape == lshape)
    {
        if (((sprite.orientation % 4) == 0) || ((sprite.orientation % 4) == 2))
        {
            if (x > 96)
            {
                return 100;
            }
        }
        else
        {
            if (x > 84)
            {
                return 88;
            }
        }
        return x;
    }

    if (sprite.shape == jshape)
    {
        if (((sprite.orientation % 4) == 0) || ((sprite.orientation % 4) == 2))
        {
            if (x > 96)
            {
                return 100;
            }
        }
        else
        {
            if (x > 84)
            {
                return 88;
            }
        }
        return x;
    }
    return 4;
}

int processGrid()
{
    int changed = 0;
    int total = 0;
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
            total += 1;
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
    score = 100 * changed / 2;
    return changed;
}
