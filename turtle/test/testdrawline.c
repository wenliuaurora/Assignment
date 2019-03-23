#include "neillsdl2.h"
#include "interp.h"
#include <assert.h> 
#include <string.h>

int main(){
    Turtle turtle;
    SDL_Simplewin sw;
    Neill_SDL_Init(&sw);
    /*In this function you can draw a line on screen*/
    turtle.currposition[0]=INITX/2+100;
    turtle.prevposition[0]=INITX/2;
    turtle.currposition[1]=INITY/2;
    turtle.prevposition[1]=INITY/2;
    Drawline(&turtle,&sw);
    SDL_Delay(DISPLAYDELAY);
    return 0;
}