#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <Player.hpp>
#include <Bullet.hpp>
#include <Enemie.hpp>
#include <Muro.hpp>
#include <SFML/Audio.hpp>
#include <Menu.hpp>

using namespace std;
using namespace sf;

void UpdatePlayer(Player &player, Bullet &bulletPlayer, Sound &laserSound);  // Metodo para actualizar la accion jugador
void UpdateBulletPlayer(Bullet &bulletPlayer, vector<vector<Enemie>> &enemies);  // Metodo para actualizar la bala del jugador
void UpdateEnemies(vector<vector<Enemie>> &enemies);  // Metodo para actualizar el movimiento de los enemigos
void UpdateBulletsEnemies(Player &player);  // Metodo para actualizar las balas enemigas
void UpdateMuro(vector<Muro> &muro, Bullet &bulletPlayer);  // Metodo para actualizar los muros
void ShowGameOver(RenderWindow &window);

Texture spritesheet;

int timer = 0;
int cadencia = 200;  // Velocidad de los enemigos

int dirEnemies = 1;  // Direccion de los enemigos
int maxX, minX;
int cantEnemies;  // Cantidad de enemigos

vector<Bullet> bulletsEnemies; // Vector de balas enemigas

vector<pair<int, Vector2f>> posicionMuro;  // Posicion de los muros con ayuda del vector pair

Vector2f sectionSpritesheet;  // Posicion de enemigos en spritesheet

IntRect playerRect;
IntRect bulletRect;
IntRect enemieRect;
IntRect muroRect;

bool bulletActive = false; // Permite disparar una bala a la vez

void RunGame() {
    if (!spritesheet.loadFromFile("assets/images/space_invaders.png")) {
        cout << "Error al cargar la textura\n";
    }

    Player player(288, 555, spritesheet);   /*Posicion de jugador*/

    Bullet bulletPlayer(0, 0, spritesheet, IntRect(0, 0, 0, 0), 0);

    vector<vector<Enemie>> enemies(7, vector<Enemie>(12, Enemie(0, 0, spritesheet, Vector2f(0, 0))));

    for (int i = 0; i < (int)enemies.size(); i++) {
        for (int j = 0; j < (int)enemies[i].size(); j++) {
            if (i == 0) {
                sectionSpritesheet = Vector2f(0, 0);  // Seleccion de personajes enemigos y animacion
            } else if (i < 3) {
                sectionSpritesheet = Vector2f(0, 9);
            } else if (i < 5) {
                sectionSpritesheet = Vector2f(0, 18);
            } else if (i < 7) {
                sectionSpritesheet = Vector2f(0, 27);
            }
            enemies[i][j] = Enemie(j * 30 + 24, i * 30 + 24, spritesheet, sectionSpritesheet);  // Posicion de enemigos en x, y
        }
    }

    vector<Muro> muro(3, Muro(0, 0, spritesheet));

    for (int i = 0; i < 3; i++) {  // Posicion de los muros
        muro[i] = Muro(70 + 200 * i, 460, spritesheet);  // Separacion de los muros
    }

    RenderWindow window(VideoMode(600, 600), "Space Invaders"); /*Creacion de ventana*/
    window.setFramerateLimit(60);

    sf::Music music;
    if (!music.openFromFile("assets/music/Y2meta.app-Space-Invaders-Aliens-Moving-Sound-_128-kbps_.ogg")) {
        // Error al cargar el archivo de música
        return;
    }

    // Reproducir la música
    music.setLoop(true);
    music.play();

    sf::SoundBuffer laserBuffer;
    if (!laserBuffer.loadFromFile("assets/music/laser.ogg")) {
        // Error al cargar el archivo de sonido
        return;
    }

    sf::Sound laserSound;
    laserSound.setBuffer(laserBuffer);

    while (window.isOpen()) {    /*Bucle principal*/
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); /*Cierra la ventana*/
            }
        }

        UpdatePlayer(player, bulletPlayer, laserSound);
        UpdateBulletPlayer(bulletPlayer, enemies);
        UpdateEnemies(enemies);
        UpdateBulletsEnemies(player);
        UpdateMuro(muro, bulletPlayer);

        if (!player.Vivo()) {
            window.close();
            ShowGameOver(window);
            return;
        }

        for (int i = 0; i < (int)enemies.size(); i++) {  // Recorre la matriz de enemigos y detecta si alguno llega al final de la pantalla
            for (int j = 0; j < (int)enemies[i].size(); j++) {
                if (enemies[i][j].Pos().y >= 480) {
                    cout << "Perdiste\n";
                    window.close();
                    ShowGameOver(window);
                    return;
                }
            }
        }

        cantEnemies = 0;

        for (int i = 0; i < (int)enemies.size(); i++) cantEnemies += (int)enemies[i].size();  // Recorre la matriz de enemigos y cuenta cuantos enemigos hay

        if (cantEnemies == 0) {
            cout << "Ganaste\n";
            window.close();
            return;
        }

        window.clear();

        for (int i = 0; i < (int)bulletsEnemies.size(); i++) {
            window.draw(bulletsEnemies[i]);
        }

        if (bulletActive) window.draw(bulletPlayer);

        for (int i = 0; i < (int)enemies.size(); i++) {
            for (int j = 0; j < (int)enemies[i].size(); j++) {
                window.draw(enemies[i][j]);
            }
        }

        for (int i = 0; i < 3; i++) window.draw(muro[i]);

        window.draw(player);

        window.display(); /*Muestra la ventana*/
    }
}


void ShowGameOver(RenderWindow &window) {
    RenderWindow gameOverWindow(VideoMode(400, 200), "Game Over");

	Music music;
	music.stop();

    Font font;
    if (!font.loadFromFile("assets/fonts/arial_narrow_7.ttf")) {
        cout << "Error al cargar la fuente\n";
        return;
    }

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setPosition(100, 80);

    while (gameOverWindow.isOpen()) {
        Event event;
        while (gameOverWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                gameOverWindow.close();
            }
        }

        gameOverWindow.clear();
        gameOverWindow.draw(gameOverText);
        gameOverWindow.display();
    }
}

int main() {
    RenderWindow window(VideoMode(600, 600), "Space Invaders");
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {    /*Bucle principal del menu*/
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); /*Cierra la ventana*/
            }

            switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;

                        case sf::Keyboard::Down:
                            menu.MoveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem()) {
                                case 0:
                                    std::cout << "Comenzar" << std::endl;
                                    window.close(); 
                                    RunGame(); 
                                    break;
                                case 1:
                                    std::cout << "Actualiza el juego para acceder a las opciones" << std::endl;
                                    break;
                                case 2:
                                    window.close();
                                    break;
                            }
                            break;
                    }
                    break;
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}

void UpdatePlayer(Player &player, Bullet &bulletPlayer, Sound &laserSound) { // Metodo para actualizar al jugador
    player.Update();

    if (player.Shoot() && !bulletActive) {  // Si se presiona la tecla espacio y no se esta disparando
        Bullet bullet(player.Pos().x + 24, player.Pos().y + 12, spritesheet, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), -10);  // Crear bala y asignarle velocidad
        bulletPlayer = bullet;  // Asignar bala
        bulletActive = true;  // Activar bala
        laserSound.play();
    }
}

void UpdateBulletPlayer(Bullet &bulletPlayer, vector<vector<Enemie>> &enemies) { // Metodo para actualizar la bala del jugador
    if (bulletActive) {
        bulletPlayer.Update();
        if (bulletPlayer.Pos().y < -24) bulletActive = false;  // Imposibilitar disparar cuando la bala sale de la pantalla

        bulletRect = IntRect(bulletPlayer.Pos().x, bulletPlayer.Pos().y, 3, 8);  // Rectangulo de la bala
        for (int i = 0; i < (int)enemies.size(); i++) {  // Recorrer enemigos y detecta intersecciones de balas
            for (int j = 0; j < (int)enemies[i].size(); j++) {
                enemieRect = IntRect(enemies[i][j].Pos().x, enemies[i][j].Pos().y, 24, 24);
                if (enemieRect.intersects(bulletRect)) {  // Si la bala intersecciona con un enemigo
                    enemies[i].erase(enemies[i].begin() + j); // Elimina al enemigo que es interceptado
                    bulletActive = false;  // Desactivar bala cuando intersecta a un enemigo

                    break;
                }
            }
            if (!bulletActive) break;
        }
        if (!bulletActive) {
            for (int i = 0; i < (int)enemies.size(); i++) {
                for (int j = 0; j < (int)enemies[i].size(); j++) {
                    enemies[i][j].AumentarCadencia();
                }
            }
            cadencia--;  // Aumentar la velocidad de los enemigos de 1 en 1
        }
    }
}

void UpdateEnemies(vector<vector<Enemie>> &enemies) {
    maxX = 0;  // Posicion maxima en x
    minX = 600;  // Posicion minima en x
    for (int i = 0; i < (int)enemies.size(); i++) {  // Recorrer enemigos y detecta intersecciones de balas
        for (int j = 0; j < (int)enemies[i].size(); j++) {
            maxX = max(maxX, (int)enemies[i][j].Pos().x + 24 * dirEnemies);
            minX = min(minX, (int)enemies[i][j].Pos().x + 24 * dirEnemies);
        }
    }

    if (minX < 24 || maxX > 576) {  // Si los enemigos  salen de la pantalla
        for (int i = 0; i < (int)enemies.size(); i++) {
            for (int j = 0; j < (int)enemies[i].size(); j++) {
                enemies[i][j].ChangeDir();
            }
        }
        dirEnemies *= -1;
    }

    for (int i = 0; i < (int)enemies.size(); i++) {
        for (int j = 0; j < (int)enemies[i].size(); j++) {
            enemies[i][j].Update();
        }
    }

    timer++;

    if (timer >= cadencia && (int)enemies[0].size() > 0) { // Va aumentando la dificultad entre mas enemigos se eliminan
        timer = 0;
        srand(time(NULL));
        int enem = rand() % (int)enemies[0].size();  // Asigna a un enemigo aleatorio para disparar
        Bullet bullet = Bullet(enemies[0][enem].Pos().x + 9, enemies[0][enem].Pos().y + 24, spritesheet, IntRect(13 * 8 + 8, 8 * 2 + 2, 8, 8), 10);  // Crear bala enemiga y asignarle velocidad
        bulletsEnemies.push_back(bullet); // Agregar bala al vector de balas enemigas
    }
}

void UpdateBulletsEnemies(Player &player) {
    for (int i = 0; i < (int)bulletsEnemies.size(); i++) {
        bulletsEnemies[i].Update();
    }

    for (int i = 0; i < (int)bulletsEnemies.size(); i++) {
        if (bulletsEnemies[i].Pos().y > 600) {
            bulletsEnemies.erase(bulletsEnemies.begin() + i);
        }
    }

    playerRect = IntRect(player.Pos().x, player.Pos().y + 9, 48, 15);  // Posicion del jugador
    for (int i = 0; i < (int)bulletsEnemies.size(); i++) {
        bulletRect = IntRect(bulletsEnemies[i].Pos().x, bulletsEnemies[i].Pos().y, 3, 24);  // Posicion de la bala enemiga
        if (playerRect.intersects(bulletRect)) {
            bulletsEnemies.erase(bulletsEnemies.begin() + i);
            player.QuitarVida();  // Quitar vida al jugador cuando la bala enemiga lo intersecta
        }
    }
}

void UpdateMuro(vector<Muro> &muro, Bullet &bulletPlayer) {  // Metodo para recorrer los muros y detectar colisiones con las balas
    if (bulletActive) {
        bulletRect = IntRect(bulletPlayer.Pos().x, bulletPlayer.Pos().y, 3, 8);  // Detectar la posicion de la bala del jugador
        for (int i = 0; i < 3; i++) {
            muro[i].Pos(posicionMuro);
            for (int j = 0; j < (int)posicionMuro.size(); j++) {
                muroRect = IntRect(posicionMuro[j].second.x, posicionMuro[j].second.y, 24, 24);  // Evaluar si la bala viene del jugador
                if (muroRect.intersects(bulletRect)) {
                    muro[i].Colision(posicionMuro[j].first, false);  // Evalua si la bala del jugador intersecta con un muro
                    bulletActive = false;
                }
            }
            if (!bulletActive) break;
        }
    }

    bool elim = false;  // Eliminar bala enemiga

    for (int h = 0; h < (int)bulletsEnemies.size(); h++) {  // Recorrer balas enemigas
        bulletRect = IntRect(bulletsEnemies[h].Pos().x, bulletsEnemies[h].Pos().y, 3, 8);  // Evaluar si la bala viene del enemigo
        for (int i = 0; i < 3; i++) {
            muro[i].Pos(posicionMuro);
            for (int j = 0; j < (int)posicionMuro.size(); j++) {
                muroRect = IntRect(posicionMuro[j].second.x, posicionMuro[j].second.y, 24, 24);
                if (muroRect.intersects(bulletRect)) {
                    muro[i].Colision(posicionMuro[j].first, true);
                    bulletsEnemies.erase(bulletsEnemies.begin() + h);
                    elim = true;
                    break;
                }
            }
            if (elim) break;
        }
    }

    for (int i = 0; i < 3; i++) muro[i].Update();
}
