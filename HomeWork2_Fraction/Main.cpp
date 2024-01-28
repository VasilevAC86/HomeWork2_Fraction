# include <iostream>
#include"Fraction.hpp"

int main() {	
	Fraction f1, f2, result; // Объекты класса Fraction для выполнения задания

	// Пользователь заполняет дробь данными с помощью метода fill_in
	std::cout << "\033[93mEnter the fraction:\033[0m" << std::endl;
	f1.fill_in();
			
	std::cout << "\033[96mYou entered the following fraction: \033[0m\033[92m";
	f1.print();	// Выводим введённую пользователем дробь, используя метод print
	output(f1); // по возможности, упрощаем дробь (например, 3/12 в 1/4)
	std::cout << "\033[0m = \033[92m" << f1.real() << "\033[0m" << std::endl;
	f1.proper(); // Проверяем введённую пользователем дробь на её правильность методом proper
		
	//Задача 1: Математические операции над двумя дробями
	std::cout << "\n\n\033[91mTask 1. Mathematical operations on two fractions: \033[0m" << std::endl << std::endl;	
	std::cout << "\033[93mEnter the second fraction:\033[0m" << std::endl;
	f2.fill_in(); // Пользователь заполняет вторую дробь данными	
	std::cout << "\033[96mThe second fraction is: \033[0m\033[92m";
	f2.print(); // Выводим вторую дробь, введённую пользователем, используя метод print
	output(f2);
	std::cout << "\033[0m = \033[92m" << f2.real() << "\033[0m" << std::endl;
	f2.proper(); // Проверяем введённую пользователем дробь на её правильность методом proper
	
	//Для дальнейших вычислений необходимо найти наименьший общий знаменатель дробей
	unsigned long long lcd; // переменная, хранящая значение наименьшего общего знаменателя (Lowest Common Denominator)
	// Если знаменатели дробей одинаковые, то
	if (f1.GetDenominator() == f2.GetDenominator())
		lcd = f1.GetDenominator();
	// иначе вычисляем наименьший общий знаменатель дробей		
	unsigned long long factor = Evklid(f1.GetDenominator(), f2.GetDenominator()); // Реализуем алгоритм Евклида
	if (factor == 1) // Если знаменатели дробей могут разделиться только на 1, то
		lcd = f1.GetDenominator() * f2.GetDenominator(); // общим знаменателем может быть только результат перемножения знаменателей дробей,	
	else // иначе, используя тернарные операторы, возвращаем наименьший из всех возможных общих знаменателей
		lcd = ((f1.GetDenominator() < f2.GetDenominator() ? f1.GetDenominator() : f2.GetDenominator()) / factor) * (f1.GetDenominator() > f2.GetDenominator() ? f1.GetDenominator() : f2.GetDenominator());

	std::cout << "\033[0m\nThe \033[4mcommon denominator\033[0m between the fractions \033[96m";
	f1.print();
	std::cout << " \033[0mand\033[96m ";
	f2.print();
	std::cout << " \033[0mis\033[92m " << lcd << "\033[0m" << std::endl << std::endl;
	// f1 + f2 = result
	result = sum(f1, f2, lcd); // Считаем сумму двух дробей
	output(f1, f2, result, '+'); // Выводим всё, что нужно в консоль
	// f1 - f2 = result
	result = subtraction(f1, f2, lcd); // Считаем разность двух дробей
	output(f1, f2, result, '-');	
	// f1 * f2 = result
	result = multiplication(f1, f2); // Перемножаем дроби
	output(f1, f2, result, '*');	
	// f1 / f2 = result
	result = divide(f1, f2); // Делим дроби
	output(f1, f2, result, '/');	
	
	//Задача 2: Математические операции над дробъю и целым числом
	std::cout << "\n\n\033[91mTask 2. Mathematical operations on fraction and integer: \033[0m" << std::endl << std::endl;
	std::cout << "\033[93mEnter the integer -> \033[0m";
	int n_sourse, n; // Переменные для хранения исходного значения числа, введённого пользователем, и числа, используемого для создания объекта
	std::cin >> n_sourse;	
	if (n_sourse < 0) {
		f2.SetSing(false); // Определяемся со знаком объекта
		n = (-1) * n_sourse;
	}
	else
		n = n_sourse;
	// Преобразовываем целое число в объект дроби
	f2.SetDenominator(f1.GetDenominator());
	f2.SetNumerator(n * f1.GetDenominator());	
	// f1 + n = result
	result = sum(f1, f2, f1.GetDenominator()); 
	output(f1, n_sourse, result, '+');
	// f1 - n = result
	result = subtraction(f1, f2, f1.GetDenominator()); 
	output(f1, n_sourse, result, '-');
	// f1 * n = result
	result = multiplication(f1, f2); 
	output(f1, n_sourse, result, '*');
	// f1 / n = result
	result = divide(f1, f2);
	output(f1, n_sourse, result, '/');

	return 0;
}