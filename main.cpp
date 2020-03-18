#include "snake.hpp"
int main(int argc, char const *argv[])
{
    window frame{900,600,"snake"};
    int snake_count=5,movement_key,level=10,score=0;
    bool gamestatus=true;
    Body snake[500];                    ///intializing base snake
    createsnake(snake_count,snake);     
    Body food;                          ///intializing base food
    food.createfood();
    String speed{"LEVEL",750,0},points{"SCORE",540,0};
    while(frame.root.isOpen()) {
        sf::Event event;
        while(frame.root.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)   frame.root.close();
            if(event.type==sf::Event::KeyPressed) 
            {
                movement_key=checkkeypressed(event.key.code);
            }
        }
        if(abs(food.posx-snake[0].posx)<30 && abs(food.posy-snake[0].posy)<30)    
        {
            food.createfood();
            score+=1*(level-9);
            points.change(score);
            snake_count++;
            if(snake_count%5==0)    
            {
                level++;
                speed.change(level-9);
            }
            snake[snake_count-1].create(snake[snake_count-2].posx,snake[snake_count-2].posy);
        }
        if(gamestatus==false)
        {
            frame.root.clear(sf::Color::White);
            String over{"GAME OVER",200,220,72};
            frame.root.draw(over.text);
            frame.root.display();
            sf::sleep(sf::milliseconds(5000));
            frame.root.close();
        }
        if(movement_key==72){
            snakemove(&gamestatus,snake,snake_count,30,0);
        }
        else if(movement_key==71)
        {
            snakemove(&gamestatus,snake,snake_count,-30,0);
        }
        else if(movement_key==73)
        {
            snakemove(&gamestatus,snake,snake_count,0,-30);
        }
        else if(movement_key==74){
            snakemove(&gamestatus,snake,snake_count,0,30);   
        }
        ///Setting frames
        frame.root.clear();
        for(int i=0;i<snake_count;i++)
        {
            frame.root.draw(snake[i].snakebody);
        }
        frame.root.draw(food.snakebody);
        frame.root.draw(speed.text);
        frame.root.draw(points.text);
        frame.root.display();
        frame.root.setFramerateLimit(level);
    }
    return 0;
}