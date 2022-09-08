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
#include <cmath>
#include <cstdlib>

// Headers abaixo são específicos de C++
#include <string>
#include <fstream>
#include <algorithm>

// Headers das bibliotecas OpenGL
#include "glad/glad.h"   // Criação de contexto OpenGL 3.3
#include "GLFW/glfw3.h"  // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "stb_image.h"

// Headers locais, definidos na pasta "include/"
#include "matrices.h"
#include "global/struct.hpp"
#include "loading/object.hpp"
#include "rendering/text.hpp"
#include "global/variable.hpp"
#include "rendering/window.hpp"
#include "rendering/object.hpp"
#include "rendering/camera.hpp"
#include "player/input.hpp"
#include "player/movement.hpp"

#define SPHERE 0
#define BUNNY  1
#define PLANE  2

int main(int argc, char *argv[]) {
	// Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
	// sistema operacional, onde poderemos renderizar com OpenGL.
	int success = glfwInit();
	if (!success) {
		fprintf(stderr, "ERROR: glfwInit() failed.\n");
		std::exit(EXIT_FAILURE);
	}

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

	// Criamos uma janela do sistema operacional, com 800 colunas e 600 linhas
	// de pixels, e com título "INF01047 ...".
	GLFWwindow *window;
	window = glfwCreateWindow(800, 600, "INF01047 - Seu Cartao - Seu Nome", NULL, NULL);
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
	FramebufferSizeCallback(window, 800, 600); // Forçamos a chamada do callback acima, para definir g_ScreenRatio.

	// Imprimimos no terminal informações sobre a GPU do sistema
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *glversion = glGetString(GL_VERSION);
	const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

	// Carregamos os shaders de vértices e de fragmentos que serão utilizados
	// para renderização. Veja slides 180-200 do documento Aula_03_Rendering_Pipeline_Grafico.pdf.
	//
	LoadShadersFromFiles();

	// Carregamos duas imagens para serem utilizadas como textura
	LoadTextureImage("data/tc-earth_daymap_surface.jpg");      // TextureImage0
	LoadTextureImage("data/tc-earth_nightmap_citylights.gif"); // TextureImage1

	// Construímos a representação de objetos geométricos através de malhas de triângulos
	ObjModel spheremodel("data/sphere.obj");
	ComputeNormals(&spheremodel);
	BuildTrianglesAndAddToVirtualScene(&spheremodel);

	ObjModel bunnymodel("data/bunny.obj");
	ComputeNormals(&bunnymodel);
	BuildTrianglesAndAddToVirtualScene(&bunnymodel);

	ObjModel planemodel("data/plane.obj");
	ComputeNormals(&planemodel);
	BuildTrianglesAndAddToVirtualScene(&planemodel);

	if (argc > 1) {
		ObjModel model(argv[1]);
		BuildTrianglesAndAddToVirtualScene(&model);
	}

	// Inicializamos o código para renderização de texto.
	TextRendering_Init();

	// Habilitamos o Z-buffer. Veja slides 104-116 do documento Aula_09_Projecoes.pdf.
	glEnable(GL_DEPTH_TEST);

	// Habilitamos o Backface Culling. Veja slides 23-34 do documento Aula_13_Clipping_and_Culling.pdf.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	g_CameraTheta = 3.1415f;
    Camera camera = Camera {
        glm::vec4(0.0f, 0.0f, 5.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, -1.0f,0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)
    };

    auto prevFrameTime = (float) glfwGetTime();

	// Ficamos em loop, renderizando, até que o usuário feche a janela
	while (!glfwWindowShouldClose(window)) {
		// Aqui executamos as operações de renderização

		// Definimos a cor do "fundo" do framebuffer como branco.  Tal cor é
		// definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto é:
		// Vermelho, Verde, Azul, Alpha (valor de transparência).
		// Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.
		//
		//           R     G     B     A
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

		glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

        auto nextFrameTime = (float) glfwGetTime();
        float delta = nextFrameTime - prevFrameTime;
        prevFrameTime = nextFrameTime;

		// Enviamos as matrizes "view" e "projection" para a placa de vídeo
		// (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
		// efetivamente aplicadas em todos os pontos.
        ComputeMovement(&camera, delta);
        glm::mat4 view = ComputeCamera(camera);

		glUniformMatrix4fv(p_view_uniform, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(p_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

		// Desenhamos o modelo da esfera
		model = Matrix_Translate(-1.0f, 0.0f, 0.0f)
				* Matrix_Rotate_Z(0.6f)
				* Matrix_Rotate_X(0.2f)
				* Matrix_Rotate_Y(g_AngleY + (float) glfwGetTime() * 0.1f);
		glUniformMatrix4fv(p_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(p_object_id_uniform, SPHERE);
		DrawVirtualObject("sphere");

		// Desenhamos o modelo do coelho
		model = Matrix_Translate(1.0f, 0.0f, 0.0f)
				* Matrix_Rotate_X(g_AngleX + (float) glfwGetTime() * 0.1f);
		glUniformMatrix4fv(p_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(p_object_id_uniform, BUNNY);
		DrawVirtualObject("bunny");

		// Desenhamos o plano do chão
		model = Matrix_Translate(0.0f, -1.1f, 0.0f);
		glUniformMatrix4fv(p_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(p_object_id_uniform, PLANE);
		DrawVirtualObject("plane");

		// Imprimimos na tela os ângulos de Euler que controlam a rotação do
		// terceiro cubo.
		TextRendering_ShowEulerAngles(window);

		// Imprimimos na informação sobre a matriz de projeção sendo utilizada.
		TextRendering_ShowProjection(window);

		// Imprimimos na tela informação sobre o número de quadros renderizados
		// por segundo (frames per second).
		TextRendering_ShowFramesPerSecond(window);

		// O framebuffer onde OpenGL executa as operações de renderização não
		// é o mesmo que está sendo mostrado para o usuário, caso contrário
		// seria possível ver artefatos conhecidos como "screen tearing". A
		// chamada abaixo faz a troca dos buffers, mostrando para o usuário
		// tudo que foi renderizado pelas funções acima.
		// Veja o link: Veja o link: https://en.wikipedia.org/w/index.php?title=Multiple_buffering&oldid=793452829#Double_buffering_in_computer_graphics
		glfwSwapBuffers(window);

		// Verificamos com o sistema operacional se houve alguma interação do
		// usuário (teclado, mouse, ...). Caso positivo, as funções de callback
		// definidas anteriormente usando glfwSet*Callback() serão chamadas
		// pela biblioteca GLFW.
		glfwPollEvents();
	}

	// Finalizamos o uso dos recursos do sistema operacional
	glfwTerminate();

	// Fim do programa
	return 0;
}
