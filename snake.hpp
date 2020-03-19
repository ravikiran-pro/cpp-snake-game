#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
class window 
{
public:
    sf::RenderWindow root;
    int frame_width;
    int frame_height;
    window()
    {

    }
    window(int width,int height,std::string title)
    {
        this->frame_width=width;
        this->frame_height=height;
        sf::VideoMode video(frame_width,frame_height);
        this->root.create(video,title);        
    }
};
class String
{
public:
    sf::Font font;
    sf::Text text;
    std::string content;
    String(std::string content,int x,int y,int size=28)
    {
        this->content=content;
        if(!font.loadFromFile("stocky.ttf")){}
            text.setFont(font);
            text.setString(content+":");
            text.setCharacterSize(size);
            text.setFillColor(sf::Color::Green);
            text.setPosition(x,y);
    }
    void change(int val)
    {
        std::string curr=std::to_string(val);
        text.setString(this->content+": "+curr);
    }
};
class Body
{
public:
        sf::RectangleShape snakebody;       
        float posx;
        float posy;
        void create(float x,float y){
            this->posx=x;
            this->posy=y;
            snakebody.setSize(sf::Vector2f(30.f,30.f));
            snakebody.setFillColor(sf::Color::White);
            snakebody.setOutlineThickness(4.f);
            snakebody.setOutlineColor(sf::Color(250, 150, 100));
            snakebody.setPosition(this->posx,this->posy);
        }
        void createfood()
        {
            srand (time(NULL));
            this->posx=rand()%29*30;
            this->posy=rand()%19*30;
            snakebody.setSize(sf::Vector2f(30.f,30.f));
            snakebody.setFillColor(sf::Color::Red);
            snakebody.setOutlineThickness(4.f);
            snakebody.setOutlineColor(sf::Color(250, 150, 100));
            snakebody.setPosition(this->posx,this->posy);
        }
};
int checkkeypressed(int key)
{
    if(key==72)  return 72;
    if(key==71)  return 71;
    if(key==73)  return 73;
    if(key==74)  return 74;
}
void createsnake(int snake_count,Body *snake)
{
    float x=500.f,y=0.f;
    for(int i=0;i<snake_count;i++)
    {
        snake[i].create(x,y);
        x-=30.f;
    }
}
bool gameover(Body *snake,int snake_count)
{
    int move_x=snake[0].posx;
    int move_y=snake[0].posy;
    for(int i=snake_count-1;i>0;i--)
    {
        if(move_x==snake[i].posx && move_y==snake[i].posy)   return false;
    }
    return true;
}
void snakemove(bool *gamestatus,Body *snake,int snake_count,int x_turn,int y_turn)
{   
        if(snake[0].posx>900)   snake[0].posx=0;
        if(snake[0].posx<0)   snake[0].posx=900;
        if(snake[0].posy>600)   snake[0].posy=0;
        if(snake[0].posy<0)   snake[0].posy=600;
        for(int i=snake_count-1;i>0;i--)
        {
            snake[i].posx=snake[i-1].posx;
            snake[i].posy=snake[i-1].posy;
        }
        snake[0].posx+=x_turn;
        snake[0].posy+=y_turn;
        bool alive=gameover(snake,snake_count);
        if(alive==false)    
        {
            *gamestatus=false;
        }
           for(int i=0;i<snake_count;i++)
            {
                snake[i].snakebody.setPosition(snake[i].posx,snake[i].posy);
            }
}
   