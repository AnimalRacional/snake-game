#define OLC_PGE_APPLICATION
#include "SnakeGame.h"
#define SG_SCREENWIDTH 40
#define SG_SCREENHEIGHT 40
#define SG_PIXELSIZE 15

int main(){
    SnakeGame instance;
    if(instance.Construct(SG_SCREENWIDTH, SG_SCREENHEIGHT, SG_PIXELSIZE, SG_PIXELSIZE)){
        instance.Start();
    }
    return 0;
}