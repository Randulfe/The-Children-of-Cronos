#ifndef CERINEALIB_H
#define CERINEALIB_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#define width 82
#define height 48
#define size 5



///////////////////////////////////////////////////////////////////////////////
/* This library if for he stack game.It is the only game that has some bugs 
when playing to it.There is a bouncing problem with the buttons that dont work
well as well as som problems with the logic from the 6th block dropped.

However,the user can still play this game but no as the original one.I wasnt 
going to put this game into my project because of this minor bugs but, as I
already created the story of the game around the number 5 and as I thought I
would have enough time to solve this issues I put it with the rest.

Due to unpredicted problems before the deadline I didnt have enough time for
solving the problems. I apologise for this game's bugs. */

///////////////////////////////////STRUCTURES///////////////////////////////////

    /** Blocks position */
    struct pos {
        int x;/**< x pos */
        int y;/**< y pos */
    } ;
    
    
    

////////////////////////////METHODS AND VARIABLES///////////////////////////////
/** cerinealib Class
 * @brief Library for the fourth game, Cerinea
* @brief Revision 1.3
* @author Mateo Randulfe
* @date May 2017
 */

class cerinealib
{
public:
    /** Constructor */
    cerinealib();
    /**
    * function that switches only the same number of leds on as the same number of lifes
    * the player still have left
    * @param pad controls leds
    */
    void leds();
    /**
    * function that initialises the values for the main positions as well as the borders to 0(this will be
    * added later when the block are dropped), the sizes to 0(appart from the main first block) because
    * they will be then set in the game,and the x and y position where the blocks to be added will start
    *moving
    */
    void init();
    /**
    * this function performs two main actuations
    * first, it draws the blocks in movent if their bool variable is true(which means that they
    * were not dropped yet).
    * second, if they are dropped(bool variables with the names or ordinals like first second etc set to false)
    * the function will leave only the part over the other block and the rest(the part out of the range)
    * will be eliminated.It also sets the size of the next block depending on the size of the block dropped
    * it will set also the left block extreme margin as border to have a reference
    * @param lcd for printing into the screen
    */
    void draw(N5110 &lcd);
    /**
    * depending on if the block is moving (ordinal variables to true) or dropped(ordinal variables to false)
    * it will update the movement from one side of the screen to the next one
    * or it will set the block to the dropped stayed position and when it reaches to five the block count
    * it will start a loop of switching the block x positions to their previous one,letting the game to keep going forever
    */
    void updatescr();
    /**
    * if buttons pressed the block will be dropped
    * if dropped it will increse the score and let the next block moving variable to true (ordinal variable) as well as setting its to false
    * @param b/a/x/y drop block
    * @param pad
    */
    void commands(DigitalOut &b,DigitalOut &a,DigitalOut &x,DigitalOut &y,Gamepad &pad);
    /**
    * function that displays the game over screen and allows player to restart game
    *once restarted,all values set to original ones
    * @param lcd for drawing into the screen
    * @param start for restarting the game
    * @param pad for putting leds off
    */
    void gameover(N5110 &lcd,DigitalOut &start);
    /**
    * @returns true if dead
    */
    bool die();
    /**
    * function that sets the velocity of the game and the difficulty level
    * the highest the score the faster the game will go and the more difficult
    */
    void velocities();
    /**
    * @returns score
    */
    int score();
    
//for displaying score
    char _buffer[20];


//sizes of the blocks depending on what is the previous block left
    int _size0,_size1,_size2,_size3,_size4,_size5;
//first block positions
    int _pos0lft,_pos0rgt,_posy0;
    int _k,_count,_score,_lifes;
//left extreme of the blocks as spacial refrerence
    int _border1,_border2,_border3,_border4,_border5;
//ordinal variables for knowing if the block was dropped
    bool _first,_second,_third,_fourth,_fith;
    pos _pos1,_pos2,_pos3,_pos4,_pos5;
    bool _dead;
#define NOTE_C6  1047
};
#endif