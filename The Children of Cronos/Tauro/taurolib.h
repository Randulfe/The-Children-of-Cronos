#ifndef TAUROLIB_H
#define TAUROLIB_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** taurolib Class
 * @brief Library for the fith game, Tauro
* @brief Revision 1.3
* @author Mateo Randulfe
* @date May 2017
 */


class taurolib
{
public:
    /** Constructor */
    taurolib();
    /**
    function for showing how to start game
    * @param lcd neccesary for displaying on the screen
    */
    void intro(N5110 &lcd);
    /*
    * checks if the answer selected is correct and depending on that it goes to the
    * transition screen directly or passing through the points penalty message
    * it also adds points if the answer was right
    * @param lcd prints in the screen
    * @param a selects the desired answer option
    */
    void update(N5110 &lcd,DigitalOut &a);
    /**
    * main draw function that draws the question on the screen and which option is the cursor on(rectangle filled black)
    * it also allows to switch between answer options selecting the desired one
    * @param pad/b/x switches between options
    * @param lcd draws in the screen
    */
    void draw(N5110 &lcd,Gamepad &pad,DigitalOut &b,DigitalOut &x);
    /**
    * fills black the option rectangle selected while the rest of them are transparent filled
    * @param lcd prints in the screen
    */
    void drawselect(N5110 &lcd);
    /**
    * draws the appropiate question for each state
    * @param lcd print in the screen
    */
    void drawquestion(N5110 &lcd);
    /** draws the points penalty due to the failed answer
    * @param lcd prints in screen
    */
    void gameover(N5110 &lcd);
    /**
    * draws the message between levels indicating in which level are you, your score and the subject of the next question
    * @param lcd prints in screen
    */
    void transition(N5110 &lcd);
    /**
    * assemblies the game
    * @param pad/b/x answer selector
    * @param start starts game
    * @param a selects answer
    */
    void game(N5110 &lcd,Gamepad &pad,DigitalOut &a,DigitalOut &start,DigitalOut &b,DigitalOut &x);
    
    /** sets initial state values*/
    void init();
    
    /**
    * @returns score
    */
    int score();


    int _state;
    int _output;
    int _count;
    int _score;
//checks if the have started or not
    bool _yes;
//for score
    char _buffer[20];
#define NOTE_A1  55
};
#endif
