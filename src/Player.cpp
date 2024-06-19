#include "Player.hpp"
#include <iostream>

Player::Player(int x, int y, sf::Texture &texture) {
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
    vidaText.setPosition(600.f, 600.f); // Posición del texto de vida inicial
    UpdateVida(); // Actualizar el texto de vida inicial
}

void Player::Update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x + vel < 552) {
        sprite.move(vel, 0); // Mover a la derecha
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x + vel * -1 > 0) {
        sprite.move(vel * -1, 0); // Mover a la izquierda
    }
}

bool Player::Shoot() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !shoot) {
        shoot = true; // Dispara
        return true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot = false;
    }
    return false;
}

sf::Vector2f Player::Pos() {
    return sprite.getPosition();
}

void Player::QuitarVida() {
    vida--;
    UpdateVida(); // Actualizar el texto de vida después de quitar vida
}

bool Player::Vivo() {
    return (vida != 0);
}

void Player::draw(sf::RenderTarget &rt, sf::RenderStates rs) const {
    rt.draw(sprite, rs);    // Dibujar el sprite del jugador
    rt.draw(vidaText, rs);  // Dibujar el texto de vida
}

void Player::UpdateVida() {
    vidaText.setString("Vida: " + std::to_string(vida)); // Actualizar el texto de vida con el valor actual de vida
}
