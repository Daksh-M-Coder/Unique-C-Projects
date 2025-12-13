# PPM Image Processor

## Description
A image processing tool that reads, manipulates, and writes PPM (Portable PixMap) image files. The program supports both ASCII (P3) and binary (P6) PPM formats and provides various image effects including grayscale conversion, sepia toning, color inversion, flipping, and brightness adjustment.

## Features
- Support for P3 (ASCII) and P6 (binary) PPM formats
- Grayscale conversion with weighted averaging
- Sepia tone effect
- Color inversion
- Horizontal and vertical flipping
- Brightness adjustment
- Load and save functionality
- Menu-driven interface

## PPM Format Support
The PPM format is a simple image format consisting of:
- Magic number (P3 for ASCII, P6 for binary)
- Width and height dimensions
- Maximum color value (255 for 8-bit)
- Pixel data (RGB triplets)

## Standard Library Functions Used
- `stdio.h` - For file I/O operations
- `stdlib.h` - For standard library functions
- `string.h` - For string manipulation
- `math.h` - For mathematical functions like `fmin`

## How to Compile and Run

### Compilation
```bash
gcc -o ppm_processor main.c -lm
```
Note: The `-lm` flag is required to link the math library.

### Execution
```bash
./ppm_processor
```

On Windows:
```bash
ppm_processor.exe
```

## How to Use
1. Run the program
2. Select operations from the menu:
   - Load an existing PPM image file
   - Apply image effects (grayscale, sepia, invert, flip, brightness)
   - Save the modified image to a new file
   - Exit the program
3. Images are saved in binary PPM (P6) format for efficiency

## Sample Usage
```
PPM Image Processor
Supports P3 (ASCII) and P6 (binary) PPM formats

===== PPM Image Processor =====
1. Load image
2. Save image
3. Grayscale conversion
4. Sepia effect
5. Invert colors
6. Flip horizontal
7. Flip vertical
8. Adjust brightness
9. Exit
=============================
Enter your choice: 1
Enter filename to load: sample.ppm
Image loaded successfully! Dimensions: 200x150

Enter your choice: 3
Image converted to grayscale!

Enter your choice: 2
Enter filename to save: grayscale_sample.ppm
Image saved successfully!
```

## Image Effects
1. **Grayscale**: Converts image to black and white using weighted RGB averaging
2. **Sepia**: Applies warm brownish tone reminiscent of old photographs
3. **Invert**: Reverses all color values (negative effect)
4. **Flip Horizontal**: Mirrors image along vertical axis
5. **Flip Vertical**: Mirrors image along horizontal axis
6. **Brightness**: Increases or decreases overall image brightness

## Educational Value
This implementation demonstrates:
1. Binary file I/O operations
2. Image data representation and manipulation
3. Color space transformations
4. Matrix operations on 2D data
5. File format parsing and generation
6. Memory management for large data structures