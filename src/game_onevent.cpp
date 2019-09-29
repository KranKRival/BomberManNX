#include "game.h"

#ifdef DEBUG_OUTPUT_GAME
#include<cstdio>
void PrintKeyInfo( SDL_KeyboardEvent *key );
#endif // DEBUG_OUTPUT_GAME

void game::OnEvent(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
    {
        Running = false;
    }

    switch( Event->type )
    {

        case SDL_JOYBUTTONDOWN:
            keyboard_input->TurnKeyOn(Event->jbutton.button);
            #ifdef DEBUG_OUTPUT_GAME
            PrintKeyInfo( &(Event->key) );
            #endif // DEBUG_OUTPUT_GAME
            break;

        case SDL_JOYBUTTONUP:
            keyboard_input->TurnKeyOff(Event->jbutton.button);
            #ifdef DEBUG_OUTPUT_GAME
            PrintKeyInfo( &(Event->key) );
            #endif // DEBUG_OUTPUT_GAME
            switch( Event->jbutton.button )
            {
                case SDLK_f: // mostly for testing
                    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    break;
                default:
                    break;
            }
            break;

        /* SDL_QUIT event (window close) */
        case SDL_QUIT:
            Running = false;
            break;

        default:
            break;
    }

}

#ifdef DEBUG_OUTPUT_GAME
void PrintKeyInfo( SDL_KeyboardEvent *key )
{
    /* Is it a release or a press? */
    if( key->type == SDL_KEYUP )
        printf( "Release:- " );
    else
        printf( "Press:- " );

    /* Print the hardware scancode first */
    printf( "Scancode: 0x%02X", key->keysym.scancode );
    /* Print the name of the key */
    printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
    /* We want to print the unicode info, but we need to make */
    /* sure its a press event first (remember, release events */
    /* don't have unicode info                                */
    if( key->type == SDL_KEYDOWN )
    {
        /* If the Unicode value is less than 0x80 then the    */
        /* unicode value can be used to get a printable       */
        /* representation of the key, using (char)unicode.    */
        printf(", Unicode: " );
        if( key->keysym.sym < 0x80 && key->keysym.sym > 0 )
        {
            printf( "%c (0x%04X)", (char)key->keysym.sym,
                    key->keysym.sym );
        }
        else
        {
            printf( "? (0x%04X)", key->keysym.sym );
        }
    }
    printf( "\n" );
    /* Print modifier info */
    //PrintModifiers( key->keysym.mod );
}

/* Print modifier info */
/*
void PrintModifiers( Unit16 mod )
{
    printf( "Modifers: " );
    // If there are none then say so and return //
    if( mod == KMOD_NONE )
    {
        printf( "None\n" );
        return;
    }
    // Check for the presence of each SDLMod value //
    // This looks messy, but there really isn't    //
    // a clearer way.                              //
    if( mod & KMOD_NUM ) printf( "NUMLOCK " );
    if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
    if( mod & KMOD_LCTRL ) printf( "LCTRL " );
    if( mod & KMOD_RCTRL ) printf( "RCTRL " );
    if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
    if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
    if( mod & KMOD_RALT ) printf( "RALT " );
    if( mod & KMOD_LALT ) printf( "LALT " );
    if( mod & KMOD_CTRL ) printf( "CTRL " );
    if( mod & KMOD_SHIFT ) printf( "SHIFT " );
    if( mod & KMOD_ALT ) printf( "ALT " );
    printf( "\n" );
}
*/
#endif // DEBUG_OUTPUT_GAME