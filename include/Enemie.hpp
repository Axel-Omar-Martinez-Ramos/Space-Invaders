#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Enemie : public Drawable{
	private:
		Sprite sprite;
		int vel;
		int state;
		int cadencia;
		int timer;
		Vector2f point; //Punto de inicio de los enemigos
	public:
		Enemie(int x, int y, Texture &texture, Vector2f p);
		void Update();
		void ChangeDir();  //Metodo para cambiar la direccion de los enemigos
		Vector2f Pos();  //Metodo para obtener la posicion de los enemigos
		void AumentarCadencia();  //Metodo para aumentar la velocidad de los enemigos
		virtual void draw(RenderTarget &rt, RenderStates rs) const;  //Metodo para dibujar enemigo
};
