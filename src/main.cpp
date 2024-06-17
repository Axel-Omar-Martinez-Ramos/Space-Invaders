#include <iostream>
#include <SFML/Graphics.hpp>
#include "Jugador.hpp"
#include "Proyectil.hpp"
#include <vector>

using namespace std;
using namespace sf;

int main()
{
    Texture spritesheet; /*Se declara la textura*/

   if (!spritesheet.loadFromFile("space_invaders.png")) { /*Cargar la textura*/
       cout << "Error al cargar la textura \n";
   }

   Jugador jugador(288, 555, spritesheet); /*Posiciones del jugador*/

   bool disparar = false;                    /*Evalua si una bala es existente*/
   Proyectil ProyectilesJugador(0,0,spritesheet,IntRect(0,0,0,0),0);           /*Vector para proyectiles*/

   RenderWindow window(VideoMode(600, 600), "Space Invaders"); /*Creacion de ventana*/
   window.setFramerateLimit(60); /* Frames de la pantalla*/

   while (window.isOpen()) { /*Abrir la ventana*/

       Event event;
       while (window.pollEvent(event)) {
           if (event.type == Event::Closed) window.close(); /*Cerrar la ventana*/
       }

       jugador.Update(); /*Llama a la funcion Update*/

       if(jugador.Disparar()&&!disparar){
        Proyectil p(jugador.Pos().x+24,jugador.Pos().y-24,spritesheet,IntRect(13*8+16,6*8+6,8,8),-5); /*Evalua si el jugador dispara*/
        ProyectilesJugador = p;
        disparar=true;
       }

       if(disparar){
            ProyectilesJugador.Update();
            if(ProyectilesJugador.Pos().y<-24) disparar = false;

        }
        window.clear(); /*Limpiar la ventana*/
        window.draw(jugador); /*Dibujar a jugador*/
         if(disparar) window.draw(ProyectilesJugador);
        window.display(); /*Aparecer pantalla*/
      }
   return 0;
   }
