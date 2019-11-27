#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "taurolib.h"

//constructor
taurolib::taurolib()
{

}
/**< structure for switching between answer options */
struct State {
    int position;/**< actual state */
    int nextstate[2];/**< next state */
};
//state array for the answers
State _answer[5]= {
    {0,{3,1}},
    {1,{0,2}},
    {2,{1,3}},
    {3,{2,0}}
};

//sets default output state and count to 0.Therefore,dafault option selected would be the first one
//sets game started as false(_yes)
void taurolib::init()
{
    _state=0;
    _output=0;
    _count=0;
    _score=0;
    _yes=false;

}
//depending on the count the question will be the one corresponding the level
void taurolib::drawquestion(N5110 &lcd)
{
    if (_count==0) {
        lcd.printString("How many",15,0);
        lcd.printString("kingdoms",15,1);
        lcd.printString("are in",12,2);
        lcd.printString("nature?",11,3);

        lcd.printString("3",7,5);
        lcd.printString("2",25,5);
        lcd.printString("5",49,5);
        lcd.printString("6",70,5);
    }
    if(_count==1) {
        lcd.printString("In which",13,0);
        lcd.printString("century was",5,1);
        lcd.printString("Sheakspere",7,2);
        lcd.printString("born?",23,3);
        lcd.printString("16",4,5);
        lcd.printString("14",24,5);
        lcd.printString("17",47,5);
        lcd.printString("13",67,5);
    }
    if(_count==2) {
        lcd.printString("tan(45)?",18,1);
        lcd.printString("0.7",2,5);
        lcd.printString("0.5",23,5);
        lcd.printString("1",50,5);
        lcd.printString("1.7",64,5);
    }
    if(_count==3) {
        lcd.printString("How many",15,0);
        lcd.printString("kinds of",15,1);
        lcd.printString("persons con-",5,2);
        lcd.printString("-sider Platon?",0,3);
        lcd.printString("2",6,5);
        lcd.printString("5",28,5);
        lcd.printString("10",47,5);
        lcd.printString("3",69,5);
    }
    if(_count==4) {
        lcd.printString("How many",15,0);
        lcd.printString("electrons does",0,1);
        lcd.printString("a molecule",9,2);
        lcd.printString("of H20 have?",5,3);
        lcd.printString("8",7,5);
        lcd.printString("10",24,5);
        lcd.printString("6",49,5);
        lcd.printString("20",68,5);
    }
    if(_count==5) {
        lcd.printString("How many",15,0);
        lcd.printString("countries are a",0,1);
        lcd.printString("part of the?",18,2);
        lcd.printString("EU?",31,3);
        lcd.printString("26",4,5);
        lcd.printString("28",25,5);
        lcd.printString("18",47,5);
        lcd.printString("27",68,5);
    }
    if(_count==6) {
        lcd.printString("How many",15,0);
        lcd.printString("elementary",8,1);
        lcd.printString("particles",8,2);
        lcd.printString("are there?",8,3);
        lcd.printString("16",4,5);
        lcd.printString("12",25,5);
        lcd.printString("3",49,5);
        lcd.printString("8",70,5);
    }
    if(_count==7) {
        lcd.printString("When did the",6,0);
        lcd.printString("Roman Empire",0,1);
        lcd.printString("fall?",5,2);
        lcd.printString("476",1,5);
        lcd.printString("350",22,5);
        lcd.printString("512",41,5);
        lcd.printString("342ac",64,5);
    }
    if(_count==8) {
        lcd.printString("What year was",5,0);
        lcd.printString("the car",3,1);
        lcd.printString("invented in?",0,2);
        lcd.printString("(18..?)",18,3);
        lcd.printString("64",4,5);
        lcd.printString("21",26,5);
        lcd.printString("07",47,5);
        lcd.printString("48",68,5);
    }
    if(_count==9) {
        lcd.printString("How many",15,0);
        lcd.printString("children does",2,1);
        lcd.printString("Cronos have?",5,2);
        lcd.printString("5",7,5);
        lcd.printString("4",28,5);
        lcd.printString("6",49,5);
        lcd.printString("8",71,5);
    }

}


//draws the option selected
void taurolib::drawselect(N5110 &lcd)
{
    lcd.drawRect(0,32,20,15,FILL_TRANSPARENT);
    lcd.drawRect(21,32,20,15,FILL_TRANSPARENT);
    lcd.drawRect(42,32,20,15,FILL_TRANSPARENT);
    lcd.drawRect(63,32,20,15,FILL_TRANSPARENT);
    if(_output==0) {
        lcd.drawRect(0,32,20,15,FILL_BLACK);
    }
    if(_output==1) {
        lcd.drawRect(21,32,20,15,FILL_BLACK);
    }
    if(_output==2) {
        lcd.drawRect(42,32,20,15,FILL_BLACK);
    }
    if(_output==3) {
        lcd.drawRect(63,32,20,15,FILL_BLACK);
    }
}

//draw main function of the questions screen
void taurolib::draw(N5110 &lcd,Gamepad &pad,DigitalOut &b,DigitalOut &x)
{
    Direction d = pad.get_direction();
    if (d==E || b) {
        wait(0.1);    //small debouncing
        if (d==E || b) {
            _state = _answer[_state].nextstate[1];
            pad.tone(NOTE_A1,0.5);
        }
    }
    if (d==W || x) {
        wait(0.1);
        if (d==W || x) {
            _state = _answer[_state].nextstate[0];
            pad.tone(NOTE_A1,0.5);
        }
    }

    _output=_answer[_state].position;
    lcd.clear();
    taurolib::drawselect(lcd);
    taurolib::drawquestion(lcd);
    lcd.refresh();
}

//transition screens depending on output
void taurolib::transition(N5110 &lcd)
{
    if(_count==0) {
        lcd.clear();
        lcd.printString("Level 1 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 2:",8,3);
        lcd.printString("Literature",8,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==1) {
        lcd.clear();
        lcd.printString("Level 2 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 3:",8,3);
        lcd.printString("Maths",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==2) {
        lcd.clear();
        lcd.printString("Level 3 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 4:",8,3);
        lcd.printString("Philosophy",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==3) {
        lcd.clear();
        lcd.printString("Level 4 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 5:",8,3);
        lcd.printString("Chemistry",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==4) {
        lcd.clear();
        lcd.printString("Level 5 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 6:",8,3);
        lcd.printString("Geography",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==5) {
        lcd.clear();
        lcd.printString("Level 6 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 7:",8,3);
        lcd.printString("Physics",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==6) {
        lcd.clear();
        lcd.printString("Level 7 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 8:",8,3);
        lcd.printString("History",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==7) {
        lcd.clear();
        lcd.printString("Level 8 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 9:",8,3);
        lcd.printString("Technology",5,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }
    if(_count==8) {
        lcd.clear();
        lcd.printString("Level 9 done!",10,0);
        lcd.printString("Get ready for:",3,1);
        lcd.printString("Level 10:",8,3);
        lcd.printString("You",15,4);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,13,5);
        lcd.refresh();
        wait(2);
    }

    if(_count==9) {
        lcd.clear();
        lcd.printString("Your final",0,0);
        lcd.printString("score is:",0,1);
        sprintf(_buffer,"Score=%2d",_score);
        lcd.printString(_buffer,0,2);
        if(_score==100) {
            _score+=100;
            lcd.printString("100%,you just",0,4);
            lcd.printString("became a God",0,5);
        }
        lcd.refresh();
        wait(2);
    }
}
//intro screen
void taurolib::intro(N5110 &lcd)
{
    lcd.clear();
    lcd.printString("Welcome,",17,1);
    lcd.printString("press start",7,3);
    lcd.refresh();
}
//game over screen
void taurolib::gameover(N5110 &lcd)
{
    lcd.clear();
    lcd.printString("MECK!! WRONG",6,1);
    lcd.printString("-5 pts",20,4);
    lcd.refresh();
    _score-=5;
    wait(2);
}
//checks if answer was right and passes the transition and/or gameover screen
void taurolib::update(N5110 &lcd,DigitalOut &a)
{
    if(_output==2 && _count==0 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=2 && _count==0 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==0 && _count==1 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=0 && _count==1 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==2 && _count==2 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=2 && _count==2 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==3 && _count==3 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=3 && _count==3 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==1 && _count==4 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=1 && _count==4 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==3 && _count==5 && a) {
        taurolib::transition(lcd);
        _score+=10;
        _count++;
    } else if(_output!=3 && _count==5 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==1 && _count==6 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=1 && _count==6 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==0 && _count==7 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=0 && _count==7 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }


    if(_output==2 && _count==8 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=2 && _count==8 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }

    if(_output==2 && _count==9 && a) {
        _score+=10;
        taurolib::transition(lcd);
        _count++;
    } else if(_output!=2 && _count==9 && a) {
        taurolib::gameover(lcd);
        taurolib::transition(lcd);
        _count++;
    }
    if(_count==10) {
        _yes=false;
        _count=0;
        _score=0;
    }

}
int taurolib::score()
{
    return _score;
}

void taurolib::game(N5110 &lcd,Gamepad &pad,DigitalOut &a,DigitalOut &start,DigitalOut &b,DigitalOut &x)
{
    if(!_yes) { //while the game hasnt started
        taurolib::intro(lcd);
    }
    if(start) {
        _yes=true;
    }
    if(_yes) { //if it has started
        taurolib::draw(lcd,pad,b,x);
        taurolib::update(lcd,a);
        wait(0.1);
    }
} //small delay