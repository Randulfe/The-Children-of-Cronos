#ifndef HYDRALIB_H
#define HYDRALIB_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#define widthA 82
#define heightA 36
#define sizeA 3


/** Head position */
    struct position {
        int x;/**< x pos */
        int y;/**< y pos */
    } ;
    /** Food position */
    struct foodposition {
        int x;/**< x pos */
        int y;/**< y pos */
    };

/** Velocity vector */
    struct velocity {
        int x;      /**< x vector */
        int y;/**< y vector */
    } ;

/** Tail position */
    struct tail {
        int X;/**< x pos */
        int Y;/**< y pos */
    } ;




/** hydralib Class
 * @brief Library for the first game, Hydra
* @brief Revision 1.3
* @author Mateo Randulfe
* @date May 2017
 */

class hydralib
{
public:
/** Constructor */
    hydralib();
/** 
* Function that initialises the values for the main positions
*/
    void init();
/**
* Function that checks if the snake touched the extremes of the screen
* or if it ate itself
* @return if it touches or not
*/
    bool border();
/**
* Function that checks if the snake head position is the same as any of his tail parts position
* ie if it ate itself
* @return if it touches or not
*/
    bool touch();
/**
* Allow player to move and changes velocity of movement depending on the players input
* @param a/b/x/y down,right,left and up
* @param pad down,right,left and up
*/
    void commands(Gamepad &pad,DigitalOut &a,DigitalOut &b,DigitalOut &x,DigitalOut &y);
/** 
* Updates the movement of the snake tail and head id the snake moves
*/
    void updatescr();
/**
* Main draw function that draws all the component of the game
* @param lcd for drawing into the screen
*/
    void draw(N5110 &lcd);
/**
* Function that displays the game over screen and allows player to restart game
*once restarted,all values set to original ones
* @param lcd for drawing into the screen
* @param start for restarting the game
* @param pad for putting leds off
*/
    void gameover(N5110 &lcd,DigitalOut &start,Gamepad &pad);
/**
* Function that switches only the same number of leds on as the same number of lifes
* the player still have left
* @param pad controls leds
*/
    void leds(Gamepad &pad);
    /**
    * Function that sets the velocity of the game and the difficulty level
    * the highest the score the faster the game will go and the more difficult
    */
    void velocities();
    /**
    * Function that draws a difficulty levels indicator in the bottom on the screen
    * next to the score
    */
    void rectangles(N5110 &lcd);
    /** Function that checks if the position of the head and the food is relatively the same
    * both of them are 3x3 rectangles. If any 2x2 parts of them are in contact it returns true
    * if it would be all 3x3 it would be too difficult
    * if it would be any 1x1 it would be too easy
    * @return true if eated
    */
    bool eat();
/**
* Pauses the game
* @param l/r/lcd pauses the game and adds a p of pause in the screen
*/    
void pausegame(DigitalOut &l,DigitalOut &r,N5110 &lcd,DigitalOut &back);
    /**
    * Function that helps lately in the main file to generate food and increase score and lenght
    */
    void auxiliar();
/** stores score
* @returns score
*/
int score();


//snake lenght,score,lifes and a buffer for printing score
    int _lenght , _score, _lifes;
    bool _pause;
    char _buffer[20];
    position _pos;
    foodposition  _food;
    velocity _vel;
    tail _body[100];
    
};
#endif