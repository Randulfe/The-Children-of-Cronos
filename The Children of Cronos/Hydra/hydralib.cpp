#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "hydralib.h"


//constructor
hydralib::hydralib()
{

}

int hydralib::score()
{
    return _score;
}

//sets positions and values to initial ones and generated new random food
void hydralib::init()
{
    _food.x=rand() %78+3;
    _food.y=rand() %30+3;
    _pos.x=widthA/2;
    _pos.y=heightA/2;
    _vel.x=0;
    _vel.y=0;
    _lenght=0;
    _score=0;
    _lifes=7;
    _pause=true;
}

//switches all the leds neccessary
void hydralib::leds(Gamepad &pad)
{
    for(int i=1; i<_lifes; i++) {
        pad.led(i,1);
    }
}
void hydralib::pausegame(DigitalOut &l,DigitalOut &r,N5110 &lcd,DigitalOut &back)
{
    if(l||r||back) {
        _pause=true;
        _vel.x=0;
        _vel.y=0;
    }

}
//first prints game over screen with the score on it
//then it allows to restart the game to initial values by pressing start
void hydralib::gameover(N5110 &lcd,DigitalOut &start,Gamepad &pad)
{

    lcd.clear();
    lcd.printString("GAME OVER",10,2);
    sprintf(_buffer,"Score=%2d ",_score);
    lcd.printString(_buffer,15,4); // print formatted data to buffer
    lcd.refresh();

    if(start) {
        pad.leds_off();
        _lifes=_lifes-1;
        _vel.x=0;
        _vel.y=0;
        _pos.x=widthA/2;
        _pos.y=heightA/2;
        _lenght=0;
        _score=0;

    }
}

//checks if the head pixels match with the food pixels
bool hydralib::eat()
{
    if ((_pos.x==_food.x && _pos.y==_food.y)||
            (_pos.x==_food.x && _pos.y==_food.y+1)||
            (_pos.x==_food.x && _pos.y+1==_food.y)||
            (_pos.x==_food.x && _pos.y+1==_food.y+1)||
            (_pos.x==_food.x+1 && _pos.y==_food.y)||
            (_pos.x==_food.x+1 && _pos.y==_food.y+1)||
            (_pos.x==_food.x+1 && _pos.y+1==_food.y)||
            (_pos.x==_food.x+1 && _pos.y+1==_food.y+1)||
            (_pos.x+1==_food.x && _pos.y==_food.y)||
            (_pos.x+1==_food.x && _pos.y==_food.y+1)||
            (_pos.x+1==_food.x && _pos.y+1==_food.y)||
            (_pos.x+1==_food.x && _pos.y+1==_food.y+1)||
            (_pos.x+1==_food.x+1 && _pos.y==_food.y)||
            (_pos.x+1==_food.x+1 && _pos.y==_food.y+1)||
            (_pos.x+1==_food.x+1 && _pos.y+1==_food.y)||
            (_pos.x+1==_food.x+1 && _pos.y+1==_food.y+1)
       ) {
        return true;
    }
    return false;
}

//depending on the score,fills certain rectangles to black or leave them transparent
void hydralib::rectangles(N5110 &lcd)
{
    lcd.drawRect(3,39,3,3,FILL_TRANSPARENT);
    lcd.drawRect(15,39,3,3,FILL_TRANSPARENT);
    lcd.drawRect(3,44,3,3,FILL_TRANSPARENT);
    lcd.drawRect(15,44,3,3,FILL_TRANSPARENT);
    lcd.drawRect(9,41,3,3,FILL_TRANSPARENT);
    if(_score>9 && _score<=29) {
        lcd.drawRect(3,39,3,3,FILL_BLACK);
    }
    if(_score>29 && _score<=44) {
        lcd.drawRect(3,39,3,3,FILL_BLACK);
        lcd.drawRect(15,39,3,3,FILL_BLACK);
    }
    if(_score>44 && _score<=59) {
        lcd.drawRect(3,39,3,3,FILL_BLACK);
        lcd.drawRect(15,39,3,3,FILL_BLACK);
        lcd.drawRect(9,41,3,3,FILL_BLACK);
    }
    if(_score>59 && _score<=74) {
        lcd.drawRect(3,39,3,3,FILL_BLACK);
        lcd.drawRect(15,39,3,3,FILL_BLACK);
        lcd.drawRect(9,41,3,3,FILL_BLACK);
        lcd.drawRect(3,44,3,3,FILL_BLACK);
    }
    if(_score>74) {
        lcd.drawRect(3,39,3,3,FILL_BLACK);
        lcd.drawRect(15,39,3,3,FILL_BLACK);
        lcd.drawRect(9,41,3,3,FILL_BLACK);
        lcd.drawRect(3,44,3,3,FILL_BLACK);
        lcd.drawRect(15,44,3,3,FILL_BLACK);
    }
}

//by using waits at the end of the game and reducing them, i can control the game speed
//i reccon i could have used tickers instead but i have some problems trying to implement it
//so i left the waits that they didnt affect at all to the performance of my game
void hydralib::velocities()
{
    if(_score<=9) {
        wait(0.08);
    }
    if(_score>9 && _score<=29) {
        wait(0.06);
    }
    if(_score>29 && _score<=44) {
        wait(0.04);
    }
    if(_score>44 && _score<=59) {
        wait(0.035);
    }
    if(_score>59 && _score<=74) {
        wait(0.025);
    }
    if(_score>74) {
        wait(0.015);
    }
}

//checks if the head pixels match with any tail parts pixels
bool hydralib::touch()
{
    int j=0;
    for(int i=_lenght+1; i>0; i--) {
        if(_pos.x==_body[i].X && _pos.y==_body[i].Y) {
            j=1;
        }
    }
    if (j==0) {
        return false;
    }
    return true;
}

//checks if the head touches the extremes of the screen or the tail of the snake
bool hydralib::border()
{

    if (_pos.x==0 || _pos.x==81) {
        return false;
    } else if(_pos.y==0 || _pos.y==35) {
        return false;
    } else if (hydralib::touch()) {
        return false;
    } else {
        return true;
    }
}

//draws  difficulty rectangles,borders,score in the screen,food,snake head and tail
//and depending on the movement of it clears certain pixels for improving the looking of it
void hydralib::draw(N5110 &lcd)
{

    lcd.clear();
    if(_pause) {
        lcd.printChar('P',4,5);
    }
    lcd.drawRect(0,0,84,38,FILL_TRANSPARENT);
    hydralib::rectangles(lcd);

    for (int i=_lenght; i>0; i--) {

        lcd.drawRect(_body[i].X,_body[i].Y,sizeA,sizeA,FILL_BLACK);
    }
    sprintf(_buffer,"Score=%2d",_score);
    lcd.printString(_buffer,33,5);
    lcd.drawRect(_food.x,_food.y,sizeA,sizeA,FILL_BLACK);
    lcd.drawRect(_pos.x,_pos.y,sizeA,sizeA,FILL_BLACK);
    lcd.setPixel(_pos.x+1,_pos.y+1,false);
    if(_vel.y== -1 && _vel.x==0) {
        lcd.setPixel(_pos.x+1,_pos.y,false);
    }
    if(_vel.y==1 && _vel.x==0) {
        lcd.setPixel(_pos.x+1,_pos.y+2,false);
    }
    if(_vel.x==-1 && _vel.y==0) {
        lcd.setPixel(_pos.x,_pos.y+1,false);
    }
    if(_vel.x==1 && _vel.y==0) {
        lcd.setPixel(_pos.x+2,_pos.y+1,false);
    }

    lcd.refresh();
}

//if the snake moves one pixel, it makes all the tail element to stay in the
//position the previous element was , making the head as the first element dependent on the velocity
void hydralib::updatescr()
{
    if(!_pause) {
        _body[0].X=_pos.x;
        _body[0].Y=_pos.y;
        for(int i=_lenght; i>0; i--) {

            _body[i].X=_body[i-1].X;
            _body[i].Y=_body[i-1].Y;
        }

        _pos.x=_pos.x+_vel.x;
        _pos.y=_pos.y+_vel.y;
    }
}

//depending on players input it will set the proper velocity that will lead to the addecuate direction
void hydralib::commands(Gamepad &pad,DigitalOut &a,DigitalOut &b,DigitalOut &x,DigitalOut &y)
{
    Direction d = pad.get_direction();
    if (_vel.x==0) {
        if (d==W) {
            _pause=false;
            _vel.x=-1;
            _vel.y=0;
        }
        if(d==E) {
            _pause=false;
            _vel.x=1;
            _vel.y=0;
        }
    }
    if(_vel.y==0) {
        if (d==N) {
            _pause=false;
            _vel.y= -1;
            _vel.x=0;
        }
        if(d==S) {
            _pause=false;
            _vel.y= 1;
            _vel.x=0;
        }
    }

    if(_vel.x==0) {
        if (b) {
            _pause=false;
            _vel.x=1;
            _vel.y=0;
        }
        if(x) {
            _pause=false;
            _vel.x=-1;
            _vel.y=0;
        }
    }
    if(_vel.y==0) {
        if (a) {
            _pause=false;
            _vel.y= 1;
            _vel.x=0;
        }
        if(y) {
            _pause=false;
            _vel.y= -1;
            _vel.x=0;
        }
    }
}
//sets randmon food and increases lenght and score
void hydralib::auxiliar()
{
    _food.x= rand()%78+3;
    _food.y= rand()%30+3;
    _lenght++;
    _score++;
}