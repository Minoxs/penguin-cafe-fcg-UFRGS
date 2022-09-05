//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "global/struct.hpp"
#include <stdexcept>

ObjModel::ObjModel(const char *filename, const char *basepath, bool triangulate) {
	printf("Carregando modelo \"%s\"... ", filename);

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);

	if (!err.empty()) fprintf(stderr, "\n%s\n", err.c_str());

	if (!ret) throw std::runtime_error("Erro ao carregar modelo.");

	printf("OK.\n");
}
