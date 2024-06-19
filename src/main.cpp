#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <Jugador.hpp>
#include <Bala.hpp>
#include <Enemigo.hpp>
#include <Muro.hpp>
#include <SFML/Audio.hpp>
#include <Menu.hpp>

using namespace std;
using namespace sf;

void UpdateJugador(Jugador &jugador, Bala &balaJugador, Sound &laserSound);  // Metodo para actualizar la accion jugador
void UpdateBalaJugador(Bala &balaJugador, vector<vector<Enemigo>> &enemigos);  // Metodo para actualizar la bala del jugador
void UpdateEnemigos(vector<vector<Enemigo>> &enemigos);  // Metodo para actualizar el movimiento de los enemigos
void UpdateBalasEnemigos(Jugador &jugador);  // Metodo para actualizar las balas enemigas
void UpdateMuro(vector<Muro> &muro, Bala &balaJugador);  // Metodo para actualizar los muros
void ShowGameOver(RenderWindow &window);

Texture spritesheet;

int timer = 0;
int cadencia = 200;  // Velocidad de los enemigos

int dirEnemigo = 1;  // Direccion de los enemigos
int maxX, minX;
int cantEnemigos;  // Cantidad de enemigos

vector<Bala> balasEnemigos; // Vector de balas enemigas

vector<pair<int, Vector2f>> posicionMuro;  // Posicion de los muros con ayuda del vector pair

Vector2f sectionSpritesheet;  // Posicion de enemigos en spritesheet

IntRect jugadorRect;
IntRect balaRect;
IntRect enemigoRect;
IntRect muroRect;

bool balaActiva = false; // Permite disparar una bala a la vez

void RunGame() {
    if (!spritesheet.loadFromFile("assets/images/space_invaders.png")) {
        cout << "Error al cargar la textura\n";
    }

    Jugador jugador(288, 555, spritesheet);   /*Posicion de jugador*/

    Bala balaJugador(0, 0, spritesheet, IntRect(0, 0, 0, 0), 0);

    vector<vector<Enemigo>> enemigos(7, vector<Enemigo>(12, Enemigo(0, 0, spritesheet, Vector2f(0, 0))));

    for (int i = 0; i < (int)enemigos.size(); i++) {
        for (int j = 0; j < (int)enemigos[i].size(); j++) {
            if (i == 0) {
                sectionSpritesheet = Vector2f(0, 0);  // Seleccion de personajes enemigos y animacion
            } else if (i < 3) {
                sectionSpritesheet = Vector2f(0, 9);
            } else if (i < 5) {
                sectionSpritesheet = Vector2f(0, 18);
            } else if (i < 7) {
                sectionSpritesheet = Vector2f(0, 27);
            }
            enemigos[i][j] = Enemigo(j * 30 + 24, i * 30 + 24, spritesheet, sectionSpritesheet);  // Posicion de enemigos en x, y
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

        UpdateJugador(jugador, balaJugador, laserSound);
        UpdateBalaJugador(balaJugador, enemigos);
        UpdateEnemigos(enemigos);
        UpdateBalasEnemigos(jugador);
        UpdateMuro(muro, balaJugador);

        if (!jugador.Vivo()) {
            window.close();
            ShowGameOver(window);
            return;
        }

        for (int i = 0; i < (int)enemigos.size(); i++) {  // Recorre la matriz de enemigos y detecta si alguno llega al final de la pantalla
            for (int j = 0; j < (int)enemigos[i].size(); j++) {
                if (enemigos[i][j].Pos().y >= 480) {
                    cout << "Perdiste\n";
                    window.close();
                    ShowGameOver(window);
                    return;
                }
            }
        }

        cantEnemigos = 0;

        for (int i = 0; i < (int)enemigos.size(); i++) cantEnemigos += (int)enemigos[i].size();  // Recorre la matriz de enemigos y cuenta cuantos enemigos hay

        if (cantEnemigos == 0) {
            cout << "Ganaste\n";
            window.close();
            return;
        }

        window.clear();

        for (int i = 0; i < (int)balasEnemigos.size(); i++) {
            window.draw(balasEnemigos[i]);
        }

        if (balaActiva) window.draw(balaJugador);

        for (int i = 0; i < (int)enemigos.size(); i++) {
            for (int j = 0; j < (int)enemigos[i].size(); j++) {
                window.draw(enemigos[i][j]);
            }
        }

        for (int i = 0; i < 3; i++) window.draw(muro[i]);

        window.draw(jugador);

        window.display(); /*Muestra la ventana*/
    }
}


void ShowGameOver(RenderWindow &window) {
    RenderWindow gameOverWindow(VideoMode(600, 600), "Game Over");

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

void UpdateJugador(Jugador &jugador, Bala &balaJugador, Sound &laserSound) { // Metodo para actualizar al jugador
    jugador.Update();

    if (jugador.Disparar() && !balaActiva) {  // Si se presiona la tecla espacio y no se esta disparando
        Bala bala(jugador.Pos().x + 24, jugador.Pos().y + 12, spritesheet, IntRect(13 * 8 + 16, 6 * 8 + 6, 8, 8), -10);  // Crear bala y asignarle velocidad
        balaJugador = bala;  // Asignar bala
        balaActiva = true;  // Activar bala
        laserSound.play();
    }
}

void UpdateBalaJugador(Bala &balaJugador, vector<vector<Enemigo>> &enemigos) { // Metodo para actualizar la bala del jugador
    if (balaActiva) {
        balaJugador.Update();
        if (balaJugador.Pos().y < -24) balaActiva = false;  // Imposibilitar disparar cuando la bala sale de la pantalla

        balaRect = IntRect(balaJugador.Pos().x, balaJugador.Pos().y, 3, 8);  // Rectangulo de la bala
        for (int i = 0; i < (int)enemigos.size(); i++) {  // Recorrer enemigos y detecta intersecciones de balas
            for (int j = 0; j < (int)enemigos[i].size(); j++) {
                enemigoRect = IntRect(enemigos[i][j].Pos().x, enemigos[i][j].Pos().y, 24, 24);
                if (enemigoRect.intersects(balaRect)) {  // Si la bala intersecciona con un enemigo
                    enemigos[i].erase(enemigos[i].begin() + j); // Elimina al enemigo que es interceptado
                    balaActiva = false;  // Desactivar bala cuando intersecta a un enemigo

                    break;
                }
            }
            if (!balaActiva) break;
        }
        if (!balaActiva) {
            for (int i = 0; i < (int)enemigos.size(); i++) {
                for (int j = 0; j < (int)enemigos[i].size(); j++) {
                    enemigos[i][j].AumentarCadencia();
                }
            }
            cadencia--;  // Aumentar la velocidad de los enemigos de 1 en 1
        }
    }
}

void UpdateEnemigos(vector<vector<Enemigo>> &enemigos) {
    maxX = 0;  // Posicion maxima en x
    minX = 600;  // Posicion minima en x
    for (int i = 0; i < (int)enemigos.size(); i++) {  // Recorrer enemigos y detecta intersecciones de balas
        for (int j = 0; j < (int)enemigos[i].size(); j++) {
            maxX = max(maxX, (int)enemigos[i][j].Pos().x + 24 * dirEnemigo);
            minX = min(minX, (int)enemigos[i][j].Pos().x + 24 * dirEnemigo);
        }
    }

    if (minX < 24 || maxX > 576) {  // Si los enemigos  salen de la pantalla
        for (int i = 0; i < (int)enemigos.size(); i++) {
            for (int j = 0; j < (int)enemigos[i].size(); j++) {
                enemigos[i][j].ChangeDir();
            }
        }
        dirEnemigo *= -1;
    }

    for (int i = 0; i < (int)enemigos.size(); i++) {
        for (int j = 0; j < (int)enemigos[i].size(); j++) {
            enemigos[i][j].Update();
        }
    }

    timer++;

    if (timer >= cadencia && (int)enemigos[0].size() > 0) { // Va aumentando la dificultad entre mas enemigos se eliminan
        timer = 0;
        srand(time(NULL));
        int enem = rand() % (int)enemigos[0].size();  // Asigna a un enemigo aleatorio para disparar
        Bala bala = Bala(enemigos[0][enem].Pos().x + 9, enemigos[0][enem].Pos().y + 24, spritesheet, IntRect(13 * 8 + 8, 8 * 2 + 2, 8, 8), 10);  // Crear bala enemiga y asignarle velocidad
        balasEnemigos.push_back(bala); // Agregar bala al vector de balas enemigas
    }
}

void UpdateBalasEnemigos(Jugador &jugador) {
    for (int i = 0; i < (int)balasEnemigos.size(); i++) {
        balasEnemigos[i].Update();
    }

    for (int i = 0; i < (int)balasEnemigos.size(); i++) {
        if (balasEnemigos[i].Pos().y > 600) {
            balasEnemigos.erase(balasEnemigos.begin() + i);
        }
    }

    jugadorRect = IntRect(jugador.Pos().x, jugador.Pos().y + 9, 48, 15);  // Posicion del jugador
    for (int i = 0; i < (int)balasEnemigos.size(); i++) {
        balaRect = IntRect(balasEnemigos[i].Pos().x, balasEnemigos[i].Pos().y, 3, 24);  // Posicion de la bala enemiga
        if (jugadorRect.intersects(balaRect)) {
            balasEnemigos.erase(balasEnemigos.begin() + i);
            jugador.QuitarVida();  // Quitar vida al jugador cuando la bala enemiga lo intersecta
        }
    }
}

void UpdateMuro(vector<Muro> &muro, Bala &balaJugador) {  // Metodo para recorrer los muros y detectar colisiones con las balas
    if (balaActiva) {
        balaRect = IntRect(balaJugador.Pos().x, balaJugador.Pos().y, 3, 8);  // Detectar la posicion de la bala del jugador
        for (int i = 0; i < 3; i++) {
            muro[i].Pos(posicionMuro);
            for (int j = 0; j < (int)posicionMuro.size(); j++) {
                muroRect = IntRect(posicionMuro[j].second.x, posicionMuro[j].second.y, 24, 24);  // Evaluar si la bala viene del jugador
                if (muroRect.intersects(balaRect)) {
                    muro[i].Colision(posicionMuro[j].first, false);  // Evalua si la bala del jugador intersecta con un muro
                    balaActiva = false;
                }
            }
            if (!balaActiva) break;
        }
    }

    bool elim = false;  // Eliminar bala enemiga

    for (int h = 0; h < (int)balasEnemigos.size(); h++) {  // Recorrer balas enemigas
        balaRect = IntRect(balasEnemigos[h].Pos().x, balasEnemigos[h].Pos().y, 3, 8);  // Evaluar si la bala viene del enemigo
        for (int i = 0; i < 3; i++) {
            muro[i].Pos(posicionMuro);
            for (int j = 0; j < (int)posicionMuro.size(); j++) {
                muroRect = IntRect(posicionMuro[j].second.x, posicionMuro[j].second.y, 24, 24);
                if (muroRect.intersects(balaRect)) {
                    muro[i].Colision(posicionMuro[j].first, true);
                    balasEnemigos.erase(balasEnemigos.begin() + h);
                    elim = true;
                    break;
                }
            }
            if (elim) break;
        }
    }

    for (int i = 0; i < 3; i++) muro[i].Update();
}
