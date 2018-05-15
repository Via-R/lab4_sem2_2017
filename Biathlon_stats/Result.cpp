/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include "Data.h"
#include <fstream>
using namespace std;
void showWinners(Data * p, string & output) {
	Data::Iterator n(p->getTop());
	int min = (*n)->sumMiss;
	string result = "";
	while (n) {
		if ((*n)->sumMiss > min || (*n)->sumMiss == -1)
			break;
		result += "Учасник: " + (*n)->surname + " " + (*n)->name + ", країна: " + (*n)->country + "\n";
		result += "Усього промахів: " + to_string((*n)->sumMiss) + "\n";
		result += "Мінімальний час стрільби: " + to_string((*n)->minShootingTime) + ", отримано на етапі #" + to_string((*n)->bestStage) + "\n\n --- <Етапи> --- \n";
		Info::InfoIterator inf((*n)->info.getTop());
		while (inf != 0) {
			result += "Етап #" + to_string((*inf)->stage) + "\n";
			result += "Стартовий номер: " + to_string((*inf)->number) + "\n";
			result += "Місце: " + to_string((*inf)->place) + "\n";
			result += "Загальний час: " + to_string((*inf)->totalTime) + "\n";
			result += "Промахів: " + to_string((*inf)->missNum) + "\n";
			result += " ----------------- \n"; 
			++inf;
		}
		result += " --- </Етапи> ---\n\n";
		++n;
	}
	if (output.length() > 0) {
		cout << "Обрано запис у файл\n\n";
		ofstream out(output);
		if (out.is_open()) {
			out << result;
			out.close();
			cout << "Результуюча інформація успішно записана у файл." << endl << endl;
		}
		else
			cout << "Цей файл неможливо відкрити/створити" << endl;
	}
	else {
		cout << "Обрано виведення у консоль.\n\n" << result << endl;
	}
}