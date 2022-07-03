
#ifndef SPRITE_H
#define SPRITE_H

#include "app.h"

#define MAX_PALETTES 256
#define MAX_SPRITES 256
#define MAX_COLOURS 16
#define MAX_SPRITE_WIDTH 256
#define MAX_SPRITE_HEIGHT 256

#define COLOUR(r, g, b)  (APP_U32)((b << 16 | g << 8 | r))

typedef struct palette_s
{
    APP_U32 index;
    APP_U32 size;
    APP_U32* colours;
} palette_t;

typedef struct sprite_s
{
    APP_U32 index;
    APP_U32 width;
    APP_U32 height;
    palette_t* palette;
    APP_U32* data;
} sprite_t;

static palette_t palettes[MAX_PALETTES];
static APP_U32 nextPalette = 0;
static sprite_t sprites[MAX_SPRITES];
static APP_U32 nextSprite = 0;
static palette_t* MakePalette(APP_U32 size, APP_U32* colours)
{
    if(nextPalette >= MAX_PALETTES || size >= MAX_COLOURS)
    {
        return NULL;
    }
    palette_t* pal = palettes + nextPalette;
    pal->index = nextPalette;
    pal->size = size;
    pal->colours = colours;

    nextPalette++;
    
    return pal;
}

static sprite_t* MakeSprite(APP_U32 width, APP_U32 height, APP_U32 paletteIndex, APP_U32* data)
{
    if(nextSprite >= MAX_SPRITES || width >= MAX_SPRITE_WIDTH || height >= MAX_SPRITE_HEIGHT || paletteIndex >= nextPalette)
    {
        return NULL;
    }

    sprite_t* sprite = sprites + nextSprite;
    sprite->index = nextSprite;
    sprite->width = width;
    sprite->height = height;
    sprite->data = data;
    sprite->palette = palettes + paletteIndex;

    nextSprite++;

    return sprite;
}

static inline void DrawSprite(APP_U32 posX, APP_U32 posY, APP_U32 spriteIndex, APP_U32* canvas, APP_U32 canvasW, APP_U32 canvasH){
	sprite_t* sprite = sprites + spriteIndex;
	int x, cX, y, cY = 0;
	for(y = 0, cY = posY; y < sprite->height && cY < canvasH; ++y, ++cY){
		for(x = 0, cX = posX; x < sprite->width && cX < canvasW; ++x, ++cX){
			canvas[cX + cY * canvasW] = sprite->palette->colours[sprite->data[x + y * sprite->width]];
		}
	}
}

#endif