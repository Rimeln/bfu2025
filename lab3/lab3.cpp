#include <iostream>


int main(){
	setlocale(LC_ALL, "Russian");



	int x,i;
	std::cout << "Enter a number from 0 to 10^9:" << std::endl;
	std::cin >> x;

	std::cout << "Enter the bit number which you need to output:" << std::endl;
	std::cin >> i;



	if ((i < 0) || (i > 32)) {
		std::cerr << "Error: Invalid bit index" << std::endl;
		return 1;
	}



	int bit = (x >> i) & 1;

	std::cout << "The value of the " << i << " bit of the number " << x << ": " << bit << std::endl;

	return 0;
}