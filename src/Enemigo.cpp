#include "Enemigo.hpp"

Enemigo::Enemigo(int x, int y, Texture &texture, Vector2f p){
	point = p;
	sprite.setTexture(texture);  //Se le asigna la textura al sprite de enemigo
	sprite.setTextureRect(IntRect(point.x,point.y,8,8));  //Se le asigna la posicion de la textura de enemigo y se asignan los puntos de posision
	sprite.setPosition(x,y);
	sprite.setScale(3,3);
	state=0;  //Estado de animacion del enemigo
	timer=0;  
	vel=24;
	cadencia=150;
}

void Enemigo::Update(){
	if(timer>=cadencia){
		sprite.move(vel,0);
		state++;
		state%=2;  //Cambio de animacion del enemigo
		sprite.setTextureRect(IntRect(point.x+state*9,point.y,8,8));  //Se van moviendo los enemigo y cambian sus animaciones
		timer=0;
	}
	timer++;  //Se aumenta el tiempo para que cambie de animacion
}

void Enemigo::ChangeDir(){
	vel*=-1;  //Cambio de direccion de los enemigos
	sprite.move(0,abs(vel));
}

Vector2f Enemigo::Pos(){
	return sprite.getPosition();  //Se obtiene la posicion de los enemigos
}

void Enemigo::AumentarCadencia(){
	cadencia--;
}

void Enemigo::draw(RenderTarget &rt, RenderStates rs) const{
	rt.draw(sprite,rs);
}
