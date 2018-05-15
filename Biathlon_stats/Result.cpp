/*�����: ���� ����� �������������, ����� �-12*/
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
		result += "�������: " + (*n)->surname + " " + (*n)->name + ", �����: " + (*n)->country + "\n";
		result += "������ ��������: " + to_string((*n)->sumMiss) + "\n";
		result += "̳�������� ��� �������: " + to_string((*n)->minShootingTime) + ", �������� �� ���� #" + to_string((*n)->bestStage) + "\n\n --- <�����> --- \n";
		Info::InfoIterator inf((*n)->info.getTop());
		while (inf != 0) {
			result += "���� #" + to_string((*inf)->stage) + "\n";
			result += "��������� �����: " + to_string((*inf)->number) + "\n";
			result += "̳���: " + to_string((*inf)->place) + "\n";
			result += "��������� ���: " + to_string((*inf)->totalTime) + "\n";
			result += "��������: " + to_string((*inf)->missNum) + "\n";
			result += " ----------------- \n"; 
			++inf;
		}
		result += " --- </�����> ---\n\n";
		++n;
	}
	if (output.length() > 0) {
		cout << "������ ����� � ����\n\n";
		ofstream out(output);
		if (out.is_open()) {
			out << result;
			out.close();
			cout << "����������� ���������� ������ �������� � ����." << endl << endl;
		}
		else
			cout << "��� ���� ��������� �������/��������" << endl;
	}
	else {
		cout << "������ ��������� � �������.\n\n" << result << endl;
	}
}