#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class SnakeGame : public olc::PixelGameEngine{
public:
    SnakeGame(){
        sAppName = "Snake Game!";
    }

public:
    bool OnUserCreate() override{
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override{
        return true;
    }
};

int main(){
    SnakeGame instance;
    if(instance.Construct(600,500,2,2)){
        instance.Start();
    }
    return 0;
}