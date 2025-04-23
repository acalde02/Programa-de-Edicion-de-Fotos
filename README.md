
# Programa de Edición de Fotos – Proyecto de Algoritmos

## Descripción del Proyecto

Este proyecto es una aplicación de consola escrita en **C++17** que permite realizar **edición básica de imágenes** mediante filtros y transformaciones sencillas. Se desarrolló con fines académicos (curso de **Algoritmos**), utilizando únicamente la biblioteca estándar de C++ y librerías auxiliares de código abierto para manejo de imágenes (stb_image/stb_image_write). El programa carga una imagen (formato **PNG/JPG** soportado) en memoria, la procesa píxel a píxel aplicando los filtros seleccionados, y guarda una nueva imagen con los cambios realizados.

---

## Funcionamiento para el Usuario

1. Ejecutar el programa desde consola.
2. Seleccionar una imagen desde `testImages/`.
3. Aplicar filtros como blanco y negro, negativo, rotar, etc.
4. Opción para deshacer cambios recientes.
5. Guardar la imagen editada en `resultImages/`.

---

## Funcionamiento Interno (Resumen Técnico)

- La imagen se representa como una matriz `vector<vector<Pixel>>`.
- Se implementó una pila (`std::stack`) para deshacer filtros.
- El filtro de relleno por color usa una pila explícita para simular búsqueda DFS.
- El filtro Pixel Sort aplica el algoritmo QuickSort recursivo por filas.
- Se usan bucles anidados para rotación, detección de bordes y efectos de brillo.

---

## Algoritmos Usados y Justificación

### Algoritmos No Recursivos

Se emplearon bucles iterativos simples para filtros como escala de grises, inversión de colores, intercambio de canales, detección de bordes (Sobel) y rotación de imágenes. Estas soluciones son eficientes (O(n)) y fáciles de mantener, ideales para recorrer estructuras como matrices de píxeles.

### Recursividad (QuickSort)

Se implementó QuickSort de manera recursiva para ordenar los píxeles en cada fila de la imagen en el filtro Pixel Sort. Este algoritmo fue elegido por su eficiencia media O(n log n) frente a otros como BubbleSort.

### Pilas

- **Historial de filtros:** Se utiliza un `std::stack` para guardar versiones anteriores de la imagen y permitir deshacer filtros.
- **Flood Fill:** Implementación iterativa de un algoritmo tipo DFS utilizando una pila explícita de coordenadas.

### Listas contiguas (vectores)

Las imágenes y las estructuras de píxeles se gestionan con `vector` y `vector<vector<Pixel>>` para facilitar el acceso aleatorio y una implementación eficiente en memoria contigua.

### Ordenamiento

Se aplicó **QuickSort** manualmente sobre cada fila de la imagen para lograr un efecto visual de gradiente (Pixel Sort), reforzando el aprendizaje del algoritmo recursivo y su uso práctico.

---

## Autores

Este proyecto fue desarrollado por:

- Adrián Calderón de Amat [@acalde02](https://github.com/acalde02)
- Pedro Antonio Morales Nieto [@ErCoCo](https://github.com/ErCoCo)
