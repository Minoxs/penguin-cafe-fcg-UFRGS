#version 330 core

#define PHONG   0
#define GOURAUD 1

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;

uniform int shading_id;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D TextureDiffuse;
uniform vec3 Ks;
uniform float SpecularExponent;

// Phong
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;

// Gouraud
out vec4 colour_vertex;

void main()
{
    gl_Position = projection * view * model * model_coefficients;
    position_world = model * model_coefficients;
    position_model = model_coefficients;
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;
    texcoords = texture_coefficients;

    if (shading_id == PHONG) {
        return;
    }
    if (shading_id == GOURAUD) {
        vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
        vec4 camera_position = inverse(view) * origin;
        vec4 p = position_world;
        vec4 n = normalize(normal);
        vec4 v = normalize(camera_position - p);
        float U = texcoords.x;
        float V = texcoords.y;
        vec3 Kd0 = texture(TextureDiffuse, vec2(U, V)).rgb;

        // HARDCODED LIGHTS
        const vec3 Ikitchen = vec3(1.0f, 1.0f, 1.0f)/1.5;
        const vec4 kitchenLightPos = vec4(5.3, 5.8, -2.3, 1.0);
        const vec3 Ibalada = vec3(0.4, 0.0, 0.0)/1.5;
        const vec4 baladaLightPos = vec4(-19.65, 5.8, -11.50, 1.0);

        vec4 l = normalize(kitchenLightPos - p);
        vec4 h = normalize(v + l);
        vec3 firstLight = Kd0 * max(0.02, dot(n,l)) + Ks * pow(max(0, dot(n, h)), 100.0f - SpecularExponent);
        firstLight *= Ikitchen;

        l = normalize(baladaLightPos - p);
        h = normalize(v + l);
        vec3 secondLight = Kd0 * max(0.02, dot(n,l)) + Ks * pow(max(0, dot(n, h)), 100.0f - SpecularExponent);
        secondLight *= Ibalada;

        colour_vertex.rgb = (firstLight + secondLight);
        colour_vertex.a = 1.0f;
        colour_vertex.rgb = pow(colour_vertex.rgb, vec3(1.0,1.0,1.0)/2.2);
        return;
    }
}
