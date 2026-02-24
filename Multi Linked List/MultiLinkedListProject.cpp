#include <iostream>
using namespace std;

class Node
{
public:
    float weight;
    string name;
    Node *next;     //link
    Node *next2;    //2nd link
};

class List
{
private:
    Node* head;
    Node* head2;

public:
    void Add(string name, float weight)
    {
        Node* person = new Node();          // create person node

        Node* current;

        person->name = name;                // insert name and weight as data
        person->weight = weight;

        //Sorted Insertion for Weights
        if (head == NULL || (head)->weight >= person->weight) { //head end
            person->next = head;
            head = person;
        }
        else {  //locate node to insert
            current = head;
            while (current->next != NULL && current->next->weight < person->weight) 
            {
                current = current->next;
            }
            person->next = current->next;   //update list
            current->next = person;
        }


        //Sorted Insertion for Names
        if (head2 == NULL || (head2)->name >= person->name) {
            person->next2 = head2;
            head2 = person;
        }
        else {
            current = head2;
            while (current->next2 != NULL && current->next2->name < person->name) 
            {
                current = current->next2;
            }
            person->next2 = current->next2;
            current->next2 = person;
        }
    }

    void PrintWeightSort()
    {
        Node* temp = head;
        while (temp)
        {
            cout << temp->name << " - " << temp->weight << ", ";       // print names and weights
            temp = temp->next;                // move to next value in list
        }
        cout << endl;
    }

    void PrintNameSort()        //same thing as PrintWeightSort()
    {
        Node* temp = head2;
        while (temp)
        {
            cout << temp->name << " - " << temp->weight << ", ";
            temp = temp->next2;
        }
        cout << endl;
    }
};

int main()
{
    List* theList = new List();
    string name;
    float weight;
    for (int i = 0; i < 15; i++)
    {
        cout << "Name: ";
        cin >> name;
        cout << "Weight: ";
        cin >> weight;
        theList->Add(name, weight);
    }

    //print names and weights
    cout << "\nNames & weights sorted(ascending) by name.: ";
    theList->PrintNameSort();
    cout << "\nNames & weights sorted(ascending) by weight.: ";
    theList->PrintWeightSort();
    
    return 0;
}

/* Output
//
Name: Mark                         
Weight: 150
Name: Tina 
Weight: 115
Name: Zach 
Weight: 55 
Name: Amy  
Weight: 140
Name: Steve
Weight: 220
Name: Brian
Weight: 250
Name: Liz
Weight: 125
Name: Brian
Weight: 220
Name: Laura
Weight: 115
Name: Alex
Weight: 175
Name: Jason
Weight: 210
Name: Eric
Weight: 175
Name: Aaron
Weight: 195
Name: Brandon
Name: Brandon
Weight: 78

Names & weights sorted(ascending) by name.: Aaron - 195, Alex - 175, Amy - 140, Brandon - 78, Brian - 220, Brian - 250, Eric - 175, Jason - 210, Kim - 135, Laura - 115, Liz - 125, Mark - 150, Steve - 220, Tina - 115, Zach - 55,

Names & weights sorted(ascending) by weight.: Zach - 55, Brandon - 78, Laura - 115, Tina - 115, Liz - 125, Kim - 135, Amy - 140, Mark - 150, Eric - 175, Alex - 175, Aaron - 195, Jason - 210, Brian - 220, Steve - 220, Brian - 250, */