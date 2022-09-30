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

    auto cubeTriangles = new ObjectTriangles("data/objects/cube.obj");

    const float conversion = 3.14159265359f/180.0f;
    ObjectInstance baseCube("", cubeTriangles);
    baseCube.DiffuseTextureID = woodTexture;

    auto ceiling = new ObjectInstance(baseCube);
    ceiling->name = "ceiling";
    ceiling->position = glm::vec4(-0.16f, 7.0f, -2.28f, 1.0f);
    ceiling->rotation = glm::vec4(0.0f * conversion, 0.0f * conversion, 0.0f * conversion, 0.0f);
    ceiling->scale = glm::vec4(27.72f, 0.49f, 27.72f, 0.0f);
    addToScene(ceiling);

    auto floor = new ObjectInstance(baseCube);
    floor->name = "floor";
    floor->position = glm::vec4(-0.16f, -1.0f, -2.28f, 1.0f);
    floor->rotation = glm::vec4(0.0f * conversion, 0.0f * conversion, 0.0f * conversion, 0.0f);
    floor->scale = glm::vec4(27.72f, 0.49f, 27.72f, 0.0f);
    addToScene(floor);

    baseCube.name = "wall00";
    baseCube.position = glm::vec4(6.47f, 6.92f, 22.35f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 14.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(4.53f, 1.02f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall01";
    baseCube.position = glm::vec4(-2.68f, 3.04f, 24.42f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 10.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(5.04f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall02";
    baseCube.position = glm::vec4(-14.27f, 3.04f, 21.9f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, -30.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall03";
    baseCube.position = glm::vec4(-24.35f, 3.04f, 11.82f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, -60.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall04";
    baseCube.position = glm::vec4(-27.88f, 3.04f, -2.29f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, -90.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall05";
    baseCube.position = glm::vec4(-24.35f, 3.04f, -16.40f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 60.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall06";
    baseCube.position = glm::vec4(-14.27f, 3.04f, -26.73f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 30.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall07";
    baseCube.position = glm::vec4(-0.17f, 3.04f, -30.89f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 0.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall08";
    baseCube.position = glm::vec4(13.94f, 3.04f, -26.73f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, -30.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall09";
    baseCube.position = glm::vec4(24.02f, 3.04f, -16.40f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, -60.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall10";
    baseCube.position = glm::vec4(27.55f, 3.04f, -2.29f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, -90.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall11";
    baseCube.position = glm::vec4(24.02f, 3.04f, 11.82f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 60.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall12";
    baseCube.position = glm::vec4(15.45f, 3.04f, 19.88f , 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 16.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(7.56f, 4.9f, 0.50f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

    baseCube.name = "wall-base";
    baseCube.position = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
    baseCube.rotation = glm::vec4(0.0f * conversion, 0.0f * conversion, 0.0f * conversion, 0.0f);
    baseCube.scale = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    addToScene(new ObjectInstance(baseCube));

//    #ifndef NDEBUG
//    ObjectInstance debugObjectInstance("debug_object", cubeTriangles);
//    debugObjectInstance.DiffuseTextureID = woodTexture;
//    auto debugObject = new DebugObject(debugObjectInstance, "CubePosition.txt");
//    debugObject->collider = new Physics::ColliderBox(&debugObject->position, 1.0f, 1.0f, 1.0f);
//    addToScene(debugObject);
//    engine->Add(debugObject->collider);
//    #endif

    auto bunny = new ObjectTriangles("data/objects/bunny.obj");
    auto bunny1 = ObjectInstance("bunny1", glm::vec4(-1.0f, 0.5f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), bunny);
    bunny1.DiffuseTextureID = furTexture;

    // Create specific instance
    player = new Player(bunny1);
    // Add collider
    player->collider = new Physics::ColliderBox(&player->position, player->triangles->bbox_min, player->triangles->bbox_max);
    // Add to the scene and physics engine
    addToScene(player);
    engine->Add(player->collider);

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
    float farplane = -45.0f; // Posição do "far plane"

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
