#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Jugador : public Drawable{
    private:
        Sprite sprite;
        int vida;
        int velocidad;
        bool disparar=false;
    public:
        Jugador(int x, int y, Texture & texture); /*Constructor de la clase Jugador(posicion del jugador y la textura)*/
        void Update();
        bool Disparar(); 
        Vector2f Pos();
        virtual void draw(RenderTarget &rt, RenderStates rs) const; /*Metodo que ayuda a dibujar a Jugador*/

};

Jugador::Jugador(int x, int y, Texture &texture){ /*Constructor de clase Jugador*/
    sprite.setTexture(texture); /*Asignacion de la textura*/
    sprite.setTextureRect(IntRect(13*8+8,7*8+7,16,8)); /*Asignacion de textura para enemigos*/
    sprite.setPosition(x,y); /*Escala de la textura*/
    sprite.setScale(3,3); /*La textura es equeña, por lo tanto se expande un 300% en x,y*/
    vida=100;
    velocidad=5;
}

void Jugador::Update(){
    if(Keyboard::isKeyPressed(Keyboard::Right)&&sprite.getPosition().x+velocidad<552){ /*Verifica si la tecla "derecha" esta presionada y limita*/
        sprite.move(velocidad,0);
    }
    if(Keyboard::isKeyPressed(Keyboard::Left)&&sprite.getPosition().x+velocidad*-1>0){ /*Verifica si la tecla "izquierda" esta presionada y limita*/
        sprite.move(velocidad*-1,0);
    }
}

bool Jugador::Disparar(){
    if(Keyboard::isKeyPressed(Keyboard::Space)&&!disparar){ /*Evalua para disparar*/
        disparar=true;    /*Evalua cuantas veces se presiona disparar*/
        return true;

    }else if(!Keyboard::isKeyPressed(Keyboard::Space)){
        disparar=false;
    }
    return false;
}

Vector2f Jugador::Pos(){
    return sprite.getPosition();
}

void Jugador::draw(RenderTarget &rt, RenderStates rs) const{ /*Se dibuja Jugador a traves del metodo draw*/
    rt.draw(sprite,rs); 
}
