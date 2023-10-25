#include <stdio.h>
#include "image.h"

int main() {
    char input_filename[100];  // Buffer para o caminho do arquivo de entrada
    char output_filename[100]; // Buffer para o caminho do arquivo de saída
    int choice;

    Image* color_image = NULL;
    Image* gray_image = NULL;

    printf("Selecione uma opção:\n");
    printf("1. Carregar imagem PPM\n");
    printf("2. Converter para tons de cinza e salvar\n");
    printf("3. Sair\n");

    while (1) {
        printf("Opção: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Digite o caminho do arquivo de entrada PPM: ");
            scanf("%s", input_filename);

            color_image = load_from_ppm(input_filename);
            if (color_image == NULL) {
                printf("Erro ao carregar a imagem.\n");
            }
        } else if (choice == 2) {
            if (color_image == NULL) {
                printf("Erro: Carregue uma imagem primeiro.\n");
            } else {
                printf("Digite o caminho do arquivo de saída PPM (tons de cinza): ");
                scanf("%s", output_filename);

                gray_image = create(color_image->rows, color_image->cols, "P2");
                rgb_to_gray(color_image, gray_image);
                write_to_ppm(gray_image, output_filename);
                printf("Imagem em tons de cinza salva em %s.\n", output_filename);
            }
        } else if (choice == 3) {
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    if (color_image != NULL) {
        free_image(color_image);
    }

    if (gray_image != NULL) {
        free_image(gray_image);
    }

    return 0;
}
