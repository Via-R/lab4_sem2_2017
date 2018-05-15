/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include "Info.h"
using namespace std;

Info::Info() {
	HEAD = nullptr;
}
Info::~Info() {
	InfoNode *Next = nullptr;
	while (HEAD != 0) {
		Next = HEAD->next;
		delete HEAD;
		HEAD = Next;
	}
}
bool Info::append(InfoNode *p) {
	InfoNode * t = HEAD, * prev = nullptr;
	if (t == 0) {
		HEAD = p;
		p->next = nullptr;
		return true;
	}

	while (t != 0) {
		if (p->stage == t->stage)
			return false;
		if (p->stage < t->stage) {
			if (prev != 0)
				prev->next = t;
			else
				HEAD = p;
			p->next = t;
			return true;
		}
		prev = t;
		t = t->next;
	}
	prev->next = p;
	p->next = nullptr;
	return true;
}
InfoNode * Info::getTop() {
	return HEAD;
}
int Info::getStagesNum() {
	InfoIterator p(HEAD);
	int max = HEAD->stage;
	while (p) {
		if (max < (*p)->stage) {
			max = (*p)->stage;
		}
		++p;
	}
	return max;
}

Info::InfoIterator::InfoIterator(InfoNode * p) {
	current = p;
}

InfoNode * Info::InfoIterator::operator * () const {
	if (current)
		return current;
}

Info::InfoIterator & Info::InfoIterator::operator ++ () {
	if (current)
		current = current->next;
	return *this;
}

Info::InfoIterator::operator bool() const {
	return current != nullptr;
}
