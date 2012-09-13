#include "../include/imageman.h"

imageman::imageman()
{
    //Load images and set them to sprites
    BackgroundImage.LoadFromFile("images/background.png");
    BackgroundImage2.LoadFromFile("images/background2.png");
    PlayerImage.LoadFromFile("images/knight_0.png");
    PlayerImage.CreateMaskFromColor(Color(255,0,255),0);
    Background.SetImage(BackgroundImage);
    Player.SetImage(PlayerImage);

    // Resize the background, so that it's much bigger than the window



}

imageman::~imageman()
{
    //dtor
}

void imageman::SetBackground2()
{

    Background2.SetImage(BackgroundImage2);
}
