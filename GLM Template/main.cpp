#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

static void printMatrix(glm::mat4& matrix) {
	std::cout << glm::to_string(matrix) << std::endl;
}

static void vectorOperations() {
	glm::vec3 v1(1.0f, 2.0f, 3.0f);
	glm::vec3 v2(4.0f, 5.0f, 6.0f);

	//Example of using glm experimental string cast functions
	std::cout << "v1: " << glm::to_string(v1) << "" << std::endl;
	std::cout << "v2: " << glm::to_string(v2) << "" << std::endl;

	//Calculate and print the result of adding vector v2 to vector v1
	glm::vec3 v_add = v1 + v2;
	std::cout << "v1 + v2: " << glm::to_string(v_add) << "" << std::endl;
	
	
	//Calculate and print the result of subtracting vector v2 to vector v1
	glm::vec3 v_sub = v1 - v2;
	std::cout << "v1 - v2: " << glm::to_string(v_sub) << "" << std::endl;
	
	
	//Calculate and print the result of the dot product between v1 and v2
	float v_dot = glm::dot(v1, v2);
	std::cout << "v1 . v2: " << v_dot << "" << std::endl;
	
	
	//Calculate and print the result of the cross product between v1 and v2
	glm::vec3 v_cross = glm::cross(v1, v2);
	std::cout << "v1 x v2: " << glm::to_string(v_cross) << "" << std::endl;	


}

static void matrixOperations() {
	glm::mat4 model = glm::mat4(1.0f);
	//std::cout << "Model Matrix [0][0]: " << model[0][0] << std::endl;

	//First, apply a translation to the model by (3, 2, -5)
	model = glm::translate(model, glm::vec3(3.0f, 2.0f, -5.0f));


	//Secondly, scale the model by (2, 2, 2)
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));


	//Then, rotate the model 45 degrees around the axis (0, 0, 1)
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));


	//Finally, print the resulting model matrix
	printMatrix(model);


}

int main() {
	vectorOperations();
	matrixOperations();
	std::cout << "Run successful";
	return 0;
}