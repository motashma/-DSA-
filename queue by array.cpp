#include<iostream>
using namespace std;
class Queue { 
    int size = 5;
    int arr[5];
    int rear;
    int front;

public:
    Queue() {
        rear = -1;
        front = 0;
    } 

    void enqueue(int v) {
        if (rear == size - 1) {
            cout << "Queue is full" << endl;
    
        }
        else{
        arr[++rear] = v;
		}
    }

    void dequeue() {
       
        cout << "Dequeued: " << arr[front] << endl;
    front++;
    }

    void empty() {
        if (front == rear) {
            cout << "Queue is empty" << endl;
        }
    }

    void full() {
        if (rear == size - 1) {
            cout << "Queue is full" << endl;
        }
    }

    void display() {
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << endl;    
        }
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
	 q.full();
    return 0;
}

