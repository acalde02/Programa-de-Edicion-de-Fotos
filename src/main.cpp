#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <filesystem>
#include "Image.h"

namespace fs = std::filesystem;
using namespace std;

int main() {
    Image img;
    string inputFile, outputFile;
    string testFolder = "testImages/";
    string saveFolder = "resultImages/";
    stack<string> filterStack;

    // Listar imágenes disponibles
    cout << "\n=== Imagenes en testImages/ ===\n";
    vector<string> archivos;
    for (const auto& entry : fs::directory_iterator(testFolder)) {
        if (entry.is_regular_file()) {
            cout << "- " << entry.path().filename().string() << "\n";
            archivos.push_back(entry.path().filename().string());
        }
    }

    // Pedir imagen de entrada
    cout << "\nIngrese el nombre de la imagen a procesar (ej: Prueba.png): ";
    cin >> inputFile;
    inputFile = testFolder + inputFile;

    if (!img.load(inputFile)) {
        cerr << "Error al cargar la imagen.\n";
        return 1;
    }

    bool usedBefore = false;
    bool menu = true;
    int opcion;

    while (menu) {
        // Mostrar menu de filtros primero
        cout << "\n=== Filtros disponibles ===\n";
        cout << "1 - Filtro rojo/azul\n";
        cout << "2 - Blanco y negro\n";
        cout << "3 - Rotar 90 grados a la derecha\n";
        cout << "4 - Invertir colores\n";
        cout << "5 - Rellenar con otro color\n";

        if (!usedBefore){
            cout << "6 - Remarcado de bordes (Sobel) (Aplicar y Guardar)\n";
            cout << "7 - Gradiente de pixeles (PixelSort) (Aplicar y Guardar)\n";
            cout << "8 - Blanqueamiento Dental (Aplicar y Guardar)\n";
            cout << "Seleccione un filtro (1-8): ";
        } else {
            cout << "6 - Deshacer filtro\n";
            cout << "7 - Guardar y salir\n";
            cout << "Seleccione una opcion (1-7): ";
        }

        cin >> opcion;

        if (!usedBefore) {
            switch (opcion) {
                case 1:
                    img.applyFilter([&]() { img.redBlueSwapFilter(); });
                    filterStack.push("rojoazul");
                    break;
                case 2:
                    img.applyFilter([&]() { img.blackAndWhiteFilter(); });
                    filterStack.push("blanquinegro");
                    break;
                case 3:
                    img.applyFilter([&]() { img.rotateClockwise(); });
                    filterStack.push("rotado");
                    break;
                case 4:
                    img.applyFilter([&]() { img.invertFilter(); });
                    filterStack.push("invertido");
                    break;
                case 5:


                    int r, g, b, r2, g2, b2;

                    while (true)
                    {
                        cout << "Ingrese el color que deseas cambiar (ej: 255 0 0): ";
                        

                        cin >> r >> g >> b;
                        // Validar entrada
                        if (cin.fail()) {
                            cerr << "ERROR: Entrada invalida.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        // Validar colores
                        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                            cerr << "ERROR: Color fuera de rango (0-255).\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        break; // Salir del bucle si la entrada es válida
                    }
                    

                    cout << "Color seleccionado: " << r << " " << g << " " << b << "\n";

                    while (true)
                    {
                        cout << "Ingrese el nuevo color (ej: 0 255 0): ";
                        cin >> r2 >> g2 >> b2;
    
                        // Validar entrada
                        if (cin.fail()) {
                            cerr << "ERROR: Entrada invalida.\n";
                            return 1;
                        }
    
                        // Validar colores
                        if (r2 < 0 || r2 > 255 || g2 < 0 || g2 > 255 || b2 < 0 || b2 > 255) {
                            cerr << "ERROR: Color fuera de rango (0-255).\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        
                        break; // Salir del bucle si la entrada es válida
    
                    }

                    img.applyFilter([&]() {
                        bool found = false;
                        for (int y = 0; y < img.getHeight() && !found; ++y) {
                            for (int x = 0; x < img.getWidth() && !found; ++x) {
                                if (img.getPixel(x, y).toPackedRGB() == Pixel(r, g, b).toPackedRGB()) {
                                    img.FloodFill(x, y, Pixel(r, g, b), Pixel(r2, g2, b2));
                                    found = true;
                                }
                            }
                        }
                    });
                    
                    filterStack.push("relleno");
                    break;
                case 6:
                    img.applyFilter([&]() { img.sobelFilter(); });
                    filterStack.push("sobel");
                    menu = false;
                    break;
                case 7:
                    img.applyFilter([&]() { img.pixelSortFilter(); });
                    filterStack.push("pixelsort");
                    menu = false;
                    break;
                case 8:
                    img.applyFilter([&]() { img.whiteningFilter(); });
                    filterStack.push("blanqueamiento");
                    menu = false;
                    break;
                default:
                    cerr << "ERROR: Opcion invalida.\n";
                    return 1;
            }
        } else {
            switch (opcion) {
                case 1:
                    img.applyFilter([&]() { img.redBlueSwapFilter(); });
                    filterStack.push("rojoazul");
                    break;
                case 2:
                    img.applyFilter([&]() { img.blackAndWhiteFilter(); });
                    filterStack.push("blanquinegro");
                    break;
                case 3:
                    img.applyFilter([&]() { img.rotateClockwise(); });
                    filterStack.push("rotado");
                    break;
                case 4:
                    img.applyFilter([&]() { img.invertFilter(); });
                    filterStack.push("invertido");
                    break;
                case 5:
                int r, g, b, r2, g2, b2;

                while (true)
                {
                    cout << "Ingrese el color que deseas cambiar (ej: 255 0 0): ";
                    

                    cin >> r >> g >> b;
                    // Validar entrada
                    if (cin.fail()) {
                        cerr << "ERROR: Entrada invalida.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    // Validar colores
                    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                        cerr << "ERROR: Color fuera de rango (0-255).\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    break; // Salir del bucle si la entrada es válida
                }
                

                cout << "Color seleccionado: " << r << " " << g << " " << b << "\n";

                while (true)
                {
                    cout << "Ingrese el nuevo color (ej: 0 255 0): ";
                    cin >> r2 >> g2 >> b2;

                    // Validar entrada
                    if (cin.fail()) {
                        cerr << "ERROR: Entrada invalida.\n";
                        return 1;
                    }

                    // Validar colores
                    if (r2 < 0 || r2 > 255 || g2 < 0 || g2 > 255 || b2 < 0 || b2 > 255) {
                        cerr << "ERROR: Color fuera de rango (0-255).\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    
                    break; // Salir del bucle si la entrada es válida

                }

                img.applyFilter([&]() {
                    bool found = false;
                    for (int y = 0; y < img.getHeight() && !found; ++y) {
                        for (int x = 0; x < img.getWidth() && !found; ++x) {
                            if (img.getPixel(x, y).toPackedRGB() == Pixel(r, g, b).toPackedRGB()) {
                                img.FloodFill(x, y, Pixel(r, g, b), Pixel(r2, g2, b2));
                                found = true;
                            }
                        }
                    }
                });
                
                filterStack.push("relleno");
                break;

                case 6:
                    img.undoFilter();
                    if (!filterStack.empty()) filterStack.pop();
                    break;
                case 7:
                    menu = false;
                    break;
                default:
                    cerr << "ERROR: Opcion invalida.\n";
                    return 1;
            }
        }
        usedBefore = true;
    }

    if (!fs::exists(saveFolder)) {
        fs::create_directory(saveFolder);
    }
    {
        string composedName = "output";
        stack<string> tempStack = filterStack;
        vector<string> parts;
        while (!tempStack.empty()) {
            parts.push_back(tempStack.top());
            tempStack.pop();
        }
        for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
            composedName += "+" + *it;
        }
        composedName += ".png";
        string outputPath = saveFolder + composedName;
        if (img.save(outputPath)) {
            cout << "Imagen guardada en: " << outputPath << "\n";
        } else {
            cerr << "ERROR al guardar la imagen.\n";
        }
    }

    return 0;
}
