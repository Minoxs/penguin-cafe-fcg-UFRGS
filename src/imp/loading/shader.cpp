//
// Created by Nicolle on 9/5/2022.
//

#include "loading.hpp"

#include "stb_image.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "global.hpp"
#include "rendering.hpp"


// Função auxilar, utilizada pelas duas funções acima. Carrega código de GPU de
// um arquivo GLSL e faz sua compilação.
void loadShader(const char *filename, GLuint shader_id) {
	// Lemos o arquivo de texto indicado pela variável "filename"
	// e colocamos seu conteúdo em memória, apontado pela variável
	// "shader_string".
	std::ifstream file;
	try {
		file.exceptions(std::ifstream::failbit);
		file.open(filename);
	} catch (std::exception &e) {
		fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
		std::exit(EXIT_FAILURE);
	}
	std::stringstream shader;
	shader << file.rdbuf();
	std::string str = shader.str();
	const GLchar *shader_string = str.c_str();
	const GLint shader_string_length = static_cast<GLint>( str.length());

	// Define o código do shader GLSL, contido na string "shader_string"
	glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

	// Compila o código do shader GLSL (em tempo de execução)
	glCompileShader(shader_id);

	// Verificamos se ocorreu algum erro ou "warning" durante a compilação
	GLint compiled_ok;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

	GLint log_length = 0;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

	// Alocamos memória para guardar o log de compilação.
	// A chamada "new" em C++ é equivalente ao "malloc()" do C.
	GLchar *log = new GLchar[log_length];
	glGetShaderInfoLog(shader_id, log_length, &log_length, log);

	// Imprime no terminal qualquer erro ou "warning" de compilação
	if (log_length != 0) {
		std::string output;

		if (!compiled_ok) {
			output += "ERROR: OpenGL compilation of \"";
			output += filename;
			output += "\" failed.\n";
			output += "== Start of compilation log\n";
			output += log;
			output += "== End of compilation log\n";
		} else {
			output += "WARNING: OpenGL compilation of \"";
			output += filename;
			output += "\".\n";
			output += "== Start of compilation log\n";
			output += log;
			output += "== End of compilation log\n";
		}

		fprintf(stderr, "%s", output.c_str());
	}

	// A chamada "delete" em C++ é equivalente ao "free()" do C
	delete[] log;
}

// Carrega um Vertex Shader de um arquivo GLSL. Veja definição de loadShader() abaixo.
GLuint loadVertexShader(const char *filename) {
	// Criamos um identificador (ID) para este shader, informando que o mesmo
	// será aplicado nos vértices.
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	// Carregamos e compilamos o shader
    loadShader(filename, vertexShaderId);

	// Retorna o ID gerado acima
	return vertexShaderId;
}

// Carrega um Fragment Shader de um arquivo GLSL . Veja definição de loadShader() abaixo.
GLuint loadFragmentShader(const char *filename) {
	// Criamos um identificador (ID) para este shader, informando que o mesmo
	// será aplicado nos fragmentos.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Carregamos e compilamos o shader
    loadShader(filename, fragmentShaderId);

	// Retorna o ID gerado acima
	return fragmentShaderId;
}

// Função que carrega os shaders de vértices e de fragmentos que serão
// utilizados para renderização. Veja slides 180-200 do documento Aula_03_Rendering_Pipeline_Grafico.pdf.
void LoadGenericShaders() {
	// Note que o caminho para os arquivos "shader_vertex.glsl" e
	// "shader_fragment.glsl" estão fixados, sendo que assumimos a existência
	// da seguinte estrutura no sistema de arquivos:
	//
	//    + FCG_Lab_01/
	//    |
	//    +--+ bin/
	//    |  |
	//    |  +--+ Release/  (ou Debug/ ou Linux/)
	//    |     |
	//    |     o-- main.exe
	//    |
	//    +--+ src/
	//       |
	//       o-- shader_vertex.glsl
	//       |
	//       o-- shader_fragment.glsl
	//
	p_vertex_shader_id = loadVertexShader("./data/shaders/generic.vert");
	p_fragment_shader_id = loadFragmentShader("./data/shaders/uvmapping.frag");

	// Deletamos o programa de GPU anterior, caso ele exista.
	if (p_program_id != 0)
		glDeleteProgram(p_program_id);

	// Criamos um programa de GPU utilizando os shaders carregados acima.
	p_program_id = CreateGpuProgram(p_vertex_shader_id, p_fragment_shader_id);

	// Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
	// Utilizaremos estas variáveis para enviar dados para a placa de vídeo
	// (GPU)! Veja arquivo "shader_vertex.glsl" e "shader_fragment.glsl".
	p_model_uniform = glGetUniformLocation(p_program_id, "model"); // Variável da matriz "model"
	p_view_uniform = glGetUniformLocation(p_program_id, "view"); // Variável da matriz "view" em shader_vertex.glsl
	p_projection_uniform = glGetUniformLocation(p_program_id, "projection"); // Variável da matriz "projection" em shader_vertex.glsl
	p_bbox_min_uniform = glGetUniformLocation(p_program_id, "bbox_min");
	p_bbox_max_uniform = glGetUniformLocation(p_program_id, "bbox_max");
    gpu_TextureDiffuseUniform = glGetUniformLocation(p_program_id, "TextureDiffuse");

	// Variáveis em "shader_fragment.glsl" para acesso das imagens de textura
	glUseProgram(p_program_id);
	glUseProgram(0);
}

// Reads texture from disk and sends to GPU
// @return Texture ID in the GPU
GLint LoadTexture(const char *filename) {
	printf("Carregando imagem \"%s\"... ", filename);

	// Primeiro fazemos a leitura da imagem do disco
	stbi_set_flip_vertically_on_load(true);
	int width;
	int height;
	int channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);

	if (data == NULL) {
		fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
		std::exit(EXIT_FAILURE);
	}

	printf("OK (%dx%d).\n", width, height);

	// Agora criamos objetos na GPU com OpenGL para armazenar a textura
	GLuint texture_id;
	GLuint sampler_id;
	glGenTextures(1, &texture_id);
	glGenSamplers(1, &sampler_id);

	// Veja slides 95-96 do documento Aula_20_Mapeamento_de_Texturas.pdf
	glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Parâmetros de amostragem da textura.
	glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Agora enviamos a imagem lida do disco para a GPU
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	GLuint textureunit = g_NumLoadedTextures;
	glActiveTexture(GL_TEXTURE0 + textureunit);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindSampler(textureunit, sampler_id);

	stbi_image_free(data);

	g_NumLoadedTextures += 1;

    return (GLint) textureunit;
}
