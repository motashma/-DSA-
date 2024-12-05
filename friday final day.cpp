#include <iostream>
using namespace std;
class Order {
public:
    string customerName;
    string productName;
    int quantity;
    double bill;
    int orderId;
    Order* next;

    Order(string name, string product, int qty, double b, int id) {
        customerName = name;
        productName = product;
        quantity = qty;
        bill = b;
        orderId = id;
        next = nullptr;
    }
};

class OrderQueue {
public:
    Order* front;
    Order* rear;
    static int orderIdCounter;  // Static variable to track order ID

    OrderQueue() {
        front = rear = nullptr;
    }

    // Method to generate a unique order ID
    static int generateOrderId() {
        return ++orderIdCounter;  // Increment and return the new unique ID
    }

    void enqueue(string name, string product, int quantity, double bill, int orderId) {
        Order* newNode = new Order(name, product, quantity, bill, orderId);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Order placed for: " << name << " | Product: " << product << " | Quantity: " << quantity << " | Bill: " << bill 
             << " | Order ID: " << orderId << endl;
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "No orders to process.\n";
            return;
        }
        Order* temp = front;
        cout << "Processing order for: " << front->customerName << " | Product: " << front->productName << endl;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    void display() {
        if (front == nullptr) {
            cout << "No orders in the queue.\n";
            return;
        }
        Order* temp = front;
        while (temp != nullptr) {
            cout << "Order ID: " << temp->orderId << " | Customer: " << temp->customerName << " | Product: " << temp->productName
                 << " | Quantity: " << temp->quantity << " | Bill: " << temp->bill << endl;
            temp = temp->next;
        }
    }

    bool cancelOrder(int orderId) {
    Order* current = front;
    Order* prev = nullptr;
    while (current != nullptr) {
        if (current->orderId == orderId) {
            if (prev == nullptr) {
                front = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == rear) {
                rear = prev;
            }
            delete current;
            cout << "Order with ID " << orderId << " canceled.\n";
            return true; // Return true indicating successful cancellation
        }
        prev = current;
        current = current->next;
    }
    // If the orderId was not found, display an invalid ID message
    cout << "Invalid Order ID: " << orderId << ". No such order exists.\n";
    return false; // Return false if the order was not found
}


    void searchOrder(int orderId) {
        Order* current = front;
        bool found = false;
        while (current != nullptr) {
            if (current->orderId == orderId) {
                cout << "Order found: \n";
                cout << "Customer: " << current->customerName << " | Product: " << current->productName 
                     << " | Quantity: " << current->quantity << " | Bill: " << current->bill << endl;
                found = true;
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Order ID " << orderId << " not found in this queue.\n";
        }
    }
    bool isOrderIdUsed(int orderId) {
    Order* current = front;
    while (current != nullptr) {
        if (current->orderId == orderId) {
            return true;  // If the orderId is found
        }
        current = current->next;
    }
    return false;  // Return false if orderId is not found
}

};

int OrderQueue::orderIdCounter = 10;  

class TakeAwayOrderQueue : public OrderQueue {
public:
    void placeTakeAwayOrder(string name, string product, int quantity, double bill, int orderId) {
        enqueue(name, product, quantity, bill, orderId);
    }
};

class DeliveryOrderQueue : public OrderQueue {
public:
    void placeDeliveryOrder(string name, string product, int quantity, double bill, int orderId, int deliveryCharges) {
        enqueue(name, product, quantity, bill + deliveryCharges, orderId);
    }
};

int city() {
    int opt;
    cout << "\nThe delivery is available for the following Areas : \n";
    cout << "\n---------------------------------";
    cout << "\n |CITY CODE |        City       |";
    cout << "\n---------------------------------";
    cout << "\n |     1    |    Islamabad      |";
    cout << "\n |     2    |    Lahore         |";
    cout << "\n |     3    |    Karachi        |";
    cout << "\n |     4    |    Multan         |";
    cout << "\n |     5    |    Peshawar       |";
    cout << "\n |     6    |    Quetta         |";
    cout << "\n |     7    |    Abbotabad      |";
    cout << "\n |     8    |    Skardu         |";
    cout << "\n |     9    |    Gawadar        |";
    cout << "\n |    10    |    Liaquat Bhag   |";
    cout << "\n---------------------------------\n";
    cout << "Enter your option: ";
    
    while (true) {
        cin >> opt;
        if (opt >= 1 && opt <= 10) {
            break;  // Valid city selected, break the loop
        } else {
            cout << "Invalid input. Please enter a valid city code (1 to 10): ";
        }
    }
    return opt;
}

int main() {
    string products[] = {"", "Facial Cleanser", "Moisturizing Cream", "Anti-Aging Serum", "Acne Treatment",
                          "Sunscreen SPF 50", "Vitamin C Serum", "Exfoliating Scrub", "Hydrating Face Mask",
                          "Eye Cream", "Night Repair Cream"};
    int prices[] = {0, 500, 1200, 1800, 800, 1500, 2500, 1000, 1300, 600, 2200};
    int stock[] = {0, 10, 5, 8, 0, 15, 7, 3, 6, 12, 4};
    string cityNames[] = {"", "Islamabad", "Lahore", "Karachi", "Multan", "Peshawar", "Quetta", "Abbotabad", "Skardu", "Gawadar", "Liaquat Bhag"};

    TakeAwayOrderQueue takeAwayQueue;
    DeliveryOrderQueue deliveryQueue;
bool exitProgram = false; // Global flag for program exit

    while (!exitProgram) { // Top-level loop
        string role;
        cout << "Enter role (admin/customer or 'exit' to quit): ";
        cin >> role;

        if (role == "exit") {
            exitProgram = true; // Set flag to exit the program
            break;
        }

        if (role == "admin") {
            int choice = -1;
    
            while (choice != 0) { // Admin menu loop
                cout << "\n*********** Admin Menu ***********\n";
                cout << "1. Serve Delivery Orders\n";
                cout << "2. Serve Takeaway Orders\n";
                cout << "3. Display All Delivery Orders\n";
                cout << "4. Display All Takeaway Orders\n";
                cout << "0. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        deliveryQueue.dequeue();
                        break;
                    case 2:
                        takeAwayQueue.dequeue();
                        break;
                    case 3:
                        deliveryQueue.display();
                        break;
                    case 4:
                        takeAwayQueue.display();
                        break;
                    case 0:
                        cout << "Exiting...\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            }
        } else if (role == "customer") {
            int choice = -1;
            while (choice != 0) {  // Customer menu loop
                cout << "\n*********** Customer Menu ***********\n";
                cout << "1. View Products and Prices\n";
                cout << "2. Order Takeaway\n";
                cout << "3. Order Delivery\n";
                cout << "4. Cancel My Order\n";
                cout << "5. Track My Order\n";
                cout << "0. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                    case 1: {  // View Products
                        cout << "\n*********** Products List ***********\n";
                        for (int i = 1; i <= 10; i++) {
                            cout << i << ". " << products[i] << " | Price: " << prices[i] << " | Stock: " << stock[i] << endl;
                        }
                        break;
                    }
           case 2: {  // Ordering Takeaway
    string name;
    int productNum, quantity, orderId;
    double bill;

    cout << "Enter your name: ";
    cin >> name;

    cout << "\n*********** Products List ***********\n";
    for (int i = 1; i <= 10; i++) {
        cout << i << ". " << products[i] << " | Price: " << prices[i] << " | Stock: " << stock[i] << endl;
    }

    // Loop until valid product number is entered
    cout << "Select product number: ";
    while (true) {
        cin >> productNum;
        if (productNum >= 1 && productNum <= 10) {
            break;  // Valid product selected, break the loop
        } else {
            cout << "Invalid input. Please enter a valid product number (1 to 10): ";
        }
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (stock[productNum] >= quantity) {
        bill = prices[productNum] * quantity;
        orderId = OrderQueue::generateOrderId();
        takeAwayQueue.placeTakeAwayOrder(name, products[productNum], quantity, bill, orderId);
        stock[productNum] -= quantity;
    } else {
        cout << "Insufficient stock for this product.\n";
    }
    break;
}

case 3: {  // Ordering Delivery
    string name;
    int productNum, quantity;
    double bill;

    int optionDelivery;
    string streetAddress;
    optionDelivery = city();

    if (optionDelivery < 1 || optionDelivery > 10) {
        cout << "Invalid city option. Try again.\n";
        break;
    }

    cout << "Selected City: " << cityNames[optionDelivery] << endl;
    cout << "Enter your street address: ";
    cin.ignore();
    getline(cin, streetAddress);

    cout << "Enter customer name: ";
    cin >> name;

    cout << "\n*********** Products List ***********\n";
    for (int i = 1; i <= 10; i++) {
        cout << i << ". " << products[i] << " | Price: " << prices[i] << " | Stock: " << stock[i] << endl;
    }
   
while (true) {
        cin >> productNum;
        if (productNum >= 1 && productNum <= 10) {
            break;  // Valid product selected, break the loop
        } else {
            cout << "Invalid input. Please enter a valid product number (1 to 10): ";
        }
    }
    cout << "Enter quantity: ";
    cin >> quantity;

    // Check stock availability
    if (quantity > stock[productNum]) {
        cout << "Sorry, we only have " << stock[productNum] << " of " << products[productNum] << " in stock.\n";
        break;
    }
    bill = prices[productNum] * quantity;
    stock[productNum] -= quantity;

    int orderId = OrderQueue::generateOrderId();

    // Check if the orderId already exists in either queue
    if (takeAwayQueue.isOrderIdUsed(orderId) || deliveryQueue.isOrderIdUsed(orderId)) {
        cout << "Order ID already used. Try again.\n";
        break;
    }

    double deliveryCharges = 200;  // Set delivery charges

    cout << "\nOrder Details (before delivery charges):\n";
    cout << "Customer Name: " << name << "\n";
    cout << "Product: " << products[productNum] << "\n";
    cout << "Quantity: " << quantity << "\n";
    cout << "Subtotal: " << bill << endl;

    double totalBill = bill + deliveryCharges;

    cout << "\nDelivery Charges: " << deliveryCharges << endl;
    cout << "Total Bill (including delivery charges): " << totalBill << endl;

    deliveryQueue.placeDeliveryOrder(name, products[productNum], quantity, bill, orderId, deliveryCharges);

    cout << "\nDelivery order has been placed successfully!\n";
    cout << "City: " << cityNames[optionDelivery] << " | Street Address: " << streetAddress << " | Order ID: " << orderId << endl;
    break;
}
case 4: {  // Cancel Order
    int orderId;
    cout << "Enter Order ID to cancel: ";
    cin >> orderId;
    if (!takeAwayQueue.cancelOrder(orderId)) {
        if (!deliveryQueue.cancelOrder(orderId)) {
            cout << "Invalid Order ID. Order not found in either queue.\n";
        }
    }
    break;
}


                    case 5: {  // Track Order
    int orderId;
    cout << "Enter Order ID to track: ";
    cin >> orderId;

    bool found = false; // Flag to track if the order is found
    string customerName, productName;
    int quantity;
    double bill;

    // Check Takeaway Queue
    Order* current = takeAwayQueue.front;
    while (current != nullptr) {
        if (current->orderId == orderId) {
            found = true;
            customerName = current->customerName;
            productName = current->productName;
            quantity = current->quantity;
            bill = current->bill;
            break;
        }
        current = current->next;
    }

  
    if (!found) {
        current = deliveryQueue.front;
        while (current != nullptr) {
            if (current->orderId == orderId) {
                found = true;
                customerName = current->customerName;
                productName = current->productName;
                quantity = current->quantity;
                bill = current->bill;
                break;
            }
            current = current->next;
        }
    }

    if (found) {
        cout << "Order found: \n";
        cout << "Customer: " << customerName << " | Product: " << productName 
             << " | Quantity: " << quantity << " | Bill: " << bill << endl;
    } else {
        cout << "Order ID " << orderId << " not found in any queue.\n";
    }
    break;
}
                    case 0:
                        cout << "Exiting...\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            }
        } else {
            cout << "Invalid role. Try again.\n";
        }
    }

    return 0;
}
