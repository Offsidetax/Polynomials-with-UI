#pragma once

#include <sstream>

#include "list.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <utility> 
#include <map>

using namespace std;

struct Monom
{
    double coefficient;
    int degree;
    Monom(double _a = 0, int _b = 0) : coefficient(_a), degree(_b) {}

    bool operator==(const Monom& other) const {
        return degree == other.degree && coefficient == other.coefficient;
    }

    bool operator!=(const Monom& other) const {
        return !(*this == other);
    }

    bool operator<(const Monom& other) const {
        if (degree != other.degree)
            return degree < other.degree;
        return 0;
    }

    bool operator>(const Monom& other) const {
        return other < *this;
    }

    bool operator<=(const Monom& other) const {
        return !(other < *this);
    }

    bool operator>=(const Monom& other) const {
        return !(*this < other);
    }

    Monom negative() { //Понадобилось для оператора -
        Monom result((-1)*coefficient, degree);
        return result;
    }

    void Print() const {
        std::cout << coefficient << " * " << "X^" << degree / 100 << " * " << "Y^" << (degree % 100) / 10 << " * " << "Z^" << degree % 10;
    }

    friend ostream& operator<<(ostream& os, const Monom& monom) {
        os << monom.coefficient << " * X^" << monom.degree / 100
            << " * Y^" << (monom.degree % 100) / 10
            << " * Z^" << monom.degree % 10;
        return os;
    }
};

template <size_t MaxDegree>
class PolinomXYZ {
    List<Monom> monoms;
public:
    PolinomXYZ() : monoms() {}

    PolinomXYZ(const vector<double>& coef, const vector<int>& deg) : monoms() {
        if (coef.size() != deg.size())
            throw "Incorrect input of coefficients or degrees";

        for (size_t i = 0; i < coef.size(); i++) {
            monoms.insert_front(Monom(coef[i], deg[i]));
        }

        sort(monoms);
    }

    vector<double> GetCoefficients() const {
        vector<double> coefficients;
        auto* current = monoms.Get_First();
        while (current) {
            coefficients.push_back(current->data.coefficient);
            current = current->next;
        }
        return coefficients;
    }

    vector<int> GetDegrees() const {
        vector<int> degrees;
        auto* current = monoms.Get_First();
        while (current) {
            degrees.push_back(current->data.degree);
            current = current->next;
        }
        return degrees;
    }

    void Print() const {
        auto* current = monoms.Get_First(); 
        if (current == nullptr) std::cout << "0" << std::endl;
        else {
            while (current) {
                current->data.Print(); 
                current = current->next;
                if (current) std::cout << " + ";
            }
            std::cout << std::endl;
        }
    }

    PolinomXYZ operator+(const PolinomXYZ& other) const {
        PolinomXYZ result;
        auto* left = monoms.Get_First();
        auto* right = other.monoms.Get_First();
        auto* ResList = result.monoms.Get_First();

        while (left || right) {
            if (left && (!right || (left->data < right->data))) {
                if (ResList == nullptr) {
                    result.monoms.insert_front(left->data);
                    ResList = result.monoms.Get_First();
                }
                else {
                    result.monoms.insert(left->data, ResList);
                    ResList = ResList->next;
                }
                left = left->next;
            }
            else if (right && (!left || (right->data < left->data))) {
                if (ResList == nullptr) {
                    result.monoms.insert_front(right->data);
                    ResList = result.monoms.Get_First();
                }
                else {
                    result.monoms.insert(right->data, ResList);
                    ResList = ResList->next;
                }
                right = right->next;
            }
            else { // Если степени мономов совпадают
                double newCoef = left->data.coefficient + right->data.coefficient;
                if (newCoef != 0) {
                    result.monoms.insert_front(Monom(newCoef, left->data.degree));
                }
                left = left->next;
                right = right->next;
            }
        }

        if (result.monoms.Get_First() != nullptr) sort(result.monoms); // Упорядочивание списка мономов
        return result;
    }

    PolinomXYZ operator-(const PolinomXYZ& other) const {
        PolinomXYZ result;
        auto* left = monoms.Get_First();
        auto* right = other.monoms.Get_First();
        auto* ResList = result.monoms.Get_First();

        while (left || right) {
            if (left && (!right || (left->data < right->data))) {
                if (ResList == nullptr) {
                    result.monoms.insert_front(left->data);
                    ResList = result.monoms.Get_First();
                }
                else {
                    result.monoms.insert(left->data, ResList);
                    ResList = ResList->next;
                }
                left = left->next;
            }
            else if (right && (!left || (right->data < left->data))) {
                if (ResList == nullptr) {
                    result.monoms.insert_front((right->data).negative());
                    ResList = result.monoms.Get_First();
                }
                else {
                    result.monoms.insert((right->data).negative(), ResList);
                    ResList = ResList->next;
                }
                right = right->next;
            }
            else { // Если степени мономов совпадают
                double newCoef = left->data.coefficient - right->data.coefficient;
                if (newCoef != 0) {
                    result.monoms.insert_front(Monom(newCoef, left->data.degree));
                }
                left = left->next;
                right = right->next;
            }
        }

       if(result.monoms.Get_First() != nullptr) sort(result.monoms); // Упорядочивание списка мономов
        return result;
    }

    PolinomXYZ operator*(double scalar) const {
        PolinomXYZ result;
        if (scalar == 0) {
            return result;
        }

        auto* current = monoms.Get_First();
        auto* ResList = result.monoms.Get_First();

        while (current) {
            if (current == monoms.Get_First()) {
                result.monoms.insert_front(Monom(current->data.coefficient * scalar, current->data.degree));
                ResList = result.monoms.Get_First();
            }
            else {
                result.monoms.insert(Monom(current->data.coefficient * scalar, current->data.degree), ResList);
                ResList = ResList->next;
            }
            current = current->next;
        }

        return result;
    }

    PolinomXYZ operator/(double scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero is not allowed");
        }

        PolinomXYZ result;
        auto* current = monoms.Get_First();
        auto* ResList = result.monoms.Get_First();

        while (current) {
            if (current == monoms.Get_First()) {
                result.monoms.insert_front(Monom(current->data.coefficient / scalar, current->data.degree));
                ResList = result.monoms.Get_First();
            }
            else {
                result.monoms.insert(Monom(current->data.coefficient / scalar, current->data.degree), ResList);
                ResList = ResList->next;
            }
            current = current->next;
        }

        return result;
    }

   /* PolinomXYZ operator*(const PolinomXYZ& other) const { //для умножения монома на моном использовал map, чтобы достичь сложности O((N^2)*logN)
        PolinomXYZ result;
        map<int, double> monomMap;
        auto* ResList = result.monoms.Get_First();

        for (auto* left = monoms.Get_First(); left; left = left->next) {
            for (auto* right = other.monoms.Get_First(); right; right = right->next) {
                if (((left->data.degree / 100 + right->data.degree /100) > 9) || ((left->data.degree % 10 + right->data.degree % 10) > 9) || (((left->data.degree / 10) % 10 + (right->data.degree / 10) % 10) > 9)) throw "Result of multipying have degree more then maximum possible (MaxDegree^3) !";

                int newDegree = left->data.degree + right->data.degree;

                double newCoef = left->data.coefficient * right->data.coefficient;

                monomMap[newDegree] += newCoef;  // O(log N) вставка/поиск
            }
        }

        // Преобразуем map обратно в список мономов
        for (pair<const int, double> entry : monomMap) {
            int deg = entry.first;   
            double coef = entry.second; 

            if (coef != 0) {
                if (ResList == nullptr) {
                    result.monoms.insert_front(Monom(coef, deg));
                    ResList = result.monoms.Get_First();
                }
                else {
                    result.monoms.insert(Monom(coef, deg), ResList);
                    ResList = ResList->next;
                }
            }
        }

        return result;
    }*/

    PolinomXYZ operator*(const PolinomXYZ& other) const { // O(N^2)
        PolinomXYZ result;
        auto* ResList = result.monoms.Get_First();

        for (auto* left = monoms.Get_First(); left; left = left->next) {
            PolinomXYZ tempResult;
            auto* TempResList = tempResult.monoms.Get_First();

            for (auto* right = other.monoms.Get_First(); right; right = right->next) {
                if (((left->data.degree / 100 + right->data.degree / 100) > 9) || ((left->data.degree % 10 + right->data.degree % 10) > 9) || (((left->data.degree / 10) % 10 + (right->data.degree / 10) % 10) > 9)) throw "Result of multipying have degree more then maximum possible (MaxDegree^3) !";

                int newDegree = left->data.degree + right->data.degree;

                double newCoef = left->data.coefficient * right->data.coefficient;

                if(TempResList == NULL) {
                    tempResult.monoms.insert_front(Monom(newCoef, newDegree));
                    TempResList = tempResult.monoms.Get_First();
                }
                else {
                    tempResult.monoms.insert(Monom(newCoef, newDegree), TempResList);
                    TempResList = TempResList->next;
                }
            }

            result = result + tempResult;
        }
        return result;
    }


    friend ostream& operator<<(ostream& os, const PolinomXYZ& polynom) { 
        auto* current = polynom.monoms.Get_First();
        if (!current) {
            os << "0";
        }
        else {
            while (current) {
                os << current->data;
                current = current->next;
                if (current) os << " + ";
            }
        }
        return os;
    }

    std::string ToString() const {
        std::ostringstream oss;
        oss << *this; // Использует уже реализованный operator<<
        return oss.str();
    }
};