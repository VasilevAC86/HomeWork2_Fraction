#pragma once

// Описание класса
class Fraction {
private:
	// Блок полей
	unsigned long long numerator_; // поле для переменной для хранения значения числителя
	unsigned long long denominator_; // поле для переменной для хранения значения знаменателя
	bool sign_; // поле для переменной для хранения знака дроби (true - это "+", false "-")		
	// Блок прототипов дружественных функций		
	friend Fraction sum(const Fraction& obj1, const Fraction& obj2, const unsigned long long lcd); // для суммы	
	friend Fraction subtraction(const Fraction& obj1, const Fraction& obj2, const unsigned long long lcd); // для разности
	friend Fraction multiplication(const Fraction& obj1, const Fraction& obj2);	// для умножения
	friend Fraction divide(const Fraction& obj1, const Fraction& obj2); // для деления
	// перегрузки для вывода в консоль
	friend void output(Fraction &obj1, Fraction &obj2, Fraction &obj3, char symbol);	
	friend void output(Fraction& obj1, int n, Fraction& obj2, char symbol);
	friend void output(Fraction obj); 	
public:	
	// конструктор объекта класса по умолчанию
	Fraction() {		
		numerator_ = 0;
		denominator_ = 1;
		sign_ = true;
	}	
	// Блок прототипов методов
	void fill_in(); // ввод в поля объекта данных от пользователя
	// перегруженный метод для корректного вывод объекта "дробь" в консоль
	void print(); 	
	void print(bool key);
	double real(); // перевод дроби в десятичное действительное число
	unsigned long long GetDenominator(); // гэттэра знаменателя дроби
	unsigned long long GetNumerator(); // гэттэра числителя дроби
	void SetSing(bool key); // сэттэра знака объекта 	
	void SetNumerator(unsigned long long numerator); // сэттэр числителя дроби 
	void SetDenominator(unsigned long long denominator); // сэттэр знаменателя дроби
	void proper(); // метод проверки дроби на правильность/неправильность	
	void simplification(); // сокращение дроби, когда числитель и знаменатель можно поделить на общий множитель
	~Fraction() {}; // деструктор
};

// Блок внещних функций
unsigned long long Evklid(unsigned long long num1, unsigned long long num2); // поиск общего знаменателя двух целых чисел (алгоритм Евклида)
bool check_simple(unsigned long long num1, unsigned long long num2); // проверка возможности сокращения дроби