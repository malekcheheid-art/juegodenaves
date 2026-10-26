# Changelog

Registro de versiones del Juego de Naves en Consola.

El formato sigue Keep a Changelog y el proyecto usa [SemVer](https://semver.org/).

## [No publicada]

## [1.0.0] - 2026-10-21

### Agregado

- Estructura obligatoria del repositorio: `src/`, `docs/`, `docs/manuales/`
  y `capturas/`.
- Archivo `.gitignore` que excluye compilados, IDEs y archivos del sistema.
- Licencia MIT.
- `README.md` con descripcion del proyecto, requisitos, compilacion,
  ejecucion, controles y estado del avance.
- Codigo base funcional en `src/main.cpp`:
  - Clase `Nave` con atributos privados (`x`, `y`, `vidas`), constructor
    parametrizado, accesores y metodos `pintar()`, `borrar()` y `mover()`.
  - Clase `Asteroide` con reinicio aleatorio al llegar al final de la pantalla.
  - Clase `Bala` con deteccion de salida del area de juego.
  - Bucle principal con lectura de teclado, movimiento y deteccion de
    colisiones entre bala-asteroide y asteroide-nave.
  - Mecanica de gestion de memoria dinamica con `new`, `delete` y `std::vector`.
- Funcionalidad adicional del desafio obligatorio: marcador de puntos
  (`SCORE`). Suma 10 puntos por cada impacto de bala sobre un asteroide y
  muestra el HUD con el nombre del piloto, las vidas y el puntaje.
- Captura de evidencia en `capturas/combate_consola.png`, con el nombre del
  piloto visible en consola.
- Informe academico en formato APA v7, con los cuatro titulos exigidos y los
  enlaces de los repositorios en las referencias:
  `docs/InformeEEST1_LPR2026_ACT08_CheheidMalek_v1.0.0.pdf`.
- Archivo `.gitattributes` que marca los PDF y las imagenes como binarios, de
  modo que `core.autocrlf` no los corrompa al clonar el repositorio.

### Pendiente

- Manual del Programador (`docs/manuales/manual_programador_v1.0.0.pdf`).
- Manual del Usuario (`docs/manuales/manual_usuario_v1.0.0.pdf`).