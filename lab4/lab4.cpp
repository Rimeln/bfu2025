#include <iostream>
#include <random>
#include <string>
#include <Windows.h>

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	std::cout << "Выберите игру 1 или 2:" << std::endl;
	std::cout << "1 - Угадай число" << std::endl;
	std::cout << "2 - Автомат по продаже напитков" << std::endl;
	int game;
	int gamecheck = 0;
	std::cin >> game;
	if ((game == 1) || (game == 2)) {
		gamecheck++;
	}
	while (gamecheck < 1) {
		std::cout << "Такой игры не существует" << std::endl;
		std::cout << "Введите цифру 1 или 2:" << std::endl;
		std::cin >> game;
		if ((game == 1) || (game == 2)) {
			gamecheck++;
		}
	}
	if (game == 1) {
		//Задание 1
		srand(time(0));
		int RandomNumber = rand() % 100 + 1;
		int UserNumber;
		int attempts = 0;
		while (true) {
			std::cout << "Введите число от 1 до 100:" << std::endl;
			std::cin >> UserNumber;
			attempts++;
			if (UserNumber > RandomNumber) {
				std::cout << "Слишком большое число" << std::endl;
			}
			if (UserNumber < RandomNumber) {
				std::cout << "Слишком маленькое число" << std::endl;
			}
			if (UserNumber == RandomNumber) {
				std::cout << "Точно! Ты угадал за " << attempts << " попыток!" << std::endl;
				break;
			}
		}
	}


	if (game == 2) {
		int WaterPrice = 30;//Стоимость воды
		int ColaPrice = 60;//Стоимость колы
		int EnergyDrinkPrice = 90;//Стоимость энергетика
		std::cout << "Выберите напиток(Вода, Кола, Энергетик):" << std::endl;
		std::cout << "Стоимость напитков" << std::endl;
		std::cout << "Вода - " << WaterPrice << " рублей" << std::endl;
		std::cout << "Кола - " << ColaPrice << " рублей" << std::endl;
		std::cout << "Энергетик - " << EnergyDrinkPrice << " рублей" << std::endl;
		std::string Drink;
		std::cin >> Drink;
		int UserMoney;
		int Errorchecking1 = 0;
		if ((Drink == "Вода") || (Drink == "вода") || (Drink == "Кола") || (Drink == "кола") || (Drink == "Энергетик") || (Drink == "энергетик")) {
			Errorchecking1++;
		}
		while (Errorchecking1 < 1) {
			std::cout << "Вы ввели несуществующий напиток" << std::endl;
			std::cin >> Drink;
			if ((Drink == "Вода") || (Drink == "вода") || (Drink == "Кола") || (Drink == "кола") || (Drink == "Энергетик") || (Drink == "энергетик")) {
				Errorchecking1++;
			}
		}
		if ((Drink == "Вода") || (Drink == "вода")) {
			std::cout << "Вы выбрали напиток " << Drink << std::endl;
			std::cout << "Стоимость напитка - " << WaterPrice << " рублей" << std::endl;
			std::cout << "Внесите сумму:" << std::endl;
			std::cin >> UserMoney;
			if (UserMoney > WaterPrice) {
				std::cout << "Вот ваш напиток " << Drink << std::endl;
				std::cout << "Ваша сдача: " << UserMoney - WaterPrice << " рублей" << std::endl;
			}
			if (UserMoney == WaterPrice) {
				std::cout << "Вот ваш напиток " << Drink << std::endl;
			}
			if (UserMoney < WaterPrice) {
				while (UserMoney < WaterPrice) {
					std::cout << "Вы внесли недостаточную сумму" << std::endl;
					int Errorchecking2;
					std::cout << "Введите число 1 или 2:" << std::endl << "1) Внести еще" << std::endl << "2) У меня нет денег" << std::endl;
					std::cin >> Errorchecking2;
					if (Errorchecking2 == 1) {
						std::cout << "Внесите еще " << WaterPrice - UserMoney << " рублей" << std::endl;
						int UserMoney1;
						std::cin >> UserMoney1;
						UserMoney = UserMoney + UserMoney1;
					}
					if (Errorchecking2 == 2) {
						std::cout << "Бомж";
						break;
					}
				}
				if (UserMoney > WaterPrice) {
					std::cout << "Вот ваш напиток " << Drink << std::endl;
					std::cout << "Ваша сдача: " << UserMoney - WaterPrice << " рублей" << std::endl;
				}
				if (UserMoney == WaterPrice) {
					std::cout << "Вот ваш напиток " << Drink << std::endl;
				}
			}
		}
		if ((Drink == "Кола") || (Drink == "кола")) {
			std::cout << "Вы выбрали напиток " << Drink << std::endl;
			std::cout << "Стоимость напитка - " << ColaPrice << " рублей" << std::endl;
			std::cout << "Внесите сумму:" << std::endl;
			std::cin >> UserMoney;
			if (UserMoney > ColaPrice) {
				std::cout << "Вот ваш напиток " << Drink << std::endl;
				std::cout << "Ваша сдача: " << UserMoney - ColaPrice << " рублей" << std::endl;
			}
			if (UserMoney == ColaPrice) {
				std::cout << "Вот ваш напиток " << Drink << std::endl;
			}
			if (UserMoney < ColaPrice) {
				while (UserMoney < ColaPrice) {
					std::cout << "Вы внесли недостаточную сумму" << std::endl;
					int Errorchecking2;
					std::cout << "Введите число 1 или 2:" << std::endl << "1) Внести еще" << std::endl << "2) У меня нет денег" << std::endl;
					std::cin >> Errorchecking2;
					if (Errorchecking2 == 1) {
						std::cout << "Внесите еще " << ColaPrice - UserMoney << " рублей" << std::endl;
						int UserMoney1;
						std::cin >> UserMoney1;
						UserMoney = UserMoney + UserMoney1;
					}
					if (Errorchecking2 == 2) {
						std::cout << "Бомж";
						break;
					}
				}
				if (UserMoney > ColaPrice) {
					std::cout << "Вот ваш напиток " << Drink << std::endl;
					std::cout << "Ваша сдача: " << UserMoney - ColaPrice << " рублей" << std::endl;
				}
				if (UserMoney == ColaPrice) {
					std::cout << "Вот ваш напиток " << Drink << std::endl;
				}
			}
		}
		if ((Drink == "Энергетик") || (Drink == "энергетик")) {
			std::cout << "Вы выбрали напиток " << Drink << std::endl;
			std::cout << "Стоимость напитка - " << EnergyDrinkPrice << " рублей" << std::endl;
			std::cout << "Внесите сумму:" << std::endl;
			std::cin >> UserMoney;
			if (UserMoney > EnergyDrinkPrice) {
				std::cout << "Вот ваш напиток " << Drink << std::endl;
				std::cout << "Ваша сдача: " << UserMoney - EnergyDrinkPrice << " рублей" << std::endl;
			}
			if (UserMoney == EnergyDrinkPrice) {
				std::cout << "Вот ваш напиток " << Drink << std::endl;
			}
			if (UserMoney < EnergyDrinkPrice) {
				while (UserMoney < EnergyDrinkPrice) {
					std::cout << "Вы внесли недостаточную сумму" << std::endl;
					int Errorchecking2;
					std::cout << "Введите число 1 или 2:" << std::endl << "1) Внести еще" << std::endl << "2) У меня нет денег" << std::endl;
					std::cin >> Errorchecking2;
					if (Errorchecking2 == 1) {
						std::cout << "Внесите еще " << EnergyDrinkPrice - UserMoney << " рублей" << std::endl;
						int UserMoney1;
						std::cin >> UserMoney1;
						UserMoney = UserMoney + UserMoney1;
					}
					if (Errorchecking2 == 2) {
						std::cout << "Бомж";
						break;
					}
				}
				if (UserMoney > EnergyDrinkPrice) {
					std::cout << "Вот ваш напиток " << Drink << std::endl;
					std::cout << "Ваша сдача: " << UserMoney - EnergyDrinkPrice << " рублей" << std::endl;
				}
				if (UserMoney == EnergyDrinkPrice) {
					std::cout << "Вот ваш напиток " << Drink << std::endl;
				}
			}
		}
		return 0;
	}
}