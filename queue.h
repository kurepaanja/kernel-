

#ifndef QUEUE_H_
#define QUEUE_H_


class PCB;

class Queue{
private:
	struct Node{
		PCB* elem;
		Node* next;
	};

	Node* first,*last;

public:

	Queue(){
		first=last=0;
	}

	~Queue();
	void add(PCB* e);
	void remove(PCB* e);
	PCB* get();
	PCB* find(int e);



	int isEmpty();

};



#endif /* QUEUE_H_ */
