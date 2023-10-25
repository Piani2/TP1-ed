#ifndef image_h
#define image_h

typedef struct {
    char type[3];        // Tipo da imagem (P2 ou P3)
    int rows;            // Número de linhas (altura) da imagem
    int cols;            // Número de colunas (largura) da imagem
    unsigned char** data; // Matriz de pixels
} Image;

// Cria uma nova imagem
Image* create(int rows, int cols, char type[]);

// Carrega uma imagem a partir de um arquivo PPM
Image* load_from_ppm(const char* filename);

// Escreve uma imagem em um arquivo PPM
void write_to_ppm(Image* image, const char* filename);

// Converte uma imagem RGB em tons de cinza
void rgb_to_gray(Image* image_rgb, Image* image_gray);

// Libera a memória alocada para a imagem
void free_image(Image* image);

#endif
