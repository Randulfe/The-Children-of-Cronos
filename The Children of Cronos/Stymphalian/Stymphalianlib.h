#ifndef STYMPHALIANLIB_H
#define STYMPHALIANLIB_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#define widthB 82
#define heightB 46
#define sizeB 3
#define NOTE_DS3 156
#define NOTE_AS2 117

/////////////////////////////////////STUCTURES/////////////////////////////////

    /** Aliens bullet position */
    struct alienbullet {
        int x;/**< x pos */
        int y;/**< y pos */
    } ;


    /** Spacecraft position */
    struct posplayer {
        int x;/**< x pos */
        int y;/**< y pos */
    } ;

    /** Bullet position */
    struct posbullet {
        int x;/**< x pos */
        int y;/**< y pos */
    } ;


/////////////////////////////METHODS AND VARIABLES////////////////////////////////

/** Stymphalianlib Class
 * @brief Library for the second game
* @brief Revision 1.3
* @author Mateo Randulfe
* @date May 2017
 */

class Stymphalianlib
{
public:
    /** Constructor */
    Stymphalianlib();
    /**
    * function that displays the game over screen and allows player to restart game
    *once restarted,all values set to original ones
    * @param lcd for drawing into the screen
    * @param start for restarting the game
    * @param pad for putting leds off
    */
    void gameover(N5110 &lcd,DigitalOut &start,Gamepad &pad);
    /**
    * updates the alien bullets and player bullets movement
    * also, it only allows to generate the bullet if the alein is on the screen
    * uses disp variables for knwing where to display the bullet(from an alive alien)
    * uses alienbullet variables for knowing if there is any bullet of that type already in
    *the screen(in that way no bullet will be generated untill there is no bullet in the screen
    */
    void updatescr();
    /**
    * allow player to move the spacecradt horizontally within the screen as well as to shoot only if there is no players bullet already in the screen
    * @param b/x/pad spacecraft horizontal movement
    * @param l/r shoot from left or right
    */
    void commands(Gamepad &pad,DigitalOut &l,DigitalOut &b,DigitalOut &x,DigitalOut &r);
    /**
    * function that initialises the values for the main positions
    * it initialises all the array alien x and y positions
    * sets no bullets bool on the screen and disp to true
    */
    void init();
    /**
    * main draw function that draws all the component of the game
    * it also clears some aliens and bullets pixels for improving appearance
    * @param lcd for drawing into the screen
    */
    void draw(N5110 &lcd);
    /**
    * checks if the palyers bullet hits any alien
    * checks if any alien bullet hits player
    */
    void touch();
    /**
    * function that switches only the same number of leds on as the same number of lifes
    * the player still have left
    * @param pad controls leds
    */
    void leds(Gamepad &pad);
    /**
    * function that moves 1 pixel the y alien position.Ready for being used by a ticker in the main file
    * in this way the aliens will move one pixel per second
    */
    void move();
    /**
    * checks if any alien alive arrived to the players height(in this way it will kill the player)
    * @returns true if any alien reached the players position
    * @returns false if not
    */
    bool destruction();
    /**
    * generates aliens bullet if no bullet in the screen (by checking alienbullet variables)
    * randomly generated bullets
    */
    void auxiliar();
    /**
    * @return die if dead variable is true
    */
    /** 
    * @returns score
    */
    int score();
    /**
    * @returns true if dead
    * @returns false if not dead
    */
    bool die();

    int _lifes, _score;

// bools for knowing if there is any bullet of that type in the screen
    bool _bulletcheck,_alienbullet0,_alienbullet1,_alienbullet2;
//bools for knowing if it died or for knowing if that alien whre the bullet was gona come out is alive or not
    bool _dead;



//i recon here I could have used an structure bu i completely forgot about it
    int _alienXsmall[11];
    int _alienXmedium[9];
    int _alienXbig[7];
    int _alienYsmall[11];
    int _alienYmedium[9];
    int _alienYbig[7];
//for printing score in the screen
    char _buffer[20];
    alienbullet _bullet0,_bullet1,_bullet2;
    posplayer _spacecraft;
    posbullet _bullet;

};
#endif