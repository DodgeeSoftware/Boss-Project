#include "FontUtils.h"

unsigned FontUtils::drawString(TTF_Font* font, SDL_Color colour, const char* text, int x, int y, SDL_Surface* surface)
{
    SDL_Surface* message;       // the surface/image area that will contain the text
    message = TTF_RenderText_Solid( font, text, colour );
    // to position the text, need to build a destination rectangle
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    offset.w = message->w;
    offset.h = message->h;
    // the text, the "clipping rectangle - 0=none, destination, and destn rect
    SDL_BlitSurface( message, 0, surface, &offset );
    // MUST free any surfaces used
    SDL_FreeSurface( message );
    return offset.h;            // the height of the text just drawn
}

unsigned FontUtils::drawCentredString(TTF_Font* font, SDL_Color colour, const char* text, int y, SDL_Surface* surface)
{
    SDL_Surface* message;       // the surface/image area that will contain the text
    message = TTF_RenderText_Solid( font, text, colour );
    int x = (surface->w - message->w) / 2;
    drawSurface( x, y, message, surface );
    SDL_FreeSurface( message );
    return message->h;            // the height of the text just drawn
}

unsigned FontUtils::drawRightAlignString(TTF_Font* font, SDL_Color colour, const char* text, int rightX, int y, SDL_Surface* surface)
{
    SDL_Surface* message;       // the surface/image area that will contain the text
    message = TTF_RenderText_Solid( font, text, colour );
    int x = rightX - message->w;
    drawSurface( x, y, message, surface );
    SDL_FreeSurface( message );
    return message->h;            // the height of the text just drawn
}

void FontUtils::drawSurface ( float x, float y, SDL_Surface *source, SDL_Surface *destination )
{
    //Make a temporary rectangle to hold the offsets required by SDL_BlitSurface()
    SDL_Rect offset;
    //Give the offsets to the rectangle
    offset.x = (Sint16) x;
    offset.y = (Sint16) y;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}
