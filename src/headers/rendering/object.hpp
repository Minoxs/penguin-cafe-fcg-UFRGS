//
// Created by Nicolle on 9/5/2022.
//
#pragma once
#ifndef PENGUINCAFE_OBJECT_SRC_RENDERING
#define PENGUINCAFE_OBJECT_SRC_RENDERING
#include "rendering.hpp"

void ComputeNormals(ObjectModel* model); 		 // Computa normais de um ObjModel, caso não existam.
void BuildTriangles(ObjectModel *model, ObjectTriangles* object); // Constrói representação de um ObjModel como malha de triângulos para renderização

void DrawSceneObject(ObjectInstance* object);
void PrintObjModelInfo(ObjectModel* model); // Função para debugging

#endif //PENGUINCAFE_OBJECT_SRC_RENDERING
