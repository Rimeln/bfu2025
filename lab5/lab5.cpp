#include <iostream>
#include <algorithm>


int FirstDigit(int Number) {
	while (Number >= 10) {
		Number /= 10;
	}
	return Number;
}


int ProductNumbers(int Number) {
	if (Number == 0) {
		return 0;
	}
	int Product = 1;
	while (Number > 0) {
		Product *= (Number % 10);
		Number /= 10;
	}
	return Product;
}


bool AllNumbersDifferent(int Number) {
	if (Number < 10) {
		return true;
	}

	bool digits[10] = { false };

	while (Number > 0) {
		int digit = Number % 10;
		if (digits[digit]) {
			return false;
		}
		digits[digit] = true;
		Number /= 10;
	}
	return true;
}


bool ProductNumbers14(int Number) {
	if (Number == 0) {
		return false;
	}

	int Product = 1;
	while (Number > 0) {
		Product *= (Number % 10);
		Number /= 10;
	}
	return (Product % 14 == 0);
}	



int main() {
	setlocale(LC_ALL, "Russian");


	int task;
	std::cout << "Выберите задание:" << std::endl;
	std::cout << "1) Отсортировать по невозрастанию последней цифры числа" << std::endl;
	std::cout << "2) Отсортировать по неубыванию первой цифры числа, произведения цифр числа или самого числа" << std::endl;
	std::cout << "3) Увеличение в матрице всех элементов столбца с наименьшей суммой" << std::endl;
	std::cout << "4) Удалить числа, все цифры которых различны" << std::endl;
	std::cin >> task;
	while (task > 4) {
		std::cout << "Задания под таким номером нет" << std::endl;
		std::cout << "Выберите задание:" << std::endl;
		std::cout << "1) Отсортировать по невозрастанию последней цифры числа" << std::endl;
		std::cout << "2) Отсортировать по неубыванию первой цифры числа, произведения цифр числа или самого числа" << std::endl;
		std::cout << "3) Увеличение в матрице всех элементов столбца с наименьшей суммой" << std::endl;
		std::cout << "4) Удалить числа, все цифры которых различны" << std::endl;
		std::cin >> task;
	}


	if (task == 1) {
		int Elements[10000];
		int NumberElements;
		std::cout << "Введите количество элементов: ";
		std::cin >> NumberElements;

		while (NumberElements > 10000) {
			std::cout << "Количество элементов должно быть не больше 10000" << std::endl;
			std::cout << "Введите количество элементов: ";
			std::cin >> NumberElements;
		}

		std::cout << "Введите последовательность чисел:";
		for (int i = 0; i < NumberElements; i++) {
			std::cin >> Elements[i];
		}

		bool DublicateNumbers = false;
		for (int i = 0; (i < NumberElements) && (!DublicateNumbers); i++) {
			for (int j = i + 1; j < NumberElements; j++) {
				if (Elements[i] == Elements[j]) {
					DublicateNumbers = true;
					break;
				}
			}
		}

		if (DublicateNumbers) {
			for (int i = 0; i < NumberElements - 1; i++) {
				for (int j = 0; j < NumberElements - i - 1; j++) {
					int LastDigit1 = Elements[j] % 10;
					int LastDigit2 = Elements[j + 1] % 10;

					if (LastDigit1 < LastDigit2) {
						std::swap(Elements[j], Elements[j + 1]);
					}
				}
			}
		}

		std::cout << "Отсортированнная6 последовательность:";
		for (int i = 0; i < NumberElements; i++) {
			std::cout << Elements[i] << " ";
		}
	}
	if (task == 2) {
		int Elements[1000];
		int NumberElements;
		std::cout << "Введите количество элементов: ";
		std::cin >> NumberElements;

		while (NumberElements > 1000) {
			std::cout << "Количество элементов должно быть не больше 1000" << std::endl;
			std::cout << "Введите количество элементов: ";
			std::cin >> NumberElements;
		}

		std::cout << "Введите последовательность чисел:";
		for (int i = 0; i < NumberElements; i++) {
			std::cin >> Elements[i];
		}

		for (int i = 0; i < NumberElements - 1; i++) {
			for (int j = 0; j < NumberElements - i - 1; j++) {
				int FirstDigit1 = FirstDigit(Elements[j]);
				int FirstDigit2 = FirstDigit(Elements[j + 1]);
				int ProductNumbers1 = ProductNumbers(Elements[j]);
				int ProductNumbers2 = ProductNumbers(Elements[j + 1]);

				if (FirstDigit1 > FirstDigit2) {
					std::swap(Elements[j], Elements[j + 1]);
				}

				else if (FirstDigit1 == FirstDigit2) {
					if (ProductNumbers1 > ProductNumbers2) {
						std::swap(Elements[j], Elements[j + 1]);
					}
					else if (ProductNumbers1 == ProductNumbers2) {
						if (Elements[j] > Elements[j + 1]) {
							std::swap(Elements[j], Elements[j + 1]);
						}
					}
				}
			}
		}

		std::cout << "Отсортированная последовательность:" << std::endl;
		for (int i = 0; i < NumberElements; i++) {
			std::cout << Elements[i] << " ";
		}
	}
	if (task == 3) {
		int n, m;
		long long Matrix[100][100];


		std::cout << "Введите количество строк матрицы:";
		std::cin >> n;
		std::cout << "Введите количество столбцов матрицы:";
		std::cin >> m;


		while ((n > 100) || (m > 100)) {
			std::cout << "Количество строк и столбцов должно быть не больше 100" << std::endl;
			std::cout << "Введите количество строк матрицы:";
			std::cin >> n;
			std::cout << "Введите количество столбцов матрицы:";
			std::cin >> m;
		}

		std::cout << "Введите элементы матрицы:" << std::endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				std::cin >> Matrix[i][j];
			}
		}

		int MinColumnSum = 1000;
		int MinColumn = 0;
		for (int j = 0; j < m; j++) {
			int ColumnSum = 0;
			for (int i = 0; i < n; i++) {
				ColumnSum += Matrix[i][j];
			}
			if (ColumnSum < MinColumnSum) {
				MinColumnSum = ColumnSum;
				MinColumn = j;
			}
		}

		for (int i = 0; i < n; i++) {
			Matrix[i][MinColumn] += 3;
		}

		std::cout << "Столбец с наименьшей суммой элементов: " << MinColumn + 1 << std::endl;
		std::cout << "Новая матрица: " << std::endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				std::cout << Matrix[i][j]<<" ";
			}
			std::cout << std::endl;
		}
	}
	if (task == 4) {
		int Elements[10000];
		int NumberElements;

		std::cout << "Введите количество элементов: ";
		std::cin >> NumberElements;

		while (NumberElements > 10000) {
			std::cout << "Количество элементов должно быть не больше 10000" << std::endl;
			std::cout << "Введите количество элементов: ";
			std::cin >> NumberElements;
		}

		std::cout << "Введите последовательность чисел:";
		for (int i = 0; i < NumberElements; i++) {
			std::cin >> Elements[i];
		}
		int DeleteNumbers = 0;
		for (int i = 0; i < NumberElements;i++){
			if (!AllNumbersDifferent(Elements[i])) {
				Elements[DeleteNumbers] = Elements[i];
				DeleteNumbers++;
			}
		}

		int DublicateNumbers = DeleteNumbers;
		for (int i = 0; i < DeleteNumbers; i++) {
			if (ProductNumbers14(Elements[i])) {
				for (int j = DublicateNumbers; j > i + 1; j--) {
					Elements[j] = Elements[j - 1];
				}
				Elements[i + 1] = Elements[i];
				DublicateNumbers++;
				i++;
			}
		}
		std::cout << "Отсортированный последовательность:" << std::endl;
		for (int i = 0; i < DublicateNumbers; i++) {
			std::cout << Elements[i] << " ";
		}
	}
	return 0;
}