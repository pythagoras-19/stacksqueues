#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include<string.h>
#include <vector>
using namespace std;
struct Node
{
    int value;
    Node* next;
    Node* prev;
};
//QUEUES
void dequeue(Node* &front, Node* &rear) // remove from front
{
	Node* temp;
	//this is where we need to focus!
	if(front)
	{
		temp = front;
		front = front->next;
		delete temp;
		if(!front)
		{
			rear = NULL;
		}
	}
}
void enqueue(Node* &front, Node* &rear, int value) // put it at the end 
//pass by alias to affect front and rear directly
{
    Node* nn = new Node;
    nn->value = value;
	nn->next = NULL; // end value
	//differentiate between an empty queue and not empty queue
	if(!front) // checking if not empty
	{
		std::cout << "In !front(), nn->value: " << nn->value << std::endl;
		rear = front = nn;
		//assign rear and front with the Node nn
	}
	else // insert another node
	{
		std::cout << "In else(), nn->value: " << nn->value << std::endl;
		rear->next = nn;
		rear = nn;
	}
}
void traverse(Node* front, Node* rear)
{
	std::cout << "In traverse() " << std::endl;
	Node* currentNode;
	for(currentNode = front; currentNode; currentNode = currentNode->next)
	{
		std::cout << currentNode->value << std::endl;
	}
}

//STACKS
void removeFromStack(Node* poppedNode) // DON'T NEED THIS ANYMORE, DELETE
/* delete because we allocated memory on heap for our stack nodes. Now that we popped our nodes from the stack
we want to delete them from memory. This is good practice and is functional for dynamic memory management.*/
{
	std::cout << "called removeFromStack() on: " << poppedNode->value << "\n";
	delete poppedNode; 
}
bool isEmpty(Node *&top)
{
	if(!top)
	{
		return true;
	}
	else return false;
}
void push(Node *&top, Node *&bottom, int num)
{
	std::cout << "Called push()\n";
	Node* newNode = new Node;
	Node* temp = new Node;
	newNode->value = num;
	if(!top) // top == NULL
	{
		top = newNode;
		top->prev = NULL;
		top->next = NULL;
		bottom = newNode;
		bottom->prev = NULL;
		bottom->next = NULL;
	}
	else
	{
		temp = newNode;
		temp->prev = NULL;
		temp->next = top;
		top->prev = temp;
		top = temp;
	}
	
}
int getLengthOfStack(Node *&top)
{
	Node* current;
	int i = 0;
	for (current = top; current; current = current->next, i++){}
	std::cout << "Length of stack is :" << i << std::endl;
	return i;
}

int pop(Node *&top)
{
	Node* temp = new Node; // used to hold the value of top so we can then delete that node after top becomes top->next
	int nodeValue = -999;
	if (getLengthOfStack(top) == 0)
	{
		std::cout << "Stack is empty! You are trying to pop a value from an empty stack!\n";
		return 0;
	}
	else
	{
		std::cout << top->value << " popped from stack." << std::endl;
		nodeValue = top->value;
		temp = top;
		top = top->next;
		delete temp;
		return nodeValue;
	}
}
//DEQUES
int getLengthOfDeque(Node *&top, Node *&bottom)
{
	std::cout << "getLengthOfDeque() called\n";
	Node* current = new Node;
	if (!top)
	{
		std::cout << "It is now an empty deque.\n";
		return 0;
	}
	int i = 0;
	for (current = top; current; current = current->next, i++); // missing semicolon here caused weird bug that was hard to solve!
	//std::cout << "i: " << i << std::endl;
	delete current;
	return i;
	
}
void printDeque(Node *&top, Node *&bottom)
{
	std::cout << "In printDeque()\n";
	Node* current = top;
	for(; current; current = current->next) 
	{
		std::cout << current->value << std::endl;
	}
	std::cout << "bottom->value: " << bottom->value << std::endl;
	delete current;
}
void pushFront(Node *&top, Node *& bottom, int value)
{
	std::cout << "pushFront() called\n";
	Node* newNode = new Node;
	Node* temp = new Node;
	if (!top)//if top is NULL
	{
		top = newNode;        //top is now a new node
		bottom = newNode;     //bottom is now a new node
		//bottom = top; 
		top->value = value;   //top = value passed in function header
		bottom->value = value;//bottom = value passed in function header
		top->prev = NULL;     //since there are no other nodes in our deque we set prev pointer to null
		top->next = NULL;     ////since there are no other nodes in our deque we set next pointer to null
	}
	else
	{
		std::cout << top->value << std::endl;
		temp = top; // temp node = previous top
		top = newNode; // give top a new node 
		top->value = value; // new top node gets new value
		top->prev = NULL; // 0
		top->next = temp; // top->next = previous top node
		bottom = bottom; // bottom stays bottom (1)
	}
}
void pushBack(Node *&top, Node *&bottom, int value)
{
	std::cout << "pushBack() called\n";
	Node* newNode = new Node;
	Node* temp = new Node;
	if(!bottom) // empty deque (no elements)
	{
		bottom = newNode;        // bottom is now a new node
		top = newNode;           // top is now a new node
		top->value = value;      // top = value passed in function header
		bottom->value = value;   // bottom = value passed function header
		bottom->prev = NULL;     // since this is the only node in our deque prev pointer will be null
		bottom->next = NULL;     // since this is the only node in our deque next pointer will be null
	}
	else
	{
		std::cout << "bottom value was : " << bottom->value << std::endl;
		temp->value = value; // temp->value = 13
		temp->prev = bottom; // temp->prev = 1
		temp->next = NULL;   // temp->next = null
		bottom->next = temp; // bottom->next = 13
		bottom = temp;       // bottom = 13
		std::cout << "new bottom value: " << bottom->value << std::endl;
	}
}
int popFront(Node *&top, Node *&bottom)
{
	Node* temp = new Node; // used to hold the value of top so we can then delete that node after top becomes top->next
	int nodeValue = -999;
	if (getLengthOfDeque(top, bottom) == 0)
	{
		std::cout << "Deque is empty! You are trying to pop a value from an empty deque!\n";
		return 0;
	}
	else
	{
		//std::cout << top->value << " popped from deque." << std::endl;
		nodeValue = top->value;
		temp = top;
		top = top->next;
		delete temp;
		return nodeValue;
	}
}
int popBack(Node *&top, Node *&bottom)
{
	Node* temp = new Node;
	int nodeValue = -999;
	if (getLengthOfDeque(top, bottom) == 0)
	{
		std::cout << "Deque is empty! You are trying to pop a value from an empty deque!\n";
		return 0;
	}
	else
	{
		std::cout << bottom->value << " popped from deque.\n";
		nodeValue = bottom->value;
		temp = bottom;
		bottom = bottom->prev;
		delete temp;
		return nodeValue;
	}
	
}
int main()
{
    //Node* head = new Node;
	Node* front = NULL;
	Node* rear = NULL;
	FILE* filePtr;
	int number[50];
	filePtr = fopen("input.txt", "r");
	if(filePtr == NULL)
	{
		std::cout << "Error! Nothing in file!" << std::endl;
		exit(1);
	}//
	int i = 0;
//QUEUES
	while (fscanf(filePtr,"%d", &number[i]) != EOF)
	{
		//no elements
		std::cout << "In loop " <<  number[i] << std::endl;
		std:: cout << "front: " << front << std::endl;
		std::cout << "rear: " << rear << std::endl;
		
		enqueue(front, rear, number[i]);
		i++;
	}
	dequeue(front, rear);

	fclose(filePtr);

	traverse(front, rear);
//STACKS
	filePtr = fopen("input.txt", "r");
	if(filePtr == NULL)
	{
		std::cout << "Error! Nothing in file!" << std::endl;
		exit(1);
	}
	Node* top = NULL;
	Node* bottom = NULL;
	i=0;
	while (fscanf(filePtr,"%d", &number[i]) != EOF)
	{
		push(top, bottom, number[i]);
		i++;
	}
	int lengthOfTheStack = getLengthOfStack(top);
	//Node* poppedValueFromStack = new Node;
	int poppedValue = -999;
	for(i=0; i < lengthOfTheStack; i++)
	{
		poppedValue = pop(top);
		std::cout << poppedValue << " popped from stack!\n";
	}
	/*to make sure our stack holding a linked list deleted properly we will call getlengthOfStack()*/
	lengthOfTheStack = getLengthOfStack(top);
	fclose(filePtr);

//DEQUES (double ended queues)
	std::cout << "Beginning deque operations.\n";
	filePtr = fopen("input.txt", "r");
	if(filePtr == NULL)
	{
		std::cout << "Error! Nothing in file!" << std::endl;
		exit(1); // exit the program if we can't open the file
	}
	//top, bottom = NULL;
	top = NULL;
	bottom = NULL;
	while (fscanf(filePtr,"%d", &number[i]) != EOF) // while we keep reading from the file and read in a number and we haven't reached the end of file (EOF)
	{
		if (number[i] >= 10)
		{
			pushBack(top, bottom, number[i]);
		}
		else pushFront(top, bottom, number[i]);
		i++;
	}
	int lengthOfTheDeque = getLengthOfDeque(top, bottom);
	std::cout << "The length of the deque is: " << lengthOfTheDeque << std::endl;
	int dequePoppedValue = -999;
	std::cout << "Top: " << top->value << "\nBottom: " << bottom->value << std::endl;
	printDeque(top, bottom);
	//TODO: searching algorithms practice
	
	//poppiing all data from deque
	for(i=0; i < lengthOfTheDeque; i++)
	{
		//poppedValue = popFront(top);
		//dequePoppedValue = popFront(top, bottom);
		dequePoppedValue = popFront(top,bottom);
		std::cout << dequePoppedValue << " popped from deque!\n";
	}
	lengthOfTheDeque = getLengthOfDeque(top, bottom);
	std::cout <<  lengthOfTheDeque << std::endl;
	fclose(filePtr);
    return 0;
}