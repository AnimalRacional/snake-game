#ifndef SG_SNAKEGAME_H
#define SG_SNAKEGAME_H
#include "olcPixelGameEngine.h"
#include <vector>
#define SG_SCREENMIDDLE v2d(ScreenWidth()/2, ScreenHeight()/2)
#define SG_UPDATETIME 0.2
#define SNAKE_COLOR olc::WHITE
#define SNAKE_PART_SIZE v2d(1,1)

typedef olc::v2d_generic<u_int8_t> v2d;

class SnakeGame : public olc::PixelGameEngine{
// Private properties
private:
    std::vector<v2d> snake_parts;
    v2d speed;
    float timeSinceUpdate;

// Public Methods
public:

    SnakeGame(){
        sAppName = "Snake Game!";
    }

    bool OnUserCreate() override{
        snake_parts.push_back(SG_SCREENMIDDLE);
        speed = v2d(1,0);
        timeSinceUpdate = 0;
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override{
        timeSinceUpdate += fElapsedTime;
        if(timeSinceUpdate >= SG_UPDATETIME){
            update_snake();
            draw_snake();
            timeSinceUpdate = 0;
        }
        return true;
    }

    void update_snake(){
        for(int i = 0; i < snake_parts.size(); i++){
            snake_parts[i].x += speed.x;
            snake_parts[i].y += speed.y;
        }
    }

    void draw_snake(){
        for(int i = 0; i < snake_parts.size(); i++){
            Clear(olc::BLACK);
            FillRect(snake_parts[i], SNAKE_PART_SIZE, SNAKE_COLOR);
        }
    }
};
#endif