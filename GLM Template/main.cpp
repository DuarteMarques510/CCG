#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

const float THRESHOLD = (float)1.0e-5;

static void printMatrix(glm::mat4& matrix) {
	for (uint16_t i = 0; i < 4; i++) {
		for (uint16_t j = 0; j < 4; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
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

static glm::vec3 randomVec() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	return glm::vec3(dist(gen), dist(gen), dist(gen));
}

static glm::mat3 randomMat3() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	glm::mat3 randomMat;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			randomMat[i][j] = dist(gen);
		}
	}
	return randomMat;
}

void exercise1() {

	glm::vec3 i = randomVec();
	std::cout << "i: " << glm::to_string(i) << std::endl;
	glm::vec3 j = randomVec();
	std::cout << "j: " << glm::to_string(j) << std::endl;
	glm::vec3 k = randomVec();
	std::cout << "k: " << glm::to_string(k) << std::endl;
	glm::vec3 left = glm::cross(i, glm::cross(j, k));
	std::cout << "Left: " << glm::to_string(left) << std::endl;
	glm::vec3 right = j * glm::dot(i, k) - k * glm::dot(i, j);
	std::cout << "Right: " << glm::to_string(right) << std::endl;
	assert(glm::all(glm::epsilonEqual(left, right, THRESHOLD)));
	/*if (glm::all(glm::epsilonEqual(left, right, THRESHOLD))) {
		std::cout << "Cross product is associative" << std::endl;
	}
	else {
		std::cout << "Cross product is not associative" << std::endl;
	}*/
}

void exercise2(const glm::vec3 &view, const glm::vec3 &up) {
	glm::vec3 view_normalized = glm::normalize(view);
	glm::vec3 w = glm::normalize(glm::cross(up, view_normalized));
	glm::vec3 u = glm::cross(view_normalized, w);

	for (uint16_t i = 0; i < 3; i++) {
		std::cout << view_normalized[i];
		if (i != 2) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
	}
	for (uint16_t i = 0; i < 3; i++) {
		std::cout << w[i];
		if (i != 2) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
	}
	for (uint16_t i = 0; i < 3; i++) {
		std::cout << u[i];
		if (i != 2) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
	}
}

glm::vec3 exercise3(const glm::vec3 &vector , const glm::vec3 &axis, const double angle) {
	glm::vec3 a = glm::normalize(axis);
	float cosTheta = glm::cos(glm::radians(angle));
	float sinTheta = glm::sin(glm::radians(angle));

	glm::vec3 v_rot = vector * cosTheta
		+ glm::cross(a, vector) * sinTheta
		+ a * glm::dot(a, vector) * (1.0f - cosTheta);

	return v_rot;
}
void testExercise3() {
	glm::vec3 expected = glm::vec3(0.0f, 1.41421f, 0.0f);
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
	float angle = 45.0f;
	glm::vec3 result = exercise3(glm::vec3(1.0f, 1.0f, 0.0f), axis, angle);
	assert(glm::all(glm::epsilonEqual(expected, result, THRESHOLD)));
	/*if (glm::all(glm::epsilonEqual(expected, result, THRESHOLD))) {
		std::cout << "Test passed" << std::endl;
	}
	else {
		std::cout << "Test failed" << std::endl;
	}*/
	
}

glm::mat3 rodriguesRotationMatrix(const glm::vec3 &axis, float angle) {
	glm::mat3 I(1.0f);
	glm::mat3 A(0.0f, -axis.z, axis.y,
				axis.z, 0.0f, -axis.x,
				-axis.y, axis.x, 0.0f);

	float cosTheta = glm::cos(glm::radians(angle));
	float sinTheta = glm::sin(glm::radians(angle));

	glm::mat3 R = I + sinTheta * A + (1.0f - cosTheta) * (A * A);
	return R;
}

void exercise4() {
	glm::vec3 x_axis(1.0f, 0.0f, 0.0f);
	glm::vec3 y_axis(0.0f, 1.0f, 0.0f);
	glm::vec3 z_axis(0.0f, 0.0f, 1.0f);
	float angle = 90.0f;

	glm::mat3 R_x = rodriguesRotationMatrix(x_axis, angle);
	glm::mat3 R_y = rodriguesRotationMatrix(y_axis, angle);
	glm::mat3 R_z = rodriguesRotationMatrix(z_axis, angle);

	std::cout << "Rotation matrix around x-axis:\n" << glm::to_string(R_x) << std::endl;
	std::cout << "Rotation matrix around y-axis:\n" << glm::to_string(R_y) << std::endl;
	std::cout << "Rotation matrix around z-axis:\n" << glm::to_string(R_z) << std::endl;

	glm::vec3 v(1.0f, 1.0f, 1.0f);
	glm::vec3 v_rot_x = R_x * v;
	glm::vec3 v_rot_y = R_y * v;
	glm::vec3 v_rot_z = R_z * v;

	std::cout << "Original vector: " << glm::to_string(v) << std::endl;
	std::cout << "Vector rotated around x-axis: " << glm::to_string(v_rot_x) << std::endl;
	std::cout << "Vector rotated around y-axis: " << glm::to_string(v_rot_y) << std::endl;
	std::cout << "Vector rotated around z-axis: " << glm::to_string(v_rot_z) << std::endl;


}

void exercise5() {

	//Generate random matrices A and B
	//prove that (AB)transposed = B_transposed * A_transposed
	glm::mat3 A = randomMat3();
	glm::mat3 B = randomMat3();
	glm::mat3 left = glm::transpose(A * B);
	glm::mat3 right = glm::transpose(B) * glm::transpose(A);
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			assert(glm::epsilonEqual(left[i][j], right[i][j], THRESHOLD));
		}
	}
	std::cout << "transpose(A*B)=transpose(B)*transpose(A) " << std::endl;

}

void exercise6() {
	//Generate random matrices A and B
	//prove that inverse(A*B) = inverse(B)* inverse(A)
	glm::mat3 A = randomMat3();
	glm::mat3 B = randomMat3();
	glm::mat3 left = glm::inverse(A * B);
	glm::mat3 right = glm::inverse(B) * glm::inverse(A);
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			assert(glm::epsilonEqual(left[i][j], right[i][j], THRESHOLD));
		}
		
	}
	std::cout << "inverse(A*B) = inverse(B) * inverse_A" << std::endl;
}

int main() {
	//vectorOperations();
	//matrixOperations();
	exercise1();
	exercise2(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	for (uint16_t i = 0; i < 10; i++) {
		testExercise3();
	}
	exercise5();
	exercise6();
	
	std::cout << "Run successful";
	return 0;
}