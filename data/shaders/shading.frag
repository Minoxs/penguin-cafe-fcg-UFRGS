#version 330 core

#define PHONG   0
#define GOURAUD 1

// Phong
in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texcoords;

// Gouraud
in vec4 colour_vertex;

uniform int shading_id;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D TextureDiffuse;
uniform vec3 Ks;
uniform float SpecularExponent;

out vec4 color;

void main()
{
    if (shading_id == PHONG) {
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

        color.rgb = (firstLight + secondLight);
        color.a = 1.0f;
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
        return;
    }
    if (shading_id == GOURAUD) {
        color = colour_vertex;
        return;
    }
}
