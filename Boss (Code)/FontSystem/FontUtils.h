#ifndef FONTUTILS_H
#define FONTUTILS_H

#include <SDL/sdl.h>
#include <SDL/SDL_ttf.h>

class FontUtils
{
    public:
        FontUtils() {}
        virtual ~FontUtils() {}

        //! draw a text string to a surface
        /** Note that this function creates a fresh surface every time it is used.
        It is more efficient to create your own function using a single surface.
        \param font: to use for the text, must be already loaded
        \param colour: to use for the text
        \param text: the C style string to display
        \param x: horizontal x location - left
        \param y: vertical y location - top
        \param surface: the destination surface  */
        static unsigned drawString( TTF_Font* font, SDL_Color colour, const char* text, int x, int y, SDL_Surface* surface );

        //! draw a text string centred on a surface, convenience function.
        /** Calculates the required x value and then calls drawSurface().
        \param font: to use for the text, must be already loaded
        \param colour: to use for the text
        \param text: the C style string to display
        \param y: vertical y location - top
        \param surface: the destination surface  */
        static unsigned drawCentredString( TTF_Font* font, SDL_Color colour, const char* text, int y, SDL_Surface* surface );

        //! draw a text string right aligned on a surface, convenience function.
        /** Calculates the required x value and then calls drawSurface().
        \param font: to use for the text, must be already loaded
        \param colour: to use for the text
        \param text: the C style string to display
        \param rightX: the far right (align) x value
        \param y: vertical y location - top
        \param surface: the destination surface  */
        static unsigned drawRightAlignString( TTF_Font* font, SDL_Color colour, const char* text, int rightX, int y, SDL_Surface* surface );

    protected:

    private:
        static void drawSurface ( float x, float y, SDL_Surface *source, SDL_Surface *destination );
};

#endif // FONTUTILS_H
