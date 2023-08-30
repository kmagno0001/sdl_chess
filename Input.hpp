#pragma once

#include <SDL2/SDL.h>
#include <array>

#define MAX_HIGH 8
#define MAX_WITH 8
#define Array std::array< std::array< Piece, MAX_WITH >, MAX_HIGH >

class Input {
public:
    inline Input( Array& board );
    inline void event_loop();

private:
    Array& board;
    SDL_Event event;
};

inline Input::Input( Array& board ):
    board{ board }
{}

inline void Input::event_loop() {
    while (  SDL_PollEvent( &event ) ) {
        switch ( event.type ) {
            case SDL_QUIT:
                exit(0);
                break;
                
            case SDL_MOUSEMOTION:
                break;
            
            default:
                break;
        }
    } 
}