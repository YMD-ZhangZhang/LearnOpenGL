#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
	Transform();

public:
	glm::vec3 localPosition;
	glm::vec3 localScale;
	glm::vec3 localRotationEuler;
};