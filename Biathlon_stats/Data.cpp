/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include "Data.h"
using namespace std;

Data::Data() {
	HEAD = nullptr;
};

Data::~Data() {
	Node * Next;
	while (HEAD != 0) {
		Next = HEAD->next;
		delete HEAD;
		HEAD = Next;
	}
}

Node * Data::getNode(string fullName) {
	Node * curr = HEAD;
	while (curr!=0) {
		if (curr->surname + curr->name + curr->country == fullName)
			return curr;
		curr = curr->next;
	}
	return nullptr;
}

void Data::setPlace(Node * el) {
	Node *p = HEAD, *prev = nullptr;
	if (p == 0) {
		HEAD = el;
		el->next = nullptr;
		return;
	}
	while (p != 0) {
		if ((el->sumMiss <= p->sumMiss || p->sumMiss == -1) && el->sumMiss != -1) {
			if (prev != 0)
				prev->next = el;
			else
				HEAD = el;
			el->next = p;
			return;
		}
		prev = p;
		p = p->next;
	}
	prev->next = el;
	el->next = nullptr;
}

void Data::goThrough() {
	Iterator f(HEAD);
	InfoNode * inf = nullptr;
	cout << ">----------------<" << endl;
	while (f) {
		cout << (*f)->surname << " " << (*f)->name << ", from " << (*f)->country << endl;
		cout << "Усього промахів: " << (*f)->sumMiss << endl;
		cout << "Мінімальний час стрільби: " << (*f)->minShootingTime << ", отримано на етапі #" << (*f)->bestStage << endl;
		cout << "\n --- <Вузли> --- \n";
		Info::InfoIterator inf((*f)->info.getTop());
		while (inf) {
			cout << "Етап #" << (*inf)->stage << endl;
			cout << "Стартовий номер: " << (*inf)->number << endl;
			cout << "Місце: " << (*inf)->place << endl;
			cout << "Загальний час: " << (*inf)->totalTime << endl;
			cout << "Найкращий час стрільби: " << (*inf)->minTime << endl;
			cout << "Промахів: " << (*inf)->missNum << endl;
			cout << "Додатковий час: " << (*inf)->extraLapsTime << endl;
			cout << "----------\n";
			++inf;
		}
		cout << " --- </Вузли> ---\n\n";
		++f;
	}
	cout << endl;
}

Node * Data::getTop() {
	return HEAD;
}

void Data::isolate(Node * p) {
	Node * Next = p->next;
	if (p != HEAD) {
		Node * t = HEAD;
		while (t != 0) {
			if (t->next == p) {
				t->next = Next;
				break;
			}
			t = t->next;
		}
	}
	else
		HEAD = p->next;
	p->next = nullptr;
}
int Data::getMissNumber() {
	Node * p = HEAD;
	int sum = 0;
	while (p != 0) {
		if (p->sumMiss != -1)
			sum += p->sumMiss;
		p = p->next;
	}
	return sum;
}

Data::Iterator::Iterator(Node * p) {
	current = p;
}

Node * Data::Iterator::operator * () const {
	if (current)
		return current;
	return nullptr;
}

Data::Iterator & Data::Iterator::operator ++ () {
	if (current)
		current = current->next;
	return *this;
}

Data::Iterator::operator bool() const {
	return current != nullptr;
}

void Data::setSumMiss(int n, Node * p) {
	p->sumMiss = n;
};
void Data::setName(std::string n, Node * p) {
	p->name = n;
};
void Data::setSurname(std::string n, Node * p) {
	p->surname = n;
};
void Data::setCountry(std::string n, Node * p) {
	p->country = n;
};
void Data::setMinShootingTime(int n, Node * p) {
	p->minShootingTime = n;
};
void Data::setBestStage(int n, Node * p) {
	p->bestStage= n;
};

Point * Data::getNodeBySumMiss(int n) {
	Node * p = HEAD;
	Point * pp;
	try {
		pp = new Point;
	}
	catch (bad_alloc) {
		cout << "Помилка виділення динамічної пам'яті" << endl << endl;
		return nullptr;
	}
	Pointers * ppp;
	while (p != 0) {
		if (p->sumMiss == n) {
			ppp = new Pointers;
			ppp->point = p;
			pp->push(ppp);
		}
		p = p->next;
	}
	return pp;
};

Point * Data::getNodeByBestStage(int n) {
	Node * p = HEAD;
	Point * pp;
	try{
		pp = new Point;
	}
	catch(bad_alloc){
		cout << "Помилка виділення динамічної пам'яті" << endl << endl;
		return nullptr;
	}
	Pointers * ppp;
	while (p != 0) {
		if (p->bestStage == n) {
			ppp = new Pointers;
			ppp->point = p;
			pp->push(ppp);
		}
		p = p->next;
	}
	return pp;
};

Point * Data::getNodeByCountry(string n) {
	Node * p = HEAD;
	Point * pp;
	try {
		pp = new Point;
	}
	catch (bad_alloc) {
		cout << "Помилка виділення динамічної пам'яті" << endl << endl;
		return nullptr;
	}
	Pointers * ppp;
	while (p != 0) {
		if (p->country == n) {
			ppp = new Pointers;
			ppp->point = p;
			pp->push(ppp);
		}
		p = p->next;
	}
	return pp;
};

Point * Data::getNodeByName(string n) {
	Node * p = HEAD;
	Point * pp;
	try {
		pp = new Point;
	}
	catch (bad_alloc) {
		cout << "Помилка виділення динамічної пам'яті" << endl << endl;
		return nullptr;
	}
	Pointers * ppp;
	while (p != 0) {
		if (p->name == n) {
			ppp = new Pointers;
			ppp->point = p;
			pp->push(ppp);
		}
		p = p->next;
	}
	return pp;
};

Point * Data::getNodeBySurname(string n) {
	Node * p = HEAD;
	Point * pp;
	try {
		pp = new Point;
	}
	catch (bad_alloc) {
		cout << "Помилка виділення динамічної пам'яті" << endl << endl;
		return nullptr;
	}
	Pointers * ppp;
	while (p != 0) {
		if (p->surname == n) {
			ppp = new Pointers;
			ppp->point = p;
			pp->push(ppp);
		}
		p = p->next;
	}
	return pp;
};

Point * Data::getNodeByMinShootingTime(int n) {
	Node * p = HEAD;
	Point * pp;
	try {
		pp = new Point;
	}
	catch (bad_alloc) {
		cout << "Помилка виділення динамічної пам'яті" << endl << endl;
		return nullptr;
	}
	Pointers * ppp;
	while (p != 0) {
		if (p->minShootingTime == n) {
			ppp = new Pointers;
			ppp->point = p;
			pp->push(ppp);
		}
		p = p->next;
	}
	return pp;
};

void Point::push(Pointers *p) {
	if (HEAD != 0) {
		p->next = HEAD;
		HEAD = p;
	}
	else {
		HEAD = p;
		p->next = nullptr;
	}
};
Point::~Point() {
	Pointers * Next;
	while (HEAD != 0) {
		Next = HEAD->next;
		delete HEAD;
		HEAD = Next;
	}
};

bool Data::checkSanity(int num) {
	Node * p = HEAD;
	while (p != 0) {
		InfoNode * inf = p->info.getTop();
		while (inf != 0) {
			if (inf->number == num) {
				return false;
			}
			inf = inf->next;
		}
		p = p->next;
	}
	return true;
}

Pointers * Point::getTop() {
	return HEAD;
}

Point::Point(){
	HEAD = nullptr;
}