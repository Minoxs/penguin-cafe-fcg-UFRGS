#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureDiffuse;

// Variáveis para controlar como objeto reage com a luz
uniform vec3 Ks;
uniform float SpecularExponent;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = texcoords.x;
    float V = texcoords.y;

    // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
    vec3 Kd0 = texture(TextureDiffuse, vec2(U, V)).rgb;

    // HARDCODED LIGHTS
    const vec3 Ikitchen = vec3(1.0f, 1.0f, 1.0f);
    const vec4 kitchenLightPos = vec4(5.3, 5.8, -2.3, 1.0);
    const vec3 Ibalada = vec3(0.4, 0.0, 0.0);
    const vec4 baladaLightPos = vec4(-19.65, 5.8, -11.50, 1.0);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(kitchenLightPos - p);
    // Vetor que define o sentido da reflexão espetacular ideal
    vec4 r = -normalize(reflect(l, n));

    // Always using a little bit of Kd0 as if it was ambient light
    vec3 firstLight = Kd0 * max(0.02, dot(n,l)) + Ks * pow(max(0, dot(r, v)), SpecularExponent);
    firstLight *= Ikitchen;

    l = normalize(baladaLightPos - p);
    r = -normalize(reflect(l, n));
    vec3 secondLight = Kd0 * max(0.02, dot(n,l)) + Ks * pow(max(0, dot(r, v)), SpecularExponent);
    secondLight *= Ibalada;

    // Taking the average of both lights to keep things a little dimmer
    color.rgb = (firstLight + secondLight)/2;

    // Transparency -- Must be 1
    color.a = 1;

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}
