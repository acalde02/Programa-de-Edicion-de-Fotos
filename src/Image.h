#include <iostream>
#include <vector>
#include <functional>
#include <stack>

#include "Pixel.h"
using namespace std;

class Image {
    vector< vector<Pixel> > pixels;
    stack<vector< vector<Pixel> >> history;

    int width, height;
    
    public:

    /**
     * @brief Carga una imagen desde un archivo.
     * @param filename Nombre del archivo de la imagen.
     * @return true si la carga fue exitosa, false en caso contrario.
     * 
     * Esta función utiliza la biblioteca stb_image para cargar imágenes en formato PNG.
     * La imagen se almacena en un vector de vectores de objetos Pixel.
     * Cada Pixel contiene los valores de color rojo, verde y azul.
     * 
     * Complexidad temporal: O(n), donde n es el número de píxeles en la imagen.
     * Complejidad espacial: O(n), donde n es el número de píxeles en la imagen.
     */
    bool load(const string &filename);

    /**
     * @brief Guarda la imagen en un archivo.
     * @param filename Nombre del archivo de salida.
     * @return true si la guardado fue exitoso, false en caso contrario.
     * 
     * Esta función utiliza la biblioteca stb_image_write para guardar imágenes en formato PNG.
     * La imagen se guarda en el formato RGB.
     * 
     * Complexidad temporal: O(n), donde n es el número de píxeles en la imagen.
     * Complejidad espacial: O(n), donde n es el número de píxeles en la imagen.
     */
    bool save(const string &filename);

    /**
     *  @brief Cambia el color rojo y azul de cada pixel de la imagen.
     *  @details Intercambia los valores de los componentes rojo y azul de cada pixel.
     * 
     *  Complejidad temporal: O(n), donde n es el número de píxeles en la imagen.
     *  Complejidad espacial: O(1).
    */ 
    void redBlueSwapFilter();

    /**
     * @brief Aplica el filtro de blanco y negro a la imagen.
     * @details Obtiene el color del pixel y lo divide entre 3
     * 
     * 
     * 
     * Complejidad temporal: O(n)
     * Complejidad espacial: O(1) 
     */
    void blackAndWhiteFilter();

    /**
     * @brief Gira el angulo 90 grados a la derecha la imagen
     * 
     * 
     * Complejidad temporal: 0(n^2)
     * Complejidad espacial: O(1)
     */
    void rotateClockwise();


    /**
     * @brief Invierte los colores de la imagen.
     * @details Cada pixel se convierte en la diferencia
     * de 255 y la tonalidad actual.
     * 
     * Complejidad Temporal O(n)
     * Complejidad Espacial: O(1)
     * 
     */
    void invertFilter();

    /**
     * @brief Dado un color seleccionado, la funcion la reemplaza por el color dado.
     * 
     * @param x: Posicion del pixel en el eje x
     * @param y: Posicion del pixel en el eje y
     * 
     * @param targetColor: El color que deseas cambiar
     * @param replacementColor: El color que deseas poner
     * 
     * 
     * Complejidad temporal: O(n)
     * Complejidad espacial: O(1)
     * 
     */
    void FloodFill(int x, int y, Pixel targetColor, Pixel replacementColor);

    /**
     * @brief Aplica un filtro a la imagen.
     * @param filter Función que representa el filtro a aplicar.
     * 
     * Esta función guarda el estado actual de la imagen en el historial antes de aplicar el filtro.
     * 
     * Complejidad temporal: O(n), donde n es el número de píxeles en la imagen.
     * Complejidad espacial: O(n), donde n es el número de píxeles en la imagen.
     */
    void applyFilter(function<void()> filter);

    /**
     * @brief Deshace el último filtro aplicado a la imagen.
     * 
     * Esta función restaura la imagen al estado anterior al último filtro aplicado.
     * 
     * Complejidad temporal: O(1).
     * Complejidad espacial: O(1).
     */
    void undoFilter();

    /**
     * @brief Aplica el filtro de Sobel a la imagen.
     * @details Este filtro se utiliza para detectar bordes en la imagen.
     * 
     * Complejidad temporal: O(n), donde n es el número de píxeles en la imagen.
     * Complejidad espacial: O(n), donde n es el número de píxeles en la imagen.
     */
    void sobelFilter();

    /**
     * @brief Aplica el filtro de PixelSort a la imagen.
     * @details Este filtro ordena los píxeles de cada fila de la imagen según su luminosidad.
     * 
     * Complejidad temporal: O(n log n), donde n es el número de píxeles en una fila.
     * Complejidad espacial: O(n), donde n es el número de píxeles en una fila.
     */
    void pixelSortFilter();

    /**
     * @brief Aplica un filtro de blanqueamiento dental a la imagen.
     * @details Este filtro se utiliza para blanquear los dientes en la imagen.
     * 
     * Complejidad temporal: O(n), donde n es el número de píxeles en la región de blanqueamiento.
     * Complejidad espacial: O(1).
     */
    void whiteningFilter();


    /**
     * @brief Devuelve el pixel en la posicion (x,y)
     * 
     * @param x: Posicion del pixel en el eje x
     * @param y: Posicion del pixel en el eje y
     * 
     * @return Pixel en la posicion (x,y)
     */
    Pixel getPixel(int x, int y) const;

    /**
     * @brief Devuelve el ancho de la imagen.
     * @return Ancho de la imagen.
     */
    int getWidth() const;


    /**
     * @brief Devuelve la altura de la imagen.
     * @return Altura de la imagen.
     */
    int getHeight() const;

    private:
        //Auxiliares para PixelSort
        void quickSort(std::vector<Pixel>& row, int low, int high);
        int partition(std::vector<Pixel>& row, int low, int high);
        int luminosity(const Pixel& p);
        
};