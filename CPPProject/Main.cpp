#include "Game.hpp"



int main() {
    
    sf::Font font;
    font.loadFromFile("Lato-Regular.ttf");
    sf::Color fillColor = sf::Color(71, 82, 94, 255);

    Game game(font, fillColor);

    return 0;
}