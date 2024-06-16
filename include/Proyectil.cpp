#include "Proyectil.hpp"

Proyectil::Proyectil(int x, int y, Texture &texture, IntRect intRect, int v){
	sprite.setTexture(texture);
	sprite.setTextureRect(intRect);
	sprite.setPosition(x,y);
	sprite.setScale(3,3);
	vel=v;
}

void Proyectil::Update(){
	sprite.move(0,vel);
}

Vector2f Proyectil::Pos(){
	return sprite.getPosition();
}
	
void Proyectil::draw(RenderTarget &rt, RenderStates rs) const{
	rt.draw(sprite,rs);
}
