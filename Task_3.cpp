#include<iostream>
#include<cmath>

struct math_vector {
	double x = 0;
	double y = 0;
};

math_vector create_vector_math() {
	math_vector vec_math;
	std::cout << "vector x: ";
	std::cin >> vec_math.x;
	std::cout << "vector y: ";
	std::cin >> vec_math.y;
	return vec_math;
}

void add() {
	math_vector first = create_vector_math();
	math_vector second = create_vector_math();
	std::cout << "\n(" << first.x + second.x << "," << first.y + second.y << ")";
}

void subtract() {
	math_vector first = create_vector_math();
	math_vector second = create_vector_math();
	std::cout << "\n(" << first.x - second.x << "," << first.y - second.y << ")";
}

void scale() {
	double scalar;
	math_vector first = create_vector_math();
	std::cout << "scalar: ";
	std::cin >> scalar;
	std::cout << "\n(" << first.x * scalar << "," << first.y * scalar << ")";
}

void length() {
	math_vector first = create_vector_math();
	std::cout << "\n(" << sqrt(std::pow(first.x, 2) + std::pow(first.y, 2)) << ")";
}

void normalize() {
	math_vector first = create_vector_math();
	double len = sqrt(std::pow(first.x, 2) + std::pow(first.y, 2));
	std::cout << "\n(" << std::pow(first.x / len,2) + std::pow(first.y / len,2) << ")";
}

int main() {
	std::string operation;
	std::cout << "Commands \nadd\nsubtract\nscale\nlength\nnormalize\nEnter: ";
	std::cin >> operation;
	if (operation == "add") {
		add();
	}
	else if (operation == "subtract") {
		subtract();
	}
	else if (operation == "scale") {
		scale();
	}
	else if (operation == "length") {
		length();
	}
	else if (operation == "normalize") {
		normalize();
	}
	else {
		std::cout << "Invalid input";
	}
}