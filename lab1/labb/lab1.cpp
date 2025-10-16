#include<iostream>
#include<limits>

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	//Символьные
	char c1;
	c1 = 'A';
	cout << "Тип данных: char" << endl;
	cout << "Размер: " << sizeof(char) << " байт" << endl;
	cout << "Текущее значение: " << c1 << endl;
	cout << "Минимальное значение: " << (int)numeric_limits<char>::min() << endl;
	cout << "Максимальное значение: " << (int)numeric_limits<char>::max() << endl<<endl;

	bool b1;
	b1 = true;
	cout << "Тип данных: bool" << endl;
	cout << "Размер: " << sizeof(bool) << " байт" << endl;
	cout << "Текущее значение: " << b1 << endl;
	cout << "Минимальное значение: " << numeric_limits<bool>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<bool>::max() << endl<<endl;
	
	//Целочисленные

	short s1;
	s1 = -1000;
	cout << "Тип данных: short" << endl;
	cout << "Размер: " << sizeof(short) << " байт" << endl;
	cout << "Текущее значение: " << s1 << endl;
	cout << "Минимальное значение: " << numeric_limits<short>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<short>::max() << endl<<endl;

	int i1;
	i1 = 100000;
	cout << "Тип данных: int" << endl;
	cout << "Размер: " << sizeof(int) << " байт" << endl;
	cout << "Текущее значение:"<< i1 << endl;
	cout << "Минимальное значение: " << numeric_limits<int>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<int>::max() << endl<<endl;

	long long l1;
	l1 = -100000000;
	cout << "Тип данных: long long" << endl;
	cout << "Размер: " << sizeof(long long) << " байт" << endl;
	cout << "Текущее значение: " << l1 << endl;
	cout << "Минимальное значение: " << numeric_limits<long long>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<long long>::max() << endl<<endl;

	//Вещественные

	float f1;
	f1 = 3.14f;
	cout << "Тип данных: float" << endl;
	cout << "Размер: " << sizeof(float) << " байт" << endl;
	cout << "Текущее значение: " << f1 << endl;
	cout << "Минимальное значение: " << numeric_limits<float>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<float>::max() << endl<<endl;
	
	double d1;
	d1 = 3.141351241;
	cout << "Тип данных: double" << endl;
	cout << "Размер: " << sizeof(double) << " байт" << endl;
	cout << "Текущее значение: " << d1 << endl;
	cout << "Минимальное значение: " << numeric_limits<double>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<double>::max() << endl<<endl;

	long double ld1;
	ld1 = 3.1415923131313131313213213;
	cout << "Тип данных: long double" << endl;
	cout << "Размер: " << sizeof(long double) << " байт" << endl;
	cout << "Текущее значение: " << ld1 << endl;
	cout << "Минимальное значение: " << numeric_limits<long double>::min() << endl;
	cout << "Максимальное значение: " << numeric_limits<long double>::max() << endl<< endl;

	int num1 = 234;
	cout << "num1 = " << num1 << endl;
	int result1 = num1 - 10;
	cout << num1 << " - 10 = " << result1 << endl << endl;

	float num2 = 461.12131;
	cout << "num2 = " << num2 << endl;
	float result2 = num2 + 4;
	cout << num2 << " + 4 = " << result2 << endl;


	return 0;
}