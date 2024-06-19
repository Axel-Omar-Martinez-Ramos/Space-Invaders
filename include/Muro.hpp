#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Muro : public Drawable{
	private:
		vector<Sprite> sprites;  //Vector de posicion de los muros
		vector<pair<int,int>> state;  //Estado de los muros
	public:
		Muro(int x, int y, Texture &texture);
		void Pos(vector<pair<int,Vector2f>> &pos);  //Metodo para obtener la posicion de los muros que siguen activos
		void Update();
		void Colision(int indice, bool up);
		virtual void draw(RenderTarget &rt, RenderStates rs) const;  //Metodo para dibujar los muros
};
