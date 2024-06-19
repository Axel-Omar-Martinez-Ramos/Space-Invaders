#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Jugador : public sf::Drawable {
private:
    sf::Sprite sprite;
    int vida;
    int vel;
    bool disparar = false;  // La bala comienza en falso porque no se está presionando
    sf::Text vidaText;   // Texto para mostrar la vida
    sf::Font font;       // Fuente para el texto

public:
    Jugador(int x, int y, sf::Texture &texture); // Constructor
    void Update();        // Método para saber si se presionó una tecla
    bool Disparar();         // Método para saber si se dispara
    void QuitarVida();    // Método para quitar vida
    bool Vivo();          // Método para saber si está vivo
    sf::Vector2f Pos();   // Método para obtener la posición
    virtual void draw(sf::RenderTarget &rt, sf::RenderStates rs) const override; // Método para dibujar
    void UpdateVida();    // Actualizar el texto de vida
};

#endif // PLAYER_HPP

