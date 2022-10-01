//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "global.hpp"

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
float g_ScreenRatio = 1.0f;

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
bool g_UsePerspectiveProjection = true;

bool g_UseFreeCamera = true;

// Variável que controla se o texto informativo será mostrado na tela.
bool g_ShowInfoText = true;

// Número de texturas carregadas pela função LoadTexture()
GLuint g_NumLoadedTextures = 0;

// Variáveis que definem um programa de GPU (shaders). Veja função LoadGenericShaders().
GLuint p_vertex_shader_id;
GLuint p_fragment_shader_id;
GLuint p_program_id = 0;
GLint p_model_uniform;
GLint p_view_uniform;
GLint p_projection_uniform;
GLint gpu_TextureDiffuseUniform;
GLint gpu_KsUniform;
GLint gpu_SpecularExponentUniform;
