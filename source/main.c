#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>

#include "libs/app.h"
#include "libs/sprite.h"
static inline APP_U32 getColour(int r, int g, int b)
{
    return (APP_U32)((b << 16 | g << 8 | r));
}
void drawBox(APP_U32 sizeX, APP_U32 sizeY, APP_U32 posX, APP_U32 posY, APP_U32 borderWidth, APP_U32 colour, APP_U32* canvas, APP_U32 canvasW, APP_U32 canvasH)
{
    int i,j,k = 0;

    const int BoxMaxX = posX + sizeX + borderWidth * 2;
    const int BoxMaxY = posY + sizeY + borderWidth * 2;

    for(j = posY; j < BoxMaxY; ++j)
    {
        //if(i > BoxPosX + EdgeWidth && i < BoxMaxX - EdgeWidth)
          //  continue;
        
        for(i = posX; i < BoxMaxX; ++i)
        {
            if(borderWidth > 0 && j > posY + borderWidth && j < BoxMaxY - borderWidth - 1 && i > posX + borderWidth && i < BoxMaxX - borderWidth - 1)
                i = BoxMaxX - borderWidth - 1;

            canvas[i + j * canvasW] = colour;
        } 
    }
}
void drawUi(APP_U32* canvas, APP_U32 canvasW, APP_U32 canvasH)
{
    int i,j,k = 0;
    int r,g,b,a = 0;
    const int BoxSize = 64;
    const int EdgeWidth = 2;
    const int BoxPosX = 10;
    const int BoxPosY = 100;
    const int BoxMaxX = BoxPosX + BoxSize + EdgeWidth + EdgeWidth;
    const int BoxMaxY = BoxPosY + BoxSize + EdgeWidth + EdgeWidth;

    drawBox(16, 16, 2, 32, 1, getColour(255, 0, 0), canvas, canvasW, canvasH);
    drawBox(130, 300, 24, 8, 1, getColour(0, 255, 0), canvas, canvasW, canvasH);
    drawBox(16, 16, 160, 32, 1, getColour(0, 0, 255), canvas, canvasW, canvasH);
   
}
int app_proc( app_t* app, void* user_data ) {
    (void) user_data;
    const int canvasW = 180;
    const int canvasH = 320;
    const int canvasSize = canvasW * canvasH;
    static APP_U32 canvas[ 180 * 320];
    memset( canvas, 0x00, sizeof( canvas ) );
    app_screenmode( app, APP_SCREENMODE_WINDOW );
    app_interpolation(app, APP_INTERPOLATION_NONE);

    APP_U32 palColours[8] = {
        COLOUR(0,0,0),
        COLOUR(255,0,0),
        COLOUR(0,255,0),
        COLOUR(0,0,255),
        COLOUR(255,255,0),
        COLOUR(255,0,255),
        COLOUR(0,255,255),
        COLOUR(255,255,255)
    };
    palette_t* palette = MakePalette(8,palColours);

    APP_U32 spriteData[] = {
        7,7,7,7,7,7,7,7,
        7,1,1,1,2,2,2,7,
        7,1,1,1,2,2,2,7,
        7,0,0,0,0,0,0,7,
        7,3,4,5,5,4,3,7,
        7,3,4,6,6,4,3,7,
        7,3,4,6,6,4,3,7,
        7,7,7,7,7,7,7,7,
    };
    sprite_t* sprite = MakeSprite(8, 8, 0,spriteData);

    while( app_yield( app ) != APP_STATE_EXIT_REQUESTED ) {
        drawUi(canvas, canvasW, canvasH);
        DrawSprite(32,32,0, canvas,canvasW,canvasH);
        //DrawSprite(32,44,0, canvas,canvasW,canvasH);
        //DrawSprite(32,40,0, canvas,canvasW,canvasH);
        //DrawSprite(64,32,0, canvas,canvasW,canvasH);
        app_present( app, canvas, canvasW, canvasH, 0xffffff, 0x000000 );
    }
    return 0;
}


int main( int argc, char** argv ) {
    (void) argc, (void ) argv;
    return app_run( app_proc, NULL, NULL, NULL, NULL );
}


// pass-through so the program will build with either /SUBSYSTEM:WINDOWS or /SUBSYSTEM:CONSOLE
#if defined( _WIN32 ) && !defined( __TINYC__ )
    #ifdef __cplusplus 
        extern "C" int __stdcall WinMain( struct HINSTANCE__*, struct HINSTANCE__*, char*, int ) { 
            return main( __argc, __argv ); 
        }
    #else
        struct HINSTANCE__;
        int __stdcall WinMain( struct HINSTANCE__* a, struct HINSTANCE__* b, char* c, int d ) { 
            (void) a, b, c, d; return main( __argc, __argv ); 
        }
    #endif
#endif


#define APP_IMPLEMENTATION
#ifdef _WIN32 
    #define APP_WINDOWS
#elif __wasm__
    #define APP_WASM
#else 
    #define APP_SDL
#endif
#define APP_LOG( ctx, level, message ) 
#include "libs/app.h"
