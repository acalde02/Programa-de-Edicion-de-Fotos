#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

using namespace std;

bool Image::load(const string &filename)
{
    int w, h, n;
    unsigned char *data = stbi_load(filename.c_str(), &w, &h, &n, 3);
    if (!data) {
        cerr << "Error loading image: " << filename << endl;
        return false;
    }

    width = w;
    height = h;
    pixels.assign(height, vector<Pixel>(width));

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * 3;
            pixels[i][j] = Pixel(data[idx], data[idx + 1], data[idx + 2]);
        }

    stbi_image_free(data);
    return true;
}


bool Image::save(const string &filename)
{
    vector<unsigned char> data(width * height * 3);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * 3;
            data[idx] = pixels[i][j].getR();
            data[idx + 1] = pixels[i][j].getG();
            data[idx + 2] = pixels[i][j].getB();
        }

    if (!stbi_write_png(filename.c_str(), width, height, 3, data.data(), width * 3))
    {
        cerr << "Error saving image: " << filename << endl;
        return false;
    }

    return true;
}


void Image::redBlueSwapFilter()
{
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int r = pixels[i][j].getR();
            int b = pixels[i][j].getB();
            pixels[i][j] = Pixel(b, pixels[i][j].getG(), r);
        }
}


void Image::blackAndWhiteFilter()
{
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int r = pixels[i][j].getR();
            int g = pixels[i][j].getG();
            int b = pixels[i][j].getB();
            int avg = (r + g + b) / 3;
            pixels[i][j] = Pixel(avg, avg, avg);
        }
}

void Image::rotateClockwise() {
    if (width == height) {
        // In-place rotation for square matrix (O(1) space)
        int n = width;
        for (int layer = 0; layer < n / 2; ++layer) {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first; i < last; ++i) {
                int offset = i - first;
                Pixel top = pixels[first][i];

                pixels[first][i] = pixels[n - 1 - i][first];
                pixels[n - 1 - i][first] = pixels[last][n - 1 - i];
                pixels[last][n - 1 - i] = pixels[i][last];
                pixels[i][last] = top;
            }
        }
    } else {
        // Fallback to extra memory for non-square images
        int newWidth = height;
        int newHeight = width;
        vector<vector<Pixel>> rotated(newHeight, vector<Pixel>(newWidth));

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                rotated[x][height - 1 - y] = pixels[y][x];
            }
        }

        pixels = rotated;
        width = newWidth;
        height = newHeight;
    }
} 

void Image::invertFilter()
{
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int r = pixels[i][j].getR();
            int g = pixels[i][j].getG();
            int b = pixels[i][j].getB();
            pixels[i][j] = Pixel(255 - r, 255 - g, 255 - b);
        }
}


void Image::FloodFill(int x, int y, Pixel targetColor, Pixel replacementColor) {
    if (targetColor.toPackedRGB() == replacementColor.toPackedRGB()) return;
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    if (pixels[y][x].toPackedRGB() != targetColor.toPackedRGB()) return;

    stack<pair<int, int>> s;
    s.push({x, y});

    while (!s.empty()) {
        auto [cx, cy] = s.top();
        s.pop();

        if (cx < 0 || cx >= width || cy < 0 || cy >= height) continue;
        if (pixels[cy][cx].toPackedRGB() != targetColor.toPackedRGB()) continue;

        pixels[cy][cx] = replacementColor;

        s.push({cx + 1, cy});
        s.push({cx - 1, cy});
        s.push({cx, cy + 1});
        s.push({cx, cy - 1});
    }
}


void Image::applyFilter(function<void()> filter)
{
    history.push(pixels);
    filter();
}

void Image::undoFilter()
{
    if (history.empty())
        return;

    pixels = history.top();
    history.pop();
}

void Image::sobelFilter() {
    vector<vector<Pixel>> newPixels = pixels;

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},\
        { 1,  2,  1}
    };

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int sumX = 0;
            int sumY = 0;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int px = pixels[i + dx][j + dy].getR(); // Suponemos que está en escala de grises
                    sumX += Gx[dx + 1][dy + 1] * px;
                    sumY += Gy[dx + 1][dy + 1] * px;
                }
            }

            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            magnitude = min(255, max(0, magnitude)); // clamp entre 0-255

            newPixels[i][j] = Pixel(magnitude, magnitude, magnitude);
        }
    }

    pixels = newPixels;

}

int Image::luminosity(const Pixel& p) {
    return (p.r + p.g + p.b) / 3;
}

int Image::partition(vector<Pixel>& row, int low, int high) {
    int pivot = luminosity(row[high]);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (luminosity(row[j]) <= pivot) {
            i++;
            swap(row[i], row[j]);
        }
    }
    swap(row[i + 1], row[high]);
    return i + 1;
}

void Image::quickSort(vector<Pixel>& row, int low, int high) {
    if (low < high) {
        int pi = partition(row, low, high);
        quickSort(row, low, pi - 1);
        quickSort(row, pi + 1, high);
    }
}

void Image::pixelSortFilter() {
    for (int y = 0; y < height; ++y) {
        quickSort(pixels[y], 0, width - 1);
    }
}

void Image::whiteningFilter() {
    // Región de dientes en coordenadas estimadas (ajustar según imagen)
    int x = 220;
    int y = 200;
    int w = 300;
    int h = 100;

    if (x + w > width || y + h > height) {
        cerr << "La región de blanqueamiento está fuera de la imagen.\n";
        return;
    }

    long rSum = 0, gSum = 0, bSum = 0;
    int count = 0;

    // Calcular color promedio
    for (int j = y; j < y + h; ++j) {
        for (int i = x; i < x + w; ++i) {
            Pixel& p = pixels[j][i];
            rSum += p.r;
            gSum += p.g;
            bSum += p.b;
            count++;
        }
    }

    if (count == 0) {
        cerr << "No se pudo calcular el color promedio.\n";
        return;
    }

    int rAvg = rSum / count;
    int gAvg = gSum / count;
    int bAvg = bSum / count;

    cout << "Color promedio en región: R=" << rAvg << " G=" << gAvg << " B=" << bAvg << "\n";

    // Aplicar blanqueamiento sumando brillo
    for (int j = y; j < y + h; ++j) {
        for (int i = x; i < x + w; ++i) {
            Pixel& p = pixels[j][i];
            p.r = min(255, p.r + 40);
            p.g = min(255, p.g + 40);
            p.b = min(255, p.b + 40);
        }
    }
}

Pixel Image::getPixel(int x, int y) const {
    return pixels[y][x];
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

