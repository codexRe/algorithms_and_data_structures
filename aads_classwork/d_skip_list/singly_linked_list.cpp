#include<bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node* next;
    Node(int data): data(data), next(nullptr){}
};

class LinkedList{
    Node* head;

    public:
        LinkedList(){
            head = nullptr;
        }

        void insertAtHead(int key){ // insertion at end
            Node* newNode = new Node(key);
            
            if(head == nullptr){
                head = newNode;
                return;
            }

            newNode->next = head;
            head = newNode;
        }

        void insertAfter(int key, int after, bool insertIfNotFound){
            Node* newNode = new Node(key);
            Node* temp1 = head;

            if (temp1 == nullptr){
                head = newNode;
                return;
            }

            while (temp1 != nullptr && temp1->data != after){
                temp1 = temp1->next;
            }

            if (!temp1){
                if (insertIfNotFound){
                    Node* tail = head;
                    while (tail->next != nullptr) {
                        tail = tail->next;
                    }
                    tail->next = newNode;
                }
                else{
                    cout << "Element " << after << " which key is to be inserted not found! Aborting operation.\n";
                    delete newNode;
                }
                return;
            }
            newNode->next = temp1->next;
            temp1->next = newNode;
        }

        void insertAtEnd(int key){
            insertAfter(key, -1, true);
        }

        void display(){ // traversal
            Node* temp = head;

            if(head == nullptr){
                cout << "List is Empty!\n";
                return;
            }

            while(temp != nullptr){
                cout << temp-> data <<" ";
                temp = temp->next;
            }
            cout <<"\n";
        }

        void deleteElement(int key){
            if(!head){
                cout << "List is Empty!\n";
                return;
            }

            Node* prev = head;
            if(head->data==key){
                head = head->next;
                delete prev;
                return;
            }

            Node* temp = head;
            while(temp != nullptr && temp->data != key){
                prev = temp;
                temp = temp->next;
            }

            if (!temp){
                cout << "Element not found! Aborting operation.\n";
                return;
            }

            prev->next = temp->next;
            delete temp;
        }
};

int main(){
    // cout << "Only one rule, keys are >= 0\n\n";
    LinkedList list;
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtHead(1); // list: 1 -> 2 -> 3
    list.insertAfter(5, 3, false); // list: 1 -> 2 -> 5 -> 3
    list.insertAfter(4, 3, false);
    list.insertAtEnd(8);
    list.display();
    list.deleteElement(4);
    list.display();

}