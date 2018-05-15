/*Автор: Рець Вадим Олександрович, група К-12*/
#include <iostream>
#include <string>
#include "Info.h"
struct Node {
	int sumMiss;
	std::string name;
	std::string surname;
	std::string country;
	int minShootingTime;
	int bestStage;
	Node * next;
	Info info;
};
struct Pointers {
	Node * point;
	Pointers * next;
};

class Point {
public:
	//Constructor and destructor
	Point();
	~Point();
	
	//Adds new element
	void push(Pointers *p);

	//Returns a pointer to the top element
	Pointers * getTop();
private:
	Pointers * HEAD;
};
class Data {
public:
	//Constructors and destructor
	Data();

	Data(const Data &) = delete;
	Data(Data &&) = delete;
	Data & operator = (const Data &) = delete;
	Data & operator = (Data &&) = delete;

	~Data();

	//Finds suitable place for a node given - they should be sorted
	void setPlace(Node * el);

	//Prints the whole array
	void goThrough();

	//Returns a pointer to a node with desired name, or nullptr if it doesn't exist
	Node * getNode(std::string fullName);

	//Returns a pointer to the top element
	Node * getTop();

	//Prepares the node for a check
	void isolate(Node * p);

	//Returns the sum of all missNumbers
	int getMissNumber();

	//Setters
	void setSumMiss(int n, Node * p);
	void setName(std::string n, Node * p);
	void setSurname(std::string n, Node * p);
	void setCountry(std::string n, Node * p);
	void setMinShootingTime(int n, Node * p);
	void setBestStage(int n, Node * p);

	//Getters
	Point * getNodeBySumMiss(int n);
	Point * getNodeByName(std::string n);
	Point * getNodeBySurname(std::string n);
	Point * getNodeByCountry(std::string n);
	Point * getNodeByMinShootingTime(int n);
	Point * getNodeByBestStage(int n);

	//Checks whether there are no other entries with the same start number
	bool checkSanity(int num);
	
	//Iterator
	class Iterator {
	public:
		//Constructors
		Iterator() = default;
		Iterator(Node * p);

		//Getting the pointer to an element if it exists
		Node * operator * () const;

		//Moving forward if possible
		Iterator & operator ++();

		//Returning true if current node isn't nullptr and false if it's nullptr
		operator bool() const;

	private:
		Node * current;
	};

private:
	Node * HEAD;
};
