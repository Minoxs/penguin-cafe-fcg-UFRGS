//
// Created by Nicolle on 9/5/2022.
//

#ifndef PENGUINCAFE_OBJECT_SRC_RENDERING
#define PENGUINCAFE_OBJECT_SRC_RENDERING

#include "global.hpp"

void ComputeNormals(ObjectModel* model); 		 // Computa normais de um ObjModel, caso não existam.
RenderObject BuildTriangles(ObjectModel *model, int ID); // Constrói representação de um ObjModel como malha de triângulos para renderização

void DrawSceneObject(SceneObject* object);
void PrintObjModelInfo(ObjectModel* model); // Função para debugging

#endif //PENGUINCAFE_OBJECT_SRC_RENDERING
