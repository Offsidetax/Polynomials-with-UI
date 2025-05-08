#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

inline bool isNumber(const std::string& str) {
	if (str.empty()) return false;

	for (size_t i = 0; i < str.length(); ++i) {
		if ((!isdigit(str[i])) && (str[i] != '.')) {
			return false;
		}
	}
	return true;
}

class Arithmetic_Expression {
	string infix;
	vector<double> coeficients;
	vector<int> deg;

	void Parse() {
		int i = 0;
		int dotNum = 0;
		bool negativeFlag = 0;
		string curItem;

		while(i < infix.length()) {
			switch (infix[i]) {
			case '+': case '-':
				if ((i == infix.length()) || !(isdigit(infix[i + 1]))) { //из состояния "+" или "-" можно попасть только в состояние "коэффициент"
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				if (infix[i] == '-') negativeFlag = 1;
				i++;
				break;

			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
				if (infix[i] == '.') curItem += '0'; //Добавляем 0 к десятичной записи числа, если его нет
				while (isdigit(infix[i]) || (infix[i] == '.')) {
					if (infix[i] == '.') dotNum++;
					curItem += infix[i];
					i++;
				}

				if ((infix[i] != '*') && (i >= infix.length())) { //после состояния "коэффициент" должно идти состояние "*"
					std::cout << "Incorrect input! (There should be a * sign after number)" << std::endl;
					throw "Incorrect input! (There should be a * sign after number)";
				}

				if ((dotNum > 1) || (infix[i - 1] == '.')) { //Проверка на правильность ввода десятичного числа
					std::cout << "Incorrect decimal number input!" << std::endl;
					throw "Incorrect decimal number input!";
				}

				if (negativeFlag == 1) { //Если перед коэфициентом был "-", то коэффициент отрицательный
					curItem = '-' + curItem;
					negativeFlag = 0;
				}
				dotNum = 0;
				coeficients.push_back(std::stod(curItem));
				curItem.clear();
				i++;
				break;

			case 'X': //Состояние "X", "Y" и "Z" включают в себя степень
				if ((i == infix.length()) || ((infix[i + 1] != '^')) || (i == 0)) { //После "X" должен идти символ "^" 
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				i++;
				i++;

				if (!isdigit(infix[i])) { //После "^" должна идти степень (в данном случае число)
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				curItem = infix[i];
				i++;

				if (infix[i] != '*') { //После показателя степени X должен идти символ "*" 
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				i++;

				if (infix[i] != 'Y') {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				break;

			case 'Y':
				if ((i == infix.length()) || ((infix[i + 1] != '^')) || (i == 0)) { //После "Y" должен идти символ "^" 
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				i++;
				i++;

				if (!isdigit(infix[i])) { //После "^" должна идти степень (в данном случае число)
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				curItem += infix[i];
				i++;

				if (infix[i] != '*') { //После показателя степени Y должен идти символ "*" 
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				i++;

				if (infix[i] != 'Z') {
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				break;

			case 'Z':
				if ((i == infix.length()) || (i == 0) || ((infix[i + 1] != '^'))) { //из состояний "Z" можно попасть только в состояние "+" или в конец строки
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}
				i++;
				i++;

				if (!isdigit(infix[i])) { //После "^" должна идти степень (в данном случае число)
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				curItem += infix[i];
				deg.push_back(std::stod(curItem));
				curItem.clear();
				i++;

				if ((i != infix.length()) && ((infix[i] != '+') && (infix[i] != '-')))  { //После показателя степени Z должен идти символ "+" или "-" 
					std::cout << "Incorrect input!" << std::endl;
					throw "Incorrect input!";
				}

				break;

			default:
				std::cout << "Unknown symbol -> " << infix[i] << " Number in string: " << i << std::endl;
				throw "Unknown symbol";
			}
		}
	}
public:
	Arithmetic_Expression(string expression) : infix(expression) {
		if (infix == "") throw "Empty string!";
		Parse();
	}

	string GetInfix() const {
		return infix;
	}

	const vector<double>& GetCoefficients() const {
		return coeficients;
	}

	const vector<int>& GetDegree() const {
		return deg;
	}
};