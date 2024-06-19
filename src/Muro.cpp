#include "Muro.hpp"

Muro::Muro(int x, int y, Texture &texture){  //Constructor de Muro
	sprites.resize(5);  //Se crea un vector de 5 sprites
	state.resize(5,{0,0});  //Se crea el tamaño del vector y se asigna la posicion del vector Muro
	for(int i = 0; i < 5; i++){
		sprites[i].setTexture(texture);  //Se le asigna la textura a los sprites
		sprites[i].setTextureRect(IntRect(16*8+9+state[i].first*9,14*8+14+state[i].second*9,8,8));  //Se le asigna la posicion de la textura de los muros
		sprites[i].setScale(3,3);
	}
	sprites[0].setPosition(x,y);  //Se le asigna la posicion de los muros
	sprites[1].setPosition(x+24,y);
	sprites[2].setPosition(x+48,y);
	sprites[3].setPosition(x,y+24);
	sprites[4].setPosition(x+48,y+24);
}

void Muro::Update(){  //Metodo para actualizar los muros
	for(int i = 0; i < 5; i++){
		sprites[i].setTextureRect(IntRect(16*8+9+state[i].first*9,14*8+14+state[i].second*9,8,8)); //Se le asigna la posicion de la textura de los muros
	}
}

void Muro::Pos(vector<pair<int,Vector2f>> &pos){  //Metodo para obtener la posicion de los muros que siguen activos
	pos.clear();
	for(int i = 0; i < 5; i++){  //Si el vector de los muros es igual a 5, esta eliminado
		if(state[i].first+state[i].second<5){
			pos.push_back({i,sprites[i].getPosition()});
		}
	}	
}

void Muro::Colision(int indice, bool up){  //Metodo para determinar que cuadro se ve afectado y cambiar su estado
	if(up) state[indice].first++;
	else state[indice].second++;
}

void Muro::draw(RenderTarget &rt, RenderStates rs) const{  //Metodo para dibujar los muros
	for(int i = 0; i < 5; i++){
		if(state[i].first+state[i].second<5){
			rt.draw(sprites[i], rs);
		}
	}
}
