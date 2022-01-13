#ifndef SG_SNAKEGAME_CPP
#define SG_SNAKEGAME_CPP
#include "olcPixelGameEngine.h"
#include <vector>
#include "SnakePart.h"
#include <pthread.h>
#define SG_SCREENMIDDLE olc::vi2d(ScreenWidth()/2, ScreenHeight()/2)
#define SG_UPDATETIME 0.1
#define SNAKE_PART_SIZE olc::vi2d(1,1)
#define SNAKE_COLOR olc::WHITE
#define SG_FOOD_COLOR olc::RED
#define SG_BG_COLOR olc::BLACK
#define SNAKE_HEAD snake_parts[0]

class SnakeGame : public olc::PixelGameEngine{
// Private properties
private:
    std::vector<SnakePart> snake_parts;
    olc::vi2d speed;
    float timeSinceUpdate;
    olc::vi2d food_location;
    bool is_dead;
    pthread_t read_speed_thread;

// Public Methods
public:

    SnakeGame(){
        sAppName = "Snake Game!";
    }

    olc::vi2d get_rand_position(){
        olc::vi2d res = olc::vi2d((rand() % ScreenWidth()), (rand() % ScreenHeight()));
        return res;
    }

    bool OnUserCreate() override{
        restart_game();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override{
        if(!is_dead){
            timeSinceUpdate += fElapsedTime;
            if(timeSinceUpdate >= SG_UPDATETIME){
                update_game();
                draw_screen();
                timeSinceUpdate = 0;
            }
        }
        else{
            show_dead_screen();
            check_for_restart();
        }
        return true;
    }

    bool OnUserDestroy() override{
        is_dead = true;
        return pthread_join(read_speed_thread, NULL) == 0;
    }

    void restart_game(){
        is_dead = false;
        snake_parts.clear();
        snake_parts.push_back(SnakePart::create(SG_SCREENMIDDLE, false));
        speed = olc::vi2d(1,0);
        update_food_location();

        srand(time(NULL));
        timeSinceUpdate = 0;
        pthread_create(&read_speed_thread, NULL, update_speed_wrapper, this);
    }

    void grow_snake(){
        snake_parts.push_back(SnakePart::create(snake_parts[snake_parts.size()-1].get_position()));
    }

    void check_for_restart(){
        if(GetKey(olc::SPACE).bHeld || GetKey(olc::ENTER).bHeld){
            restart_game();
        }
    }

    void show_dead_screen(){
        Clear(olc::RED);
        DrawString(1,ScreenHeight()/2,"Dead!");
    }

    void die(){
        is_dead = true;
        show_dead_screen();
    }

    bool snake_died(){
        for(int i = 1; i < snake_parts.size(); i++){
            if(snake_parts[i].get_position() == SNAKE_HEAD.get_position() && !snake_parts[i].is_frozen()){
                return true;
            }
        }
        return false;
    }

    void update_game(){
        update_snake();
        if(snake_collides_with(food_location)){
            grow_snake();
            update_food_location();
        }
        if(snake_died()){
            die();
        }
    }

    bool snake_collides_with(olc::vi2d pos){
        for(int i = 0; i < snake_parts.size(); i++){
            if(pos == snake_parts[i].get_position()){ return true; }
        }
        return false;
    }

    void update_snake(){
        for(int i = snake_parts.size()-1; i > 0; i--){
            snake_parts[i].update_part(snake_parts[i-1].get_position(), ScreenWidth(), ScreenHeight());
        }
        SNAKE_HEAD.update_part_by_speed(speed, ScreenWidth(), ScreenHeight());
    }

    static void *update_speed_wrapper(void* arg){
        SnakeGame* game = reinterpret_cast<SnakeGame*>(arg);
        while(!game->is_dead){
            std::cout << "";
            game->update_speed();
        }
        return NULL;
    }

    void update_speed(){
        olc::vi2d res = speed;
        if(GetKey(olc::Key::LEFT).bHeld){
            res.y = 0;
            res.x = -1;
        }
        else if(GetKey(olc::Key::RIGHT).bHeld){
            res.y = 0;
            res.x = 1;
        }

        if(GetKey(olc::Key::UP).bHeld){
            res.x = 0;
            res.y = -1;
        }
        else if(GetKey(olc::Key::DOWN).bHeld){
            res.x = 0;
            res.y = 1;
        }
        if(SNAKE_HEAD.get_position() + res != snake_parts[1].get_position()){
            speed = res;
        }

    }

    void draw_screen(){
        Clear(SG_BG_COLOR);
        draw_snake();
        draw_food();
    }

    void draw_snake(){
        for(int i = 0; i < snake_parts.size(); i++){
            FillRect(snake_parts[i].get_position(), SNAKE_PART_SIZE, SNAKE_COLOR);
        }
    
    }

    void draw_food(){
        FillRect(food_location, SNAKE_PART_SIZE, SG_FOOD_COLOR);
    }

    void update_food_location(){
        bool found_valid_location = false;
        olc::vi2d res;
        while(!found_valid_location){
            res = get_rand_position();
            if(!snake_collides_with(res)){
                found_valid_location = true;
                food_location = res;
            }
        }
    }
};
#endif
