struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

// Example usage in GLSL
void main() {
    vec3 ambient = material.ambient;
    vec3 diffuse = material.diffuse;
    vec3 specular = material.specular;
    float shininess = material.shininess;

    // Use these in your lighting calculations
}
