#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Number {
private:
    Texture t_minus ;
    Texture t_0 ;
    Texture t_1 ;
    Texture t_2 ;
    Texture t_3 ;
    Texture t_4 ;
    Texture t_5 ;
    Texture t_6 ;
    Texture t_7 ;
    Texture t_8 ;
    Texture t_9 ;
public:
    int number ;
    Sprite s_minus ;
    Sprite s_0 ;
    Sprite s_1 ;
    Sprite s_2 ;
    Sprite s_3 ;
    Sprite s_4 ;
    Sprite s_5 ;
    Sprite s_6 ;
    Sprite s_7 ;
    Sprite s_8 ;
    Sprite s_9 ;
    Number(int x, int y) ;
    Sprite getDigit() ;
};
