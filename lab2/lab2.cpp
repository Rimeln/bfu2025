#include<iostream>

int main() {

	//1 Задание
	setlocale(LC_ALL, "Russian");

	std::cout << "1 Задание" << std::endl << std::endl << std::endl;

	std::cout << "Введите число от 1000 до 9999:" << std::endl;
	int x;
    std::cin >> x;
	std::cout<< " " << std::endl;
	int s1;
	s1 = x % 10;
	x = x / 10;
	int s2;
	s2 = x % 10;
	x = x / 10;
	int s3;
	s3 = x % 10;
	x = x / 10;
	int s4;
	s4 = x % 10;
	std::cout << s1 << s2 << s3 << s4 << std::endl << std::endl << std::endl << std::endl;
	//2 Задание

	std::cout << "2 Задание" << std::endl << std::endl << std::endl;

	std::cout << "Введите координату x для первой точки от -100 до 100:" << std::endl;
	int x1;
	std::cin >> x1;
	std::cout << "Введите координату y для первой точки от -100 до 100:" << std::endl;
	int y1;
	std::cin >> y1;
	std::cout << "Введите координату x для второй точки от -100 до 100:" << std::endl;
	int x2;
	std::cin >> x2;
	std::cout << "Введите координату y для второй точки от -100 до 100:" << std::endl;
	int y2;
	std::cin >> y2;
	std::cout << " " << std::endl<<std::endl;


	double rt = pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);

	std::cout<< "Расстояние между двумя точками: " << rt << std::endl;


	return 0;
}