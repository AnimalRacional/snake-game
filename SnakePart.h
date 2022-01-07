#ifndef SG_SNAKEPART_H
#define SG_SNAKEPART_H
#include "olcPixelGameEngine.h"

struct SnakePart {
// Private Properties
private:
    bool frozen;
    olc::vi2d position;

// Public Methods
public:
    static int wrap_number(int num, int exc_max){
        int res = num % exc_max;
        if(res < 0){
            res = exc_max-1;
        }
        return res;
    }

    static SnakePart create(olc::vi2d pos, bool frozen = true){
        SnakePart res;
        res.frozen = true;
        res.position = pos;
        return res;
    }


    void update_part(olc::vi2d new_pos, int screen_width, int screen_height){
        if(!frozen){
            position = new_pos;
            position.x %= screen_width;
            position.y %= screen_height;
        }
        else{
            frozen = false;
        }
    }

    void update_part_by_speed(olc::vi2d speed, int screen_width, int screen_height){
        if(!frozen){
            position += speed;
            position.x = wrap_number(position.x, screen_width);
            position.y = wrap_number(position.y, screen_height);
        }
        else{
            frozen = false;
        }
    }

    olc::vi2d get_position(){ return position; }
    bool is_frozen(){ return frozen; }
};

#endif