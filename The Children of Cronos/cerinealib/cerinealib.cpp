#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "cerinealib.h"

//constructor
cerinealib::cerinealib()
{

}
int cerinealib::score()
{
    return _score;
}
//initial values,only first block allowed to move(first=true)
void cerinealib::init()
{
    _size0=45;
    _size1=0;
    _size2=0;
    _size3=0;
    _size4=0;
    _pos0lft=20;
    _pos0rgt=65;
    _posy0=43;
    _k=1;
    _count=0;
    _score=0;
    _lifes=7;
    _border1=0;
    _border2=0;
    _border3=0;
    _border4=0,_border5=0;
    _first=true;
    _second=false;
    _third=false;
    _fourth=false;
    _fith=false;
    _dead=false;
    _pos1.x=85;
    _pos1.y=_posy0-7;
    _pos2.x=-_size1;
    _pos2.y=_pos1.y-7;
    _pos3.x=85;
    _pos3.y=_pos2.y-7;
    _pos4.x=-_size3;
    _pos4.y=_pos3.y-7;
    _pos5.x=85;
    _pos5.y=_pos4.y-7;
}

//gameover screen with score on it
//allows to restart the game
void cerinealib::gameover(N5110 &lcd,DigitalOut &start)
{
    lcd.clear();
    lcd.printString("GAME OVER",10,2);
    sprintf(_buffer,"Score=%2d ",_score);
    lcd.printString(_buffer,10,4); // print formatted data to buffer
    lcd.refresh();

    if(start) {
        _lifes=_lifes-1;
        _dead=false;
        _count=0;
        _score=0;
        _pos0lft=20;
        _pos0rgt=65;
        _pos1.x=85;
        _pos2.x=-_size1;
        _pos3.x=85;
        _pos4.x=-_size2;
        _pos5.x=85;
        _size0=45;
        _size1=0;
        _size2=0;
        _size3=0;
        _size4=0;
        _pos1.y=_posy0-7;
        _pos2.y=_pos1.y-7;
        _pos3.y=_pos2.y-7;
        _pos4.y=_pos3.y-7;
        _pos5.y=_pos4.y-7;
        _border1=0;
        _border2=0;
        _border3=0;
        _border4=0,_border5=0;
        _first=true;
        _second=false;
        _third=false;
        _fourth=false;
        _fith=false;
    }
}





void cerinealib::draw(N5110 &lcd)
{
    lcd.clear();
    //****true conditions**********//
    //draws moving blocks
    if(_first) {
        lcd.drawRect(_pos1.x,_pos1.y,_size0,size,FILL_BLACK);
    }

    if(_second) {
        lcd.drawRect(_pos2.x,_pos2.y,_size1,size,FILL_BLACK);
    }

    if(_third) {
        lcd.drawRect(_pos3.x,_pos3.y,_size2,size,FILL_BLACK);
    }

    if(_fourth) {
        lcd.drawRect(_pos4.x,_pos4.y,_size3,size,FILL_BLACK);
    }

    if(_fith) {
        lcd.drawRect(_pos5.x,_pos5.y,_size4,size,FILL_BLACK);
    }

    //*****false conditions**********//
    //draws dropped blocks

    if(!_first) {
        //out of the first block
        if(_pos1.x>_pos0rgt) {
            _dead=true;
        }
        //inside of the first block
        if(_pos1.x>_pos0lft && _pos1.x<_pos0rgt) {
            _size1=_size0-(_pos1.x+_size0-_pos0rgt); //new size of the block leaving only the part over the initial block in which it has falled
            _border1=_pos1.x;  //set new left extreme, in this case the same as its x position
            lcd.drawRect(_border1,_pos1.y,_size1,size,FILL_BLACK);
        }
        if(_pos1.x<_pos0lft && (_pos1.x+_size0)>_pos0rgt) {//in the range
            _size1=_size0-(_pos0lft-_pos1.x);
            _border1=_pos0lft; //in this case the new left border corresponds to the previous block x position
            lcd.drawRect(_border1,_pos1.y,_size1,size,FILL_BLACK);
        }
        if(_pos1.x<_pos0lft && (_pos1.x+_size0)<_pos0rgt) {//out of range
            _dead=true;
        }
        if(_pos1.x==_pos0lft && _pos1.x+_size0==_pos0rgt) {//in the range.Perfect block dropped
            _size1=_size0;
            _border1=_pos0lft;
            lcd.drawRect(_border1,_pos1.y,_size1,size,FILL_BLACK);
        }
    }


    if(!_second && !_first) {
        if(_pos2.x>(_border1+_size1)) {
            _dead=true;
        }
        if(_pos2.x>_border1 && _pos2.x<(_border1+_size1)) {
            _size2=_size1-(_pos2.x+_size1-(_border1+_size1));
            _border2=_pos2.x;
            lcd.drawRect(_border2,_pos2.y,_size2,size,FILL_BLACK);
        }
        if(_pos2.x<_border1 && (_pos2.x+_size1)<(_border1+_size1)) {
            _size2=_size1-(_border1-_pos2.x);
            _border2=_border1;
            lcd.drawRect(_border2,_pos2.y,_size2,size,FILL_BLACK);
        }
        if(_pos2.x<_border1 && (_pos2.x+_size1)>(_border1+_size1)) {
            _dead=true;
        }
        if(_pos2.x==_border1 && _pos2.x+_size1==(_border1+_size1)) {
            _size2=_size1;
            _border2=_border1;
            lcd.drawRect(_border2,_pos2.y,_size2,size,FILL_BLACK);
        }
    }

    if(!_second && !_first && !_third) {
        if(_pos3.x>(_border2+_size2)) {
            _dead=true;
        }
        if(_pos3.x>_border2 && _pos3.x<(_border2+_size2)) {
            _size3=_size2-(_pos3.x+_size2-(_border2+_size2));
            _border3=_pos3.x;
            lcd.drawRect(_border3,_pos3.y,_size3,size,FILL_BLACK);
        }
        if(_pos3.x<_border2 && (_pos3.x+_size2)<(_border2+_size2)) {
            _size3=_size2-(_border2-_pos3.x);
            _border3=_border2;
            lcd.drawRect(_border3,_pos3.y,_size3,size,FILL_BLACK);
        }
        if(_pos3.x<_border2 && (_pos3.x+_size2)>(_border2+_size2)) {
            _dead=true;
        }
        if(_pos3.x==_border2 && _pos3.x+_size2==(_border2+_size2)) {
            _size3=_size2;
            _border3=_border2;
            lcd.drawRect(_border3,_pos3.y,_size3,size,FILL_BLACK);
        }
    }

    if(!_second && !_first && !_third && !_fourth) {
        if(_pos4.x>(_border3+_size3)) {
            _dead=true;
        }
        if(_pos4.x>_border3 && _pos4.x<(_border3+_size3)) {
            _size4=_size3-(_pos4.x+_size3-(_border3+_size3));
            _border4=_pos4.x;
            lcd.drawRect(_border4,_pos4.y,_size4,size,FILL_BLACK);
        }
        if(_pos4.x<_border3 && (_pos4.x+_size3)<(_border3+_size3)) {
            _size4=_size3-(_border3-_pos4.x);
            _border4=_border3;
            lcd.drawRect(_border4,_pos4.y,_size4,size,FILL_BLACK);
        }
        if(_pos4.x<_border3 && (_pos4.x+_size3)>(_border3+_size3)) {
            _dead=true;
        }
        if(_pos4.x==_border3 && _pos4.x+_size3==(_border3+_size3)) {
            _size4=_size3;
            _border4=_border3;
            lcd.drawRect(_border4,_pos4.y,_size4,size,FILL_BLACK);
        }
    }

    if(!_second && !_first && !_third && !_fourth && !_fith) {
        if(_pos5.x>(_border4+_size4)) {
            _dead=true;
        }
        if(_pos5.x>_border4 && _pos5.x<(_border4+_size4)) {
            _size5=_size4-(_pos5.x+_size4-(_border4+_size4));
            _border5=_pos5.x;
            lcd.drawRect(_border5,_pos5.y,_size5,size,FILL_BLACK);
        }
        if(_pos5.x<_border4 && (_pos5.x+_size4)<(_border4+_size4)) {
            _size5=_size4-(_border4-_pos5.x);
            _border5=_border4;
            lcd.drawRect(_border5,_pos5.y,_size5,size,FILL_BLACK);
        }
        if(_pos5.x<_border4 && (_pos5.x+_size4)>(_border4+_size4)) {
            _dead=true;
        }
        if(_pos5.x==_border4 && _pos5.x+_size4==(_border4+_size4)) {
            _border5=_border4;
            lcd.drawRect(_border5,_pos5.y,_size4,size,FILL_BLACK);
        }
    }
//prints difficulty level indicator in circles.When the difficulty level increases, a circle fills black
    sprintf(_buffer,"%2d ",_score);
    lcd.printString(_buffer,0,0);
    if(_score<=6) {
        lcd.drawCircle(50,3,3,FILL_BLACK);
        lcd.drawCircle(60,3,3,FILL_TRANSPARENT);
        lcd.drawCircle(70,3,3,FILL_TRANSPARENT);
    }
    if(_score>6 && _score<=12) {
        lcd.drawCircle(50,3,3,FILL_BLACK);
        lcd.drawCircle(60,3,3,FILL_BLACK);
        lcd.drawCircle(70,3,3,FILL_TRANSPARENT);
    }
    if(_score>12) {
        lcd.drawCircle(50,3,3,FILL_BLACK);
        lcd.drawCircle(60,3,3,FILL_BLACK);
        lcd.drawCircle(70,3,3,FILL_BLACK);
    }
    lcd.drawRect(_pos0lft,_posy0,_size0,size,FILL_BLACK);
    lcd.refresh();

}

void cerinealib::commands(DigitalOut &b,DigitalOut &a,DigitalOut &x,DigitalOut &y,Gamepad &pad)
{

    if(b||a||x||y) {
        wait(0.1);    //small button debouncing
        if(b||a||x||y) {
            pad.tone(NOTE_C6,0.5);
            _count++;     //block counting added everytime a button is pressed
        }
    }



    if(_count==1 && _first) {
        _first=false;          //first set it to false,then set the next one to true
        _second=true;
        _score++;
    }

    if(_second && _count==2) {
        _second=false;
        _third=true;
        _score++;
    }

    if(_third && _count==3) {
        _third=false;
        _fourth=true;
        _score++;
    }

    if(_fourth && _count==4) {
        _fourth=false;
        _fith=true;
        _score++;
    }

    if(_fith && _count==5) {
        _fith=false;
        _score++;
    }


}


void cerinealib::updatescr()
{

//**********true conditions************//
//movement of the blocks in the screen from left to right or viceversa
    if(_first) {
        _pos1.x=_pos1.x-_k;
        if(_pos1.x==0) {
            _k=-1;
        }
        if ((_pos1.x+45)==84 && _k==-1) {
            _k=1;
        }
    }

    if(_second) {
        if(_pos2.x<0) {
            _k=1;
        }
        _pos2.x=_pos2.x+_k;
        if(_pos2.x==0) {
            _k=1;
        }
        if ((_pos2.x+_size1)==84 && _k==1) {
            _k=-1;
        }
    }

    if(_third) {
        if(_pos3.x>84) {
            _k=1;
        }
        _pos3.x=_pos3.x-_k;
        if(_pos3.x==0) {
            _k=-1;
        }
        if ((_pos3.x+_size2)==84 && _k==-1) {
            _k=1;
        }
    }

    if(_fourth) {
        if(_pos4.x<0) {
            _k=1;
        }
        _pos4.x=_pos4.x+_k;
        if(_pos4.x==0) {
            _k=1;
        }
        if ((_pos4.x+_size3)==84 && _k==1) {
            _k=-1;
        }
    }

    if(_fith) {
        _pos5.x=_pos5.x-_k;
        _pos5.y=_pos4.y-7;

        if(_pos5.x>84) {
            _k=1;
        }
        if(_pos5.x<=0) {
            _k=-1;
        }
        if ((_pos5.x+_size4)==84 && _k==-1) {
            _k=1;
        }
    }


//**************false conditions**********//

//blocks dropped movement
    if (!_first) {
        _pos1.y=_posy0-size;
        _pos1.x=_pos1.x;
    }

    if (!_second) {
        _pos2.y=_pos1.y-size;
        _pos2.x=_pos2.x;
    }

    if (!_third) {
        _pos3.y=_pos2.y-size;
        _pos3.x=_pos3.x;
    }

    if (!_fourth) {
        _pos4.y=_pos3.y-size;
        _pos4.x=_pos4.x;
    }
//resets the loop
//everything switches position to the next one
    if (!_fith && _count==5) {
        _pos5.y=_pos4.y-size;
        _pos5.x=_pos5.x;
        _pos0lft=_pos1.x;
        _pos1.x=_pos2.x;
        _pos3.x=_pos4.x;
        _pos4.x=_pos5.x;
        _size0=_size1;
        _size1=_size2;
        _size2=_size3;
        _size3=_size4;
        _size4=_size5;
        _border1=_border2;
        _border2=_border3;
        _border3=_border4;
        _border4=_border5;
        //sets 5 to move again with the previous block size
        _fith=true;
        _pos5.x=-_size4;
        //goes back to 4 the count
        _count=4;
    }
}
//increse of velocities by waits depending on the score
void cerinealib::velocities()
{
    if(_score<=6) {
        wait(0.05);
    } else if(_score>=6 && _score<=12) {
        wait(0.03);
    } else if(_score>12) {
        wait(0.01);
    }
}

//sends dead variable to main file
bool cerinealib::die()
{
    if (_dead) {
        return true;
    }
    return false;
}

