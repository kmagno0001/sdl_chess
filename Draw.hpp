#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <array>
#include <iostream>
#include "Entity.hpp"

#define WITH 840
#define HIGH 840

#define MAX_HIGH 8
#define MAX_WITH 8
#define Array std::array< std::array< Piece, MAX_WITH >, MAX_HIGH >

class Draw {
public:
    inline Draw( Array& board );
    inline void prepare_scene( void );
    inline void present_scene( void );
    inline void drawing_onScreen( void );
    inline void clear_screen( void );

    inline SDL_Texture* load_img_texture( Type_piece ty_piece );
    
private:
    Array& board;
    SDL_Texture* text_background;

    struct Window_Render{
        SDL_Window *window; 
        SDL_Renderer *renderer; 
    } Wind;
};

inline Draw::Draw( Array& board ):
    board{ board } 
{
    memset( &Wind, 0, sizeof( Wind ) );

    IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG );

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cout << "Failed to init the video" << SDL_GetError();
        std::exit(1);
    }

    Wind.window = SDL_CreateWindow( "CHESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WITH, HIGH, SDL_WINDOW_ALLOW_HIGHDPI );

    if ( !Wind.window ) {
        std::cout << "Failed to open window" << SDL_GetError();
        std::exit(1);
    } 

    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    Wind.renderer = SDL_CreateRenderer( Wind.window, -1, SDL_RENDERER_ACCELERATED);

    if ( !Wind.renderer ) {
        std::cout << "Failed to Create the Renderer" << SDL_GetError();
        std::exit(1);
    }

    int x {0}; 
    int y {-100};

    for ( int row=0; row < MAX_HIGH; ++row ) {
        for ( int col=0; col < MAX_WITH; ++col ) {
            if ( (row == 0 || row == 7) &&  (col == 0 || col == 7) ) {
                board[row][col] = { x, y, NULL, TOWER };  
            } else if ( (row == 0 || row == 7) && (col == 1 || col == 6) ) {
                board[row][col] = { x, y, NULL, BISHOP };
            } else if ( (row == 0 || row == 7) && (col == 2 || col == 5) ) {
                board[row][col] = { x, y, NULL, KNIGHT }; 
            } else if ( (row == 0 || row == 7) && col == 3 ) {
                board[row][col] = { x, y, NULL, KING};    
            } else if ( (row == 0 || row == 7) && col == 4 ) {
                board[row][col] = { x, y, NULL, QUEEN};  
            } else if ( row == 1 || row == 6 ) {
                board[row][col] = { x, y, NULL, PAWN};
            } else {
                board[row][col] = { x, y, NULL, NONE }; 
                continue;
            }        
            
            board[row][col].texture = load_img_texture( board[row][col].ty_piece );        
            x += 100;        
        }
        x = 0;
        y += 100;
    }

    text_background = { IMG_LoadTexture( Wind.renderer, "img_src/board.jpg" ) };
}

inline void Draw::prepare_scene( void ) {
    SDL_Rect dest;
    dest.h = 840;
    dest.w = 840;

    SDL_QueryTexture( text_background, NULL, NULL, &dest.w, &dest.h );
    SDL_RenderCopy( Wind.renderer, text_background, &dest,  NULL );
    SDL_SetRenderTarget( Wind.renderer, text_background );
}

inline void Draw::present_scene( void ) {
    SDL_RenderPresent( Wind.renderer );
}

inline SDL_Texture* Draw::load_img_texture( Type_piece ty_piece ) {
    std::string string { "img_src/" };

    switch ( ty_piece )
    {
    case PAWN:
        string += "Pawn.png";
        break;
    case TOWER:
        string += "Tower.png";
        break;
    case BISHOP:
        string += "Bishop.png";
        break;
    case KNIGHT:
        string += "Knight.png";
        break;
    case KING:
        string += "King.png";
        break;
    case QUEEN:
        string += "Queen.png";
        break;    
    default:
        break;
    }

    return IMG_LoadTexture( Wind.renderer, string.c_str() );
}

inline void Draw::drawing_onScreen( void ) {
    SDL_Rect dest;

    for ( auto row=0; row < MAX_HIGH; ++row ) {
        for ( auto col=0; col < MAX_WITH; ++col ) {
            dest.x =  board[row][col].x;
            dest.y = board[row][col].y;  
            
            SDL_QueryTexture( board[row][col].texture, NULL, NULL, &dest.w, &dest.h );
            SDL_RenderCopy( Wind.renderer, board[row][col].texture, NULL, &dest );
        }
    }
}

inline void Draw::clear_screen( void ) {
    SDL_RenderClear( Wind.renderer );
}