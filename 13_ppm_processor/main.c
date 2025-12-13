#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000

// PPM image structure
typedef struct {
    int width;
    int height;
    int max_color;
    unsigned char pixels[MAX_HEIGHT][MAX_WIDTH][3];  // RGB pixels
} PPMImage;

// Function prototypes
int load_ppm(const char* filename, PPMImage* img);
int save_ppm(const char* filename, const PPMImage* img);
void grayscale(PPMImage* img);
void sepia(PPMImage* img);
void invert(PPMImage* img);
void flip_horizontal(PPMImage* img);
void flip_vertical(PPMImage* img);
void adjust_brightness(PPMImage* img, int adjustment);
void print_menu();

int main() {
    PPMImage img;
    char filename[256];
    int choice;
    char continue_operation;
    
    printf("PPM Image Processor\n");
    printf("Supports P3 (ASCII) and P6 (binary) PPM formats\n\n");
    
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {  // Load image
                printf("Enter filename to load: ");
                scanf("%s", filename);
                if (load_ppm(filename, &img)) {
                    printf("Image loaded successfully! Dimensions: %dx%d\n", img.width, img.height);
                } else {
                    printf("Failed to load image!\n");
                }
                break;
            }
            
            case 2: {  // Save image
                printf("Enter filename to save: ");
                scanf("%s", filename);
                if (save_ppm(filename, &img)) {
                    printf("Image saved successfully!\n");
                } else {
                    printf("Failed to save image!\n");
                }
                break;
            }
            
            case 3:  // Grayscale conversion
                grayscale(&img);
                printf("Image converted to grayscale!\n");
                break;
                
            case 4:  // Sepia effect
                sepia(&img);
                printf("Sepia effect applied!\n");
                break;
                
            case 5:  // Invert colors
                invert(&img);
                printf("Colors inverted!\n");
                break;
                
            case 6:  // Flip horizontal
                flip_horizontal(&img);
                printf("Image flipped horizontally!\n");
                break;
                
            case 7:  // Flip vertical
                flip_vertical(&img);
                printf("Image flipped vertically!\n");
                break;
                
            case 8: {  // Adjust brightness
                int adjustment;
                printf("Enter brightness adjustment (-255 to 255): ");
                scanf("%d", &adjustment);
                adjust_brightness(&img, adjustment);
                printf("Brightness adjusted!\n");
                break;
            }
            
            case 9:  // Exit
                printf("Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nContinue? (y/n): ");
        scanf(" %c", &continue_operation);
        if (continue_operation != 'y' && continue_operation != 'Y') {
            break;
        }
        printf("\n");
    }
    
    return 0;
}

// Load PPM image from file
int load_ppm(const char* filename, PPMImage* img) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return 0;
    }
    
    char format[3];
    if (fscanf(file, "%2s", format) != 1) {
        fclose(file);
        return 0;
    }
    
    // Skip comments
    int ch;
    while ((ch = fgetc(file)) == '#') {
        while (fgetc(file) != '\n');
    }
    ungetc(ch, file);
    
    if (fscanf(file, "%d %d %d", &img->width, &img->height, &img->max_color) != 3) {
        fclose(file);
        return 0;
    }
    
    // Validate dimensions
    if (img->width <= 0 || img->height <= 0 || 
        img->width > MAX_WIDTH || img->height > MAX_HEIGHT ||
        img->max_color != 255) {
        fclose(file);
        return 0;
    }
    
    fgetc(file);  // Skip newline
    
    if (strcmp(format, "P3") == 0) {
        // ASCII PPM
        for (int y = 0; y < img->height; y++) {
            for (int x = 0; x < img->width; x++) {
                int r, g, b;
                if (fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                    fclose(file);
                    return 0;
                }
                img->pixels[y][x][0] = (unsigned char)r;
                img->pixels[y][x][1] = (unsigned char)g;
                img->pixels[y][x][2] = (unsigned char)b;
            }
        }
    } else if (strcmp(format, "P6") == 0) {
        // Binary PPM
        for (int y = 0; y < img->height; y++) {
            for (int x = 0; x < img->width; x++) {
                unsigned char pixel[3];
                if (fread(pixel, 1, 3, file) != 3) {
                    fclose(file);
                    return 0;
                }
                img->pixels[y][x][0] = pixel[0];
                img->pixels[y][x][1] = pixel[1];
                img->pixels[y][x][2] = pixel[2];
            }
        }
    } else {
        fclose(file);
        return 0;
    }
    
    fclose(file);
    return 1;
}

// Save PPM image to file
int save_ppm(const char* filename, const PPMImage* img) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    
    // Save as binary PPM (P6)
    fprintf(file, "P6\n%d %d\n%d\n", img->width, img->height, img->max_color);
    
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            unsigned char pixel[3] = {
                img->pixels[y][x][0],
                img->pixels[y][x][1],
                img->pixels[y][x][2]
            };
            fwrite(pixel, 1, 3, file);
        }
    }
    
    fclose(file);
    return 1;
}

// Convert image to grayscale
void grayscale(PPMImage* img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            unsigned char r = img->pixels[y][x][0];
            unsigned char g = img->pixels[y][x][1];
            unsigned char b = img->pixels[y][x][2];
            
            // Weighted average for better grayscale conversion
            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            
            img->pixels[y][x][0] = gray;
            img->pixels[y][x][1] = gray;
            img->pixels[y][x][2] = gray;
        }
    }
}

// Apply sepia effect
void sepia(PPMImage* img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            unsigned char r = img->pixels[y][x][0];
            unsigned char g = img->pixels[y][x][1];
            unsigned char b = img->pixels[y][x][2];
            
            // Sepia transformation
            unsigned char tr = (unsigned char)fmin(255, 0.393 * r + 0.769 * g + 0.189 * b);
            unsigned char tg = (unsigned char)fmin(255, 0.349 * r + 0.686 * g + 0.168 * b);
            unsigned char tb = (unsigned char)fmin(255, 0.272 * r + 0.534 * g + 0.131 * b);
            
            img->pixels[y][x][0] = tr;
            img->pixels[y][x][1] = tg;
            img->pixels[y][x][2] = tb;
        }
    }
}

// Invert colors
void invert(PPMImage* img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            img->pixels[y][x][0] = 255 - img->pixels[y][x][0];  // Red
            img->pixels[y][x][1] = 255 - img->pixels[y][x][1];  // Green
            img->pixels[y][x][2] = 255 - img->pixels[y][x][2];  // Blue
        }
    }
}

// Flip image horizontally
void flip_horizontal(PPMImage* img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width / 2; x++) {
            // Swap pixels
            unsigned char temp[3];
            temp[0] = img->pixels[y][x][0];
            temp[1] = img->pixels[y][x][1];
            temp[2] = img->pixels[y][x][2];
            
            img->pixels[y][x][0] = img->pixels[y][img->width - 1 - x][0];
            img->pixels[y][x][1] = img->pixels[y][img->width - 1 - x][1];
            img->pixels[y][x][2] = img->pixels[y][img->width - 1 - x][2];
            
            img->pixels[y][img->width - 1 - x][0] = temp[0];
            img->pixels[y][img->width - 1 - x][1] = temp[1];
            img->pixels[y][img->width - 1 - x][2] = temp[2];
        }
    }
}

// Flip image vertically
void flip_vertical(PPMImage* img) {
    for (int y = 0; y < img->height / 2; y++) {
        for (int x = 0; x < img->width; x++) {
            // Swap pixels
            unsigned char temp[3];
            temp[0] = img->pixels[y][x][0];
            temp[1] = img->pixels[y][x][1];
            temp[2] = img->pixels[y][x][2];
            
            img->pixels[y][x][0] = img->pixels[img->height - 1 - y][x][0];
            img->pixels[y][x][1] = img->pixels[img->height - 1 - y][x][1];
            img->pixels[y][x][2] = img->pixels[img->height - 1 - y][x][2];
            
            img->pixels[img->height - 1 - y][x][0] = temp[0];
            img->pixels[img->height - 1 - y][x][1] = temp[1];
            img->pixels[img->height - 1 - y][x][2] = temp[2];
        }
    }
}

// Adjust brightness
void adjust_brightness(PPMImage* img, int adjustment) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            for (int c = 0; c < 3; c++) {  // RGB channels
                int new_value = img->pixels[y][x][c] + adjustment;
                if (new_value < 0) new_value = 0;
                if (new_value > 255) new_value = 255;
                img->pixels[y][x][c] = (unsigned char)new_value;
            }
        }
    }
}

// Print menu
void print_menu() {
    printf("===== PPM Image Processor =====\n");
    printf("1. Load image\n");
    printf("2. Save image\n");
    printf("3. Grayscale conversion\n");
    printf("4. Sepia effect\n");
    printf("5. Invert colors\n");
    printf("6. Flip horizontal\n");
    printf("7. Flip vertical\n");
    printf("8. Adjust brightness\n");
    printf("9. Exit\n");
    printf("=============================\n");
}