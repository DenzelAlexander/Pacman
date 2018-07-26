#ifndef MYDLL_H
#define MYDLL_H
#include <iostream>
#include <fstream>


using namespace std;





class HighScores
{
	struct Node
	{
		int i;
		string name;
		int Rank = 0;
		Node* next;
		Node *prev;
	};
	Node *head;
	Node *tail;

public:
HighScores()
{
	head = tail = nullptr;
}

~HighScores()
{
	clear();
}

void insert(int i, string name)
{
    Node * n = new Node;
    n->i = i;
    n->name = name;
    n->next = 0;
    n->prev = 0;

    if (head == 0)
        {
            head = n;
            tail = n;
            int Rank = 1;
            n->Rank = Rank;
        }
    else
        {
           Node * p = head;
            Node *q = 0;
            int Rank = 1;
            while (p != 0 && i < p->i)
                {
                q = p;
                p = p->next;
                Rank++;
                }
            if (q == 0)
            {
                head = n;
            }
            else
            {
                q->next = n;
            }
            if (p == 0)
            {
                tail = n;
            }
            else
            {
                p->prev = n;
            }
            n->Rank = Rank;
            n->prev = q;
            n->next = p;
            listEdit();

    }
}
    bool scoreCheck(int i)
{
    if(head == 0){
        cout << "Congratulations, you are one of the best players! " << endl;
        cout << "Please enter your name: ";
        return true;
    }
    Node * p = head;
    Node * q = 0;
    int Rank = 1;
    while (p != 0 && i < p->i && Rank < 11)
                {
                q = p;
                p = p->next;
                Rank++;
                }
    if (Rank <= 10){
        cout << "Congratulations, you are one of the best players! " << endl;
        cout << "Please enter your name: ";
        return true;
    }
    else
        return false;
}
void listEdit()
{
    Node * p = head;
    Node * q = 0;
    int Rank = 1;
    while (p != 0)
    {
        p->Rank = Rank;
        q = p;
        p = p->next;
        Rank++;
    }
    Rank--;
    if(Rank > 10)
    {
        p = 0;
        tail = tail->prev;
        tail->next = p;
        delete p;

    }
}
void remove(int i)
{
	Node* p = head, *q = nullptr;

	while(p && p->i != i)
	{
		q = p;
		p = p->next;
	}

	if(p)
	{
		if(q)
			q->next = p->next;
		else
			head = p->next;

		if(p->next)
			p->next->prev = q;
		else
			tail = q;

		delete p;
	}
}

bool find(int i) const
{
	Node* p = tail;

	while(p)
	{
		if(p->i == i)
			return true;

		p = p->prev;
	}

	return false;
}

void clear()
{
	while(tail)
	{
		Node* p = tail;
		tail = tail->prev;
		delete p;
	}

	head = nullptr;
}

void print() const
{
    std::cout << "=====Top 10 High Scores=====" << endl;
	for(Node* p = head; p; p = p->next){
        std::cout << p->Rank << ". ";
		std::cout << p->name << " ";
        std::cout << p->i << "\t";

	std::cout << std::endl;
	}
}

void reverse() const
{
	for(Node* p = tail; p; p = p->prev)
    std::cout << p->i << "\t";
	std::cout << std::endl;
}
    void saveScore(){
    ofstream myfile;
    myfile.open("example.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();
    }
};

#endif
