
#include "game.h"
//serial object for checking with printf()
Serial serial(USBTX, USBRX); 
////////////////////////////////////////////////////
int main()
{
    init();           //initialisats all games inits
    
    //pc.printf("intro done\n");
    
    intro();          //fancy intro
    introlights.detach(); //detach into switching on lights  function
    while(menuselection) {
        
        //pcd.printf("menu screen\n");
        
        pad.leds_on(); 
        float pott=pad.read_pot();
        lcd.setBrightness(pott);
        menuscreen();              //displays manu screen
        menuselect();              //allows to switch between positions
    }
    
//pc.printf("out of the game\n");

}
/////////////////////////////////////////////////////////////////

//if new game selected do this
void newgame()
{
    while(selection) {                                      //while the games selection variable is true,allow to choose game
    
    //pc.printf("games screen in\n");
    
        pad.leds_on();
        float pott=pad.read_pot();
        totalscore=scoreg1+scoreg2+scoreg3+scoreg4+scoreg5;//adds up all the individual games scores
        
        //pc.printf("score:%d\n",totalscore);
        
        game();                                            //peforms the game selection screen
        select();                                          //allows to select between screens
        if (r) {                                           //if back button(in this case r) is pressed,set the games selector running variable as false and the menu selecor variable to true
        
        //pc.printf("go back\n");
        
            selection=false;
            menuselection=true;
        }
    }
}

////////////////////////////////////////////////////////////////////

//if menuselection is true,menu screen is running
void menuscreen()
{
    drawselectmenu();                           //allows o select options
    Direction d = pad.get_direction();
    if (d==S || a) {
        wait(0.1);                            //small button debouncing
        if (d==S || a) {
            statemenu = menu[statemenu].nextstate[1];  //swiches between options
        }
    }
    if (d==N || y) {
        wait(0.1);
        if(d==N || y) {
            statemenu = menu[statemenu].nextstate[0];
        }
    }
    outputmenu=menu[statemenu].position;
    //pc.printf("%d\n",statemenu);
}

//if selection is true, the games selector screen is running
void game()
{
    drawselectscreen();                //displays games to be chosen
    Direction d = pad.get_direction();
    if (d==S || a) {
        wait(0.1);                    //small debouncing
        if (d==S || a) {
            state = games[state].nextstate[1];
        }
    }
    if (d==N || y) {
        wait(0.1);
        if(d==N || y) {
            state = games[state].nextstate[0];//same as previous function
            wait(0.1);
        }
    }
    output=games[state].position;
    //pc.printf("%d\n",state);

}
//in the menu screen,the player selects the desired option screen by pressing l
void menuselect()
{
    if(l && outputmenu==0) {   //if one option is chosen
        menuselection=false;   //stop running menu screen, log off from this screen
        selection=true;       //start running the chosen option, log in in this screen
        newgame();            //do the chosen option functions
    }

    if(l && outputmenu==1) {
        menuselection=false;
        highscr=true;
        highscores();
    }
    
    if(l && outputmenu==2) {
        menuselection=false;
        tut=true;
        tutorial();
    }
    
    if(l && outputmenu==3) {
        menuselection=false;
        stor=true;
        story();
    }
}

//same as previous function but instead of wih menu options wih the different games

void select()
{
    if(start && output==0) {
        selection=false;
        game1=true;
        gameone();
    }
    if(start && output==1) {
        selection=false;
        game2=true;
        gametwo();
    }
    if(start && output==2) {
        selection=false;
        game3=true;
        gamethree();
    }
    if(start && output==3) {
        selection=false;
        game4=true;
        gamefour();
    }
    if(start && output==4) {
        selection=false;
        game5=true;
        gamefive();
    }
}



//////////////////////GAMES/////////////////////////////////////////////////////
void gamefive()
{
    while(game5) {                //if game 5 running
    
    //pc.printf("game05\n");
    
        float pott=pad.read_pot();
        lcd.setBrightness(pott);
        if(back) {
            if (tau.score()>scoreg5) { //if back,get the score if bigger than the previous one
                scoreg5=tau.score();
            }
            game5=false;   //log off the game 5 function
            selection=true;  //go back to games selecor screen,log into it
        }
        tau.game(lcd,pad,a,start,b,x);  //performs game 5

    }
}

void gamefour()
{
    
    //pc.printf("game04\n");
    
    while(game4) {
        float pott=pad.read_pot();
        lcd.setBrightness(pott);
        if(back) {                 //same as before
            game4=false;
            selection=true;
        }
        if(!cer.die()) {              //if player hasnt died
            cer.commands(b,a,x,y,pad); //performs the game in the addecuate order of first commands(players input)
            cer.updatescr();          //then updates the movment of the blocks and check if they are dopped(refer to library for more info)
            cer.draw(lcd);           //draws the game and checks if player dies 
            cer.velocities();        //depending on the score increase or not the game velocity
        } else if(cer.die()) {     //if died game over and allows to restart
            cer.gameover(lcd,start);
            if (cer.score()>scoreg4) {
                scoreg4=cer.score();
            }
        }
    }
}

void gamethree()
{
    
    //pc.printf("game03\n");
    
    while(game3) {
        float pott=pad.read_pot();
        lcd.setBrightness(pott);
        if(back) {      //same as before
            game3=false;
            selection=true;
        }
        if(aurig.touch()) { //if bird didnt touch the pipes
            srand( time( NULL ) ); //genrates random
            aurig.pipegenerator(pad,start); //generaes pipes (for more info refer to library)
            aurig.updatescr(a,b,x,y,pad);   //updates the screen movement and bird movement
            aurig.draw(lcd);
            wait(0.05);
        } else {                           //if bird touched the pipes
            aurig.gameover(lcd,pad,l,r); //gameover and allows to reset
            if (aurig.score()>scoreg3) {
                scoreg3=aurig.score();
            }
        }
    }
}

void gametwo()
{
    
    //pc.printf("game02\n");
    
    alienmove.attach(&aliens, 1.0);
    while(game2) {
        float pott=pad.read_pot();
        lcd.setBrightness(pott);
        if(back) {        //same as before
            game2=false;
            selection=true;
            alienmove.detach(); //detach the movement of the aliens if the player gets out of the game
        }
        if (!stym.die()) {  //if player didnt die (refer to library for more info)
            stym.leds(pad); //lifes showed in the leds
            stym.commands(pad,l,b,x,r); //input
            stym.touch();  //checks if any bullet has hitted anything
            srand(time(NULL));
            stym.auxiliar(); //generates new alien bullets
            stym.updatescr(); //updates the movement
            stym.draw(lcd); //draws the screen
            wait(0.08);  //small delay
        } else if(stym.die()) { //if dead
            stym.gameover(lcd,start,pad); //gameover allowing to restart
            if (stym.score()>scoreg2) {
                scoreg2=stym.score();
            }
        }
    }
}


void gameone()
{

    //pc.printf("game01\n");

    while(game1) {
        float pott=pad.read_pot();
        lcd.setBrightness(pott);
        if(back) { //same as before
            game1=false;
            selection=true;
        }
        if (hyd.border()) { //if player didnt hit anything
            hyd.leds(pad); //lifes
            hyd.commands(pad,a,b,x,y); //input(refer to library for more info)
            if (hyd.eat()) { //if snake eats food
                pad.tone(NOTE_GS6,0.5);
                srand( time( NULL ) );
                hyd.auxiliar(); //generates new food
            }
            hyd.updatescr(); //updates movement
            hyd.pausegame(l,r,lcd,back); //checks if the game has been paused
            hyd.draw(lcd); //draws screen
            hyd.touch();  //checks if snake ates itself
            hyd.velocities(); //the higher score the faster the gam will go
        } else {
            hyd.gameover(lcd,start,pad);
            if (hyd.score()>scoreg1) {
                scoreg1=hyd.score();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

//draws the games selector screen
void drawselectscreen()
{
    lcd.clear();

    if(output==0) {
        lcd.drawRect(0,8,84,8,FILL_BLACK);
    }
    if(output==1) {
        lcd.drawRect(0,16,84,8,FILL_BLACK);
    }
    if(output==2) {
        lcd.drawRect(0,24,84,8,FILL_BLACK);
    }
    if(output==3) {
        lcd.drawRect(0,32,84,8,FILL_BLACK);
    }
    if(output==4) {
        lcd.drawRect(0,40,84,8,FILL_BLACK);
    }
    lcd.printString("DEMETER",0,1);
    lcd.printString("ZEUS",0,2);
    lcd.printString("HERA",0,3);
    lcd.printString("POSEIDON",0,4);
    lcd.printString("HADES",0,5);
    lcd.refresh();
}
//draws the men options selectors
void drawselectmenu()
{
    lcd.clear();
    lcd.printString("MENU",30,0);
    lcd.printString("GAME",0,2);
    lcd.printString("SCORES",0,3);
    lcd.printString("TUTORIAL",0,4);
    lcd.printString("STORY",0,5);

    if(outputmenu==0) {
        lcd.drawRect(0,16,84,8,FILL_BLACK);
        lcd.printString("GAME",0,2);
    }
    if(outputmenu==1) {
        lcd.drawRect(0,24,84,8,FILL_BLACK);
        lcd.printString("SCORES",0,3);
    }
    if(outputmenu==2) {
        lcd.drawRect(0,32,84,8,FILL_BLACK);
        lcd.printString("TUTORIAL",0,4);
    }
    if(outputmenu==3) {
        lcd.drawRect(0,40,84,8,FILL_BLACK);
        lcd.printString("STORY",0,5);
    }

    lcd.refresh();
}

//prints the intro
void intro()
{
    //pc.printf("intro\n");
    Bitmap sprite(randulfe,15,72);
    sprite.render(lcd,6,0);
    sprite.print();
    lcd.printString("presents",5,4);
    lcd.refresh();
    wait(1);
    lcd.printString(".",60,4);
    lcd.refresh();
    wait(1);
    lcd.printString(".",65,4);
    lcd.refresh();
    wait(1);
    lcd.printString(".",70,4);
    lcd.refresh();
    wait(1);
    lcd.clear();
    Bitmap sprite1(gamename,15,72);
    Bitmap sprite2(gamename1,17,72);
    Bitmap sprite3(gamename2,10,13);
    sprite1.render(lcd,0,0);
    sprite3.render(lcd,25,15);
    sprite2.render(lcd,4,26);
    sprite1.print();
    sprite3.print();
    sprite2.print();
    lcd.refresh();
    wait(8);
    lcd.clear();
    lcd.printString("In menu scr:",0,0);
    lcd.printString("select:l",0,1);
    lcd.printString("Back:r",0,2);
    lcd.printString("In game scr:",0,3);
    lcd.printString("select:start",0,4);
    lcd.printString("Back:back",0,5);
    lcd.refresh();
    wait(4);
    lcd.clear();
    lcd.printString("In the games",0,0);
    lcd.printString("the leds",0,1);
    lcd.printString("indicate",0,2);
    lcd.printString("your lifes",0,3);
    lcd.printString("left!",0,4);
    lcd.refresh();
    wait(4);
}

//performs story screen and the story selector algorithm as the one i showed previously
void story()
{
    //pc.printf("story\n");
    while(stor) {
        lcd.clear();
        lcd.printString("NEXT",60,5);
        if(outputstory==0) {
            lcd.printString("Hey there! :)",0,0);
            lcd.printString("Welcome to the",0,1);
            lcd.printString("Olympus.Hestia",0,2);
            lcd.printString("God of home,",0,3);
            lcd.printString("needs your hlp",0,4);
        }
        if(outputstory==1) {
            lcd.printString("for protecting",0,0);
            lcd.printString("the sacred",0,1);
            lcd.printString("fire.But first",0,2);
            lcd.printString("you need to",0,3);
            lcd.printString("prove to the",0,4);
        }
        if(outputstory==2) {
            lcd.printString("ancient gods",0,0);
            lcd.printString("(siblings of",0,1);
            lcd.printString("Hestia) that",0,2);
            lcd.printString("you're a brave",0,3);
            lcd.printString("soldier.",0,4);
        }

        if(outputstory==3) {
            lcd.printString("You must pass",0,0);
            lcd.printString("their challen-",0,1);
            lcd.printString("-ges!Get ",0,2);
            lcd.printString("ready for the",0,3);
            lcd.printString("adventure!!!",0,4);
        }
        lcd.refresh();

        Direction d = pad.get_direction();
        if (d==E || b) {
            wait(0.1);
            if (d==E || b) {
            statestory = games[statestory].nextstate[1];
            }
        }
        if (d==W || x) {
            wait(0.1);
            if (d==W || x) {
            statestory = games[statestory].nextstate[0];
         }   
        }
        outputstory=games[statestory].position;
        if(r) {
            stor=false;
            menuselection=true;
        }
    }
}

//shows scores for each game and a total score
void highscores()
{
    //pc.printf("highscores\n");
    while(highscr) {
        lcd.clear();
        sprintf(buffer0,"TOT score=%2d",totalscore);
        lcd.printString(buffer0,0,0);
        sprintf(buffer1,"Game 1=%2d",scoreg1);
        lcd.printString(buffer1,0,1);
        sprintf(buffer2,"Game 2=%2d",scoreg2);
        lcd.printString(buffer2,0,2);
        sprintf(buffer3,"Game 3=%2d",scoreg3);
        lcd.printString(buffer3,0,3);
        sprintf(buffer4,"Game 4=%2d",scoreg4);
        lcd.printString(buffer4,0,4);
        sprintf(buffer5,"Game 5=%2d",scoreg5);
        lcd.printString(buffer5,0,5);
        lcd.refresh();
        if(r) {
            highscr=false;
            menuselection=true;
        }
    }
}

//draws the tutorial screens and allows to switch between options as showed previousl
void tutorial()
{
    //pc.printf("tutorial\n");
    while(tut) {
        lcd.clear();
        lcd.printChar('1',0,0);
        lcd.printChar('2',16,0);
        lcd.printChar('3',32,0);
        lcd.printChar('4',48,0);
        lcd.printChar('5',64,0);

        if(outpututorial==0) {
            lcd.drawRect(0,0,9,9,FILL_BLACK);
            lcd.printString("Y,A,X,B:",0,2);
            lcd.printString("UP,DWN,LFT,RGT",0,3);
            lcd.printString("L,R     PAUSE",0,5);
        }
        if(outpututorial==1) {
            lcd.drawRect(16,0,9,9,FILL_BLACK);
            lcd.printString("A,B,JOY:",0,2);
            lcd.printString("MOVE RGT/LFT",0,3);
            lcd.printString("L,R     SHOOT",0,5);
        }
        if(outpututorial==2) {
            lcd.drawRect(32,0,9,9,FILL_BLACK);
            lcd.printString("A,B,X,Y:",0,2);
            lcd.printString("JUMP",0,3);
        }
        if(outpututorial==3) {
            lcd.drawRect(48,0,9,9,FILL_BLACK);
            lcd.printString("A/B/X/Y:",0,2);
            lcd.printString("LEAVE BLOCK",0,3);
        }
        if(outpututorial==4) {
            lcd.drawRect(64,0,9,9,FILL_BLACK);
            lcd.printString("JOY:",0,2);
            lcd.printString("SELECT",0,3);
            lcd.printString("A:CONTINUE",0,5);
        }
        lcd.refresh();

        Direction d = pad.get_direction();
        if (d==E || b) {
            wait(0.1);
            if (d==E || b) {
            statetutorial = games[statetutorial].nextstate[1];
            }
        }
        if (d==W || x) {
            wait(0.1);
            if (d==W || x) {
            statetutorial = games[statetutorial].nextstate[0];
            
        }}
        outpututorial=games[statetutorial].position;
        if(r) {
            tut=false;
            menuselection=true;
        }


    }
}
//ligh function for increasing one in the intro
void lights()
{

    if(k==1 && lit>6) {
        k=-1;
    }
    if(k==-1 && lit<0) {
        k=1;
    }
    lit+=k;


    for(int i=1; i<lit; i++) {
        pad.led(i,1);
    }
}
//function that allows the ticker to peform a library function
void aliens()
{
    stym.move();
}
//initialise objects
void init()
{
    //pc.printf("game starts\n");
    introlights.attach(&lights,1);
    tau.init();
    cer.init();
    aurig.init();
    stym.init();
    hyd.init();
    pad.init();
    lcd.init();
    lcd.normalMode();
    lcd.setBrightness(0.5);
}