/*Автор: Рець Вадим Олександрович, група К-12*/
#include "Lexer.h"
class Builder {
public:
	//Constructors
	Builder() = default;
	Builder(Data * p);

	//Reads file and assigns the values given to variables of container
	bool readFile(std::string & filename, Data * d);
private:
	Lexer lex;
	Data * data;
};