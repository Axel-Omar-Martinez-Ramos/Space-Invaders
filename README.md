## SPACE INVADERS

![image](/assets/images/captura_juego.png)


#### El objetivo de éste proyecto es desarrollar un juego arcade basado en "Space Invaders" utilizando imagenes de un Spritesheet. Asi como tambien ofrecer al usuario una dinámica simple de juego y entretenida, en la cuál el usuario actua como una nave espacial que dispara misiles contra otras con la escencia del juego retro "Space Enviders (1978).
- El jugador controla un cañón que puede moverse a la derecha o izquierda y un botón de disparo

- Su objetivo es destruir filas de extraterrestres invasores (de los cuales hay tres tipos: con forma de calamar, de cangrejo y de pulpo) que van acercándose a la Tierra cada vez más rápidamente a medida que el jugador va destruyendo a los enemigos.

- Este ciclo se puede repetir en forma indefinida. Si los invasores llegan al cañón controlado por el jugador, el juego termina.


### ESTRUCTURA

El proyecto esta desarrollado sobre MinGW64 utilizando Msys2
y como editor se esta utilizando Visual Studio Code.

Éste proyecto está organizado en diferentes carpetas, lo cual permite que el desarrollo de éste sea mas organizado. Entre las carpetas de desarrollo de encuentran:
<li>
  Readme.md: Es un archivo de tipo markdown en el cual esta la descripcion de los datos generales del proyecto.
</li>
<li>
  Src/: Contiene los archivos principales del proyecto, incluyendo el archivo "main.cpp"
</li>
<li>
  Include/: Contiene los archivos en los cuales se encuentran las clases del juego y estructuras para el proyecto.
</li>
<li>
  Assets: Contiene recursos graficos, de audio y de fuente para el juego.
</li>
<li>
  Docs/: Contiene archivos base del proyecto, como por ejemplo el diagrama de clases UML, etc.
</li>
<li>
  Bin/: Contiene el archivo.exe ejecutable.
</li>

### PROGRAMAS NECESARIOS:

### Visual estudio code
<li>
Descargar e instalar vscode en el siguiente [Enlace.](https://code.visualstudio.com/)
</li

### MSYS2 (Windows)
<li>

Instalar Msys2 usando el siguiente [Enlace.](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe)
</li>
Agregar los siguientes directorios al Path de Windows y reiniciar:

> C:\msys64\mingw64\bin

> C:\msys64\usr\bin

### Github Desktop
<li>
Cliente de escritorio para clonar el repositorio, descargar usando el siguiente [enlace](https://desktop.github.com/).
</li>

### Git
<li>
Para poder realizar commits de vscode es necesario tener instalado Git, descargarlo del siguiente [enlace](https://git-scm.com/).
</li>

###INSTALAR LAS SIGUIENTES LIBRERIAS EN LA TERMINAL DE MSYS2:

<li>

https://code.visualstudio.com/docs/cpp/config-mingw

> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

</li>
<li>

https://packages.msys2.org/package/mingw-w64-x86_64-sfml

> pacman -S mingw-w64-x86_64-sfml
</li>
<li>

https://box2d.org/documentation/

https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64

> pacman -S mingw-w64-x86_64-box2d

</li>

### COMPLEMENTOS:

<li>
  Material Icon Theme.
</li>
<li>
  C/C++ EXTENSION PACK
</li>
<li>
  Plant UML
</li>
<li>
  Cmake Tools
</li>
<li>
GitGraph
</li>

### PARA EJECUTAR EL PROGRAMA ESCRIBA:

> make runmain

### VIDEO DEMOSTRATIVO DEL JUEGO:

https://youtu.be/fuSjoDq3nCk

