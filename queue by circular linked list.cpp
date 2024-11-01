#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next; 
    
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = NULL;  
        rear = NULL;  
    }

    void enqueue(int value) {
    	
        Node* n = new Node();
        
        n->data=value;
        n->next=NULL;
        if (rear == NULL) {  
            front = rear = n;
			  
            return;
        }
        else{
		
        rear->next = n; 
        rear = n; 
    }
        rear -> next=front;
    }

    void dequeue() {
        if (front == NULL) {  
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Dequeued: " << front->data << endl;
        Node* temp = front; 
        
        if (front == NULL) {  
            rear = NULL; 
        }
        else { 
		front = front->next; 
		rear->next = front; 
		}
        delete temp;
    }

    void empty() {
        if (front == NULL) {  
            cout << "Queue is empty" << endl;
        } else {
            cout << "Queue is not empty" << endl;
        }
    }

    void display() {
        Node* ptr = front;
        cout<<"Elements of queue"<<endl;
        do { cout << ptr->data << " "; 
		ptr = ptr->next; 
		} while (ptr != front);
		 
        cout << endl;
    }
};
 int main()
{
    Queue q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	q.display();
	q.dequeue( );
	q.display();
	
	q.empty();
	

	
	
	return 0;
}