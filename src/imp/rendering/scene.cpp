//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "rendering.hpp"

#include <matrices.h>
#include "glm/gtc/type_ptr.hpp"
#include <global.hpp>

#include <loading.hpp>
#include <utility>

Scene::Scene() {
    // Template
    // auto triangle = new ObjectTriangles("model_path", ID);
    // ObjectInstance instance("name", position, rotation, triangles);
    // addToScene(new ObjectInstance(instance));
    LoadGenericShaders();
    engine = new Physics::Engine();

    // Carregamos duas imagens para serem utilizadas como textura
    GLint earthTexture = LoadTexture("data/textures/earth_texture.jpg");
    GLint woodTexture = LoadTexture("data/textures/wood.jpg");
    GLint furTexture = LoadTexture("data/textures/rabbit_fur.jpg");

    // Construímos a representação de objetos geométricos através de malhas de triângulos
    auto sphere = new ObjectTriangles("data/objects/sphere.obj");

    ObjectInstance sphere1("planeta1",
                           glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f),
                           glm::vec4(0.2f, 0.0f, 0.6f, 0.0f),
                           sphere);
    sphere1.DiffuseTextureID = earthTexture;

    // Create specific instance
    auto planet = new RotatingObject(sphere1);
    // Add collision
    planet->collider = new Physics::CollisionSphere(&planet->position, 1.0f);

    // Add to scene and physics engine
    addToScene(planet);
    engine->AddSphere(planet->collider);

    auto bunny = new ObjectTriangles("data/objects/bunny.obj");

    const glm::vec4 playerInitialPosition = glm::vec4(-2.0f, 1.0f, 2.0f, 1.0f);

    auto planemodel = new ObjectTriangles("data/objects/plane.obj");
    auto planemodel1 = ObjectInstance("planemodel1", glm::vec4(0.0f, -1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), planemodel);

    addToScene(new ObjectInstance(planemodel1));

    #ifndef NDEBUG
    auto debugTriangles = new ObjectTriangles("data/objects/cube.obj");
    ObjectInstance debugObject("debug_object", debugTriangles);
    debugObject.DiffuseTextureID = woodTexture;
    addToScene(new DebugObject(debugObject, "CubePosition.txt"));
    #endif

    auto bunny1 = ObjectInstance("bunny1", playerInitialPosition, glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), bunny);
    bunny1.DiffuseTextureID = furTexture;

    // Create specific instance
    player = new Player(bunny1);
    // Add collider
    player->collider = new Physics::CollisionBox(&player->position, player->triangles->bbox_min, player->triangles->bbox_max);
    // Add to the scene and physics engine
    addToScene(player);
    engine->AddBox(player->collider);

    ObjectInstance camera("camera", glm::vec4(0.0f, 3.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), nullptr);
    lookAtCamera = new LookAtCamera(camera, &player->position);
    addToScene(lookAtCamera);

    mainCamera = player;
}

void Scene::addToScene(ObjectInstance* object) {
    virtualScene[object->name] = object;
}

void Scene::Render(float time, float delta) {
    if (g_UseFreeCamera) {
        mainCamera = player;
    } else {
        mainCamera = lookAtCamera;
    }
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
    glm::mat4 view = mainCamera->GetViewMatrix();

    glUniformMatrix4fv(p_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(p_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

    for (const std::pair<const std::string, ObjectInstance*> &instance: virtualScene) {
        instance.second->Proc(time, delta);
        instance.second->Draw();
    }
}
