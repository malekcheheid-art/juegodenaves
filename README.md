# Juego de Naves en Consola

Simulador de combate espacial en consola, escrito en C++ como ejercicio de
introduccion a la Programacion Orientada a Objetos (POO).

La actividad consiste en definir la clase `Nave` y su entorno de juego
(asteroide y bala) utilizando encapsulamiento, metodos publicos y constructores.

## Datos del proyecto

| Campo | Valor |
| --- | --- |
| Materia | Laboratorio de Programacion (LPR) |
| Institucion | E.E.S.T. N. 1 "Eduardo Ader" - Vicente Lopez |
| Curso | 5. ano - 3. grupo (A-B) |
| Actividad | N. 8 - Introduccion a POO en C++ |
| Docente | Mansilla Munoz York Elias |
| Licencia | MIT (ver [LICENSE](LICENSE)) |

## Requisitos

- Sistema operativo Windows.
- Compilador con soporte para C++ (Visual Studio, MinGW o Code::Blocks).
- En este punto del proyecto no se requiere ningun motor de juego ni
  libreria externa: todo se resuelve con la biblioteca estandar y las API de
  Windows (`windows.h`, `conio.h`).

## Compilacion

Con MinGW:

```
g++ src/main.cpp -o juego_naves.exe
```

Con Visual Studio: abrir el archivo `src/main.cpp` y compilar en modo consola.

## Ejecucion

```
./juego_naves.exe
```

El programa solicita el nombre y apellido del piloto antes de iniciar la
partida. Ese dato se muestra en pantalla y es el que debe quedar visible en la
captura de evidencia.

## Controles

| Tecla | Accion |
| --- | --- |
| `W` | Mover la nave hacia arriba |
| `A` | Mover la nave hacia la izquierda |
| `S` | Mover la nave hacia la abajo |
| `D` | Mover la nave hacia la derecha |
| `ESPACIO` | Disparar |

La conversion a minuscula se realiza con `tolower()` para evitar que el bloqueo
de mayusculas del teclado altere los comandos.

## Estructura del proyecto

```
juegodenaves/
├── .gitignore
├── LICENSE
├── README.md
├── docs/
│   ├── InformeEEST1_LPR2026_ACT08_G03_v1.0.0.pdf
│   ├── CHANGELOG.md
│   └── manuales/
│       ├── manual_programador_v1.0.0.pdf
│       └── manual_usuario_v1.0.0.pdf
├── src/
│   └── main.cpp
└── capturas/
    └── combate_consola.png
```

## Arquitectura del codigo

El motor se apoya en tres clases definidas dentro de `src/main.cpp`:

- `Nave`: representa al jugador. Declara en `private` sus coordenadas (`x`, `y`)
  y su cantidad de `vidas`, de modo que nadie desde `main()` pueda alterarlos
  directamente. La interaccion se produce unicamente a traves de metodos publicos
  como `mover()`, `pintar()`, `borrar()`, `reducirVida()` y los accesores `getX()`,
  `getY()` y `getVidas()`.
- `Asteroide`: enemigo que desciende de forma continua y reaparece en la parte
  superior al llegar al final de la pantalla.
- `Bala`: proyectil que asciende y se elimina al salir del area de juego.

Las clases `Asteroide` y `Bala` se almacenan en `std::vector` de punteros
(`vector<Asteroide*>` y `vector<Bala*>`) porque la cantidad de instancias cambia
en tiempo de ejecucion: cada disparo agrega un elemento y cada impacto elimina
otro. La memoria se libera de forma explicita con `delete` antes de quitar el
elemento del vector.

El bucle principal (`while (!gameOver)`) ejecuta tres tareas por vuelta: leer el
teclado, mover los proyectiles y detectar colisiones tanto entre bala y
asteroide como entre asteroide y nave. Al llegar las vidas a cero se termina el
juego y se muestra `GAME OVER`.

## Documentacion

- `docs/`: informe academico en formato APA v7, historial de versiones y
  manuales de programador y de usuario.
- `capturas/`: evidencia fotografica de la consola durante la ejecucion.

## Estado del proyecto

- [x] Estructura de carpetas del repositorio
- [x] Codigo base funcional (motor del juego)
- [ ] Funcionalidad adicional del desafio obligatorio
- [ ] Informe APA v7
- [ ] Manual del programador
- [ ] Manual del usuario
- [ ] Capturas de ejecucion