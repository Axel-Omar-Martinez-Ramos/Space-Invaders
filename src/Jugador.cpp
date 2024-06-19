#include "Jugador.hpp"
#include <iostream>

Jugador::Jugador(int x, int y, sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(13 * 8 + 8, 7 * 8 + 7, 16, 8)); // Posición de comienzo y tamaño
    sprite.setPosition(x, y); // Posición inicial
    sprite.setScale(3, 3); // Escala
    vida = 3;
    vel = 5;

    // Cargar la fuente
    if (!font.loadFromFile("assets/fonts/arial_narrow_7.ttf")) {
        std::cerr << "Error al cargar la fuente\n";
    }

    // Configurar el texto de vida
    vidaText.setFont(font);
    vidaText.setCharacterSize(20);
    vidaText.setFillColor(sf::Color::White);
    vidaText.setPosition(10.f, 10.f); // Posición del texto de vida inicial
    UpdateVida(); // Actualizar el texto de vida inicial
}

void Jugador::Update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x + vel < 552) {
        sprite.move(vel, 0); // Mover a la derecha
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x + vel * -1 > 0) {
        sprite.move(vel * -1, 0); // Mover a la izquierda
    }
}

bool Jugador::Disparar() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !disparar) {
        disparar = true; // Dispara
        return true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        disparar = false;
    }
    return false;
}

sf::Vector2f Jugador::Pos() {
    return sprite.getPosition();
}

void Jugador::QuitarVida() {
    vida--;
    UpdateVida(); // Actualizar el texto de vida después de quitar vida
}

bool Jugador::Vivo() {
    return (vida != 0);
}

void Jugador::draw(sf::RenderTarget &rt, sf::RenderStates rs) const {
    rt.draw(sprite, rs);    // Dibujar el sprite del jugador
    rt.draw(vidaText, rs);  // Dibujar el texto de vida
}

void Jugador::UpdateVida() {
    vidaText.setString("Vida: " + std::to_string(vida)); // Actualizar el texto de vida con el valor actual de vida
}
