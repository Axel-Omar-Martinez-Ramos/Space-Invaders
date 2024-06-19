#include "Menu.hpp"

Menu::Menu(float width, float height){
    if(!font.loadFromFile("./assets/fonts/arial_narrow_7.ttf")){
    
    }


    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1)*1));

    menu[0].setOrigin(menu[0].getGlobalBounds().width/2, menu[0].getGlobalBounds().height/2);


    menu[1].setFont(font);
    menu[1].setString("Options");
    menu[1].setFillColor(sf::Color::Green);
    menu[1].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1)*2));

    menu[1].setOrigin(menu[1].getGlobalBounds().width/2, menu[1].getGlobalBounds().height/2);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Red);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1)*3));

    menu[2].setOrigin(menu[2].getGlobalBounds().width/2, menu[2].getGlobalBounds().height/2);

    selectedItemIndex = 0;

}

Menu::~Menu(){

}

void Menu::draw(sf::RenderWindow &window){
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        window.draw(menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}