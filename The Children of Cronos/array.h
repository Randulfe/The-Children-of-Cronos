#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"


#define A 1 //this maks easier to draw somehing on the array and see the shape


//arays for intro bitmaps
int randulfe[] {
    0,A,A,A,A,A,A,A,0,0,0,A,A,A,A,A,0,A,A,A,A,0,0,0,A,A,A,A,A,A,A,0,0,0,A,A,A,A,0,A,A,A,A,A,A,A,0,0,A,A,A,A,A,A,A,A,A,A,A,A,A,0,0,0,0,A,A,A,A,0,0,0,
    A,0,0,0,0,0,0,0,A,0,A,0,0,0,0,0,A,A,0,0,0,A,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,0,0,0,0,A,0,0,0,A,0,0,0,0,A,0,0,
    A,0,0,A,A,A,A,A,0,A,0,0,A,A,A,0,0,A,0,0,0,0,A,A,0,0,0,A,0,0,0,0,A,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,0,0,0,0,A,0,0,A,0,0,0,0,0,0,A,0,
    A,0,0,A,0,0,0,A,0,A,0,A,0,0,0,A,0,A,0,0,0,0,A,A,0,0,0,A,0,A,0,0,0,A,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,A,A,A,A,0,0,A,A,A,A,0,0,A,0,0,A,A,A,0,0,A,
    A,0,0,A,0,0,A,0,0,A,0,A,0,0,0,A,0,A,0,0,0,0,0,A,0,0,0,A,0,A,A,0,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,A,0,0,0,0,0,A,
    A,0,0,A,0,A,0,0,0,A,0,A,0,0,0,A,0,A,0,0,0,0,0,0,0,0,0,A,0,A,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,A,0,0,0,0,0,A,
    A,0,0,A,A,0,0,0,A,A,0,A,A,A,A,A,0,A,0,0,0,0,0,0,0,0,0,A,0,A,0,0,A,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,A,A,A,A,0,0,A,A,A,A,0,0,A,0,A,0,0,0,0,0,A,
    A,0,0,0,0,0,0,A,0,A,0,0,0,0,0,0,0,A,0,0,0,0,0,0,0,0,0,A,0,A,0,0,A,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,A,A,0,0,0,0,0,A,0,0,A,0,0,A,A,A,0,0,A,
    A,0,0,A,A,0,0,A,0,A,0,0,A,A,A,0,0,A,0,0,0,A,0,0,0,0,0,A,0,A,0,0,A,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,A,A,0,0,0,0,0,A,0,0,A,0,0,0,0,0,0,0,A,
    A,0,0,A,0,A,0,0,A,A,0,0,A,0,A,0,0,A,0,0,0,A,A,0,0,0,0,A,0,A,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,A,0,0,A,A,A,A,0,0,A,A,A,A,0,0,0,A,0,0,0,0,0,A,0,
    A,0,0,A,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,0,A,0,A,0,0,0,A,0,A,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,A,0,0,0,0,0,0,0,A,A,A,A,A,0,0,
    A,0,0,A,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,0,A,0,0,A,0,0,A,0,A,A,0,0,0,A,0,0,0,0,0,0,0,A,0,0,A,A,A,A,0,0,A,0,0,A,0,0,A,A,A,A,A,0,0,0,0,0,0,0,0,0,0,
    A,0,0,A,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,A,0,0,0,0,0,A,A,0,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,0,A,0,0,0,0,0,0,0,0,0,0,
    A,0,0,A,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,0,A,0,0,A,0,0,A,0,0,0,0,A,0,0,0,A,0,0,0,A,0,A,0,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,0,A,0,0,0,0,0,0,0,0,0,0,
    A,A,A,A,0,0,A,A,A,A,A,A,A,0,A,A,A,A,A,A,A,A,0,0,A,A,A,A,A,A,A,A,0,0,0,0,0,A,A,A,0,0,A,A,A,A,A,A,A,A,A,A,0,0,A,A,A,A,A,A,A,A,0,0,0,0,0,0,0,0,0,0
};


int gamename[] {

    A,A,A,A,A,A,A,A,A,0,A,A,A,A,A,A,A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    A,0,0,0,0,0,A,0,A,0,A,0,A,0,A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    A,A,A,0,A,A,A,0,A,A,A,0,A,0,A,A,A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,A,0,A,0,A,0,0,0,0,0,A,0,A,A,A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,A,0,A,0,A,0,A,A,A,0,A,0,A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,A,0,A,0,A,0,A,0,A,0,A,0,A,0,0,0,0,0,A,A,A,A,A,A,A,0,0,A,A,A,A,A,A,A,0,0,A,A,A,0,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,0,0,A,A,A,A,0,0,0,0,0,0,0,0,0,
    0,0,A,A,A,0,A,A,A,0,A,A,A,A,A,A,A,0,0,A,0,0,0,0,A,0,A,0,0,A,0,A,0,A,0,A,0,0,A,0,0,A,A,0,0,0,0,0,A,0,0,0,0,0,A,0,A,0,0,A,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,0,A,A,A,0,A,A,A,A,0,A,0,A,0,A,0,0,A,0,0,0,A,0,A,A,0,0,A,0,0,A,A,A,A,0,A,0,0,A,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,0,A,0,A,0,A,0,0,A,0,A,0,A,0,A,A,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,A,0,0,A,0,A,A,A,A,0,A,0,A,0,A,0,0,A,0,A,0,A,0,0,0,0,A,A,0,0,A,A,A,A,0,0,A,0,A,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,A,0,A,0,A,0,0,A,0,A,0,A,0,A,0,A,0,A,0,0,A,A,A,A,0,0,0,A,A,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,A,0,A,0,A,0,0,A,0,0,0,A,0,A,A,0,A,A,0,0,A,0,0,A,0,0,A,0,0,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,0,A,A,A,0,A,0,0,A,0,A,0,A,0,A,A,A,A,0,0,A,A,0,A,0,A,0,A,0,0,A,A,A,A,0,0,A,A,0,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,0,0,0,0,A,0,A,0,0,A,0,A,0,A,0,0,0,0,A,0,A,0,A,0,A,0,A,0,A,0,0,0,0,0,A,0,0,A,0,A,0,0,A,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,A,A,A,A,A,A,A,0,0,A,A,A,A,A,A,A,A,A,A,A,0,0,A,A,A,0,A,A,A,A,A,A,A,A,A,A,A,A,0,0,A,A,A,0,0,0,0,0,0,0,0,0

};


int gamename2[] {

    0,A,A,A,A,0,A,A,0,0,0,0,0,
    A,0,0,0,0,A,0,0,A,0,0,0,0,
    A,0,A,A,0,A,0,A,A,0,0,0,0,
    A,0,A,A,0,A,A,0,A,0,0,0,0,
    A,0,A,A,0,A,A,0,A,0,0,0,0,
    A,0,A,A,0,A,0,A,0,0,0,0,0,
    A,0,A,A,0,A,0,A,A,A,0,0,0,
    A,0,A,A,0,A,0,0,0,A,0,0,0,
    A,0,A,A,0,A,0,A,A,A,0,0,0,
    A,0,0,0,0,A,0,A,0,0,0,0,0,
    0,A,A,A,A,0,A,A,0,0,0,0,0
};





int gamename1[] {
    0,0,0,0,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,0,0,0,0,A,A,A,A,A,0,0,0,A,A,A,A,0,0,0,0,A,A,A,A,0,0,0,A,A,A,A,A,0,0,0,0,0,0,0,A,A,A,A,A,A,A,A,A,0,0,0,
    0,0,0,A,0,0,0,0,0,0,A,0,0,0,0,0,0,0,0,0,0,A,0,0,A,0,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,0,0,0,0,A,0,0,0,0,0,0,0,0,A,0,0,0,
    0,0,A,0,0,0,0,0,0,0,A,0,0,A,A,A,A,A,A,0,0,A,0,A,0,0,0,0,0,0,0,A,0,A,0,0,A,0,0,0,0,A,0,0,A,0,A,0,0,0,0,0,0,0,A,0,0,0,A,0,0,0,0,0,0,0,0,0,A,0,0,0,
    0,A,0,0,0,A,A,A,A,A,A,0,0,A,0,0,0,0,A,0,0,A,A,0,0,A,A,A,A,A,0,0,A,A,0,0,A,0,0,0,0,A,0,0,A,A,0,0,A,A,A,A,A,0,0,A,0,A,0,0,0,A,A,A,A,A,A,A,A,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,0,0,0,A,0,0,A,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,0,0,0,0,0,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,A,A,A,0,0,A,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,0,0,0,0,0,0,0,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,0,0,0,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,0,0,0,0,0,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,0,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,A,0,0,0,A,A,A,A,A,A,0,0,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,A,0,0,0,0,0,0,0,0,A,0,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,0,A,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,A,A,A,A,A,0,0,0,A,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,0,A,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,0,0,0,0,0,A,0,0,A,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,0,0,A,0,0,A,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,A,0,0,A,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,A,A,A,A,A,A,A,A,A,0,0,A,0,0,0,
    A,0,0,0,A,0,0,0,0,0,A,0,0,A,0,0,0,A,0,0,A,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,A,0,A,0,0,A,0,0,A,0,0,0,A,0,0,0,A,0,0,0,A,0,0,0,0,0,0,0,0,0,0,0,A,0,0,0,
    0,A,0,0,0,A,A,A,A,A,A,0,0,A,0,0,0,0,A,0,0,A,A,0,0,A,A,A,A,A,0,0,A,A,0,0,A,0,0,A,0,0,0,0,A,A,0,0,A,A,A,A,A,0,0,A,A,0,0,0,0,0,0,0,0,0,0,0,A,0,0,0,
    0,0,A,0,0,0,0,0,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,A,0,0,0,0,0,0,0,A,0,A,0,0,A,0,0,0,A,0,0,0,A,0,A,0,0,0,0,0,0,0,A,0,A,0,0,0,0,0,0,0,0,0,0,0,A,0,0,0,
    0,0,0,A,0,0,0,0,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,A,0,0,A,0,0,A,0,0,0,0,0,A,0,0,A,0,0,0,0,0,0,0,0,0,0,A,0,0,0,0,
    0,0,0,0,A,A,A,A,A,A,A,A,A,A,0,0,0,0,A,A,A,A,0,0,0,A,A,A,A,A,0,0,0,A,A,A,A,0,0,0,0,A,A,A,A,0,0,0,A,A,A,A,A,0,0,0,A,A,A,A,A,A,A,A,A,A,A,0,0,0,0,0

};