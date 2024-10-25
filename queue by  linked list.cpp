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

    void enqueue(int v) {
    	
        Node* n = new Node();
        
        n->data=v;
        n->next=NULL;
        if (rear == NULL) {  
            front = rear = n;  
            
        }
        else{
		
        rear->next = n; 
        rear = n; }
    }

    void dequeue() {
        if (front == NULL) {  
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Dequeued: " << front->data << endl;
        Node* temp = front; 
        front = front->next; 
        delete temp;
    }

    void empty() {
        if (front == NULL) {  
            cout << "Queue is empty" << endl;
}
}

    void display() {
        Node* current = front;
        while (current != NULL) {  
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    q.dequeue();
    q.dequeue();

    q.display(); 
    q.empty();   

    return 0;
}

