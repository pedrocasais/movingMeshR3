#version 330 core

// Input vertex data
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

// Output data; will be interpolated for each fragment
out vec3 FragPos;
out vec3 Normal;

// Uniform variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Calculate the fragment position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Calculate the normal in world space
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    // Calculate the final position of the vertex
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
