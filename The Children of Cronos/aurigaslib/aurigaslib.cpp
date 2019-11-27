#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "aurigaslib.h"
//constructor
aurigaslib::aurigaslib()
{

}

int aurigaslib::score()
{
    return _score;
}
//initial values and new random y top pipes positions
void aurigaslib::init()
{
    _check=false;
    _force=-1;
    _vel=0;
    _gravity=0;
    _velpipe=1;
    _score=0;
    _lifes=7;
    _pospipe0=60;
    _pospipe1=_pospipe0+21;
    _pospipe2=_pospipe1+21;
    _pospipe3=_pospipe2+21;
    _k=0;
    _pipe0.top= rand ()% 35+3;
    _pipe0.bottom= heightC-_pipe0.top-10;
    _pipe1.top= rand ()% 35+3;
    _pipe1.bottom=heightC-_pipe1.top-10;
    _pipe2.top= rand ()% 35+3;
    _pipe2.bottom=heightC-_pipe2.top-10;
    _pipe3.top= rand ()% 35+3;
    _pipe3.bottom=heightC-_pipe3.top-10;
    _posbird.x=10;
    _posbird.y=heightC/2;
}
//leds on depending on how many lifes left
void aurigaslib::leds(Gamepad &pad)
{
    for(int i=1; i<_lifes; i++) {
        pad.led(i,1);
    }
}

//gameover screen with score displayed on the screen
//let the player restart the game to its initial values
void aurigaslib::gameover(N5110 &lcd,Gamepad &pad,DigitalOut &l,DigitalOut &r)
{

    lcd.clear();
    lcd.printString("GAME OVER",15,0);
    sprintf(_buffer,"Score=%2d ",_score);
    lcd.printString(_buffer,18,1); // print formatted data to buffer
    lcd.printString("PRESS L/R",10,4);
    lcd.printString("for new game",5,5);
    lcd.drawLine(0,23,84,23,FILL_BLACK);
    lcd.refresh();

    if(l||r) {
        _k=0;
        _vel=0;
        _gravity=0;
        pad.leds_off();
        _lifes=_lifes-1;
        pad.leds_off();
        _posbird.x=10;
        _posbird.y=heightC/2;
        _pospipe0=60,_pospipe1=_pospipe0+21,_pospipe2=_pospipe1+21,_pospipe3=_pospipe2+21;
        _score=0;
        _check=true;
        lcd.clear();
    }
}


//checks if the bird hits the pipes
bool aurigaslib::touch()
{
    if(
        ((_posbird.x==_pospipe0 ||_posbird.x==_pospipe0+1 || _posbird.x==_pospipe0+2 || _posbird.x==_pospipe0+3) && (_posbird.y<=_pipe0.top || _posbird.y+2>=(heightC-_pipe0.bottom)))||
        ((_posbird.x==_pospipe1 ||_posbird.x==_pospipe1+1 || _posbird.x==_pospipe1+2 || _posbird.x==_pospipe1+3) && (_posbird.y<=_pipe1.top || _posbird.y+2>=(heightC-_pipe1.bottom)))||
        ((_posbird.x==_pospipe2 ||_posbird.x==_pospipe2+1 || _posbird.x==_pospipe2+2 || _posbird.x==_pospipe2+3) && (_posbird.y<=_pipe2.top || _posbird.y+2>=(heightC-_pipe2.bottom)))||
        ((_posbird.x==_pospipe3 ||_posbird.x==_pospipe3+1 || _posbird.x==_pospipe3+2 || _posbird.x==_pospipe3+3) && (_posbird.y<=_pipe3.top || _posbird.y+2>=(heightC-_pipe3.bottom)))) {

        return false;
    }
    return true;
}

//draws components
//the pipes are drawed as follow:there are two main rectangles drawed over the pipe x position
//the first one is the top part of the pipe.It starts from y=0 until the randomly generated value pipe.top
//the second one is the bottom part of the pipe.It starts from (height-bottom).Bottom variable is the
//position corresponding with the top one plus 1o pixels. Then it goes until the bottom of the screen with
//the size of the bottom variable.In this way,the bird will have 10 pixels to pass in between the pipes
void aurigaslib::draw(N5110 &lcd)
{
    lcd.clear();
    if(_k==0) {
        lcd.printString("PRESS",0,4);
        lcd.printString("START",0,5);
    }
    lcd.drawRect(_posbird.x,_posbird.y,3,3,FILL_BLACK);
    lcd.setPixel(_posbird.x-1,_posbird.y+1,1);
    lcd.setPixel(_posbird.x+3,_posbird.y+1,1);
    lcd.setPixel(_posbird.x+1,_posbird.y+1,0);
    lcd.drawRect(_pospipe0,0,sizeC,_pipe0.top,FILL_BLACK);
    lcd.drawRect(_pospipe0,heightC-_pipe0.bottom,sizeC,_pipe0.bottom,FILL_BLACK);
    lcd.drawRect(_pospipe1,0,sizeC,_pipe1.top,FILL_BLACK);
    lcd.drawRect(_pospipe1,heightC-_pipe1.bottom,sizeC,_pipe1.bottom,FILL_BLACK);
    lcd.drawRect(_pospipe2,0,sizeC,_pipe2.top,FILL_BLACK);
    lcd.drawRect(_pospipe2,heightC-_pipe2.bottom,sizeC,_pipe2.bottom,FILL_BLACK);
    lcd.drawRect(_pospipe3,0,sizeC,_pipe3.top,FILL_BLACK);
    lcd.drawRect(_pospipe3,heightC-_pipe3.bottom,sizeC,_pipe3.bottom,FILL_BLACK);

    lcd.refresh();
}

//updates movements and allows to jump with a determined force against the gravity
void aurigaslib::updatescr(DigitalOut &a,DigitalOut &b,DigitalOut &x,DigitalOut &y,Gamepad &pad)
{
    if (_posbird.y<0) {
        _posbird.y=0;
    }

    if(_posbird.y>heightC) {
        _posbird.y=heightC-_k;
        _vel=0;
    }


    if((a | b | x | y)&& _k==1) {
        pad.tone(NOTE_DS5,0.5);
        _vel=_force;
        _posbird.y+=_vel;
    }

    _vel+=_gravity;
    _posbird.y+=_vel;
    _pospipe0=_pospipe0-_k;
    _pospipe1=_pospipe1-_k;
    _pospipe2=_pospipe2-_k;
    _pospipe3=_pospipe3-_k;

    if(_pospipe0<0) {
        _pospipe0=84;
    }
    if(_pospipe1<0) {
        _pospipe1=84;
    }
    if(_pospipe2<0) {
        _pospipe2=84;
    }
    if(_pospipe3<0) {
        _pospipe3=84;
    }

    if(_posbird.x==_pospipe0) {
        _score+=10;
    }
    if(_posbird.x==_pospipe1) {
        _score+=10;
    }
    if(_posbird.x==_pospipe2) {
        _score+=10;
    }
    if(_posbird.x==_pospipe3) {
        _score+=10;
    }
}

//generates random top values and set the bottom as the height minus the top minus a margin of 10 pixels for leaving some space in between

void aurigaslib::pipegenerator(Gamepad &pad,DigitalOut &start)
{
    if(start) {
        _k=1;
        _gravity=0.3;
    }
    aurigaslib::leds(pad);
    if(_pospipe0==0) {

        _pipe0.top= rand ()% 35+3;
        _pipe0.bottom= heightC-_pipe0.top-10;
    }
    if(_pospipe1==0) {

        _pipe1.top= rand ()% 35+3;
        _pipe1.bottom= heightC-_pipe1.top-10;
    }
    if(_pospipe2==0) {

        _pipe2.top= rand ()% 35+3;
        _pipe2.bottom=heightC-_pipe2.top-10;
    }
    if(_pospipe3==0) {

        _pipe3.top= rand ()% 35+3;
        _pipe3.bottom=heightC-_pipe3.top-10;
    }

}