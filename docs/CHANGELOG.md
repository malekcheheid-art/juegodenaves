# Changelog

Registro de versiones del Juego de Naves en Consola.

El formato sigue Keep a Changelog y el proyecto usa [SemVer](https://semver.org/).

## [No publicada]

## [1.0.0] - 2026

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

### Pendiente

- Funcionalidad adicional del desafio obligatorio (una de las quince
  opciones publicadas por la catedra).
- Informe academico en formato APA v7.
- Manual del Programador.
- Manual del Usuario.
- Capturas de pantalla de la ejecucion.