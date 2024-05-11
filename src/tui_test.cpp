#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <experimental/random>
#include <list>
#include <fstream>

using namespace std;
using namespace ftxui;

int main(int argc, char const *argv[])
{
    fstream imagen;
    list<string> textos;
    string linea;

    fstream imagen2;
    list<string> textos2;
    string linea2;

    imagen.open("./assets/imagen.txt");

    while (getline(imagen, linea))
    {
        textos.push_back(linea);
    }
    imagen.close();

    imagen2.open("./assets/imagen2.txt");

    while (getline(imagen2, linea2))
    {
        textos2.push_back(linea2);
    }
    imagen2.close();

    int posX = 1;
    int posY = 20 - 4; 
    int posY_Pr = 20- 5; 
    int posX_Pr = 2;

    int AnchoI = 140;
    int AltoI = 20;

    bool dir = 1;

    int fotograma = 0;
    string reset;

    while (true)
    {
        fotograma++;

        
        int R = 0;
        int G = 0;
        int B = 0;

        Element personaje = spinner(21, fotograma);
        Decorator colorFondo = bgcolor(Color::RGB(R, G, B));
        Decorator colorTexto = color(Color::RGB(B, G, R));
        Element dibujo = border({hbox() | colorFondo | colorTexto});

        // Crear dimensiones de pantalla
        Dimensions Alto = Dimension::Fixed(AltoI);
        Dimensions Ancho = Dimension::Fixed(AnchoI);

        // Crear pantalla
        Screen pantalla = Screen::Create(Ancho, Alto);

        // Imprimir en la pantalla
        Render(pantalla, dibujo);

        int l = 0;
        for (auto &&texto : textos)
        {
            int i = 0;
            for (auto &&letra : texto)
            {
                pantalla.PixelAt(posX + i, posY + l).character = letra;
                i++;
            }
            l++;
        }

        int x = 0;
        for (auto &&texto2 : textos2)
        {
            int y = 0;
            for (auto &&letra2 : texto2)
            {
                pantalla.PixelAt(posX_Pr + x, posY_Pr + y).character = letra2;
                x++;
            }
            y++;
        }

        

        if (dir == 1)
        {
            posX = posX + 2;
        }
        if (posX >= AnchoI - 8)
        {
            dir = 0;
        }
        if (dir == 0)
        {
            posX = posX - 3;
        }
        if (posX <= 1)
        {
            dir = 1;
        }

         posX_Pr = posX + 8;
        posY_Pr--;
        if (posY_Pr <= 0)
        {
            posY_Pr = 19 - 4;
        }

        pantalla.Print();

        reset = pantalla.ResetPosition();
        cout << reset;
        this_thread::sleep_for(0.1s);
    }

    return 0;
}