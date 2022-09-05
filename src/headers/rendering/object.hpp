//
// Created by Nicolle on 9/5/2022.
//

#ifndef PENGUINCAFE_OBJECT_SRC_RENDERING
#define PENGUINCAFE_OBJECT_SRC_RENDERING

#include "global/struct.hpp"

void BuildTrianglesAndAddToVirtualScene(ObjModel *); // Constrói representação de um ObjModel como malha de triângulos para renderização
void ComputeNormals(ObjModel *model); // Computa normais de um ObjModel, caso não existam.
void DrawVirtualObject(const char *object_name);
void PrintObjModelInfo(ObjModel *); // Função para debugging

#endif //PENGUINCAFE_OBJECT_SRC_RENDERING
