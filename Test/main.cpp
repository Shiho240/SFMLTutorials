
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML Views");

// Load a sound buffer from a wav file
    sf::SoundBuffer Buffer;
    if (!Buffer.LoadFromFile("sound.wav"))
        return EXIT_FAILURE;

// Load the sprite image from a file
    sf::Image Image;
    if (!Image.LoadFromFile("sprite.png"))
        return EXIT_FAILURE;

    // Create the sprite
    sf::Sprite Sprite(Image);

    // Change its properties
    //Sprite.SetColor(sf::Color(0, 255, 255, 128));
    Sprite.SetPosition(200.f, 100.f);
    //Sprite.SetScale(2.f, 2.f);
    // Create a sprite for the background
    sf::Image BackgroundImage;
    if (!BackgroundImage.LoadFromFile("background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite Background(BackgroundImage);

    // Create another sprite for the cursor
    sf::Image CursorImage;
    if (!CursorImage.LoadFromFile("cursor.tga"))
        return EXIT_FAILURE;
    sf::Sprite Cursor(CursorImage);

    // Resize the background, so that it's much bigger than the window
    Background.Resize(2000, 2000);

    // Define a text for displaying some instructions
    sf::String Text("Use the arrow keys to move the camera\nUse the + and - keys to zoom and unzoom");
    Text.Move(10, 500);
    Text.SetColor(sf::Color::White);

    // Create a view with the same size as the window, located somewhere in the center of the background
    sf::Vector2f Center(1000, 1000);
    sf::Vector2f HalfSize(400, 300);
    sf::View View(Center, HalfSize);

    // To start, put the cursor at the center
    Cursor.SetCenter(32, 32);
    Cursor.SetPosition(Center);

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                App.Close();
        }
    sf::Sound Sound(Buffer);
           // Get elapsed time
        float ElapsedTime = App.GetFrameTime();
// Move the sprite
        if (App.GetInput().IsKeyDown(sf::Key::Left))  Sprite.Move(-50 * ElapsedTime, 0);
        if (App.GetInput().IsKeyDown(sf::Key::Right)) Sprite.Move( 50 * ElapsedTime, 0);
        if (App.GetInput().IsKeyDown(sf::Key::Up))    Sprite.Move(0, -50 * ElapsedTime);
        if (App.GetInput().IsKeyDown(sf::Key::Down))  Sprite.Move(0,  50 * ElapsedTime);

        // Rotate the sprite
        if (App.GetInput().IsKeyDown(sf::Key::Add))      Sprite.Rotate(- 100 * ElapsedTime);
        if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Sprite.Rotate(+ 100 * ElapsedTime);


        // Create a sound instance and play it
        if (App.GetInput().IsKeyDown(sf::Key::Space)) Sound.Play();

        // Move the view using arrow keys
        float Offset = 200.f * App.GetFrameTime();
        if (App.GetInput().IsKeyDown(sf::Key::Up))    View.Move( 0,      -Offset);
        if (App.GetInput().IsKeyDown(sf::Key::Down))  View.Move( 0,       Offset);
        if (App.GetInput().IsKeyDown(sf::Key::Left))  View.Move(-Offset,  0);
        if (App.GetInput().IsKeyDown(sf::Key::Right)) View.Move( Offset,  0);

        // Zoom and unzoom using + and - keys
       // if (App.GetInput().IsKeyDown(sf::Key::Add))      View.Zoom(1.001f);
       // if (App.GetInput().IsKeyDown(sf::Key::Subtract)) View.Zoom(0.999f);

        // Set the view
        App.SetView(View);

        // Clear screen
        App.Clear();

        // Draw background
        App.Draw(Background);

        // Draw cursor
       // sf::Vector2f CursorPos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());
       // Cursor.SetPosition(CursorPos);
       // App.Draw(Cursor);

        // Reset to the default view to draw the interface
        App.SetView(App.GetDefaultView());

        // Draw some instructions
        App.Draw(Text);

        // Display sprite in our window
        App.Draw(Sprite);


        // Finally, display rendered frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}
