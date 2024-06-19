#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Bala : public Drawable {
	private:
		Sprite sprite;
		int vel;
	public:
		Bala(int x, int y, Texture &texture, IntRect intRect, int v);  //Constructor
		void Update();  //Metodo para mover la bala
		Vector2f Pos();  //Metodo para obtener la posicion de la bala
		virtual void draw(RenderTarget &rt, RenderStates rs) const;
};
