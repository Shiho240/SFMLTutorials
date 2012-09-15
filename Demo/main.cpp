#include <SFML/Audio.hpp>
#include "include/imageman.h"
#include <iostream>
#include "collision.h"
using namespace sf;



int main()
{
RenderWindow Game(VideoMode(600,600), "Knight Zero");   //create window

imageman Imageman;    //init image manager and load images

    //Create a view
    View View(FloatRect(0,0,600,600));
    float view_max = 700;
    float view_min = 300;
    //Set some player image stuff
    Imageman.Player.SetCenter(100,150);
    Imageman.Player.SetPosition(100,600);
    Imageman.Player.SetSubRect(IntRect(0,0,75,100));
    Imageman.Player2.SetPosition(150,450);

    int level = 1;  //set lvl to first

    //load music
    Music Music1;
    Music1.OpenFromFile("sound/bach.ogg");
    Music1.SetLoop(true);
    Music1.Play();

    Collision Collision;
while(Game.IsOpened())
{
        Event Event;
        while (Game.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == Event::Closed)
                Game.Close();

            // Escape key : exit
            if ((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Escape))
                Game.Close();
        }

        float Offset = 200.f * Game.GetFrameTime(); //set offset
        Vector2f PlayerPos = Game.ConvertCoords(Imageman.Player.GetPosition().x, Imageman.Player.GetPosition().y);  //get player pos in vector

        //Move View
        if (Game.GetInput().IsKeyDown(Key::Left) && View.GetCenter().x > view_min && Imageman.Player.GetPosition().x < (view_max + 100) ) View.Move(-Offset,  0);
        if (Game.GetInput().IsKeyDown(Key::Right) && View.GetCenter().x < view_max && Imageman.Player.GetPosition().x > view_min) View.Move( Offset,  0);

        //Move Player
        if(Game.GetInput().IsKeyDown(Key::Left) && Imageman.Player.GetPosition().x > 100 && (Collision.PixelPerfectTest(Imageman.Player, Imageman.Background, 127) == false))
        {
            Imageman.Player.SetSubRect(IntRect(75,0,150,100));
            Imageman.Player.Move(-Offset, 0);
        }
        if (Game.GetInput().IsKeyDown(Key::Right) && Imageman.Player.GetPosition().x < (view_max + 200) && ((Collision.PixelPerfectTest(Imageman.Player, Imageman.Background, 127) == false) || Imageman.Player.GetPosition().y < 600))
        {
            Imageman.Player.Move(Offset, 0);
            Imageman.Player.SetSubRect(IntRect(0,0,75,100));
        }
        if (Game.GetInput().IsKeyDown(Key::Up) && Imageman.Player.GetPosition().y > 500) Imageman.Player.Move(0, -Offset);

        if (!Game.GetInput().IsKeyDown(Key::Up) && Imageman.Player.GetPosition().y < 600 && (Collision.PixelPerfectTest(Imageman.Player, Imageman.Background, 127) == false)) Imageman.Player.Move(0, Offset);

        //load new level
        if(Imageman.Player.GetPosition().x > 900 && level == 1)
        {
            View.SetCenter(300,300);
            view_max = 1700;
            Imageman.Player.SetPosition(100,600);
            Imageman.SetBackground2();
            Imageman.Background.Resize(1000,600);
            level = 2;
        }
        // Zoom and unzoom using + and - keys
        //if (Game.GetInput().IsKeyDown(Key::Add))      View.Zoom(1.001f);
        //if (Game.GetInput().IsKeyDown(Key::Subtract)) View.Zoom(0.999f);

        // Set the view
        Game.SetView(View);

        // Clear screen
        Game.Clear();

        // Draw background
        if(level == 1)
        Game.Draw(Imageman.Background);
        else
        Game.Draw(Imageman.Background2);
        // Draw cursor
       // Vector2f PlayerPos = Game.ConvertCoords(Game.GetInput().GetMouseX(), Game.GetInput().GetMouseY());
        //Imageman.Player.SetPosition(PlayerPos);
        Game.Draw(Imageman.Player);
        Game.Draw(Imageman.Player2);

        // Reset to the default view to draw the interface
        Game.SetView(Game.GetDefaultView());

        // Finally, display rendered frame on screen
        Game.Display();


}

return EXIT_SUCCESS;
}
