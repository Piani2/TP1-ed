#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Image* create(int rows, int cols, char type[]) {
    Image* img = (Image*)malloc(sizeof(Image));

    if (img) {
        strcpy(img->type, type);
        img->rows = rows;
        img->cols = cols;

        img->data = (unsigned char**)malloc(rows * sizeof(unsigned char*));
        for (int i = 0; i < rows; i++) {
            img->data[i] = (unsigned char*)malloc(cols * sizeof(unsigned char));
        }
    }

    return img;
}

Image* load_from_ppm(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char type[3];
    int rows, cols, max_value;

    // Leia o cabeçalho do arquivo PPM
    if (fscanf(file, "%2s", type) != 1 || (strcmp(type, "P2") != 0 && strcmp(type, "P3") != 0)) {
        printf("Formato de arquivo PPM inválido.\n");
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d %d", &cols, &rows, &max_value) != 3 || max_value != 255) {
        printf("Cabeçalho de arquivo PPM inválido.\n");
        fclose(file);
        return NULL;
    }

    // Aloque memória para a estrutura Image
    Image* image = create(rows, cols, type);
    if (image == NULL) {
        printf("Erro ao alocar memória para a imagem.\n");
        fclose(file);
        return NULL;
    }

    // Leia os dados da imagem
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (strcmp(type, "P3") == 0) {
                int r, g, b;
                if (fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                    printf("Erro ao ler os pixels da imagem.\n");
                    fclose(file);
                    free_image(image);
                    return NULL;
                }
                image->data[i][j] = (unsigned char)((r + g + b) / 3);
            } else {
                int pixel;
                if (fscanf(file, "%d", &pixel) != 1) {
                    printf("Erro ao ler os pixels da imagem.\n");
                    fclose(file);
                    free_image(image);
                    return NULL;
                }
                image->data[i][j] = (unsigned char)pixel;
            }
        }
    }

    fclose(file);
    return image;
}

void write_to_ppm(Image* image, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }

    // Escreva o cabeçalho do arquivo PPM
    fprintf(file, "%s\n", image->type);
    fprintf(file, "%d %d\n", image->cols, image->rows);
    fprintf(file, "255\n");  // Valor máximo do pixel

    // Escreva os pixels da imagem
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
            fprintf(file, "%d", image->data[i][j]);
            if (j < image->cols - 1) {
                fprintf(file, " ");
            } else {
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
    printf("Imagem gravada com sucesso em %s.\n", filename);
}

void rgb_to_gray(Image* image_rgb, Image* image_gray) {
    if (image_rgb == NULL || image_gray == NULL) {
        printf("Erro: Imagem de entrada ou de saída ausente.\n");
        return;
    }

    if (strcmp(image_rgb->type, "P3") != 0) {
        printf("Erro: A imagem de entrada deve ser do tipo P3 (colorida).\n");
        return;
    }

    if (strcmp(image_gray->type, "P2") != 0) {
        printf("Erro: A imagem de saída deve ser do tipo P2 (tons de cinza).\n");
        return;
    }

    if (image_rgb->rows != image_gray->rows || image_rgb->cols != image_gray->cols) {
        printf("Erro: As dimensões das imagens de entrada e saída devem ser iguais.\n");
        return;
    }

    for (int i = 0; i < image_rgb->rows; i++) {
        for (int j = 0; j < image_rgb->cols; j++) {
            int r = image_rgb->data[i][j * 3];
            int g = image_rgb->data[i][j * 3 + 1];
            int b = image_rgb->data[i][j * 3 + 2];
            int gray_value = (int)(0.299 * r + 0.587 * g + 0.114 * b);
            image_gray->data[i][j] = (unsigned char)gray_value;
        }
    }

    printf("Conversão para tons de cinza concluída.\n");
}

void free_image(Image* image) {
    for (int i = 0; i < image->rows; i++) {
        free(image->data[i]);
    }
    free(image->data);
    free(image);
}
