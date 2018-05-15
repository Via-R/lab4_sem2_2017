/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include "Lexer.h"
#include <sstream>
using namespace std;
int Lexer::statData[3];

void Lexer::parseStr(string & line, int & c, int & error) {
	int pos1 = line.find("header:"), pos2 = line.find("footer:");
	int type = 0;

	if (pos1 == 0)
		type = -1;
	else if (pos2 == 0)
		type = 1;
	if (!pos1 || !pos2)
		line.erase(line.begin(), line.begin() + 7);
	istringstream iss(line);
	int count = 0;
	int intCount = 0;
	int strCount = 0;
	string temp = "";
	int prev = 0, pos;
	while ((pos = line.find_first_of(" \f\n\r\v\b\t;", prev)) != string::npos) {
		if (pos > prev) {
			if (count == 13 || (count == 1 && type == -1) || (count == 2 && type == 1)) {
				count++;
				break;
			}
			temp = line.substr(prev, pos - prev);
			if (type != 0) {
				if (temp.find_first_not_of("0123456789") != std::string::npos) {
					error = 2;
					return;
				}
			}
			if (type == 0) {
				if (count <= 2 || count > 5) {
					if (temp.find_first_not_of("-0123456789") != std::string::npos) {
						error = 2;
						return;
					}
					if (stoi(temp) < -1) {
						error = 2;
						return;
					}
					intData[intCount] = stoi(temp);
					intCount++;
				}
				else {
					strData[strCount] = temp;
					strCount++;
				}
			}
			else if (type == -1) {
				statData[0] = stoi(temp);
			}
			else {
				statData[1 + count] = stoi(temp);
			}
			count++;
		}
		prev = pos + 1;
	}
	if (getIntVar(9) > getIntVar(3) && getIntVar(3) != -1 && getIntVar(8) != -1){
		error = 2;
		return;
	}
	if ((count != 13 && count != 0 && type == 0) || prev < line.length() || (type == 1 && count != 2) || (type == -1 && count != 1)) {
		error = 1;
	}
	else if (count == 0 || type != 0)
		error = 0;
	else if (count == 13){
		c++;
	}
}

string Lexer::getStrVar(int ch) {
	return strData[ch];
}

int Lexer::getIntVar(int ch) {
	return intData[ch];
}

int Lexer::getStaticInt(int ch) {
	return statData[ch];
}

bool Lexer::checkFormat(std::string & start, std::string & end) {
	bool s = start.find("header:") != std::string::npos ? true : false;
	bool e = end.find("footer:") != std::string::npos ? true : false;
	return (s && e);
}