//
// Created by Nicolle on 9/5/2022.
//

#include "player.hpp"

#include <limits>
#include "global.hpp"
#include "loading.hpp"

double g_LastCursorPosX;
double g_LastCursorPosY;

bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false;
bool g_MiddleMouseButtonPressed = false;

int cursorMode = GLFW_CURSOR_DISABLED;
float g_CameraTheta = 0.0f;
float g_CameraPhi = 0.0f;
float g_CameraDistance = 3.5f;

float g_ForearmAngleZ = 0.0f;
float g_ForearmAngleX = 0.0f;

float g_TorsoPositionX = 0.0f;
float g_TorsoPositionY = 0.0f;

float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

bool g_isWPressed = false;
bool g_isSPressed = false;
bool g_isAPressed = false;
bool g_isDPressed = false;
bool g_isEPressed = false;
bool g_isGPressed = false;
bool g_isKPressed = false;

bool g_is0Pressed = false;
bool g_is1Pressed = false;
bool g_is2Pressed = false;
bool g_is3Pressed = false;
bool g_is4Pressed = false;
bool g_is5Pressed = false;
bool g_is6Pressed = false;
bool g_is7Pressed = false;
bool g_is8Pressed = false;
bool g_is9Pressed = false;

// Função callback chamada sempre que o usuário aperta algum dos botões do mouse
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_LeftMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_LeftMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_RightMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_RightMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_RightMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_MiddleMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_MiddleMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_MiddleMouseButtonPressed = false;
    }
}

// Função callback chamada sempre que o usuário movimentar o cursor do mouse em
// cima da janela OpenGL.
void CursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
	// Abaixo executamos o seguinte: caso o botão esquerdo do mouse esteja
	// pressionado, computamos quanto que o mouse se movimento desde o último
	// instante de tempo, e usamos esta movimentação para atualizar os
	// parâmetros que definem a posição da câmera dentro da cena virtual.
	// Assim, temos que o usuário consegue controlar a câmera.

	if (cursorMode == GLFW_CURSOR_DISABLED) {
		// Deslocamento do cursor do mouse em x e y de coordenadas de tela!
		auto dx = (float) (xpos - g_LastCursorPosX);
		auto dy = (float) (ypos - g_LastCursorPosY);

		// Atualizamos parâmetros da câmera com os deslocamentos
		g_CameraTheta -= 0.01f * dx;
		g_CameraPhi += 0.01f * dy;

		// Em coordenadas esféricas, o ângulo phi deve ficar entre -pi/2 e +pi/2.
		float phimax = 3.141592f / 2;
		float phimin = -phimax;

		if (g_CameraPhi > phimax) g_CameraPhi = phimax;
		if (g_CameraPhi < phimin) g_CameraPhi = phimin;
	}

	// Atualizamos as variáveis globais para armazenar a posição atual do
	// cursor como sendo a última posição conhecida do cursor.
	g_LastCursorPosX = xpos;
	g_LastCursorPosY = ypos;
}

// Função callback chamada sempre que o usuário movimenta a "rodinha" do mouse.
void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	// Atualizamos a distância da câmera para a origem utilizando a
	// movimentação da "rodinha", simulando um ZOOM.
	g_CameraDistance -= 0.1f * yoffset;

	// Uma câmera look-at nunca pode estar exatamente "em cima" do ponto para
	// onde ela está olhando, pois isto gera problemas de divisão por zero na
	// definição do sistema de coordenadas da câmera. Isto é, a variável abaixo
	// nunca pode ser zero. Versões anteriores deste código possuíam este bug,
	// o qual foi detectado pelo aluno Vinicius Fraga (2017/2).
	const float verysmallnumber = std::numeric_limits<float>::epsilon();
	if (g_CameraDistance < verysmallnumber)
		g_CameraDistance = verysmallnumber;
}

// Definição da função que será chamada sempre que o usuário pressionar alguma
// tecla do teclado. Veja http://www.glfw.org/docs/latest/input_guide.html#input_key
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod) {
	const float delta = 3.141592 / 16; // 22.5 graus, em radianos.

	switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
			return;

		case GLFW_KEY_X:
			if (action == GLFW_PRESS) g_AngleX += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
			return;

		case GLFW_KEY_Y:
			if (action == GLFW_PRESS) g_AngleY += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
			return;

		case GLFW_KEY_Z:
			if (action == GLFW_PRESS) g_AngleZ += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
			return;

		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS) {
				g_AngleX = 0.0f;
				g_AngleY = 0.0f;
				g_AngleZ = 0.0f;
				g_ForearmAngleX = 0.0f;
				g_ForearmAngleZ = 0.0f;
				g_TorsoPositionX = 0.0f;
				g_TorsoPositionY = 0.0f;
			}
			return;

		case GLFW_KEY_P:
			if (action == GLFW_PRESS) g_UsePerspectiveProjection = true;
			return;

		case GLFW_KEY_O:
			if (action == GLFW_PRESS) g_UsePerspectiveProjection = false;
			return;

		case GLFW_KEY_H:
			if (action == GLFW_PRESS) g_ShowInfoText = !g_ShowInfoText;
			return;

		case GLFW_KEY_R:
			if (action == GLFW_PRESS) {
                LoadGenericShaders();
				fprintf(stdout, "Shaders recarregados!\n");
				fflush(stdout);
			}
			return;

		case GLFW_KEY_W:
			g_isWPressed = (action != GLFW_RELEASE);
			return;

		case GLFW_KEY_S:
			g_isSPressed = (action != GLFW_RELEASE);
			return;

		case GLFW_KEY_A:
			g_isAPressed = (action != GLFW_RELEASE);
			return;

		case GLFW_KEY_D:
			g_isDPressed = (action != GLFW_RELEASE);
			return;

        case GLFW_KEY_E:
            g_isEPressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_G:
            g_isGPressed = (action != GLFW_RELEASE);
            return;

		case GLFW_KEY_LEFT_ALT:
		case GLFW_KEY_RIGHT_ALT:
			if (action == GLFW_PRESS) {
				cursorMode = (cursorMode == GLFW_CURSOR_DISABLED) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
				glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
				glfwSetInputMode(window, GLFW_CURSOR, cursorMode);
			}
			return;

        case GLFW_KEY_C:
            if (action == GLFW_PRESS) g_UseFreeCamera = !g_UseFreeCamera;
            return;

		case GLFW_KEY_K:
			g_isKPressed = (action != GLFW_RELEASE);
			return;

        case GLFW_KEY_KP_0:
            g_is0Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_1:
            g_is1Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_2:
            g_is2Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_3:
            g_is3Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_4:
            g_is4Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_5:
            g_is5Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_6:
            g_is6Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_7:
            g_is7Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_8:
            g_is8Pressed = (action != GLFW_RELEASE);
            return;

        case GLFW_KEY_KP_9:
            g_is9Pressed = (action != GLFW_RELEASE);
            return;

		default:
			return;
	}
}

// Definimos o callback para impressão de erros da GLFW no terminal
void ErrorCallback(int error, const char *description) {
	fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
