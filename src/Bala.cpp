#include "Bala.hpp"

Bala::Bala(int x, int y, Texture &texture, IntRect intRect, int v){   //Constructor
	sprite.setTexture(texture);
	sprite.setTextureRect(intRect);
	sprite.setPosition(x,y);
	sprite.setScale(3,3);
	vel=v;
}

void Bala::Update(){  //Metodo para mover la bala
	sprite.move(0,vel);
}

Vector2f Bala::Pos(){
	return sprite.getPosition();  //Metodo para obtener la posicion de la bala
}
	
void Bala::draw(RenderTarget &rt, RenderStates rs) const{  //Metodo para dibujar la bala
	rt.draw(sprite,rs);
}
