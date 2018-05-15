/*Автор: Рець Вадим Олександрович, група К-12*/
#include "Data.h"
class Lexer {
public:
	//Ignoring the default constructor
	Lexer() = default;

	//Parsing the string given into an information to be stored in class
	void parseStr(std::string & line, int & c, int & error);

	//Functions that return specific private variables
	std::string getStrVar(int ch);
	int getIntVar(int ch);
	int getStaticInt(int ch);
	bool checkFormat(std::string & start, std::string & end);

private:
	int intData[10];
	std::string strData[3];
	static int statData[3];
};