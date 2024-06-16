#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Proyectil : public Drawable {
	private:
		Sprite sprite;
		int vel;
	public:
		Proyectil(int x, int y, Texture &texture, IntRect intRect, int v);
		void Update();
		Vector2f Pos();
		virtual void draw(RenderTarget &rt, RenderStates rs) const; 
};
