# Programa de Edición de Fotos

Este proyecto es una aplicación de escritorio en C++ que permite aplicar filtros y transformaciones básicas a imágenes. Está construido usando únicamente la biblioteca estándar de C++ (STD), lo que lo hace portable y fácil de compilar en diferentes sistemas.

## Características

- Conversión a escala de grises, sepia y negativo.
- Ajuste de brillo y contraste.
- Rotación y escalado de imágenes.
- Interfaz simple por línea de comandos.
- Soporte para formatos de imagen comunes como PNG y JPG.

## Requisitos

- Compilador compatible con C++17.
- CMake 3.10 o superior.
- Sistema con soporte para operaciones de lectura/escritura de archivos de imagen (JPG, PNG, etc.).

## Instalación

### 1. Clona el repositorio:

```bash
git clone https://github.com/acalde02/Programa-de-Edicion-de-Fotos.git
cd Programa-de-Edicion-de-Fotos
```

### 2. Crea el directorio de compilación:

```bash
mkdir build
cd build
```

### 3. Genera el proyecto con CMake:

```bash
cmake ..
```

### 4. Compílalo:

```bash
make
```

## Uso

Desde el directorio `build`, ejecuta:

```bash
./ProgramaEdicionFotos
```

Sigue las instrucciones en pantalla para cargar una imagen, elegir un filtro o transformación, y guardar el resultado.  
Las imágenes editadas se guardan en la carpeta `resultImages`.

## Estructura del Proyecto

```
Programa-de-Edicion-de-Fotos/
├── src/             # Código fuente del programa
├── testImages/      # Imágenes de prueba incluidas para experimentar
├── resultImages/    # Salida de imágenes editadas
├── CMakeLists.txt   # Archivo para configurar la compilación
```

## Licencia

Este proyecto utiliza únicamente la biblioteca estándar de C++ (STD), que se encuentra bajo la licencia de la implementación utilizada (por ejemplo, GNU GPL para GCC o Apache 2.0/LLVM para Clang).

No se incluye código de terceros con licencias adicionales.

---

## Autores

Este proyecto fue desarrollado por:

- Adrián Calderón de Amat  [@acalde02](https://github.com/acalde02)
- Pedro Antonio Morales Nieto [@ErCoCo](https://github.com/ErCoCo)




