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
    const float conversion = 3.14159265359f/180.0f;
    // Template
    // auto triangle = new ObjectTriangles("model_path", ID);
    // ObjectInstance instance("name", position, rotation, triangles);
    // addToScene(new ObjectInstance(instance));
    LoadGenericShaders();
    engine = new Physics::Engine();

    // Load all textures and sends to GPU once
    GLint whiteTexture = LoadTexture("data/textures/white.png");
    GLint blueTexture = LoadTexture("data/textures/blue.png");
    GLint woodTexture = LoadTexture("data/textures/wood.jpg");
    GLint outsideScenario = LoadTexture("data/textures/outside.jpg");
    GLint penguinTexture = LoadTexture("data/textures/penguin_player.png");
    GLint chefTexture = LoadTexture("data/textures/penguin_chef.png");
    GLint cashRegisterTexture = LoadTexture("data/textures/cash_register.jpg");
    GLint sofaTexture = LoadTexture("data/textures/sofa.jpg");
    GLint tableTexture = LoadTexture("data/textures/table_wood.jpg");
    GLint wetFloorSignTexture = LoadTexture("data/textures/wet_floor_sign.jpg");
    GLint appleTexture = LoadTexture("data/textures/apple.jpg");
    GLint cakeTexture = LoadTexture("data/textures/carrot_cake.jpg");
    GLint croissantTexture = LoadTexture("data/textures/croissant.jpg");
    GLint barrelTexture = LoadTexture("data/textures/barrel.jpg");
    GLint teaTexture = LoadTexture("data/textures/jug.jpg");

    // Outside
    auto outsideTriangles = new ObjectTriangles("data/objects/outside.obj");
    ObjectInstance outsideCube("outside", outsideTriangles);
    outsideCube.position = glm::vec4(7.42f, 3.11f, 27.39f, 1.0f);
    outsideCube.rotation = glm::vec4(0.0f * conversion, 14.0f * conversion, 0.0f * conversion, 0.0f);
    outsideCube.DiffuseTextureID = outsideScenario;
    addToScene(new ObjectInstance(outsideCube), true);

    auto cubeTriangles = new ObjectTriangles("data/objects/cube.obj");
    ObjectInstance baseCube("", cubeTriangles);
    baseCube.DiffuseTextureID = blueTexture;

    // Iglu
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
    floor->scale = glm::vec4(29.72f, 0.49f, 29.72f, 0.0f);
    addToScene(floor);

    ObjectInstance* auxInstance;

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

    auto IglooColliderPosition = new glm::vec4(-0.2616f, 3.1616f, -2.9877f, 1.0f);
    auto IglooCollider = new Physics::ColliderSphere(IglooColliderPosition, 25.6f);
    IglooCollider->inverted = true;
    engine->Add(IglooCollider);

    // Kitchen
    baseCube.name = "counter-top";
    baseCube.position = glm::vec4(13.44f, -0.58f, 0.6f, 1.0f);
    baseCube.rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    baseCube.scale = glm::vec4(1.8f, 2.0f, 20.71f, 0.0f);
    addToScene(new ObjectInstance(baseCube), true);

    #ifndef NDEBUG
    ObjectInstance debugObjectInstance("debug_object", cubeTriangles);
    debugObjectInstance.DiffuseTextureID = woodTexture;
    debugObjectInstance.scale = glm::vec4(1.5f, 2.0f, 5.0f, 0.0f);
    auto debugObject = new DebugObject(debugObjectInstance, "CubePosition.txt");
    addToScene(debugObject, true);
    #endif

    auto penguinTriangles = new ObjectTriangles("data/objects/penguin.obj");
    ObjectInstance basePenguin("", penguinTriangles);

    // Penguin Chef Mustache
    basePenguin.name = "chef-penguin";
    basePenguin.position = glm::vec4(17.73f, 1.8f, 10.37f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 167.0f * conversion, 0.0f * conversion, 0.0f);
    basePenguin.DiffuseTextureID = chefTexture;

    auto chefWalkingPath = new BezierCurve(glm::vec4(17.73f, 1.8f, 10.37f, 1.0f),
                                           glm::vec4(30.78f, 1.8f, 20.50f, 1.0f),
                                           glm::vec4(8.0f, 1.8f, -23.31f, 1.0f),
                                           glm::vec4(24.27f, 1.8f, -11.22f, 1.0f)
                                           );

    auto leChef = new BezierObject(basePenguin, chefWalkingPath);
    addToScene(leChef, true, 0.85f);

    // Cash Register
    auto cashRegisterPt1Triangles = new ObjectTriangles("data/objects/cash_register_only.obj");
    ObjectInstance cashRegister01("cash-register",
                                  glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f),
                                  glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                                  cashRegisterPt1Triangles);

    cashRegister01.DiffuseTextureID = cashRegisterTexture;

    auto cashRegisterPt2Triangles = new ObjectTriangles("data/objects/cash_register_part.obj");
    ObjectInstance cashRegister02("cash-register-part",
                                  glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f),
                                  glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                                  cashRegisterPt2Triangles);

    cashRegister02.DiffuseTextureID = cashRegisterTexture;

    addToScene(new ObjectInstance(cashRegister01));
    addToScene(new ObjectInstance(cashRegister02));

    // Sofas
    auto sofaTriangles = new ObjectTriangles("data/objects/sofa.obj");
    ObjectInstance baseSofa("", sofaTriangles);
    baseSofa.DiffuseTextureID = sofaTexture;

    baseSofa.name = "sofa01";
    baseSofa.position = glm::vec4(-25.35f, -0.4f, 1.34f , 1.0f);
    baseSofa.scale = glm::vec4(4.0f, 4.0f, 4.0f, 0.0f);
    addToScene(new ObjectInstance(baseSofa), true);

    baseSofa.name = "sofa02";
    baseSofa.position = glm::vec4(-25.35f, -0.4f, -6.31 , 1.0f);
    baseSofa.scale = glm::vec4(4.0f, 4.0f, 4.0f, 0.0f);
    addToScene(new ObjectInstance(baseSofa), true);

    // Tables and NPCs
    basePenguin.DiffuseTextureID = penguinTexture;
    auto tableTriangles = new ObjectTriangles("data/objects/table.obj");
    ObjectInstance baseTable("", tableTriangles);
    baseTable.DiffuseTextureID = tableTexture;

    baseTable.name = "table01";
    baseTable.position = glm::vec4(-15.0f, -0.4f, 14.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc01";
    basePenguin.position = glm::vec4(-15.0, 1.8f, 16.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 90.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table01"), true, 0.85f);

    baseTable.name = "table02";
    baseTable.position = glm::vec4(-15.0f, -0.4f, 6.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc02";
    basePenguin.position = glm::vec4(-15.0, 1.8f, 8.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 90.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table02"), true, 0.85f);

    basePenguin.name = "npc03";
    basePenguin.position = glm::vec4(-15.0, 1.8f, 4.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table02"), true, 0.85f);

    baseTable.name = "table03";
    baseTable.position = glm::vec4(-15.0f, -0.4f, -1.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc04";
    basePenguin.position = glm::vec4(-15.0, 1.8f, -3.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table03"), true, 0.85f);

    baseTable.name = "table04";
    baseTable.position = glm::vec4(-15.0f, -0.4f, -8.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc05";
    basePenguin.position = glm::vec4(-15.0, 1.8f, -6.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 90.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table04"), true, 0.85f);

    baseTable.name = "table05";
    baseTable.position = glm::vec4(-15.0f, -0.4f, -16.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc06";
    basePenguin.position = glm::vec4(-15.0, 1.8f, -18.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table05"), true, 0.85f);

    baseTable.name = "table06";
    baseTable.position = glm::vec4(-3.0f, -0.4f, 14.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc07";
    basePenguin.position = glm::vec4(-3.0, 1.8f, 16.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 90.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table06"), true, 0.85f);

    baseTable.name = "table07";
    baseTable.position = glm::vec4(-3.0f, -0.4f, 5.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc08";
    basePenguin.position = glm::vec4(-3.0, 1.8f, 7.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 90.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table07"), true, 0.85f);

    basePenguin.name = "npc09";
    basePenguin.position = glm::vec4(-3.0, 1.8f, 3.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table07"), true, 0.85f);

    baseTable.name = "table08";
    baseTable.position = glm::vec4(-3.0f, -0.4f, -3.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc10";
    basePenguin.position = glm::vec4(-3.0, 1.8f, -5.0f, -1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table08"), true, 0.85f);

    baseTable.name = "table09";
    baseTable.position = glm::vec4(-3.0f, -0.4f, -11.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc11";
    basePenguin.position = glm::vec4(-3.0, 1.8f, -9.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 90.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table09"), true, 0.85f);

    basePenguin.name = "npc12";
    basePenguin.position = glm::vec4(-3.0, 1.8f, -13.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table09"), true, 0.85f);

    baseTable.name = "table10";
    baseTable.position = glm::vec4(-3.0f, -0.4f, -21.0f , 1.0f);
    baseTable.scale = glm::vec4(3.0f, 3.0f, 3.0f, 0.0f);
    addToScene(new ObjectInstance(baseTable), true);

    basePenguin.name = "npc13";
    basePenguin.position = glm::vec4(-3.0f, 1.8f, -23.0f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, 270.0f * conversion, 0.0f * conversion, 0.0f);
    addToScene(new Customer(basePenguin, "table10"), true, 0.85f);

    // Wet Floot Sign
    auto signTriangles = new ObjectTriangles("data/objects/wet_floor_sign.obj");
    ObjectInstance floorSign("wet-floor-sign", signTriangles);
    floorSign.position = glm::vec4(5.0f, -0.65f, -18.0f, 1.0f);
    floorSign.scale = glm::vec4(4.0f, 4.0f, 4.0f, 0.0f);
    floorSign.DiffuseTextureID = wetFloorSignTexture;
    addToScene(new ObjectInstance(floorSign), true);

    // Barrel
    auto barrelTriangles = new ObjectTriangles("data/objects/barrel.obj");
    ObjectInstance barrel("barrel", barrelTriangles);
    barrel.DiffuseTextureID = barrelTexture;
    addToScene(new ObjectInstance(barrel), true, 0.9f);

    auto barrelPartTriangles = new ObjectTriangles("data/objects/barrel_part.obj");
    ObjectInstance barrelPart("barrel-part", barrelPartTriangles);
    barrelPart.DiffuseTextureID = barrelTexture;
    addToScene(new ObjectInstance(barrelPart));

    // Comidas - Base
    auto appleTriangles = new ObjectTriangles("data/objects/apple.obj");
    ObjectInstance baseApple("", appleTriangles);
    baseApple.DiffuseTextureID = appleTexture;

    auto croissantTriangles = new ObjectTriangles("data/objects/croissant.obj");
    ObjectInstance baseCroissant("", croissantTriangles);
    baseCroissant.DiffuseTextureID = croissantTexture;

    auto cakeTriangles = new ObjectTriangles("data/objects/carrot_cake.obj");
    ObjectInstance baseCake("", cakeTriangles);
    baseCake.DiffuseTextureID = cakeTexture;

    auto teaTriangles = new ObjectTriangles("data/objects/jug.obj");
    ObjectInstance baseTea("", teaTriangles);
    baseTea.DiffuseTextureID = teaTexture;

    /* TODO: Posição para quando as comidas forem servidas
     * table 01: glm::vec4(-15.0f, 2.1f, 14.0f, 1.0f)
     * table 02: glm::vec4(-15.0f, 2.1f, 6.0f, 1.0f)
     * table 03: glm::vec4(-15.0f, 2.1f, -1.0f, 1.0f)
     * table 04: glm::vec4(-15.0f, 2.1f, -8.0f, 1.0f)
     * table 05: glm::vec4(-15.0f, 2.1f, -16.0f, 1.0f)
     * table 06: glm::vec4(-3.0f, 2.1f, 14.0f, 1.0f)
     * table 07: glm::vec4(-3.0f, 2.1f, 5.0f, 1.0f)
     * table 08: glm::vec4(-3.0f, 2.1f, -3.0f, 1.0f)
     * table 09: glm::vec4(-3.0f, 2.1f, -11.0f, 1.0f)
     * table 10: glm::vec4(-3.0f, 2.1f, -21.0f, 1.0f)
    */

    baseApple.name = "exemplar-apple";
    baseApple.position = glm::vec4(13.42f, 1.4f, -2.0f, 1.0f);
    baseApple.rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    baseApple.scale = glm::vec4(13.0f, 13.0f, 13.0f, 0.0f);
    addToScene(new Food(baseApple, 1.0f));

    baseCroissant.name = "exemplar-croissant";
    baseCroissant.position = glm::vec4(13.85f, 1.4f, 3.0f, 1.0f);
    baseCroissant.rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    baseCroissant.scale = glm::vec4(13.0f, 13.0f, 13.0f, 0.0f);
    addToScene(new Food(baseCroissant, 1.0f));

    baseCake.name = "exemplar-cake";
    baseCake.position = glm::vec4(14.0f, 1.4f, -7.0f, 1.0f);
    baseCake.rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    baseCake.scale = glm::vec4(10.0f, 10.0f, 10.0f, 0.0f);
    addToScene(new Food(baseCake, 1.0f));

    baseTea.name = "exemplar-tea";
    baseTea.position = glm::vec4(13.42f, 1.4f, 8.0f, 1.0f);
    baseTea.rotation = glm::vec4(0.0f, 90.0f * conversion, 0.0f, 0.0f);
    baseTea.scale = glm::vec4(5.0f, 5.0f, 5.0f, 0.0f);
    addToScene(new Food(baseTea, 1.0f));

    // Player/Main Penguin
    basePenguin.name = "player";
    basePenguin.position = glm::vec4(3.28f, 1.8, -2.04f, 1.0f);
    basePenguin.rotation = glm::vec4(0.0f * conversion, -90.0f * conversion, 0.0f * conversion, 0.0f);
    basePenguin.DiffuseTextureID = penguinTexture;

    ObjectInstance playerView("player-camera", nullptr);
    playerView.position = glm::vec4(3.28f, 2.8f, -2.04f, 1.0f);
    playerView.rotation = glm::vec4(0.0f * conversion, 0.0f * conversion, 1.0f * conversion, 0.0f);

    player = new Player(
            basePenguin,
            new Camera(playerView)
    );
    // Add to the scene and physics engine
    addToScene(player, true, 0.85f);
    engine->Add(player->hand);

    ObjectInstance camera("camera", glm::vec4(18.9f, 5.89f, -1.79f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), nullptr);
    lookAtCamera = new LookAtCamera(camera, &player->position);
    addToScene(lookAtCamera);
    mainCamera = player->view;
}

void Scene::addToScene(ObjectInstance* object, bool addBoxCollider, float boundingBoxScale) {
    if (addBoxCollider) {
        auto scalingFactor = 1.0f - boundingBoxScale;

        auto collider = new Physics::ColliderBox(
            &object->position,
            object->triangles->bbox_min + (object->triangles->bbox_max - object->triangles->bbox_min) * scalingFactor,
            object->triangles->bbox_max + (object->triangles->bbox_min - object->triangles->bbox_max) * scalingFactor,
            object->scale
        );

        object->collider = collider;
        engine->Add(collider);
    }

    virtualScene[object->name] = object;
}

void Scene::addToScene(Food* food) {
    engine->Add(food->interact);
    engine->Add((Physics::ColliderSphere*) food->collider);
    virtualScene[food->name] = food;
}

void Scene::Render(float time, float delta) {
    if (g_UseFreeCamera) {
        mainCamera = player->view;
    } else {
        mainCamera = lookAtCamera;
    }
    // Aqui executamos as operações de renderização

    // Define default framebuffer colour
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
    float farplane = -60.0f; // Posição do "far plane"

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
