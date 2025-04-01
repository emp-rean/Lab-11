/*Ввести последовательность натуральных чисел. Если последовательность упорядочена по убыванию или по возрастанию, удалить из
последовательности простые числа, и продублировать числа, кратные 10. В противном случае упорядочить последовательность по неубыванию
первой цифры.   Последовательность хранить в двусвязном циклическом списке с фиктивным элементом.*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int d) : data(d), prev(nullptr), next(nullptr) {}
};

void addNode(Node* dummy, int value) {
    Node* newNode = new Node(value);
    newNode->prev = dummy->prev;
    newNode->next = dummy;
    dummy->prev->next = newNode;
    dummy->prev = newNode;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for(int i=5; i*i<=n; i+=6)
        if(n%i == 0 || n%(i+2) == 0) return false;
    return true;
}

bool isAscending(Node* dummy) {
    Node* curr = dummy->next;
    while(curr->next != dummy) {
        if(curr->data > curr->next->data) return false;
        curr = curr->next;
    }
    return true;
}

bool isDescending(Node* dummy) {
    Node* curr = dummy->next;
    while(curr->next != dummy) {
        if(curr->data < curr->next->data) return false;
        curr = curr->next;
    }
    return true;
}

int firstDigit(int n) {
    while(n >= 10) n /= 10;
    return n;
}

// Сортировка
void sortList(Node* dummy) {
    bool swapped;
    Node* ptr1;
    Node* lptr = dummy;

    if(dummy->next == dummy) return;

    do {
        swapped = false;
        ptr1 = dummy->next;

        while(ptr1->next != lptr) {
            if(firstDigit(ptr1->data) > firstDigit(ptr1->next->data)) {
                // Меняем данные местами
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while(swapped);
}

int main() {
    Node* dummy = new Node(0);
    dummy->prev = dummy;
    dummy->next = dummy;

    int num;
    cout << "Enter numbers: \n";
    while(cin >> num && num > 0)
        addNode(dummy, num);

    if(dummy->next == dummy) {
        cout << "Empty list!\n";
        delete dummy;
        return 0;
    }

    bool sorted = isAscending(dummy) || isDescending(dummy);

    if(sorted) {
        // Удаление простых чисел
        Node* curr = dummy->next;
        while(curr != dummy) {
            Node* next = curr->next;
            if(isPrime(curr->data)) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
            }
            curr = next;
        }

        // Дублирование кратных 10
        curr = dummy->next;
        while(curr != dummy) {
            if(curr->data % 10 == 0) {
                Node* copy = new Node(curr->data);
                copy->next = curr->next;
                copy->prev = curr;
                curr->next->prev = copy;
                curr->next = copy;
                curr = copy->next; // Пропускаем копию
            } else {
                curr = curr->next;
            }
        }
    } else {
        sortList(dummy);
    }

    // Вывод результата
    cout << "Result: ";
    Node* curr = dummy->next;
    while(curr != dummy) {
        cout << curr->data << " ";
        curr = curr->next;
    }

    // Очистка памяти
    curr = dummy->next;
    while(curr != dummy) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete dummy;
}