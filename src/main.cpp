//     Universidade Federal do Rio Grande do Sul
//             Instituto de Informática
//       Departamento de Informática Aplicada
//
//    INF01047 Fundamentos de Computação Gráfica
//               Prof. Eduardo Gastal
//
//                   LABORATÓRIO 5
//

// Arquivos "headers" padrões de C podem ser incluídos em um
// programa C++, sendo necessário somente adicionar o caractere
// "c" antes de seu nome, e remover o sufixo ".h". Exemplo:
//    #include <stdio.h> // Em C
//  vira
//    #include <cstdio> // Em C++
//
#include <cstdlib>

// Headers abaixo são específicos de C++
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

// Headers das bibliotecas OpenGL
#include "glad/glad.h"   // Criação de contexto OpenGL 3.3
#include "GLFW/glfw3.h"  // Criação de janelas do sistema operacional

#include "stb_image.h"

// Headers locais, definidos na pasta "include/"
#include "game.hpp"

int main() {
	// Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
	// sistema operacional, onde poderemos renderizar com OpenGL.
	int success = glfwInit();
	if (!success) {
		fprintf(stderr, "ERROR: glfwInit() failed.\n");
		std::exit(EXIT_FAILURE);
	}

    srand(time(0));

	// Definimos o callback para impressão de erros da GLFW no terminal
	glfwSetErrorCallback(ErrorCallback);

	// Pedimos para utilizar OpenGL versão 3.3 (ou superior)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// Pedimos para utilizar o perfil "core", isto é, utilizaremos somente as
	// funções modernas de OpenGL.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// Criamos uma janela do sistema operacional, com 800 colunas e 600 linhas
	// de pixels, e com título "INF01047 ...".
	GLFWwindow *window;
	window = glfwCreateWindow(mode->width, mode->height, "INF01047 - Penguin Cafe - Trabalho Final", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
		std::exit(EXIT_FAILURE);
	}

    // Definimos a função de callback que será chamada sempre que o usuário
	// pressionar alguma tecla do teclado ...
	glfwSetKeyCallback(window, KeyCallback);
	// ... ou clicar os botões do mouse ...
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// ... ou movimentar o cursor do mouse em cima da janela ...
	glfwSetCursorPosCallback(window, CursorPosCallback);
	// ... ou rolar a "rodinha" do mouse.
	glfwSetScrollCallback(window, ScrollCallback);

	// Indicamos que as chamadas OpenGL deverão renderizar nesta janela
	glfwMakeContextCurrent(window);

	// Carregamento de todas funções definidas por OpenGL 3.3, utilizando a
	// biblioteca GLAD.
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	// Definimos a função de callback que será chamada sempre que a janela for
	// redimensionada, por consequência alterando o tamanho do "framebuffer"
	// (região de memória onde são armazenados os pixels da imagem).
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    int realWidht, realHeight;
    glfwGetFramebufferSize(window, &realWidht, &realHeight);
    FramebufferSizeCallback(window, realWidht, realHeight);
	glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);

	// Imprimimos no terminal informações sobre a GPU do sistema
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *glversion = glGetString(GL_VERSION);
	const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

	// Inicializamos o código para renderização de texto.
	TextRendering_Init();

    // Print loading screen
    glClearColor(0.4f, 0.0f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TextRendering_PrintString(window, "Carregando...", -0.1, 0, 3.5f);
    glfwSwapBuffers(window);

	// Habilitamos o Z-buffer. Veja slides 104-116 do documento Aula_09_Projecoes.pdf.
	glEnable(GL_DEPTH_TEST);

	// Habilitamos o Backface Culling. Veja slides 23-34 do documento Aula_13_Clipping_and_Culling.pdf.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

    auto game = new Game();

    glfwSetTime(0);
    auto prevFrameTime = (float) glfwGetTime();
	// Ficamos em loop, renderizando, até que o usuário feche a janela
	while (!glfwWindowShouldClose(window)) {
        // Compute frame time
        auto frameTime = (float) glfwGetTime();
        float delta = frameTime - prevFrameTime;

        // Run a game step
        game->Step();
        // Render Scene
        game->scene->Render(frameTime, delta);

        TextRendering_ShowFramesPerSecond(window);
		glfwSwapBuffers(window);
		glfwPollEvents();

        prevFrameTime = frameTime;
	}

	// Finalizamos o uso dos recursos do sistema operacional
	glfwTerminate();

	// Fim do programa
	return 0;
}
