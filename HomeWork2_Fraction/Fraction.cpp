#include<iostream>
#include"Fraction.hpp"

void Fraction::fill_in() {
	char my_Choice; // переменная для хранения выбора пользователя значения знака дроби
	std::cout << "Specify the fraction \033[4msign\033[0m: press \033[91m-\033[0m to negative  \033[4mor\033[0m  press \033[91many other key\033[0m to positive -> ";
	std::cin >> my_Choice;
	if (my_Choice == '-')
		sign_ = false;
	std::cout << "Enter the \033[4mnumerator\033[0m of the fraction -> ";
	std::cin >> numerator_;
	if (numerator_ == 0) { // Имплементизация математического нуля
		denominator_ = 1;
		sign_ = true;
		return;
	}
	std::cout << "Enter the \033[4mdenominator\033[0m of the fraction -> ";	
	std::cin >> denominator_;
	// Выявление и обработка исключения (нулевой знаменатель)
	try { 
		if (denominator_ == 0)
			throw std::exception("\n\033[91m!!!It's impossible to create a fraction with a zero denominator!!!\033[0m");
	}
	catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
		while (denominator_ <= 0) {
			std::cout << "Enter the \033[4mdenominator\033[0m one more time -> ";
			std::cin >> denominator_;
		}
	}		
}

Fraction sum(const Fraction& obj1, const Fraction& obj2, const unsigned long long lcd) {
	Fraction result; // новый объект класса (результата вычисления)
	result.denominator_ = lcd;
	if ((obj1.sign_ && obj2.sign_) || (obj1.sign_ == false && obj2.sign_ == false)) { // Блок вычислений, когда обе дроби однознаковые			
		result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) + obj2.numerator_ * (lcd / obj2.denominator_);
		if (obj1.sign_ == false)
			result.sign_ = false;
		return result;
	}	
	if (obj1.sign_) { // Блок вычислений, когда только первая дробь положительная
		if (obj2.numerator_*(lcd/obj2.denominator_) <= obj1.numerator_*(lcd/obj1.denominator_))
			result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) - obj2.numerator_ * (lcd / obj2.denominator_);
		else {
			result.numerator_ = obj2.numerator_ * (lcd / obj2.denominator_) - obj1.numerator_ * (lcd / obj1.denominator_);
			result.sign_ = false;
		}
		return result;
	}	
	// Блок вычислений, когда только вторая дробь положительная
	if (obj1.numerator_*(lcd/obj1.denominator_) <= obj2.numerator_*(lcd/obj2.denominator_))
		result.numerator_ = obj2.numerator_ * (lcd / obj2.denominator_) - obj1.numerator_ * (lcd / obj1.denominator_);
	else {
		result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) - obj2.numerator_ * (lcd / obj2.denominator_);
		result.sign_ = false;
	}
	return result;	
}

Fraction subtraction(const Fraction& obj1, const Fraction& obj2, const unsigned long long lcd) {
	Fraction result; // новый объект класса (результата вычисления)
	result.denominator_ = lcd;
	if (obj1.sign_ && obj2.sign_) { // Блок вычислений, когда обе дроби положительные
		if (obj1.numerator_*(lcd/obj1.denominator_) >= obj2.numerator_*(lcd/obj2.denominator_))
			result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) - obj2.numerator_ * (lcd / obj2.denominator_);
		else {
			result.numerator_ = obj2.numerator_ * (lcd / obj2.denominator_) - obj1.numerator_ * (lcd / obj1.denominator_);
			result.sign_ = false;
		}
		return result;
	}
	if (obj1.sign_ == false && obj2.sign_ == false) { // Блок вычислений, когда обе дроби отрицательные
		if (obj1.numerator_*(lcd/obj1.denominator_) >= obj2.numerator_*(lcd/obj2.denominator_)) {
			result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) - obj2.numerator_ * (lcd / obj2.denominator_);
			result.sign_ = false;
		}
		else
			result.numerator_= obj2.numerator_ * (lcd / obj2.denominator_) - obj1.numerator_ * (lcd / obj1.denominator_);
		return result;
	}
	if (obj1.sign_ == false) { // Блок вычислений, когда только первая дробь отрицательная
		result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) + obj2.numerator_ * (lcd / obj2.denominator_);
		result.sign_ = false;
		return result;
	}
	// Блок вычислений, когда только вторая дробь отрицательная
	result.numerator_ = obj1.numerator_ * (lcd / obj1.denominator_) + obj2.numerator_ * (lcd / obj2.denominator_);
	return result;
}

Fraction multiplication(const Fraction& obj1, const Fraction& obj2) {
	Fraction result;
	result.denominator_ = obj1.denominator_ * obj2.denominator_;
	result.numerator_ = obj1.numerator_ * obj2.numerator_;
	if ((obj1.sign_ && obj2.sign_ == false) || (obj1.sign_ == false && obj2.sign_)) // Если исходные дроби разнознаковые, то
		result.sign_ = false;
	if (obj1.numerator_ == 0 || obj2.numerator_ == 0)
		result.sign_ = true;
	return result;
}

Fraction divide(const Fraction& obj1, const Fraction& obj2) {			
	Fraction result;
	result.numerator_ = obj1.numerator_ * obj2.denominator_;
	result.denominator_ = obj1.denominator_ * obj2.numerator_;
	if ((obj1.sign_ && obj2.sign_ == false) || (obj1.sign_ == false && obj2.sign_)) // Если исходные дроби разнознаковые, то
		result.sign_ = false;
	return result;
}

void output(Fraction& obj1, Fraction& obj2, Fraction& obj3, char symbol) {
	obj1.print();	
	std::cout << ' ' << symbol << ' ';
	if (obj2.sign_)
		obj2.print();
	else
		obj2.print(false);
	std::cout << "\033[0m = \033[92m";
	obj3.print();		
	output(obj3);
	std::cout << "\033[0m = \033[92m" << obj3.real() << "\033[0m" << std::endl;
	obj3.SetSing(true); // Обязательно после вывода результата устанавливаем знак объекта по умолчанию для корректности дальнейшего его\
	использования в расчётах
}

void output(Fraction& obj1, int n, Fraction& obj2, char symbol) {
	obj1.print();	
	if (n >= 0)
		std::cout << ' ' << symbol << ' ' << n << ' ' << " = \033[92m";
	else
		std::cout << ' ' << symbol << " (" << n << ')' << " = \033[92m";
	obj2.print();	
	output(obj2);	
	std::cout << "\033[0m = \033[92m" << obj2.real() << "\033[0m" << std::endl;
	obj2.SetSing(true);
}

void output(Fraction obj) {
	if (obj.numerator_ == 0) 		
		return;			
	if (check_simple(obj.GetNumerator(), obj.GetDenominator())) { 
		obj.simplification();
		std::cout << "\033[0m = \033[92m";
		obj.print();
	}
}

unsigned long long Evklid(unsigned long long num1, unsigned long long num2) {
	while (num1 != num2)
		if (num1 > num2)
			num1 -= num2;
		else
			num2 -= num1;
	return num1;
}

bool check_simple(unsigned long long num1, unsigned long long num2) {
	if (Evklid(num1,num2) == 1)
		return false;
	return true;
}

void Fraction::print() {		
	if (sign_) 
		std::cout << numerator_ << '/' << denominator_;			
	else
		std::cout << '-' << numerator_ << '/' << denominator_;	
}

void Fraction::print(bool key) {
	if (sign_)
		std::cout << numerator_ << '/' << denominator_;
	else
		std::cout << "(-" << numerator_ << '/' << denominator_ << ')';
}

double Fraction::real() {
	if (sign_)
		return (numerator_ / double(denominator_));
	return ((-1)*(numerator_ / double(denominator_)));
}

unsigned long long Fraction::GetDenominator() {
	return denominator_;
}

unsigned long long Fraction::GetNumerator() {
	return numerator_;
}

void Fraction::SetSing(bool key) {
	sign_ = key;
}

void Fraction::SetNumerator(unsigned long long numerator) {	
	this->numerator_=numerator;	
}

void Fraction::SetDenominator(unsigned long long denominator) {
	this->denominator_ = denominator;
}

void Fraction::proper() {
	if (numerator_ < denominator_)
		if (numerator_ != 0)
			std::cout << "The entered fraction is \033[96mimproper!\033[0m";
		else return;
	else
		if (numerator_ > denominator_) {				
			std::cout << "The entered fraction is \033[96mproper\033[0m and equal to \033[92m";
			if (sign_ == false)
				std::cout << '-';
			std::cout << numerator_ / denominator_ << " \033[0m";
			if ((numerator_ - (numerator_ / denominator_)*denominator_) == 0)
				return;
			else {
				if (check_simple((numerator_ - (numerator_ / denominator_))*denominator_, denominator_)) {
					Fraction obj;
					obj.denominator_ = denominator_;
					obj.numerator_ = numerator_ - (numerator_ / denominator_)*denominator_;
					obj.simplification();
					std::cout << "\033[92m";
					obj.print();
					std::cout << "\033[0m";
					return;
				}				
				std::cout << "\033[92m" << (numerator_ - (numerator_ / denominator_) * denominator_) << '/' << denominator_ << "\033[0m";
			}
		}
		else {
			std::cout << "The entered fraction is a\033[96m whole number\033[0m and equal to \033[92m";
			if (sign_ == false)
				std::cout << '-';
			std::cout << numerator_ / denominator_ << "\033[0m";
		}
}

void Fraction::simplification() {
	unsigned long long divider = Evklid(numerator_, denominator_);
	numerator_ /= divider;
	denominator_ /= divider;
}










