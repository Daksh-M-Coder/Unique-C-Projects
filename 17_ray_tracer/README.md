# Ray Tracer

A 3D rendering engine that uses ray tracing techniques to generate realistic images by simulating the physics of light.

## Description

This project implements a basic ray tracer that can render spheres with realistic lighting effects including shadows, reflections, and specular highlights. The renderer uses mathematical concepts from vector mathematics and optics to simulate how light interacts with objects in a 3D scene.

## Features

- Ray-sphere intersection calculations
- Phong lighting model with ambient, diffuse, and specular components
- Reflections with configurable reflectivity
- Shadow calculation using shadow rays
- PPM image format output
- Configurable scene with multiple light sources
- Depth-limited recursion for performance control

## Compilation

To compile this project, use the following command:

```bash
gcc -o raytracer main.c -lm
```

Note: The `-lm` flag is required to link the math library.

## Usage

Run the program with:

```bash
./raytracer
```

The program will generate a `raytracer_output.ppm` file in the current directory. This file contains the rendered image in PPM format, which can be viewed with most image viewers or converted to other formats.

## How It Works

1. **Scene Setup**: The program initializes a 3D scene with spheres and light sources
2. **Ray Generation**: For each pixel, a ray is cast from the camera through the pixel into the scene
3. **Intersection Testing**: The program checks if the ray intersects with any objects in the scene
4. **Lighting Calculation**: For the closest intersection, lighting is computed using the Phong model
5. **Reflection Handling**: Recursive ray tracing handles reflections up to a maximum depth
6. **Image Output**: The computed colors are saved to a PPM file

## Technical Details

- Uses vector mathematics for all spatial calculations
- Implements the Phong reflection model for realistic lighting
- Handles shadows by casting additional rays toward light sources
- Supports recursive reflections with depth limiting to prevent infinite recursion
- Outputs images in the PPM format (Portable Pixmap)

## Possible Extensions

- Add support for other primitive shapes (planes, triangles)
- Implement refraction for transparent materials
- Add texture mapping support
- Implement acceleration structures for faster ray-object intersection
- Add anti-aliasing for smoother images
- Support for loading scenes from external files

## Requirements

- Standard C library
- Math library (`libm`)

## License

This project is released into the public domain.