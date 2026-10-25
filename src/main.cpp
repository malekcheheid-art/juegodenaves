/*
==================================================================================
    Materia: Laboratorio de Programacion (LPR) - 5to Ano
    Institucion: E.E.S.T. N. 1 "Eduardo Ader" - Vicente Lopez
    Archivo: src/main.cpp
    Actividad 8: Introduccion a POO - Motor de Juego de Naves
                (Clases, Objetos, Encapsulamiento y Constructores)
    Docente: Mansilla Munoz York Elias
    Estudiante: [COMPLETAR APELLIDO Y NOMBRE]

    Descripcion:
        Simulador de combate espacial en consola. El jugador maneja una nave
        que se desplaza por la pantalla, dispara proyectiles y pierde vidas
        cuando es alcanzada por los asteroides que descienden desde arriba.

    Controles:
        W / A / S / D  Mover la nave
        ESPACIO         Disparar

    Compilacion (MinGW):
        g++ src/main.cpp -o juego_naves.exe
==================================================================================
*/

#include <iostream>   // Flujos de entrada y salida (cout, cin)
#include <windows.h>   // API de Windows: consola, Sleep, GetStdHandle
#include <conio.h>     // Entrada de teclado sin eco: _kbhit, _getch
#include <vector>      // Contenedor dinamico std::vector
#include <ctime>       // time() para la semilla del generador de numeros aleatorios
#include <cctype>      // tolower()

using namespace std;

/*
----------------------------------------------------------------------------------
    Funcion auxiliar: gotoxy
----------------------------------------------------------------------------------
    Coloca el cursor de la consola en la coordenada (x, y), donde el origen
    (0, 0) es la esquina superior izquierda. Se declara antes de las clases
    porque el cuerpo de los metodos pintar() y borrar() la invoca.

    Internamente se obtiene el handle de la salida estandar, se arma una
    estructura COORD con las coordenadas y se la pasa a SetConsoleCursorPosition.
----------------------------------------------------------------------------------
*/
void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

/*
----------------------------------------------------------------------------------
    Funcion auxiliar: ocultarCursor
----------------------------------------------------------------------------------
    Oculta el cursor de la consola para que el titilando no alterne con el
    dibujo del juego. SetConsoleCursorInfo recibe un puntero a la estructura
    CONSOLE_CURSOR_INFO, de ahi el uso del operador & (pasaje por referencia).
----------------------------------------------------------------------------------
*/
void ocultarCursor() {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

/*
==================================================================================
    CLASE NAVE (el jugador)
==================================================================================

    private:  los datos internos (x, y, vidas) quedan ocultos. Desde main() no se
              puede escribir directamente jugador.x = 99; solo se acceden a ellos
              mediante los metodos publicos. Eso es el encapsulamiento.

    public:   las acciones y los accesores. Son la unica "puerta controlada" que
              tiene el resto del programa para interactuar con el objeto.
==================================================================================
*/
class Nave {
private:
    int x, y;     // Coordenadas de la nave en la consola
    int vidas;    // Cantidad de vidas restantes

public:
    /*
    ------------------------------------------------------------------------------
        CONSTRUCTOR: Nave(int _x, int _y, int _vidas)

        Es el metodo que se ejecuta al crear el objeto, por ejemplo:
            Nave jugador(35, 20, 3);

        Su trabajo es inicializar los atributos privados con los valores recibidos
        por parametro. El prefijo guion bajo (_x) se usa para distinguir los
        parametros de los atributos de la clase, ya que ambos se llaman igual.
        Sin este bloque, x, y y vidas quedarian con valores indeterminados.
    ------------------------------------------------------------------------------
    */
    Nave(int _x, int _y, int _vidas) {
        x = _x;
        y = _y;
        vidas = _vidas;
    }

    // Accesores: devuelven el valor de un atributo privado (solo lectura)
    int getX() { return x; }
    int getY() { return y; }
    int getVidas() { return vidas; }

    // Metodo de comportamiento: descuenta una vida
    void reducirVida() { vidas--; }

    /*
    ------------------------------------------------------------------------------
        Dibuja la nave en tres lineas: la punta superior, el cuerpo y la base.
        Cada gotoxy() reposiciona el cursor y el cout escribe el fragmento.
    ------------------------------------------------------------------------------
    */
    void pintar() {
        gotoxy(x, y);     cout << "  ^  ";
        gotoxy(x, y + 1); cout << " (O) ";
        gotoxy(x, y + 2); cout << "^^^^ ";
    }

    /*
    ------------------------------------------------------------------------------
        Borra la nave escribiendo espacios en las mismas posiciones donde la
        dibuja pintar(). Es indispensable antes de moverla para no dejar
        "estelas" de caracteres en la consola.
    ------------------------------------------------------------------------------
    */
    void borrar() {
        gotoxy(x, y);     cout << "     ";
        gotoxy(x, y + 1); cout << "     ";
        gotoxy(x, y + 2); cout << "     ";
    }

    /*
    ------------------------------------------------------------------------------
        Mueve la nave segun la tecla presionada.

        Cada comparacion combina dos condiciones gracias al operador logico AND
        (&&): no basta con que la tecla sea correcta, tambien se verifica que la
        nueva posicion no se salga del area de juego.
    ------------------------------------------------------------------------------
    */
    void mover(char tecla) {
        borrar();  // Primero se borra de la posicion anterior

        if (tecla == 'a' && x > 2)  x--;   // izquierda
        if (tecla == 'd' && x < 70) x++;   // derecha
        if (tecla == 'w' && y > 3)  y--;   // arriba
        if (tecla == 's' && y < 20) y++;   // abajo

        pintar(); // Luego se dibuja en la nueva posicion
    }
};

/*
==================================================================================
    CLASE ASTEROIDE
==================================================================================
    Enemigo que cae desde la parte superior de la pantalla. Al llegar al final
    reaparece arriba, en una columna aleatoria.
==================================================================================
*/
class Asteroide {
private:
    int x, y;

public:
    // Constructor: inicializa la posicion del asteroide
    Asteroide(int _x, int _y) { x = _x; y = _y; }

    int getX() { return x; }
    int getY() { return y; }

    void pintar() { gotoxy(x, y); cout << "O"; }
    void borrar() { gotoxy(x, y); cout << " "; }

    void mover() {
        borrar();
        y++;  // baja una fila por vuelta del bucle principal

        // Si llego al final del area de juego, reinicia arriba
        if (y > 23) {
            y = 4;
            x = (rand() % 70) + 2;  // columna aleatoria entre 2 y 71
        }

        pintar();
    }
};

/*
==================================================================================
    CLASE BALA
==================================================================================
    Proyectil que asciende. Se descarta cuando sale por arriba del area visible.
==================================================================================
*/
class Bala {
private:
    int x, y;

public:
    Bala(int _x, int _y) { x = _x; y = _y; }

    int getX() { return x; }
    int getY() { return y; }

    void mover() {
        gotoxy(x, y); cout << " ";  // borra de la posicion anterior
        y--;                         // sube una fila
        gotoxy(x, y); cout << "|";  // dibuja en la nueva posicion
    }

    bool fueraDeRango() { return y < 4; }
};

/*
==================================================================================
    PROGRAMA PRINCIPAL
==================================================================================
*/
int main() {

    // Siembra el generador de numeros aleatorios con la hora actual, para que
    // las posiciones de los asteroides sean distintas en cada partida.
    srand(time(NULL));

    // Peticion del nombre del piloto: se muestra en pantalla y debe quedar
    // legible en la captura de evidencia.
    string nombrePiloto;
    cout << "Ingresa tu Nombre y Apellido (Se mostrara en la captura de pantalla): ";
    getline(cin, nombrePiloto);  // getline permite escribir nombre y apellido con espacios

    system("cls");     // limpia la pantalla
    ocultarCursor();   // oculta el cursor

    bool gameOver = false;
    int score = 0;  // Funcionalidad 1: Marcador de puntos

    // Se crea el objeto jugador: se ejecuta el constructor con (35, 20, 3)
    Nave jugador(35, 20, 3);

    // Vectores de punteros porque la cantidad de asteroides y balas cambia
    // dinamicamente durante la partida.
    vector<Asteroide*> asteroides;
    vector<Bala*> balas;

    // Carga inicial: 5 asteroides en posiciones aleatorias
    for (int i = 0; i < 5; i++) {
        asteroides.push_back(new Asteroide((rand() % 70) + 2, (rand() % 5) + 4));
    }

    jugador.pintar();

    /*
    ------------------------------------------------------------------------------
        BUCLE PRINCIPAL
        Mientras queden vidas, repite: mostrar HUD, leer teclado, mover balas,
        mover asteroides y detectar colisiones.
    ------------------------------------------------------------------------------
    */
    while (!gameOver) {

        // HUD: nombre del piloto, vidas y puntaje
        gotoxy(2, 1);
        cout << "PILOTO: " << nombrePiloto << "  ";

        gotoxy(2, 2);
        cout << "VIDAS: " << jugador.getVidas() << "  ";

        gotoxy(15, 2);
        cout << "SCORE: " << score << "  ";

        // --- Entrada de teclado ---
        // _kbhit() indica si hay una tecla presionada pendiente de leer,
        // de ese modo el juego no se detiene esperando al usuario.
        if (_kbhit()) {
            // tolower() convierte la tecla a minuscula para que el Bloq Mayus
            // del teclado no impida jugar.
            char tecla = tolower(_getch());

            if (tecla == ' ') {
                // La bala nace dos columnas a la derecha y una fila arriba,
                // justo sobre el centro de la nave.
                balas.push_back(new Bala(jugador.getX() + 2, jugador.getY() - 1));
            } else {
                jugador.mover(tecla);
            }
        }

        // --- Proyectiles ---
        for (int i = 0; i < balas.size(); i++) {
            balas[i]->mover();

            // Si la bala salio del area de juego, se libera la memoria y se
            // quita del vector. El delete evita una fuga de memoria: sin el,
            // el espacio queda reservado pero inutilizable.
            if (balas[i]->fueraDeRango()) {
                gotoxy(balas[i]->getX(), balas[i]->getY());
                cout << " ";
                delete balas[i];
                balas.erase(balas.begin() + i);
            }
        }

        // --- Asteroides y colisiones ---
        for (int i = 0; i < asteroides.size(); i++) {
            asteroides[i]->mover();

            // COLISION ASTEROIDE -> JUGADOR
            // El asteroide tiene que caer dentro del rectangulo que ocupa la nave
            // (4 columnas de ancho por 3 filas de alto).
            if ((asteroides[i]->getX() >= jugador.getX() && asteroides[i]->getX() <= jugador.getX() + 4) &&
                (asteroides[i]->getY() >= jugador.getY() && asteroides[i]->getY() <= jugador.getY() + 2)) {

                jugador.borrar();
                jugador.reducirVida();

                // El asteroide impactado se reemplaza por uno nuevo arriba
                asteroides[i]->borrar();
                asteroides[i] = new Asteroide((rand() % 70) + 2, 4);

                jugador.pintar();

                // Si se agotaron las vidas, termina la partida
                if (jugador.getVidas() == 0) gameOver = true;
            }

            // COLISION BALA -> ASTEROIDE
            for (int j = 0; j < balas.size(); j++) {
                if (asteroides[i]->getX() == balas[j]->getX() &&
                    (asteroides[i]->getY() == balas[j]->getY() ||
                     asteroides[i]->getY() + 1 == balas[j]->getY())) {

                    // Se borra y libera la bala
                    gotoxy(balas[j]->getX(), balas[j]->getY());
                    cout << " ";
                    delete balas[j];
                    balas.erase(balas.begin() + j);

                    // Se borra y reemplaza el asteroide
                    asteroides[i]->borrar();
                    asteroides[i] = new Asteroide((rand() % 70) + 2, 4);

                    score += 10;  // Funcionalidad 1: sumar puntos por impacto

                    break;  // una bala no puede destruir dos asteroides
                }
            }
        }

        // Pausa breve para que el movimiento sea visible y no ocupe toda la CPU
        Sleep(30);
    }

    // --- Fin de la partida ---
    system("cls");
    gotoxy(30, 10);
    cout << "G A M E   O V E R... O sea... Perdiste!!";
    gotoxy(30, 12);
    system("pause");

    return 0;
}