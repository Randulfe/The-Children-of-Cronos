# The-Children-of-Cronos
This was a project I made in my second year of Mechtronics & Robotics Engineering degree as part of a module of embedded systems. The purpose was to create a piece of software (most likely a game) to interact with the electronics we created in our lab (image below). 

<img src="https://github.com/Randulfe/The-Children-of-Cronos/blob/master/20170511_114029.jpg" width="300">

The microcontroller we used was a **FRDM-K64F** from **NXP** and the code was all written in **C++** using the online IDE of mbed that I also used for online source control.

This video-game was made out of 5 mini games inspired by popular old games like **snake**, **space invaders** and other more recent ones like **flappy birds**. Such a variety of mini games let me learn a lot about different game dynamics. Moreover, I used a common tematic based on the Greek mythology (each game represented one of the children of the titan Cronos) to connect all the mini games and make a bigger clearer picture specially for the point system that the game was using. 

Each mini game was created in a separate C++ library with its classes and objects that then were imported into the `main cpp game file` that connected all of them and added some other extra functionalities like lighting and intro/outro screens. The games took use of all the electronic feautures avalaiable *(sound effects, screen restrictions, storage using a SD card, lightning, a potentiometer, a joystick, several buttons and battery saving spenses)*. 

This was one of my first programming projects and the one that made me decide to focus more on software development as I really loved and enjoyed it. 

<img src="https://github.com/Randulfe/The-Children-of-Cronos/blob/master/20170328_203310.jpg" width="300">

### Instructions

If you wish to run this project into your own device or explore its features, please check [the main folder containing the game code](https://github.com/Randulfe/The-Children-of-Cronos/tree/master/The%20Children%20of%20Cronos) where you will find the high level libraries for all the games and the low level libraries for interacting with the electronics such as the gamepad or the joysticks. 

### License

Copyright (c) 2016 Mateo Randulfe
