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

static void printMatrix(glm::mat3& matrix) {
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

static void printMatrix(glm::dmat3& matrix) {
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
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
	std::cout << "EXERCISE 1: " << std::endl;
	glm::vec3 i = randomVec();
	std::cout << "i: " << glm::to_string(i) << std::endl;
	glm::vec3 j = randomVec();
	std::cout << "j: " << glm::to_string(j) << std::endl;
	glm::vec3 k = randomVec();
	std::cout << "k: " << glm::to_string(k) << std::endl;
	glm::vec3 left = glm::cross(i, glm::cross(j, k));
	std::cout << "Left: " << glm::to_string(left) << std::endl;
	glm::vec3 right = j * glm::dot(i, k) - k * glm::dot(i, j);
	std::cout << "Right: " << glm::to_string(right) << std::endl << std::endl; //double endl to separate exercises
	assert(glm::all(glm::epsilonEqual(left, right, THRESHOLD)));
}

void exercise2(const glm::vec3 &view, const glm::vec3 &up) {
	std::cout << "EXERCISE 2: " << std::endl;
	glm::vec3 view_normalized = glm::normalize(view);
	std::cout << "View normalized: " << glm::to_string(view_normalized) << std::endl;
	glm::vec3 w = glm::normalize(glm::cross(up, view_normalized));
	std::cout << "W: " << glm::to_string(w) << std::endl;
	glm::vec3 u = glm::cross(view_normalized, w);
	std::cout << "U: " << glm::to_string(u) << std::endl;

	glm::mat3 frame;
	frame[0] = view_normalized;
	frame[1] = w;
	frame[2] = u;
	std::cout << "Frame: " << std::endl;
	printMatrix(frame);
	std::cout << std::endl; //give some space between exercises
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
	std::cout << "Test exercise 3 passed" << std::endl;
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
	std::cout << "EXERCISE 4: " << std::endl;
	glm::vec3 x_axis(1.0f, 0.0f, 0.0f);
	glm::vec3 y_axis(0.0f, 1.0f, 0.0f);
	glm::vec3 z_axis(0.0f, 0.0f, 1.0f);
	std::vector<glm::vec3> vectors = { x_axis, y_axis, z_axis };
	float angle = 90.0f;

	glm::vec3 v_x(1.0f, 0.0f, 0.0f);
	glm::vec3 v_y(0.0f, 1.0f, 0.0f);
	glm::vec3 v_z(0.0f, 0.0f, 1.0f);
	std::vector<glm::vec3> axes = { v_x, v_y, v_z };

	std::vector<glm::vec3> results = { glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			std::cout << "Vector: " << glm::to_string(vectors[i]) << std::endl;
			glm::vec3 result = rodriguesRotationMatrix(axes[j], angle) * vectors[i]; // Rotação em torno de X
			std::cout << "After rotation around X-axis: " << glm::to_string(result) << std::endl;
			std::cout << "Expected: " << glm::to_string(results[i * 3 + j]) << std::endl;
			for (uint16_t k = 0; k < 3; k++) {
				assert(glm::epsilonEqual(result[k], results[i * 3 + j][k], THRESHOLD));
			}
			std::cout << std::endl;
		}
	}

}

void exercise5() {
	std::cout << "EXERCISE 5: " << std::endl;
	//Generate random matrices A and B
	//prove that (AB)transposed = B_transposed * A_transposed
	glm::mat3 A = randomMat3();
	std::cout << "Matrix A: " << std::endl;
	printMatrix(A);
	glm::mat3 B = randomMat3();
	std::cout << "Matrix B: " << std::endl;
	printMatrix(B);
	glm::mat3 left = glm::transpose(A * B);
	std::cout << "transpose(A*B): " << std::endl;
	printMatrix(left);
	glm::mat3 right = glm::transpose(B) * glm::transpose(A);
	std::cout << "transpose(B)*transpose(A): " << std::endl;
	printMatrix(right);
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			assert(glm::epsilonEqual(left[i][j], right[i][j], THRESHOLD));
		}
	}
	std::cout << "transpose(A*B)=transpose(B)*transpose(A)\n " << std::endl; //double endl to separate exercises

}

void exercise6() {
	//Generate random matrices A and B
	//prove that inverse(A*B) = inverse(B)* inverse(A)

	std::cout << "EXERCISE 6: " << std::endl;
	glm::dmat3 A = randomMat3();
	std::cout << "Matrix A: " << std::endl;
	printMatrix(A);
	glm::dmat3 B = randomMat3();
	std::cout << "Matrix B: " << std::endl;
	printMatrix(B);
	glm::dmat3 left = glm::inverse(A * B);
	std::cout << "inverse(A*B): " << std::endl;
	printMatrix(left);
	glm::dmat3 right = glm::inverse(B) * glm::inverse(A);
	std::cout << "inverse(B)*inverse(A): " << std::endl;
	printMatrix(right);
	for (uint16_t i = 0; i < 3; i++) {
		for (uint16_t j = 0; j < 3; j++) {
			assert(fabs(left[i][j] - right[i][j] < THRESHOLD));
		}

	}
	std::cout << "inverse(A*B) = inverse(B) * inverse(A)\n" << std::endl; //double endl to separate exercises
}

int main() {
	//vectorOperations();
	//matrixOperations();
	exercise1();
	exercise2(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::cout << "Exercise 3: " << std::endl;
	for (uint16_t i = 0; i < 10; i++) {
		testExercise3();
	}
	std::cout << std::endl; //give some space between exercises
	exercise4();
	exercise5();
	exercise6();
	
	std::cout << "Run successful";
	return 0;
}