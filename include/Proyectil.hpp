#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Proyectil : public Drawable{
    private: 
        Sprite sprite;
        int vel;
    public:
        Proyectil(int x, int y, Texture &texture, IntRect IntRect, int velocidad_bala); /*Constaructor del proyectil*/
        void Update();
        Vector2f Pos();
        virtual void draw(RenderTarget &rt, RenderStates rs) const; /*Indica como dibujar la clase Proyectil*/
};

Proyectil::Proyectil(int x, int y, Texture &texture, IntRect IntRect, int v){
    sprite.setTexture(texture); /*Asignacion de la textura*/
    sprite.setTextureRect(IntRect); /*Asignacion de textura para proyectil*/
    sprite.setPosition(x,y); /*Escala de la textura*/
    sprite.setScale(3,3); /*La textura es equeña, por lo tanto se expande un 300% en x,y*/
    vel=v;

}

void Proyectil::Update(){
    sprite.move(0,vel); /*Se delimita la bala a que solo se mueva en el eje y*/
}

void Proyectil::draw(RenderTarget &rt, RenderStates rs) const{
    rt.draw(sprite,rs);

}
Vector2f Proyectil::Pos(){
    return sprite.getPosition();
}
