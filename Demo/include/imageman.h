#ifndef IMAGEMAN_H
#define IMAGEMAN_H
#include <SFML/Graphics.hpp>
using namespace sf;

class imageman
{
    public:
        imageman();
        virtual ~imageman();
        Image BackgroundImage, BackgroundImage2;
        Image PlayerImage;
        Sprite Player;
        Sprite Player2;
        Sprite Background;
        Sprite Background2;
        void SetBackground2();
    protected:
    private:
};

#endif // IMAGEMAN_H
