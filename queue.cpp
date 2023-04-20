

#include "queue.h"
#include "system.h"


Queue::~Queue(){
	lock
	while(first){
		Node* del=first;
		first=first->next;
		delete del;
	}
	first=last=0;
	unlock
}


void Queue::add(PCB* e){
	lock
	Node* help=new Node();
	help->elem=e;
	help->next=0;
	if(first==0) first=help;
	last=help;
	unlock
}

void Queue::remove(PCB* e){

	Node* current=first;
	Node* prev=0;
	lock
	if(first==0){ //red prazan
		unlock
		return;
	}
	while(current && current->elem!=e){ // trazimo element
		prev=current;
		current=current->next;
	}

	if(current==0){
		unlock
		return;
	}
	if(current==first){
		first=first->next;
		delete current;
		unlock
		return;
	}
	if(current==last){
		last=prev;
		prev->next=0;
		delete current;
		unlock
		return;
	}else{
		prev->next=current->next;
		delete current;
		unlock
		return;
	}
}

PCB* Queue::get(){
	Node* current=0;
	lock
	if(first==0){
		unlock
		return 0;
	}
	current=first;
	first=first->next;
	if(first==0){
		last=0;
	}
	unlock
	current->next=0;
	return current->elem;
}

int Queue::isEmpty(){
	if(first==0) return 1;
	else return 0;
}

PCB* Queue::find(int e){
	lock
	Node* help=first;
	while(help!=0){
		if(help->elem->getID()==e){
			unlock
			return help->elem;
		}
	help=help->next;
	}
	unlock
	return 0;
}



