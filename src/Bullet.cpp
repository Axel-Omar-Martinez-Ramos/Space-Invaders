#include "Bullet.hpp"

Bullet::Bullet(int x, int y, Texture &texture, IntRect intRect, int v){   //Constructor
	sprite.setTexture(texture);
	sprite.setTextureRect(intRect);
	sprite.setPosition(x,y);
	sprite.setScale(3,3);
	vel=v;
}

void Bullet::Update(){  //Metodo para mover la bala
	sprite.move(0,vel);
}

Vector2f Bullet::Pos(){
	return sprite.getPosition();  //Metodo para obtener la posicion de la bala
}
	
void Bullet::draw(RenderTarget &rt, RenderStates rs) const{  //Metodo para dibujar la bala
	rt.draw(sprite,rs);
}
