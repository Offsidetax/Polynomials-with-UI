#pragma once
#include <iostream>
using namespace std;

template <class T>
class List {
	struct Node {
		T data;
		Node* next;
		Node(T value = T(), Node* n = nullptr) {
			data = value;
			next = n;
		}

		Node& operator=(const Node& other) {
			data = other.data;
			next = nullptr;
			next = other.next;
		}

		~Node() {
			next = nullptr;
			data = 0;
		}
	};

	Node* First;
public:
	List() :First(nullptr) {}

	List(const List& other) {
		if ((!other.First) || (other.Get_First() == nullptr)) {
			First = nullptr;
		}
		else {
			this->First = new Node(other.First->data, nullptr);
			Node* current = First;
			Node* ocurrent = other.First;

			while (ocurrent->next) {
				current->next = new Node(ocurrent->next->data, nullptr);
				current = current->next;
				ocurrent = ocurrent->next;
			}
		}
	}

	List(int n, T deflt = T()) {
		if (n <= 0) throw "List doesn`t exist";

		First = new Node(deflt, nullptr);
		Node* current = First;

		for (int i = 1; i < n; ++i) {
			Node* tmp = new Node(deflt, nullptr);
			current->next = tmp;
			current = current->next;
		}
	}

	~List() {
		while (First) {
			Node* Second = First->next;
			delete First;
			First = Second;
		}
	}

	List& operator=(const List& other) {
		if (!other.First) {
			First = nullptr;
			return *this;
		}

		while (First) {
			Node* Second = First->next;
			delete First;
			First = Second;
		}

		First = new Node(other.First->data, nullptr);
		Node* current = First;
		Node* ocurrent = other.First;

		while (ocurrent->next) {
			current->next = new Node(ocurrent->next->data, nullptr);
			current = current->next;
			ocurrent = ocurrent->next;
		}

		return *this;
	}

	inline void print() {
		Node* current = First;

		while (current) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << "\n";
	}

	friend istream& operator>>(istream& istr, const List& l) {
		Node* current = l.First;

		while (current) {
			istr >> current->data;
			current = current->next;
		}

		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const List& l) {
		Node* current = l.First;

		while (current) {
			ostr << current->data << ' ';
			current = current->next;
		}
		std::cout << "\n";

		return ostr;
	}

	bool operator==(const List& other) const { //Needed for tests
		Node* current_that = this->First;
		Node* current_other = other.First;

		while (current_that) {
			if (current_other == nullptr) return 0;

			if (current_that->data != current_other->data) return 0;

			current_that = current_that->next;
			current_other = current_other->next;
		}

		if (current_other != nullptr)
			return 0;
		else
			return 1;
	}

	T& operator[](int index) {
		if ((index < 0) || (this->size() <= index)) throw "Element doesn`t exist";

		Node* current = First;
		int i = 0;
		while (current->next) {
			if (i == index) return current->data;
			current = current->next;
			i++;
		}
	}

	T& operator[](int index) const {
		if ((index < 0) || (this->size() <= index)) throw "Element doesn`t exist";

		Node* current = First;
		int i = 0;
		while (current->next) {
			if (i == index) return current->data;
			current = current->next;
			i++;
		}
	}

	Node* insert(T value, Node* prev) {
		Node* current = new Node();

		current->next = prev->next;
		current->data = value;
		prev->next = current;

		return current;
	}

	Node* insert_front(T value) {
		Node* first_first = new Node();

		first_first->next = First;
		first_first->data = value;
		First = first_first;

		return First;
	}

	Node* find(T value) {
		Node* current = First;

		while (current->next) {
			if (value == current->data) return current;
			current = current->next;
		}

		return nullptr;
	}

	int size() const{
		Node* current = First;
		int size = 1;

		while (current->next) {
			size += 1;
			current = current->next;
		}

		return size;
	}

	Node* Get_First() const{
		return First;
	}

	Node* erase(Node* prev) {
		Node* current = prev->next;

		prev->next = current->next;
		delete current;

		return prev->next;
	}

	Node* erase_front() {
		Node* current = First;

		First = current->next;
		delete current;

		return First;
	}

	friend void sort(List& current) {
		if (current.First == nullptr) throw "Zero length list can't be sorted";
		if (current.First->next == nullptr) return;

		List other;
		List res;

		Node* slow = current.First;
		Node* fast = current.First;
		Node* mid;

		///////split list/////////////////////////////
		while ((fast != nullptr) && (fast->next != nullptr)) {
			fast = (fast->next)->next;

			if (fast != nullptr) {
				slow = slow->next;
			}
		}

		mid = slow->next;
		slow->next = nullptr;  //split our list on two smaller lists

		other.First = mid; //list other is a second half of given list

		//std::cout << "List was splited\n";
		/////////////////////////////////////////

		//////sorting splits////////////
		sort(current); //sorting first half of list
		sort(other); //sorting second half of list
		/////////////////////////////////

		res.First = unite(current.First, other.First);

		current.First = res.First;
		res.First = nullptr;
		other.First = nullptr;
	}

	friend Node* unite(Node* current, Node* other) { //Needed for sort (unite lists in sorted one)
		if (current == nullptr) return other;
		if (other == nullptr) return current;

		if (current->data < other->data) {
			current->next = unite(current->next, other);
			return current;
		}
		else {
			other->next = unite(current, other->next);
			return other;
		}
	}
};