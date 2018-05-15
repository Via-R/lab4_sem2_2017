/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include <string>

struct InfoNode {
	int stage;
	int number;
	int totalTime;
	int place;
	int minTime;
	int missNum;
	int extraLapsTime;
	InfoNode * next;
};

class Info {
public:
	//Constructors and destructor
	Info();
	~Info();
	Info(const Info &) = delete;
	Info(Info &&) = delete;
	Info & operator = (const Info &) = delete;
	Info & operator = (Info &&) = delete;

	//Appends an element to a suitable place - elements should be sorted
	bool append(InfoNode *p);

	//Returns the maximum stage number
	int getStagesNum();

	//Returns a pointer to the top element
	InfoNode * getTop();

	//Iterator
	class InfoIterator {
	public:
		//Constructors
		InfoIterator() = default;
		InfoIterator(InfoNode * p);

		//Getting the pointer to an element if it exists
		InfoNode * operator * () const;

		//Moving forward if possible
		InfoIterator & operator ++();

		//Returning true if current node isn't nullptr and false if it's nullptr
		operator bool() const;

	private:
		InfoNode * current;
	};

private:
	InfoNode * HEAD;
};