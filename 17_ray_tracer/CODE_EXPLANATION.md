# Ray Tracer - Code Explanation

This document provides a detailed explanation of the implementation of the Ray Tracer project.

## Data Structures

### Vec3
Represents a 3D vector with x, y, and z components. Used for positions, directions, and normals in 3D space.

```c
typedef struct {
    double x, y, z;
} Vec3;
```

### Color
Represents an RGB color with red, green, and blue components stored as unsigned chars (0-255).

```c
typedef struct {
    unsigned char r, g, b;
} Color;
```

### Ray
Represents a ray with an origin point and direction vector.

```c
typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;
```

### Sphere
Represents a sphere with position, radius, color, and material properties.

```c
typedef struct {
    Vec3 center;
    double radius;
    Color color;
    int specular;         // Specular exponent for highlights
    double reflective;    // Reflectivity coefficient (0.0 to 1.0)
} Sphere;
```

### Light
Represents a point light source with position, color, and intensity.

```c
typedef struct {
    Vec3 position;
    Color color;
    double intensity;
} Light;
```

## Core Functions

### Vector Operations

#### vec3_add, vec3_subtract, vec3_multiply
Basic vector arithmetic operations for addition, subtraction, and scalar multiplication.

#### vec3_normalize
Normalizes a vector to unit length, essential for direction vectors and surface normals.

#### vec3_dot
Computes the dot product of two vectors, used extensively in lighting calculations.

#### vec3_length
Calculates the magnitude (length) of a vector.

### Color Operations

#### color_multiply, color_add, color_scale
Functions for manipulating colors, including scaling by factors and combining colors.

#### clamp_color
Ensures color component values stay within the valid range (0-255).

### Ray-Sphere Intersection

The `intersect_ray_sphere` function solves the quadratic equation derived from the parametric ray equation and sphere equation:

```
|O + tD - C|² = r²
```

Where O is the ray origin, D is the ray direction, C is the sphere center, r is the radius, and t is the parameter we solve for. Expanding this gives us the quadratic equation:

```
t²(D·D) + 2t(D·(O-C)) + (O-C)·(O-C) - r² = 0
```

We use the quadratic formula to solve for t, checking the discriminant to determine if intersections exist.

### Lighting Calculations

#### compute_lighting
Implements the Phong lighting model with three components:

1. **Ambient Lighting**: Global illumination that affects all surfaces equally
2. **Diffuse Lighting**: Directional lighting based on the angle between the surface normal and light direction
3. **Specular Lighting**: Highlights based on the angle between the reflection vector and view direction

The function also checks for shadows by casting rays from the intersection point toward each light source.

#### is_in_shadow
Casts a shadow ray from a point toward a light source and checks if it intersects any objects before reaching the light.

### Ray Tracing

#### trace_ray
The core recursive function that traces a ray through the scene:

1. Find the closest intersection with any sphere
2. If no intersection, return background color
3. Calculate lighting at the intersection point
4. Handle reflections by recursively tracing reflected rays
5. Combine direct lighting and reflected light based on material properties

The recursion depth is limited by `MAX_DEPTH` to prevent infinite loops and control performance.

## Main Function

The main function orchestrates the rendering process:

1. Initializes the scene with spheres and lights
2. Allocates memory for the pixel buffer
3. For each pixel:
   - Calculates the corresponding ray direction
   - Traces the ray to get the pixel color
   - Stores the color in the pixel buffer
4. Saves the image to a PPM file
5. Cleans up allocated memory

## Mathematical Concepts

### Vector Mathematics
Extensive use of vector operations for:
- Position and direction calculations
- Surface normal computations
- Lighting calculations (dot products)
- Reflection vector calculations

### Quadratic Equations
Used for ray-object intersection testing with analytical solutions.

### Recursive Algorithms
Ray tracing naturally lends itself to recursive implementation for handling reflections and refractions.

### Linear Algebra
Transformations between coordinate systems (world space to camera space to screen space).

## Performance Considerations

1. **Depth Limiting**: Recursion is limited to prevent excessive computation
2. **Early Exit**: Intersection testing stops at the first closer intersection
3. **Memory Management**: Single allocation for the entire image buffer
4. **Efficient Data Structures**: Simple arrays for objects with linear search

## Possible Optimizations

1. **Acceleration Structures**: Implement BVH or octrees for faster intersection testing
2. **Spatial Partitioning**: Divide the scene to reduce intersection tests
3. **Multi-threading**: Parallelize pixel computation across CPU cores
4. **SIMD Instructions**: Use vectorized operations for batch calculations
5. **Adaptive Sampling**: Vary ray count based on scene complexity

## Learning Outcomes

This project demonstrates:
- Advanced use of mathematical concepts in programming
- Implementation of physically-based rendering techniques
- Recursive algorithm design
- Memory management in C
- File I/O for image output
- Structured approach to complex problem solving