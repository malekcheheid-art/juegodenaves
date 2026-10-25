<!-- =====================================================================
     INFORME APA v7 — ACTIVIDAD 8 (LPR 5.° año, grupo A) — ESTUDIANTE: Malek Cheheid

     Este archivo es la FUENTE editable del informe.
     El entregable es el PDF generado con el mismo contenido:
         docs/InformeEEST1_LPR2026_ACT08_CheheidMalek_v1.0.0.pdf

     Regla del profesor (Escudo Anti-Excusas, p. 7 del enunciado):
         "Su informe debe tener exactamente 4 títulos: Introducción,
          Desarrollo, Conclusión y Referencias. Ni más, ni menos."

     Por eso las 4 preguntas del Cuestionario Técnico se responden con
     TÍTULOS EN NEGRITA EN LÍNEA (subtítulos de nivel 2 en APA), no con
     encabezados nuevos. Así el documento mantiene exactamente 4 títulos.

     REGLA DE AUTORÍA: el profesor entrega el motor (clases Nave, Asteroide,
     Bala y el bucle de main()). El informe NO dice "escribí" ni "definí"
     sobre ese código: se describe en tercera persona y se analiza. En
     primera persona sólo aparece lo hecho por el estudiante —compilar,
     analizar, documentar, implementar el score, revisar y publicar—.

     Cada párrafo se escribe en una sola línea del Markdown: el generador
     del PDF une las líneas contiguas como un mismo párrafo, salvo en la
     sección Referencias, donde cada línea es una entrada aparte.
     ===================================================================== -->


&nbsp;

# Programación Orientada a Objetos en C++: Diseño e Implementación de un Simulador de Combate Espacial en Consola (*class Nave*)

&nbsp;

**Malek Cheheid**

E.E.S.T. N.° 1 "Eduardo Ader" — Vicente López

LPR: Laboratorio de Programación

5.° año, 3.°, grupo A — 2.° cuatrimestre

Actividad N.° 8: Programación Orientada a Objetos (POO) en C++

Profesor de grupo: Yamil Ganduglia

21 de octubre de 2026

**Repositorios del proyecto**

GitHub: https://github.com/malekcheheid-art/juegodenaves.git

GitLab: https://gitlab.com/malekcheheid-art/juegodenaves.git

&nbsp;

---

&nbsp;

# Introducción

Para la Actividad N.° 8 de Laboratorio de Programación (LPR) trabajé sobre un simulador de combate espacial en consola, escrito en C++. El profesor me entregó el código base en `src/main.cpp`; a mí me tocó compilarlo, leerlo línea por línea, explicar sus decisiones de diseño y sumarle una funcionalidad propia. La actividad me pedía además dar el paso del `struct` —que usé en la Actividad N.° 7 para agrupar variables sueltas— a una `class`, que además de agrupar los datos los guarda adentro y decide desde afuera qué se puede tocar. Ese es el punto central de la Programación Orientada a Objetos (cplusplus.com, s. f.).

El juego entero vive en ese único archivo, con 372 líneas. Ahí hay tres clases: `Nave`, que es el jugador; `Asteroide`, que cae desde arriba y vuelve a aparecer en una columna aleatoria cuando llega abajo; y `Bala`, que sube desde la nave y desaparece al salir de la pantalla. El bucle principal de `main()` lee el teclado sin frenar el juego, usando `_kbhit()` y `_getch()`, mueve las balas, hace descender los asteroides y compara posiciones para detectar los impactos. Ese motor lo compilé con TDM-GCC 10.3 en modo C++17 y con las advertencias activadas (`-Wall -Wextra`), y terminó sin errores.

Trabajé siguiendo la metodología 5R del profesor: **registrar** (copié el código, lo compilé y lo ejecuté), **reducir** (marqué dónde termina la sección `private:` y dónde empieza la `public:`), **responder** (este cuestionario técnico), **reflexionar** (agregué una funcionalidad extra) y **revisar** (publiqué todo en los dos repositorios).

Como desafío obligatorio para aprobar, implementé una sola funcionalidad de las 15 del anexo: la N.° 1, el marcador de puntos o *score*.

&nbsp;

# Desarrollo

**Qué Diferencia a un `struct` de una `class`.** En C++, las dos palabras hacen casi lo mismo: las dos agrupan atributos y métodos, las dos aceptan constructores, sobrecarga y herencia. La única diferencia de regla es el acceso por defecto. Todo lo que se declara con `struct` es `public` por defecto; todo lo que se declara con `class` es `private` por defecto. La herencia sigue la misma lógica: pública en `struct`, privada en `class` (cplusplus.com, s. f.; GeeksforGeeks, s. f.).

En la práctica eso se nota en la clase `Nave` que trae el código base. Está en `src/main.cpp`, líneas 84 a 161, y tiene esta forma:

```cpp
class Nave {
private:
    int x, y;     // Coordenadas de la nave en la consola
    int vidas;    // Cantidad de vidas restantes

public:
    Nave(int _x, int _y, int _vidas) { ... }
    int getX() { return x; }
    void reducirVida() { vidas--; }
    ...
};
```

Los tres atributos —`x`, `y` y `vidas`— quedan antes de cualquier especificador de acceso, así que están privados. Por consecuencia, si alguien escribiera `jugador.vidas = 99;` dentro de `main()`, el compilador frenaría el proceso con un error de acceso. Si esa misma clase se hubiera declarado con la palabra `struct` en lugar de `class`, la línea compilaría y correría sin avisar nada. Ahí está la diferencia real: con `struct` se deja la puerta abierta y con `class` se la cierra. Por eso digo que el `struct` junta datos sueltos, y que la `class` arma una caja fuerte que contiene los datos y, además, las funciones que tienen derecho a moverlos.

**Por Qué No Dejé la *Salud* como Pública.** Si `vidas` fuera `public`, cualquiera podría escribirle cualquier cosa. Basta con que un programador novato escriba, por descuido, `jugador.vidas = -5;`: el programa compila igual. Después, dentro del bucle, la condición `if (jugador.getVidas() == 0)` ya no se cumple nunca, `gameOver` nunca pasa a `true` y el juego queda girando en un bucle infinito mientras el HUD anuncia vidas negativas. Si en cambio se escribe `jugador.vidas = 999999;`, desaparece el desafío y la partida pierde todo el sentido. En los dos casos el error es silencioso: no lo ve el compilador, lo ve —o no ve— el que está jugando.

Por eso el código encapsula `vidas` en `private` y deja dos puertas nomás. Una de lectura, `getVidas()` en la línea 112, que devuelve el valor pero no permite escribirlo. Y una de escritura, `reducirVida()` en la línea 115, cuyo cuerpo entero es `vidas--;`. Como existe una sola vía para cambiarla y esa vía únicamente resta de a uno, el estado de la nave no se puede descomponer. Con este diseño el objeto cuida su propio estado sin que yo tenga que estar pendiente, y si algún día quiero agregarle un escudo o una regeneración, cambio la clase y no tengo que tocar una sola línea de `main()`.

**Para Qué Sirve el Constructor de `Nave`.** El constructor es la función miembro que se ejecuta sola, una única vez, en el instante exacto en que se crea el objeto. Se llama con el mismo nombre que la clase y no devuelve nada, ni siquiera `void` (Microsoft, 2022; cplusplus.com, s. f.). En el código base está en la línea 103 y tiene esta forma:

```cpp
Nave(int _x, int _y, int _vidas) {
    x = _x;
    y = _y;
    vidas = _vidas;
}
```

Se invoca en `main()` con la sentencia `Nave jugador(35, 20, 3);`, en la línea 249.

El trabajo del constructor es dejar el objeto en un estado válido antes de que cualquier método lo toque. Si se borra ese bloque, al declarar `jugador` las variables `x`, `y` y `vidas` no reciben ningún valor. Como son tipos básicos, la memoria queda con basura y las primeras llamadas a `getVidas()` o a `mover()` devuelven y operan con números indeterminados: eso en C++ se llama comportamiento indefinido. El guion bajo de los parámetros (`_x`, `_y`, `_vidas`) está ahí para distinguirlos de los atributos, porque los dos se llaman igual y dentro del constructor la palabra `x` se resuelve hacia el miembro de la clase. Existe además una forma más prolija, la lista de inicialización de miembros, que asigna antes de entrar al cuerpo del constructor: `Nave(int x, int y, int vidas) : x(x), y(y), vidas(vidas) {}` (Microsoft, 2022).

Aclaro una diferencia con el enunciado. La pregunta del cuestionario menciona un bloque `Nave(string _nombre, ...)`. En el código que entregó el profesor el nombre del piloto no se guarda dentro de la clase: se lee en `main()` con `getline(cin, nombrePiloto)` antes de arrancar la partida, se usa como sistema anti-copia y se dibuja directamente en la cabecera de la consola, en la línea 274. Me parece que está bien resuelto así. El nombre es un dato para mostrar en pantalla, no un estado de la nave; si estuviera dentro de la clase, la tendrían que obligar a saber dibujar y se mezclarían dos responsabilidades que conviene separar. Si decidiera sumarlo, tendría que cambiar la firma a `Nave(string _nombre, int _x, int _y, int _vidas)`, declarar el atributo `string nombre` y agregar su accesor `getNombre()`.

**Qué Funcionalidad Agregué y Dónde la Inserté.** Elegí la funcionalidad N.° 1, el marcador de puntos. La implementé con tres toques puntuales dentro de `src/main.cpp`, sin modificar ninguna de las tres clases que ya traía el motor.

Primero, declaré el acumulador en la línea 246, al lado de `bool gameOver = false;`: `int score = 0;`. Lo dejé como variable local de `main()`, no como variable global. Prefiero que viva en ese ámbito: una global se puede cambiar desde cualquier punto del archivo y eso rompe justo lo que estoy aprendiendo a hacer en esta actividad.

Segundo, lo muestro en el HUD, dentro del bucle `while (!gameOver)`, en las líneas 279 y 280:

```cpp
gotoxy(15, 2);
cout << "SCORE: " << score << "  ";
```

Los dos espacios del final no son de adorno: sirven para borrar los dígitos que sobran cuando el número cambia de ancho, por ejemplo al pasar de `SCORE: 9` a `SCORE: 10`.

Tercero, sumo los puntos en la línea 353, dentro del bloque de colisión bala → asteroide, apenas se destruye el asteroide impactado: `score += 10;`. Así cada acierto vale 10 puntos y el marcador se actualiza en la misma vuelta del bucle.

Elegí esta funcionalidad porque se ve de inmediato en la consola, que es exactamente lo que pide la rúbrica para la captura de evidencia, y porque sirve de base para otras del anexo, como la dificultad progresiva o el disparo doble. Para verificarla compilé con `g++ -std=c++17 -Wall -Wextra src/main.cpp -o juego_naves.exe` y no hubo errores de compilación. Después ejecuté una partida y confirmé que el HUD muestra el nombre del piloto, las vidas restantes y el puntaje acumulado, como se ve en la Figura 1.

{{FIGURA:capturas/combate_consola.png|Ejecución de la Partida en Consola}}

**Código completo `main.cpp`**

{{CODIGO:src/main.cpp}}

&nbsp;

# Conclusión

Con esta actividad pasé de agrupar datos sueltos con `struct` a trabajar con objetos de verdad. La conclusión más clara para mí es que la diferencia de sintaxis entre las dos palabras es mínima —sólo el acceso por defecto—, pero lo que cambia en serio es quién manda sobre los datos.

Sobre el encapsulamiento me quedó demostrado que proteger `vidas` no es un capricho de la materia. Al dejar una única vía de escritura, `reducirVida()`, y una de sólo lectura, `getVidas()`, el objeto se cuida solo y yo desde `main()` pierdo —y dejo de necesitar— la posibilidad de romperlo. Sobre los constructores entendí que su función es que un objeto nazca con valores definidos; sin ellos estaría leyendo basura de memoria.

El motor que entrega la actividad compila y corre con TDM-GCC 10.3 en modo C++17, e implementa las tres clases, el bucle principal, las dos detecciones de colisiones —bala con asteroide y asteroide con nave— y la memoria dinámica con `new` y `delete` sobre contenedores `std::vector` de punteros. Yo verifiqué que todo eso funcione en mi máquina y le sumé la funcionalidad obligatoria de marcador de puntos, que se ve en el HUD y en la captura de evidencia.

Al revisar el código encontré tres cosas que quiero corregir después. Falta un `delete` del asteroide que se reemplaza al impactar, para que la memoria quede tan limpia como ya la queda con las balas. Conviene sumar `#include <string>`, porque hoy depende de inclusiones transitivas. Y en los tres bucles que recorren un `std::vector` el índice está declarado como `int`, con lo que quedan tres advertencias de comparación entre signo distinto que se arreglan pasándolo a `size_t`. Ninguna de las tres rompe el juego, pero me parece que anotarlas también forma parte del trabajo.

&nbsp;

# Referencias

Cheheid, M. (2026a). *Juego de naves en consola* (v1.0.0) [Repositorio de código fuente]. GitHub. https://github.com/malekcheheid-art/juegodenaves.git

Cheheid, M. (2026b). *Juego de naves en consola* (v1.0.0) [Repositorio de código fuente]. GitLab. https://gitlab.com/malekcheheid-art/juegodenaves.git

cplusplus.com. (s. f.). *Classes (I)*. Recuperado el 21 de octubre de 2026, de https://cplusplus.com/doc/tutorial/classes/

GeeksforGeeks. (s. f.). *Access modifiers in C++*. Recuperado el 21 de octubre de 2026, de https://www.geeksforgeeks.org/access-modifiers-in-c/

Git. (s. f.). *Git documentation*. Recuperado el 21 de octubre de 2026, de https://git-scm.com/doc

Microsoft. (2022, 7 de febrero). *Constructores (C++)*. Microsoft Learn. https://learn.microsoft.com/es-es/cpp/cpp/constructors-cpp
