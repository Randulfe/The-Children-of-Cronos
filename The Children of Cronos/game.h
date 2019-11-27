#include "mbed.h"
#include "N5110.h"
#include "Bitmap.h"
#include "Gamepad.h"
#include "hydralib.h"
#include "Stymphalianlib.h"
#include "aurigaslib.h"
#include "cerinealib.h"
#include "taurolib.h"
#include "array.h"


/** Selector */
struct State {
    int position;     /**< position */
    int nextstate[2];/**< next state */
};

/**
@file game.h
@brief Header file for the function prototyps and variables of the main game file
@author Mateo Randulfe
@date May 2017
*/

/**
* x button connection
* @param x
*/
DigitalOut  x (PTC17);
/**
* y button connection
* @param y
*/
DigitalOut  y (PTC12);
/**
* a button connection
* @param a
*/
DigitalOut  a (PTB9);
/**
* b button connection
* @param b
*/
DigitalOut  b (PTD0);
/**
* l button connection
* @param l
*/
DigitalOut  l (PTB18);
/**
* r button connection
* @param r
*/
DigitalOut  r (PTB3);
/**
* start button connection
* @param start
*/
DigitalOut  start (PTC5);
/**
* back button connection
* @param back
*/
DigitalOut back(PTB19);
/**
* lcd objct for interacting with the screen library
* @param lcd
*/

N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
/**
* gamepad objct for interacting with the gamepad library
* @param pad
*/
Gamepad pad;
/**
* hydralib objct for interacting with the first game library(the snake)
* @param hyd
*/
hydralib hyd;
/**
* Stymphalianlib objct for interacting with the second game library(space invaders)
* @param stym
*/
Stymphalianlib stym;
/**
* aurigaslib objct for interacting with the third game library(flappy birds)
* @param aurig
*/
aurigaslib aurig;
/**
* cerinealib objct for interacting with the fourth game library(stack)
* @param cer
*/
cerinealib cer;
/**
* taurolib objct for interacting with the fith game library(quesions and answers)
* @param tau
*/
taurolib tau;

/**
* ticker object for switching on progressively the lights in the intro
*/
Ticker introlights;
/**
* ticker object for moving the aliens each second in th space invaders game
*/
Ticker alienmove;

/**
* initialises all the objects like gamepad and lcd
* it also performs h init function of all the games
*/
void init();
/**
* brief intro with the game name in a fancy way using bitmaps
*/
void intro();
/**
* switchs on progressivly the lights in the intro screen
*/
void lights();
/**
* displays the different games selector screen and allows to switch between them
*/
void game();
/**
* function that allows to select the five different games in an up down selector using a sructure
*/
void select();
/**
* executes the screen where the player can select the option he wants like tutoria,story of the game,the games screen or the scores
*/
void menuscreen();
/**
* function that allows to select the different menu options the player have
*/
void menuselect();
/**
* draws the screen that selects beween the five different games(which is inside itself of the menuselct screen
*/
void drawselectmenu();
/**
* draws the screen that selects beween opions in the menu
*/
void drawselectscreen();

/** selects between different games */
void selected();
/**
* displays the tutorial screen and the selecor of it.The player can choose to read the instructions of the different levels
*/
void tutorial();
/**
* displays the game sory screen and the selecor of it.The player can scrolls to keep reading the story.
*/
void story();
/**
* displays the highest scores
*/
void highscores();
/**
* saves the score if pressed and if its bigger than the thid position
*/
void savescore();

/** performs the aliens movement */
void aliens();
/**
* executes the screen where the player can select the game he wants
*/
void newgame();
/**
* function that assemblies the first game
*/
void gameone();

//if false the game is not running i true it will be running
bool game1=false;
/**
* function that assemblies the second game
*/
void gametwo();
// if false the game is not running i true it will be running
bool game2=false;
/**
* function that assemblies the third game
*/
void gamethree();
//if false the game is not running i true it will be running
bool game3=false;
/**
* function that assemblies the fourth game
*/
void gamefour();
// if false the game is not running i true it will be running
bool game4=false;
/**
* function that assemblies the fith game
*/
void gamefive();
// if false the game is not running i true it will be running
bool game5=false;
// if false the menu screen will not be displayed if true it will
bool menuselection=true;
// if false the games selector screen will not be displayed if true it will
bool selection=true;
// if false the tutorial screen will not be displayed if true it will
bool tut=false;
// if false the story screen will not be displayed if true it will
bool stor=false;
// if false the highscore screen will not be displayed if true it will
bool highscr=false;
// if false the save screen will not be displayed if true it will
bool savescr=false;


/** structure array for the different games*/
State games[5]= {
    {0,{4,1}},
    {1,{0,2}},
    {2,{1,3}},
    {3,{2,4}},
    {4,{3,0}}
};
/** structure array for the different menu options*/
State menu[4]= {
    {0,{3,1}},
    {1,{0,2}},
    {2,{1,3}},
    {3,{2,0}}
};
/** structure array for the tutorial options*/
State tuto[5]= {
    {0,{4,1}},
    {1,{0,2}},
    {2,{1,3}},
    {3,{2,4}},
    {4,{3,0}}
};

//arrays for displaying scores
char buffer0[20];
char buffer1[20];
char buffer2[20];
char buffer3[20];
char buffer4[20];
char buffer5[20];

int statetutorial=0;
int outpututorial=0;

int statemenu=0;
int outputmenu=0;


int statestory=0;
int outputstory=0;

int state=0;
int output=0;

//???
int lit=0;
//??
int k=1;

int totalscore;
//different scores for the games
int scoreg1, scoreg2,scoreg3,scoreg4,scoreg5;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349

