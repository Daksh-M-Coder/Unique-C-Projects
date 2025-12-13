#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 5
#define PI 3.14159265359

// Vector structure
typedef struct {
    double x, y, z;
} Vec3;

// Color structure
typedef struct {
    unsigned char r, g, b;
} Color;

// Ray structure
typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

// Sphere structure
typedef struct {
    Vec3 center;
    double radius;
    Color color;
    int specular;
    double reflective;
} Sphere;

// Light structure
typedef struct {
    Vec3 position;
    Color color;
    double intensity;
} Light;

// Scene objects
Sphere spheres[10];
Light lights[5];
int sphere_count = 0;
int light_count = 0;

// Vector operations
Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 vec3_subtract(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 vec3_multiply(Vec3 v, double scalar) {
    return (Vec3){v.x * scalar, v.y * scalar, v.z * scalar};
}

Vec3 vec3_normalize(Vec3 v) {
    double length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    if (length == 0) return (Vec3){0, 0, 0};
    return (Vec3){v.x/length, v.y/length, v.z/length};
}

double vec3_dot(Vec3 a, Vec3 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

double vec3_length(Vec3 v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Color operations
Color color_multiply(Color c, double factor) {
    Color result;
    result.r = (unsigned char)(c.r * factor > 255 ? 255 : c.r * factor);
    result.g = (unsigned char)(c.g * factor > 255 ? 255 : c.g * factor);
    result.b = (unsigned char)(c.b * factor > 255 ? 255 : c.b * factor);
    return result;
}

Color color_add(Color a, Color b) {
    Color result;
    result.r = (unsigned char)(a.r + b.r > 255 ? 255 : a.r + b.r);
    result.g = (unsigned char)(a.g + b.g > 255 ? 255 : a.g + b.g);
    result.b = (unsigned char)(a.b + b.b > 255 ? 255 : a.b + b.b);
    return result;
}

Color color_scale(Color c, double factor) {
    Color result;
    result.r = (unsigned char)(c.r * factor);
    result.g = (unsigned char)(c.g * factor);
    result.b = (unsigned char)(c.b * factor);
    return result;
}

// Ray-sphere intersection
int intersect_ray_sphere(Ray ray, Sphere sphere, double* t1, double* t2) {
    Vec3 oc = vec3_subtract(ray.origin, sphere.center);
    
    double a = vec3_dot(ray.direction, ray.direction);
    double b = 2.0 * vec3_dot(oc, ray.direction);
    double c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
    
    double discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return 0; // No intersection
    }
    
    *t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    *t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    return 1; // Intersection found
}

// Get sphere normal at point
Vec3 get_sphere_normal(Sphere sphere, Vec3 point) {
    Vec3 normal = vec3_subtract(point, sphere.center);
    return vec3_normalize(normal);
}

// Clamp color values
Color clamp_color(Color c) {
    Color result;
    result.r = c.r > 255 ? 255 : (c.r < 0 ? 0 : c.r);
    result.g = c.g > 255 ? 255 : (c.g < 0 ? 0 : c.g);
    result.b = c.b > 255 ? 255 : (c.b < 0 ? 0 : c.b);
    return result;
}

// Check if point is in shadow
int is_in_shadow(Vec3 point, Light light) {
    Vec3 light_direction = vec3_subtract(light.position, point);
    double light_distance = vec3_length(light_direction);
    light_direction = vec3_normalize(light_direction);
    
    Ray shadow_ray = {vec3_add(point, vec3_multiply(light_direction, 0.001)), light_direction};
    
    for (int i = 0; i < sphere_count; i++) {
        double t1, t2;
        if (intersect_ray_sphere(shadow_ray, spheres[i], &t1, &t2)) {
            if (t1 > 0.001 && t1 < light_distance) {
                return 1; // Point is in shadow
            }
        }
    }
    
    return 0; // Point is not in shadow
}

// Compute lighting at a point
Color compute_lighting(Vec3 point, Vec3 normal, Vec3 view_direction, Sphere sphere) {
    Color final_color = {0, 0, 0};
    
    for (int i = 0; i < light_count; i++) {
        Light light = lights[i];
        
        // Check if point is in shadow
        if (is_in_shadow(point, light)) {
            continue;
        }
        
        // Diffuse lighting
        Vec3 light_direction = vec3_normalize(vec3_subtract(light.position, point));
        double diffuse_intensity = vec3_dot(normal, light_direction);
        if (diffuse_intensity < 0) diffuse_intensity = 0;
        
        Color diffuse = color_scale(sphere.color, diffuse_intensity * light.intensity);
        
        // Specular lighting
        Vec3 reflection = vec3_subtract(
            vec3_multiply(normal, 2 * vec3_dot(light_direction, normal)),
            light_direction
        );
        double specular_intensity = vec3_dot(reflection, view_direction);
        if (specular_intensity > 0) {
            specular_intensity = pow(specular_intensity, sphere.specular);
            Color specular = color_scale((Color){255, 255, 255}, specular_intensity * light.intensity);
            diffuse = color_add(diffuse, specular);
        }
        
        final_color = color_add(final_color, diffuse);
    }
    
    return clamp_color(final_color);
}

// Trace a ray and return color
Color trace_ray(Ray ray, int depth) {
    if (depth >= MAX_DEPTH) {
        return (Color){0, 0, 0}; // Black for maximum depth
    }
    
    double closest_t = 1e308; // Infinity
    int closest_sphere_index = -1;
    
    // Find closest intersection
    for (int i = 0; i < sphere_count; i++) {
        double t1, t2;
        if (intersect_ray_sphere(ray, spheres[i], &t1, &t2)) {
            if (t1 > 0.001 && t1 < closest_t) {
                closest_t = t1;
                closest_sphere_index = i;
            } else if (t2 > 0.001 && t2 < closest_t) {
                closest_t = t2;
                closest_sphere_index = i;
            }
        }
    }
    
    // No intersection found
    if (closest_sphere_index == -1) {
        return (Color){135, 206, 235}; // Sky blue background
    }
    
    // Get intersection point
    Vec3 point = vec3_add(ray.origin, vec3_multiply(ray.direction, closest_t));
    
    // Get surface normal
    Vec3 normal = get_sphere_normal(spheres[closest_sphere_index], point);
    
    // Compute view direction
    Vec3 view_direction = vec3_multiply(ray.direction, -1);
    view_direction = vec3_normalize(view_direction);
    
    // Compute lighting
    Color color = compute_lighting(point, normal, view_direction, spheres[closest_sphere_index]);
    
    // Handle reflection
    double reflectivity = spheres[closest_sphere_index].reflective;
    if (reflectivity > 0 && depth < MAX_DEPTH) {
        // Calculate reflection direction: R = D - 2(D·N)N
        double dot_product = vec3_dot(ray.direction, normal);
        Vec3 reflection_direction = vec3_subtract(
            ray.direction,
            vec3_multiply(normal, 2 * dot_product)
        );
        
        Ray reflected_ray = {vec3_add(point, vec3_multiply(normal, 0.001)), reflection_direction};
        Color reflected_color = trace_ray(reflected_ray, depth + 1);
        
        color = color_add(
            color_scale(color, 1 - reflectivity),
            color_scale(reflected_color, reflectivity)
        );
    }
    
    return clamp_color(color);
}

// Initialize scene
void init_scene() {
    // Add spheres
    spheres[0] = (Sphere){
        {0, -1, 3}, 1, {255, 0, 0}, 500, 0.2 // Red sphere
    };
    spheres[1] = (Sphere){
        {2, 0, 4}, 1, {0, 0, 255}, 500, 0.3 // Blue sphere
    };
    spheres[2] = (Sphere){
        {-2, 0, 4}, 1, {0, 255, 0}, 10, 0.4 // Green sphere
    };
    spheres[3] = (Sphere){
        {0, -5001, 0}, 5000, {255, 255, 0}, 1000, 0.5 // Yellow ground
    };
    sphere_count = 4;
    
    // Add lights
    lights[0] = (Light){
        {0, 2, 0}, {255, 255, 255}, 0.8 // White light
    };
    lights[1] = (Light){
        {2, 1, 0}, {255, 0, 0}, 0.5 // Red light
    };
    light_count = 2;
}

// Save image to PPM file
void save_image(Color* pixels, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }
    
    fprintf(file, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        fputc(pixels[i].r, file);
        fputc(pixels[i].g, file);
        fputc(pixels[i].b, file);
    }
    
    fclose(file);
    printf("Image saved as %s\n", filename);
}

int main() {
    printf("Ray Tracer - Generating 3D scene...\n");
    
    // Initialize scene
    init_scene();
    
    // Allocate pixel buffer
    Color* pixels = malloc(WIDTH * HEIGHT * sizeof(Color));
    if (!pixels) {
        printf("Error: Failed to allocate memory for pixels\n");
        return 1;
    }
    
    // Camera setup
    Vec3 camera_position = {0, 0, 0};
    
    // Render scene
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Convert pixel coordinates to normalized device coordinates
            double ndc_x = (x + 0.5) / WIDTH;
            double ndc_y = (y + 0.5) / HEIGHT;
            
            // Convert to screen space coordinates (-1 to 1)
            double screen_x = 2 * ndc_x - 1;
            double screen_y = 1 - 2 * ndc_y; // Flip Y axis
            
            // Aspect ratio correction
            screen_x *= (double)WIDTH / HEIGHT;
            
            // Create ray direction
            Vec3 ray_direction = vec3_normalize((Vec3){screen_x, screen_y, 1});
            
            // Create ray
            Ray ray = {camera_position, ray_direction};
            
            // Trace ray and get color
            Color color = trace_ray(ray, 0);
            
            // Store pixel
            pixels[y * WIDTH + x] = color;
        }
        
        // Progress indicator
        if (y % (HEIGHT / 10) == 0) {
            printf("Rendering progress: %d%%\n", (y * 100) / HEIGHT);
        }
    }
    
    // Save image
    save_image(pixels, "raytracer_output.ppm");
    
    // Cleanup
    free(pixels);
    
    printf("Ray tracing complete! Image saved as raytracer_output.ppm\n");
    printf("You can view the image with any program that supports PPM format.\n");
    
    return 0;
}