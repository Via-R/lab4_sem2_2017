/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include "Builder.h"
#include <fstream>
#include <string>
using namespace std;

Builder::Builder(Data *p) {
	data = p;
}
bool Builder::readFile(string &filename, Data * d){
	data = d;
	ifstream file(filename);
	if (file.is_open()) {
		string line = "";
		int count = 0;
		int lineCount = 0;
		int error;
		bool crashed = false;
		cout << "Успішно прочитано файл \"" << filename << "\"" << endl << endl;
		string firstLine;
		
		getline(file, firstLine);
		file.clear();
		file.seekg(-1, ios_base::end);
		bool keepLooping = true;
		while (keepLooping) {
			char ch;
			file.get(ch);

			if ((int)file.tellg() <= 1) {
				file.seekg(0);
				keepLooping = false;
			}
			else if (ch == '\n') {
				keepLooping = false;
			}
			else {
				file.seekg(-2, ios_base::cur);
			}
		}
		string lastLine;
		getline(file, lastLine);
		file.clear();
		file.seekg(0, ios::beg);
		
		if (lex.checkFormat(firstLine, lastLine)) {
			while (getline(file, line)) {
				lineCount++;
				error = -1;
				lex.parseStr(line, count, error);
				crashed = error > 0 ? true : false;
				if (error == 1) {
					cout << "Неправильна кількість аргументів у рядку #" << lineCount << endl << endl;
					file.close();
					cout << "Файл закрито." << endl << endl;
					return false;
				}
				else if (error == 2) {
					cout << "Надано неправильний формат інформації у рядку #" << lineCount << endl << endl;
					file.close();
					cout << "Файл закрито." << endl << endl;
					return false;
				}
				else if (error == 0) {
					continue;
				}

				Node *p;
				p = data->getNode(lex.getStrVar(0) + lex.getStrVar(1) + lex.getStrVar(2));
				int t1 = lex.getIntVar(5) - lex.getIntVar(4);
				int t2 = lex.getIntVar(7) - lex.getIntVar(6);
				int minT1T2 = t1 < t2 ? t1 : t2;

				InfoNode * n;
				try {
					n = new InfoNode;
				}
				catch (bad_alloc&) {
					cout << "Помилка виділення динамічної пам'яті\n\n";
					delete n;
					return false;
				}
				n->stage = lex.getIntVar(0);
				n->number = lex.getIntVar(1);
				n->place = lex.getIntVar(2);
				n->minTime = minT1T2;
				n->missNum = lex.getIntVar(8);
				n->totalTime = lex.getIntVar(3);
				n->extraLapsTime = lex.getIntVar(9);
				if (n->totalTime == -1) {
					n->minTime = -1;
					n->extraLapsTime = -1;
					n->missNum = -1;
					minT1T2 = -1;
				}

				if (p == 0) {
					try {
						p = new Node;
					}
					catch (bad_alloc&) {
						cout << "Помилка виділення динамічної пам'яті\n\n";
						delete n;
						return false;
					}
					p->name = lex.getStrVar(1);
					p->surname = lex.getStrVar(0);
					p->country = lex.getStrVar(2);
					p->sumMiss = lex.getIntVar(8);
					p->bestStage = lex.getIntVar(0);

					p->minShootingTime = minT1T2;

					if (n->totalTime == -1) {
						p->sumMiss = -1;
						p->bestStage = -1;
						p->minShootingTime = -1;
					}
					data->setPlace(p);
				}
				else {
					if (p->sumMiss != -1 && p->bestStage != -1 && p->minShootingTime != -1 && n->totalTime != -1) {
						p->sumMiss += lex.getIntVar(8);
						if (minT1T2 < p->minShootingTime) {
							p->bestStage = lex.getIntVar(0);
							p->minShootingTime = minT1T2;
						}
					}
					else {
						p->sumMiss = -1;
						p->bestStage = -1;
						p->minShootingTime = -1;
					}
				}

				if (!p->info.append(n)) {
					cout << "Такий етап вже описано, двоякість інформації у рядку #" << lineCount << endl <<endl;
					file.close();
					cout << "Файл закрито." << endl << endl;
					return false;
				};
				data->isolate(p);
				if (!data->checkSanity(n->number)) {
					cout << "Учасника з таким номером уже описано, двоякість інформації у рядку #" << lineCount << endl << endl;
					return false;
				}
				
				data->setPlace(p);
			}
			file.close();
			cout << "Файл закрито." << endl << endl;
			if (count <= 0) {
				cout << "Відсутні записи між ключовими словами header та footer." << endl << endl;
			}
			if (crashed || count <= 0) {
				return false;
			}
			bool trueStages = data->getTop()->info.getStagesNum() == lex.getStaticInt(0) ? true : false;
			bool trueMisses = data->getMissNumber() == lex.getStaticInt(2) ? true : false;
			bool trueCount = count == lex.getStaticInt(1) ? true : false;

			if (trueCount && trueMisses && trueStages)
				return true;
			else {
				if (!trueCount)
					cout << "Надано неправильну інформацію у footer'і (кількість записів)" << endl << endl;
				if (!trueMisses)
					cout << "Надано неправильну інформацію у footer'і (кількість промахів)" << endl << endl;
				if (!trueStages)
					cout << "Надано неправильну інформацію у header'і (кількість етапів)" << endl << endl;
				return false;
			}
		}
		else {
			cout << "Неправильний формат файлу (перевірте наявність ключових слів header та footer, а також символу \":\" після них" << endl <<endl;
			return false;
		}
	}
	else {
		cout << "Неможливо відкрити файл з даною назвою\n\n";
		return false;
	}
}