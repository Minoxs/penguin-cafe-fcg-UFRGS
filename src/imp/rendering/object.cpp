//
// Created by Nicolle on 9/5/2022.
//

#include "global.hpp"
#include "player.hpp"

#include "glad/glad.h"
#include "matrices.h"
#include "glm/gtc/type_ptr.hpp"

ObjectInstance::ObjectInstance(const ObjectInstance &object) {
    name = object.name;
    position = object.position;
    rotation = object.rotation;
    scale = object.scale;
    triangles = object.triangles;
    ShadingType = object.ShadingType;
    DiffuseTextureID = object.DiffuseTextureID;
    Ks = object.Ks;
    SpecularExponent = object.SpecularExponent;
    collider = object.collider;
}

ObjectInstance::ObjectInstance(const char* name, ObjectTriangles* triangles) {
    this->name = name;
    this->triangles = triangles;
}

ObjectInstance::ObjectInstance(const char* name, glm::vec4 position, glm::vec4 rotation, ObjectTriangles* triangles) {
    this->name = name;
    this->position = position;
    this->rotation = rotation;
    this->triangles = triangles;
}

void ObjectInstance::Proc(float time, float delta) {
    // Base object is static
}

// Função que desenha um objeto armazenado em g_VirtualScene. Veja definição
// dos objetos na função BuildTrianglesAndAddToVirtualScene().
void ObjectInstance::Draw() {
	// Calcular a Model matrix
	glm::mat4 model = Matrix_Translate(position.x, position.y, position.z)
						* Matrix_Rotate_Z(rotation.z)
						* Matrix_Rotate_X(rotation.x)
						* Matrix_Rotate_Y(rotation.y)
                        * Matrix_Scale(scale.x, scale.y, scale.z);

	// Send model matrix
	glUniformMatrix4fv(gpu_ModelUniform, 1, GL_FALSE, glm::value_ptr(model));

    // Send shading type
    glUniform1i(gpu_ShadingIDUniform, ShadingType);

    // Send diffuse texture ID
	glUniform1i(gpu_TextureDiffuseUniform, DiffuseTextureID);
    glUniform3f(gpu_KsUniform, Ks.x, Ks.y, Ks.z);
    glUniform1f(gpu_SpecularExponentUniform, SpecularExponent);

	// "Ligamos" o VAO. Informamos que queremos utilizar os atributos de
	// vértices apontados pelo VAO criado pela função BuildTrianglesAndAddToVirtualScene(). Veja
	// comentários detalhados dentro da definição de BuildTrianglesAndAddToVirtualScene().
	glBindVertexArray(triangles->vertex_array_object_id);

	// Pedimos para a GPU rasterizar os vértices dos eixos XYZ
	// apontados pelo VAO como linhas. Veja a definição de
	// g_VirtualScene[""] dentro da função BuildTrianglesAndAddToVirtualScene(), e veja
	// a documentação da função glDrawElements() em
	// http://docs.gl/gl3/glDrawElements.
	glDrawElements(
			triangles->rendering_mode,
			triangles->num_indices,
			GL_UNSIGNED_INT,
			(void *) (triangles->first_index * sizeof(GLuint))
	);

	// "Desligamos" o VAO, evitando assim que operações posteriores venham a
	// alterar o mesmo. Isso evita bugs.
	glBindVertexArray(0);
}

BezierObject::BezierObject(const ObjectInstance &object, BezierCurve *curve) : ObjectInstance(object) {
    this->curve = curve;
}

void BezierObject::Proc(float time, float delta) {
    currentPosition += delta/4.0f;

    if (currentPosition >= 1.0f) {
        currentPosition -= 1.0f;
        curve->reverse = !curve->reverse;
    }

    auto nextPosition = curve->calculate(currentPosition);
    auto moved = collider->TryMove(nextPosition - position, true);
    if (!moved) {
        currentPosition -= delta/4.0f;
        timeStuck += delta;
    } else {
        timeStuck = 0.0f;
    }

    if (timeStuck > 1.0f) {
        currentPosition = 1 - currentPosition;
        curve->reverse = !curve->reverse;
    }
}

BezierCurve::BezierCurve(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

glm::vec4 lerp(glm::vec4 p1, glm::vec4 p2, float t) {
    return p1 + t * (p2 - p1);
}

glm::vec4 BezierCurve::calculate(float t) const {
    if (reverse) {
        t = 1 - t;
    }

    glm::vec4 c_12 = lerp(p1, p2, t);
    glm::vec4 c_23 = lerp(p2, p3, t);
    glm::vec4 c_34 = lerp(p3, p4, t);

    glm::vec4 c_123 = lerp(c_12, c_23, t);
    glm::vec4 c_234 = lerp(c_23, c_34, t);

    return lerp(c_123, c_234, t);
}
