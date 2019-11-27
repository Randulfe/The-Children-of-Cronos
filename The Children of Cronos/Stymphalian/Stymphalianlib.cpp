#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Stymphalianlib.h"

//constructor
Stymphalianlib::Stymphalianlib()
{

}
//die bool function for passing dead variable result to main file
bool Stymphalianlib::die()
{
    if (_dead) {
        return true;
    }
    return false;
}

//initial values and arrays
// disp to false and bullets to true(no bullets in the screen)
void Stymphalianlib::init()
{

    _bullet.x=widthB/2;
    _bullet.y=heightB-5;
    _spacecraft.x=widthB/2;
    _spacecraft.y=heightB-5;
    _bullet0.x=rand()%6+1;
    _bullet1.x=rand()%8+1;
    _bullet2.x=rand()%10+1;
    _bullet0.y=3;
    _bullet1.y=-10;
    _bullet2.y=-23;
    _lifes=7;
    _score=0;

    _bulletcheck=true;
    _alienbullet0=true;
    _alienbullet1=true;
    _alienbullet2=true;
    _dead=false;

    _alienXbig[0]=1;
    _alienYbig[0]=3;
    _alienXbig[1]=2;
    _alienYbig[1]=3;
    _alienXbig[2]=3;
    _alienYbig[2]=3;
    _alienXbig[3]=4;
    _alienYbig[3]=3;
    _alienXbig[4]=5;
    _alienYbig[4]=3;
    _alienXbig[5]=6;
    _alienYbig[5]=3;
    _alienXbig[6]=7;
    _alienYbig[6]=3;

    _alienXmedium[0]=1;
    _alienYmedium[0]=-10;
    _alienXmedium[1]=2;
    _alienYmedium[1]=-10;
    _alienXmedium[2]=3;
    _alienYmedium[2]=-10;
    _alienXmedium[3]=4;
    _alienYmedium[3]=-10;
    _alienXmedium[4]=5;
    _alienYmedium[4]=-10;
    _alienXmedium[5]=6;
    _alienYmedium[5]=-10;
    _alienXmedium[6]=7;
    _alienYmedium[6]=-10;
    _alienXmedium[7]=8;
    _alienYmedium[7]=-10;
    _alienXmedium[8]=9;
    _alienYmedium[8]=-10;

    _alienXsmall[0]=1;
    _alienYsmall[0]=-23;
    _alienXsmall[1]=2;
    _alienYsmall[1]=-23;
    _alienXsmall[2]=3;
    _alienYsmall[2]=-23;
    _alienXsmall[3]=4;
    _alienYsmall[3]=-23;
    _alienXsmall[4]=5;
    _alienYsmall[4]=-23;
    _alienXsmall[5]=6;
    _alienYsmall[5]=-23;
    _alienXsmall[6]=7;
    _alienYsmall[6]=-23;
    _alienXsmall[7]=8;
    _alienYsmall[7]=-23;
    _alienXsmall[8]=9;
    _alienYsmall[8]=-23;
    _alienXsmall[9]=10;
    _alienYsmall[9]=-23;
    _alienXsmall[10]=11;
    _alienYsmall[10]=-23;
}

//if alien y position higher than 40 (spacecraft position), then return true
bool Stymphalianlib::destruction()
{
    for (int i=0; i<7; i++) {
        if( _alienYbig[i]>40) {
            return true;
        }
    }
    for (int i=0; i<9; i++) {
        if(_alienYmedium[i]>40) {
            return true;
        }
    }
    for (int i=0; i<11; i++) {
        if(_alienYsmall[i]>40) {
            return true;
        }
    }

    return false;
}



//direction commands
//if there was no player bullet on the screen, then if r or l pressed shoot the bullet from spacecraft position
void Stymphalianlib::commands(Gamepad &pad,DigitalOut &l,DigitalOut &b,DigitalOut &x,DigitalOut &r)
{
    Direction d = pad.get_direction();
    if (d==W) {
        _spacecraft.x=_spacecraft.x-1;
    } else if(d==E) {
        _spacecraft.x=_spacecraft.x+1;
    }
    if (x) {
        _spacecraft.x=_spacecraft.x-1;
    } else if(b) {
        _spacecraft.x=_spacecraft.x+1;
    }

    if (_spacecraft.x<1) {
        _spacecraft.x=1;
    }
    if (_spacecraft.x>78) {
        _spacecraft.x=78;
    }

    if (_bulletcheck==true) {
        if (l) {
            pad.tone(NOTE_AS2,0.5);
            _bullet.x=_spacecraft.x;
            _bullet.y=_spacecraft.y;
            _bulletcheck=false;
        }

        if(r) {
            pad.tone(NOTE_DS3,0.5);
            _bullet.x=_spacecraft.x+6;
            _bullet.y=_spacecraft.y;
            _bulletcheck=false;
        }
    }
}


//move y position of aliens
void Stymphalianlib::move()
{

    for (int i=0; i<7; i++) {
        _alienYbig[i]++;
    }

    for (int i=0; i<9; i++) {
        _alienYmedium[i]++;
    }
    for (int i=0; i<11; i++) {
        _alienYsmall[i]++;
    }
}

void Stymphalianlib::leds(Gamepad &pad)
{
    for(int i=1; i<_lifes; i++) {
        pad.led(i,1);
    }
}

//check if any pixel of players bullet hitted any alien(in that case increse score and delete players bullet)
//also put alien far away from the screen for appearing then as the player keeps killing aliens
void Stymphalianlib::touch()
{
    for(int i=0; i<7; i++) {

        if(  (    (_bullet.x==(_alienXbig[i]*10)) || (_bullet.x==(_alienXbig[i]*10+1))  ||
                  (_bullet.x+1==(_alienXbig[i]*10)) || (_bullet.x+1==(_alienXbig[i]*10+1))||
                  (_bullet.x==(_alienXbig[i]*10+2)) || (_bullet.x+1==(_alienXbig[i]*10+2))   )&& _bullet.y<(_alienYbig[i]+4)) {

            _bulletcheck= true;
            _bullet.x=_spacecraft.x;
            _bullet.y=_spacecraft.y;
            _alienYbig[i]=-35;
            _score++;
        }
    }

    for(int i=0; i<9; i++) {

        if(  (    (_bullet.x==(_alienXmedium[i]*8)) || (_bullet.x==(_alienXmedium[i]*8+1))  ||
                  (_bullet.x+1==(_alienXmedium[i]*8)) || (_bullet.x+1==(_alienXmedium[i]*8+1))  )&& _bullet.y<(_alienYmedium[i]+4)) {

            _bulletcheck= true;
            _bullet.x=_spacecraft.x;
            _bullet.y=_spacecraft.y;
            _alienYmedium[i]=-48;
            _score+=2;
        }
    }


    for(int i=0; i<11; i++) {

        if(  (    (_bullet.x==(_alienXsmall[i]*7)) || (_bullet.x==(_alienXsmall[i]*7+1))  ||
                  (_bullet.x+1==(_alienXsmall[i]*7)) || (_bullet.x+1==(_alienXsmall[i]*7+1))  )&& _bullet.y<(_alienYsmall[i]+4)) {

            _bulletcheck= true;
            _bullet.x=_spacecraft.x;
            _bullet.y=_spacecraft.y;
            _alienYsmall[i]=-61;
            _score+=3;
        }
    }
//check if any alien bullet hitted the player or if they arrived to his y position(destruction)
//in that case dead is true
    if((_spacecraft.x-1==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+1==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+2==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+3==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+4==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+5==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+6==_bullet0.x*10 && _bullet0.y>40) ||
            (_spacecraft.x+7==_bullet0.x*10 && _bullet0.y>40)|| Stymphalianlib::destruction()) {
        _dead=true;
    }

    if((_spacecraft.x-1==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+1==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+2==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+3==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+4==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+5==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+6==_bullet1.x*8 && _bullet1.y>40) ||
            (_spacecraft.x+7==_bullet1.x*8 && _bullet1.y>40)|| Stymphalianlib::destruction()) {
        _dead=true;
    }

    if((_spacecraft.x==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+1==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+2==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+3==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+4==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+5==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+6==_bullet2.x*7 && _bullet2.y>40) ||
            (_spacecraft.x+7==_bullet2.x*7 && _bullet2.y>40)|| Stymphalianlib::destruction()) {
        _dead=true;
    }
}
//game over screen
//if restart pressed, set values to original ones as well as the arrays to initial state
void Stymphalianlib::gameover(N5110 &lcd,DigitalOut &start,Gamepad &pad)
{
    lcd.clear();
    lcd.printString("GAME OVER",10,2);
    sprintf(_buffer,"Score=%2d ",_score);
    lcd.printString(_buffer,10,4); // print formatted data to buffer
    lcd.refresh();

    if(start) {
        pad.leds_off();
        _dead=false;
        _bullet0.y=0;
        _bullet1.y=0;
        _bullet2.y=0;
        _lifes=_lifes-1;
        _spacecraft.x=widthB/2;
        _spacecraft.y=heightB-5;
        _score=0;
        _alienXbig[0]=1;
        _alienYbig[0]=3;
        _alienXbig[1]=2;
        _alienYbig[1]=3;
        _alienXbig[2]=3;
        _alienYbig[2]=3;
        _alienXbig[3]=4;
        _alienYbig[3]=3;
        _alienXbig[4]=5;
        _alienYbig[4]=3;
        _alienXbig[5]=6;
        _alienYbig[5]=3;
        _alienXbig[6]=7;
        _alienYbig[6]=3;

        _alienXmedium[0]=1;
        _alienYmedium[0]=-10;
        _alienXmedium[1]=2;
        _alienYmedium[1]=-10;
        _alienXmedium[2]=3;
        _alienYmedium[2]=-10;
        _alienXmedium[3]=4;
        _alienYmedium[3]=-10;
        _alienXmedium[4]=5;
        _alienYmedium[4]=-10;
        _alienXmedium[5]=6;
        _alienYmedium[5]=-10;
        _alienXmedium[6]=7;
        _alienYmedium[6]=-10;
        _alienXmedium[7]=8;
        _alienYmedium[7]=-10;
        _alienXmedium[8]=9;
        _alienYmedium[8]=-10;

        _alienXsmall[0]=1;
        _alienYsmall[0]=-23;
        _alienXsmall[1]=2;
        _alienYsmall[1]=-23;
        _alienXsmall[2]=3;
        _alienYsmall[2]=-23;
        _alienXsmall[3]=4;
        _alienYsmall[3]=-23;
        _alienXsmall[4]=5;
        _alienYsmall[4]=-23;
        _alienXsmall[5]=6;
        _alienYsmall[5]=-23;
        _alienXsmall[6]=7;
        _alienYsmall[6]=-23;
        _alienXsmall[7]=8;
        _alienYsmall[7]=-23;
        _alienXsmall[8]=9;
        _alienYsmall[8]=-23;
        _alienXsmall[9]=10;
        _alienYsmall[9]=-23;
        _alienXsmall[10]=11;
        _alienYsmall[10]=-23;
    }
}


//draws all the bullets,aliens,and player
//clears some pixels for improving appearance
void Stymphalianlib::draw(N5110 &lcd)
{
    lcd.clear();
    lcd.drawRect(_bullet.x,_bullet.y,2,2,FILL_BLACK);
    for (int i=0; i<7; i++) {
        lcd.drawRect(_bullet0.x*10,_bullet0.y,2,2,FILL_BLACK);
    }
    for (int i=0; i<9; i++) {
        lcd.drawRect(_bullet1.x*8,_bullet1.y,2,2,FILL_BLACK);
    }
    for (int i=0; i<11; i++) {
        lcd.drawRect(_bullet2.x*7,_bullet2.y,2,2,FILL_BLACK);
    }

    for (int i=0; i<7; i++) {

        lcd.drawRect(_alienXbig[i]*10,_alienYbig[i],3,3,FILL_BLACK);
        lcd.setPixel(_alienXbig[i]*10+1,_alienYbig[i]+1,0);
    }
    for (int i=0; i<9; i++) {
        lcd.drawRect(_alienXmedium[i]*8,_alienYmedium[i],2,2,FILL_BLACK);
        lcd.setPixel(_alienXmedium[i]*8+1,_alienYmedium[i],0);
    }
    for (int i=0; i<11; i++) {
        lcd.drawRect(_alienXsmall[i]*7,_alienYsmall[i],2,2,FILL_BLACK);
        lcd.setPixel(_alienXsmall[i]*7+1,_alienYsmall[i]+1,0);
        lcd.setPixel(_alienXsmall[i]*7,_alienYsmall[i]+1,0);
    }

    lcd.drawRect(_spacecraft.x,_spacecraft.y,8,2,FILL_BLACK);
    lcd.drawRect(_spacecraft.x,_spacecraft.y+-1,2,2,FILL_BLACK);
    lcd.drawRect(_spacecraft.x+6,_spacecraft.y-1,2,2,FILL_BLACK);
    lcd.drawLine(_spacecraft.x+2,_spacecraft.y+1,_spacecraft.x+6,_spacecraft.y+2,0);
    lcd.refresh();
}



//if players bullet on the screen move it two pixels each time
//if bullet got away from screen make it to appear again in spacecraft position
void Stymphalianlib::updatescr()
{

    if(_bullet.y<2) {
        _bulletcheck=true;
        _bullet.x=_spacecraft.x;
        _bullet.y=_spacecraft.y;
    }

    if(_bulletcheck==false) {
        _bullet.x=_bullet.x;
        _bullet.y += -2;
    }

    if(_bulletcheck==true) {
        _bullet.x=_spacecraft.x;
        _bullet.y=_spacecraft.y;
    }

//*****************FIRST UPDATE BULLET0***********//////////
//if the alien is not in the screen dont let the bullet to be shooted
    for (int i=0; i<7; i++) {
        if(_alienYbig[i]<3 && _bullet0.x==i) {
            _alienbullet0=true;
        }
    }
//if the alien bullet got away from the screen generate a new bullet in random position
    if(_bullet0.y>48) {
        _alienbullet0=true;
    }
//if alien bullet in the screen move it two pixels each time
    if(_alienbullet0==false) {
        _bullet0.x=_bullet0.x;
        _bullet0.y+=2;
    }

//*****************SECOND UPDATE BULLET1***********//////////
    for (int i=0; i<9; i++) {
        if(_alienYmedium[i]<3 && _bullet1.x==i) {
            _alienbullet1=true;
        }
    }

    if(_bullet1.y>48) {
        _alienbullet1=true;
    }


    if(_alienbullet1==false) {
        _bullet1.x=_bullet1.x;
        _bullet1.y+=2;
    }
//*****************THIRD UPDATE BULLET2***********//////////
    for (int i=0; i<11; i++) {
        if(_alienYsmall[i]<3 && _bullet2.x==i) {
            _alienbullet2=true;
        }
    }

    if(_bullet2.y>48 ) {
        _alienbullet2=true;
    }


    if(_alienbullet2==false) {
        _bullet2.x=_bullet2.x;
        _bullet2.y+=2;
    }
}
//generate alien bullets in random position where the aliens are
//afterwards set alienbullet to false as there is a bullet in the screen
void Stymphalianlib::auxiliar()
{
    if(_alienbullet0==true) {
        _bullet0.x=rand()%6+1;
        _bullet0.y=_alienYbig[_bullet0.x-1];
        _alienbullet0=false;
    }
    if(_alienbullet1==true) {
        _bullet1.x=rand()%8+1;
        _bullet1.y=_alienYmedium[_bullet1.x-1];
        _alienbullet1=false;
    }
    if(_alienbullet2==true) {
        _bullet2.x=rand()%10+1;
        _bullet2.y=_alienYsmall[_bullet2.x-1];
        _alienbullet2=false;
    }
}

int Stymphalianlib::score()
{
    return _score;
}