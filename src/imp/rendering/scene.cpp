//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "rendering.hpp"

#include <matrices.h>
#include "glm/gtc/type_ptr.hpp"
#include <global.hpp>

#include <player.hpp>
#include <loading.hpp>

#define SPHERE 0
#define BUNNY  1
#define PLANE  2
#define PENGUIN 3

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
// (map).  Veja dentro da função BuildTrianglesAndAddToVirtualScene() como que são incluídos
// objetos dentro da variável g_VirtualScene, e veja na função main() como
// estes são acessados.
std::map<std::string, ObjectInstance*> g_VirtualScene;

void addToScene(ObjectInstance* object) {
	g_VirtualScene[object->name] = object;
}

void InitializeScene(char* files[], int length) {
    // Carregamos os shaders de vértices e de fragmentos que serão utilizados
    // para renderização. Veja slides 180-200 do documento Aula_03_Rendering_Pipeline_Grafico.pdf.
    //
    LoadShadersFromFiles();

    // Carregamos duas imagens para serem utilizadas como textura
    LoadTextureImage("data/tc-earth_daymap_surface.jpg");      // TextureImage0
    LoadTextureImage("data/tc-earth_nightmap_citylights.gif"); // TextureImage1

    // Construímos a representação de objetos geométricos através de malhas de triângulos
	auto sphere = new ObjectTriangles("data/sphere.obj", SPHERE);

	ObjectInstance sphere1("planeta1",
						   glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f),
						   glm::vec3(0.2f, 0.0f, 0.6f),
						   sphere);

	ObjectInstance sphere2("planeta2",
						   glm::vec4(-2.0f, 5.0f, 3.0f, 1.0f),
						   glm::vec3(0.2f, 0.0f, 0.6f),
						   sphere);

	addToScene(new RotatingObject(sphere2));
	addToScene(new RotatingObject(sphere1));

    auto bunny = new ObjectTriangles("data/bunny.obj", BUNNY);

    const glm::vec4 playerInitialPosition = glm::vec4(-2.0f, 1.0f, 2.0f, 1.0f);

	auto bunny1 = ObjectInstance("bunny1", glm::vec4(2.0f, 1.0f, 4.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), bunny);
    auto bunny2 = ObjectInstance("player", playerInitialPosition, glm::vec3(0.0f, 0.0f, 0.0f), bunny);

    addToScene(new PlayerObject(bunny2));

    auto planemodel = new ObjectTriangles("data/plane.obj", PLANE);
	auto planemodel1 = ObjectInstance("planemodel1", glm::vec4(0.0f, -1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), planemodel);

	addToScene(new ObjectInstance(planemodel1));
}

void RenderScene(Camera *camera, float time, float delta) {
    // Aqui executamos as operações de renderização

    // Definimos a cor do "fundo" do framebuffer como branco.  Tal cor é
    // definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto é:
    // Vermelho, Verde, Azul, Alpha (valor de transparência).
    // Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.
    //
    //           R     G     B     A
    glClearColor(0.4f, 0.0f, 0.4f, 1.0f);

    // "Pintamos" todos os pixels do framebuffer com a cor definida acima,
    // e também resetamos todos os pixels do Z-buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo
    // os shaders de vértice e fragmentos).
    glUseProgram(p_program_id);

    // Agora computamos a matriz de Projeção.
    glm::mat4 projection;

    // Note que, no sistema de coordenadas da câmera, os planos near e far
    // estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.
    float nearplane = -0.1f;  // Posição do "near plane"
    float farplane = -10.0f; // Posição do "far plane"

    if (g_UsePerspectiveProjection) {
        // Projeção Perspectiva.
        // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.
        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
    } else {
        // Projeção Ortográfica.
        // Para definição dos valores l, r, b, t ("left", "right", "bottom", "top"),
        // PARA PROJEÇÃO ORTOGRÁFICA veja slides 219-224 do documento Aula_09_Projecoes.pdf.
        // Para simular um "zoom" ortográfico, computamos o valor de "t"
        // utilizando a variável g_CameraDistance.
        float t = 1.5f * g_CameraDistance / 2.5f;
        float b = -t;
        float r = t * g_ScreenRatio;
        float l = -r;
        projection = Matrix_Orthographic(l, r, b, t, nearplane, farplane);
    }

    // Enviamos as matrizes "view" e "projection" para a placa de vídeo
    // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
    // efetivamente aplicadas em todos os pontos.
    glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem
    glm::mat4 view = camera->GetViewMatrix();

    glUniformMatrix4fv(p_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(p_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

	for (const std::pair<const std::string, ObjectInstance*> &instance: g_VirtualScene) {
		instance.second->Proc(time, delta);
		instance.second->Draw();
	}
}

