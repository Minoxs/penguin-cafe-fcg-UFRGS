//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "global.hpp"

#include "matrices.h"

// Pilha que guardará as matrizes de modelagem.
std::stack<glm::mat4> g_MatrixStack;

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
float g_ScreenRatio = 1.0f;

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
bool g_UsePerspectiveProjection = true;

bool g_UseFreeCamera = true;

// Variável que controla se o texto informativo será mostrado na tela.
bool g_ShowInfoText = true;

// Número de texturas carregadas pela função LoadTextureImage()
GLuint g_NumLoadedTextures = 0;

// Variáveis que definem um programa de GPU (shaders). Veja função LoadShadersFromFiles().
GLuint p_vertex_shader_id;
GLuint p_fragment_shader_id;
GLuint p_program_id = 0;
GLint p_model_uniform;
GLint p_view_uniform;
GLint p_projection_uniform;
GLint p_object_id_uniform;
GLint p_bbox_min_uniform;
GLint p_bbox_max_uniform;

// Função que pega a matriz M e guarda a mesma no topo da pilha
void PushMatrix(glm::mat4 M) {
	g_MatrixStack.push(M);
}

// Função que remove a matriz atualmente no topo da pilha e armazena a mesma na variável M
void PopMatrix(glm::mat4 &M) {
	if (g_MatrixStack.empty()) {
		M = Matrix_Identity();
	} else {
		M = g_MatrixStack.top();
		g_MatrixStack.pop();
	}
}
