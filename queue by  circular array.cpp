#include <iostream>
using namespace std;

const int size = 5;

class Queue {
private:
    int arr[size];
    int front;
    int rear;
    int count;

public:
    Queue() {
        front = 0;
        rear = 0;
        count = 0;    
    }    

    void enqueue(int v) {
        if (count == size) {
            cout << "Queue is full \n";
        } else {
            arr[rear] = v;
            rear = (rear + 1) % size;
            count++;
        }
    }

    void dequeue() {  
        if (count == 0) {
            cout << "Queue is empty \n";
        } else { 
            int value = arr[front];
            front = (front + 1) % size;
            cout << "Dequeued: " << value << endl;
            count--;
        }
    }

    void full() const {
        if (count == size) {
            cout << "Queue is full \n";
        }    
    }

    void empty() const {
        if (count == 0) {
            cout << "Queue is empty \n";
        }
    }

    void display() const {
        cout << "Display: \n";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % size] << endl;
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
    q.display();

    q.dequeue();
    q.display();

    q.full();
    q.empty();

    return 0;
}

