//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "rendering.hpp"

#include <matrices.h>
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <global.hpp>

#include <player.hpp>
#include <rendering.hpp>
#include <loading.hpp>

#define SPHERE 0
#define BUNNY  1
#define PLANE  2

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
// (map).  Veja dentro da função BuildTrianglesAndAddToVirtualScene() como que são incluídos
// objetos dentro da variável g_VirtualScene, e veja na função main() como
// estes são acessados.
std::map<std::string, SceneObject*> g_VirtualScene;

void addToScene(SceneObject* object) {
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
	auto sphere = new RenderObject("data/sphere.obj", SPHERE);

	SceneObject sphere1("planeta1",
						glm::vec3(-1.0f, 0.0f, 0.0f),
						glm::vec3(0.2f, 0.0f, 0.6f),
						sphere);

	SceneObject sphere2("planeta2",
						glm::vec3(-2.0f, 5.0f, 3.0f),
						glm::vec3(0.2f, 0.0f, 0.6f),
						sphere);

	addToScene(new RotatingObject(sphere2));
	addToScene(new SceneObject(sphere1));

    auto bunny = new RenderObject("data/bunny.obj", BUNNY);

	auto bunny1 = SceneObject("bunny1", glm::vec3(), glm::vec3(), bunny);

	addToScene(new RotatingObject(bunny1));

    auto planemodel = new RenderObject("data/plane.obj", PLANE);
	auto planemodel1 = SceneObject("planemodel1", glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(), planemodel);

	addToScene(new SceneObject(planemodel1));

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

	for (const std::pair<const std::string, SceneObject*> &instance: g_VirtualScene) {
		instance.second->Proc(time, delta);
		DrawSceneObject(instance.second);
	}
}

