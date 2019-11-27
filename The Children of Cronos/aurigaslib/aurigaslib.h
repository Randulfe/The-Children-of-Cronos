#ifndef AURIGASLIB_H
#define AURIGASLIB_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#define widthC 82
#define heightC 48
#define sizeC 4
#define NOTE_DS5 622

//////////////////////////////////STRUCTURES///////////////////////////////////

    /** structure for pipes height */
    struct pipes {
        int top;/**< top rectangle position */
        int bottom;/**< bottom rectangle position */
    };

    /** structure for bird position */
    struct bird {
        int x;/**< x position */
        int y;/**< y position */
    };

//////////////////////////////////METHODS AND VARIABLES/////////////////////////

/** aurigaslib Class
 * @brief Library for the third game, Aurigas
* @brief Revision 1.3
* @author Mateo Randulfe
* @date May 2017
 */
class aurigaslib
{
public:
    /** Constructor */
    aurigaslib();
    /**
    *sets positions and values to initial ones and generates new pipe random heights
    */
    void init();
    /*
    * if the game starts(start pressed), set pipes velocity (k=1) and gravity to their proper values
    * generates random pipes heights if they get out of the screen (smaller their x pos than 0)
    * @param pad set leds() function
    * @param start for starting moving all the game
    */
    void pipegenerator(Gamepad &pad,DigitalOut &start);
    /**
    * function that allows user to jump whithin the screen
    * moves the pipes
    * when the pipes get out of the screen in the left they restart in the right
    * @param a/b/x/y jump
    */
    void updatescr(DigitalOut &a,DigitalOut &b,DigitalOut &x,DigitalOut &y,Gamepad &pad);
    /**
    * draws all the components and clears some pixels of the bird for improving its looking
    * @param lcd for printing in the screen
    */
    void draw(N5110 &lcd);
    /**
    * check if any bird pixel hitted any pipe
    * @returns true if the player hits the pipes
    * @returns false if he doesnt 
    */
    bool touch();
    /**
    * function that displays the game over screen and allows player to restart game
    * once restarted,all values set to original ones
    * @param lcd for drawing into the screen
    * @param l/r for restarting the game
    * @param pad for putting leds off
    */
    void gameover(N5110 &lcd,Gamepad &pad,DigitalOut &l,DigitalOut &r);
    /**
    * function that switches only the same number of leds on as the same number of lifes
    * the player still have left
    * @param pad controls leds
    */

    void leds(Gamepad &pad);
    /** 
    * @returns score
    */
    
    int score();
//for printing the score
    char _buffer[20];


    int _force;
//physics variables
    float _vel , _gravity, _velpipe;
    int _score,_lifes;
//x pipes position
    int _pospipe0,_pospipe1;
    int _pospipe2,_pospipe3;
//checks if game start was pressed and game didnt started yet
    int _k;
    bool _check;
    pipes _pipe0,_pipe1,_pipe2,_pipe3;
    bird _posbird;

};
#endif
