#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include "Draw.hpp"
#include "Input.hpp"

#define MAX_HIGH 8
#define MAX_WITH 8
#define Array std::array< std::array< Piece, MAX_WITH >, MAX_HIGH >

class Logic {
public:
    Logic();

private:
    enum State {
        WHITE_, BLACK_, 
    }current_state;
    Array board;
    Draw draw;
    Input input;
};

Logic::Logic():
    draw{ board }, 
    input{ board }
{
    while ( 1 ) {
        draw.prepare_scene();
        input.event_loop();
        draw.drawing_onScreen();
        draw.present_scene();
        draw.clear_screen();
        SDL_Delay(32);
    }
}


    

