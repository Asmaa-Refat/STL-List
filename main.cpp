#include <iostream>
#include <iterator>
using namespace std;
template <class T>
//STL list implementation
class List
{
private:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;
    Node* dummy;    //the node after the tail node
    int length;    // tells me how many nodes are there in the list

public:
    List()  //default constructor
    {
        length = 0;
        Node* dummyNode = new Node;
        head = tail = dummyNode;
        dummy = dummyNode;
        dummy->next = nullptr;

    }

    List(T value, int initial_size)  // constructs a list having initial_size elements whose values are value <parametrized constructor>
    {
        length = initial_size;
        Node* newNode = new Node;
        newNode->data = value;

        head = tail = newNode;
        Node* temp = head;

        for(int i = 1; i < initial_size; i++)
        {
               Node* newnode = new Node;
               newnode->data = value;
               temp->next = newnode;
               temp = tail = temp->next;
               newnode->next = nullptr;
        }

         Node* dummyNode = new Node;
         tail->next = dummyNode;
         dummy = dummyNode;
    }

    int Size()     //returns the current number of elements in the list
    {
        return length;
    }

    void addFirst(T element)
    {
        Node* newnode = new Node;
        newnode->data = element;

        if(length == 0)
        {
           head = tail = newnode;
           newnode->next = dummy;
        }
        else
        {
           newnode->next = head;
           head = newnode;
        }
        length++;
    }


    Node* getPrevious(Node* target)  //takes a node and returns its previous node
    {
        Node* current = head;
        while(current != tail)
        {
            if(current->next == target)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    void Clear()
    {
        Node* temp = head;
        while(temp != dummy)
        {
            removeFirst();
            temp = temp->next;
        }
    }
//*********************************************
//*********************************************
    class Iterator           //inner class is like a friend, it can only access the outer class with an object
    {
     private:
            Node* current;
            List<T> obj;        //that's why i created that object
     public:
        Iterator(List<T>& obj)
        {
            current = obj.head;
            this->obj = obj;
        }

        Iterator(Node* node)
        {
            current = node;
        }

        void operator++ ()
        {
            current = current->next;
            if(current == obj.dummy)
                throw ("Exception: It's pointing after the last element!");
        }

        void operator-- ()
        {
            Node* prev = obj.getPrevious(current);
            current = prev;
            if(current == obj.head)
                throw ("Exception: It's pointing to the first element of the list!");
        }

        T& operator* ()    //dereference operator
        {
            return current->data;
        }

        bool operator == (const Iterator &other)  //comparing iterator with iterator
        {
            return current == other.current;
        }
        bool operator == (Node* node)    //comparing Iterator with a node
        {
            return current == node;
        }
    };
//*****************************************************
//*****************************************************
    void insertAtPos(int pos , T element)
    {
        if (pos == 0)
            addFirst(element);
        else if (pos == length)
            addLast(element);
        else
        {
            Node* newnode = new Node;
            newnode->data = element;

            Node* temp = head;
            for(int i =1; i<pos; i++)
                temp = temp->next;

            newnode->next = temp->next;
            temp->next = newnode;
            length++;
        }
    }

    void Insert(T value, Iterator position)  //adds an element at position specified by the iterator
    {
        int place = -1;   //the position of the node that the iterator points to
        Node* temp = head;
        while(temp != dummy)
        {
            if(position == temp)
            {
                place++;
                break;
            }
            place++;
            temp = temp->next;
        }
        insertAtPos(place,value);
    }

    void removeFirst()
    {
        if (length == 1)
        {
           head = tail = dummy;
           delete head;
           length--;
        }
        else
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            length--;
        }
    }

    void removeLast()
    {
        if (length == 1)
        {
           head = tail = dummy;
           delete tail;
           delete head;
           length--;
        }
        else
        {
            Node* previous = getPrevious(tail);
            delete tail;
            previous->next = dummy;
            tail = previous;
            length--;
        }
    }

    Iterator Erase(Iterator position)  // erases the element specified by the iterator and return an iterator to the next element
    {
        if(position == head)
        {
                removeFirst();  //this function has inside of it the step of ( head = head->next )
                return  head;   // that's why i just type return head
        }
        else if (position == tail)
        {
                removeLast();
                return nullptr;
        }
        else if (position == dummy)
        {
            throw "sorry can't point after the last element!";
        }
        else
        {
          Node* temp = head;
          while(temp != dummy)
              {
                if(position == temp)
                {   Node* previous = getPrevious(temp);
                    previous->next = temp->next;
                    delete temp;
                    return previous->next;
                }
                temp = temp->next;
              }
            return nullptr;
        }
    }

    void addLast(T element)
    {
        Node* newnode = new Node;
        newnode->data = element;
        if(length==0)
        {
            head = tail = newnode;
            newnode->next = dummy;
        }
        else
        {
         tail->next = newnode;
         tail = newnode;
         newnode->next = dummy;
        }
        length++;
    }


    List<T>& operator= (List<T> &another_list) // overloads the assignment operator to deep copy a list into another list and return the current list by reference.
    {
        if(length!=0)  //empty the list if it's already has numbers inside it
            Clear();

        Node* temp = head;                         //pointer to traverse the empty list
        Node* another_temp = another_list.head;   //pointer to traverse the full list

        for(int i = 0; i<another_list.length; i++)
        {
            addLast(another_temp->data);
            another_temp = another_temp->next;
            if(length == 1)
               temp = head;
            else
                temp = temp->next;
        }
        return *this;
    }

    Iterator Begin()
    {
        Iterator it(head);
        return it;                    //  or simply i can type (  Iterator(head)   )
    }

    Iterator End()
    {
        return Iterator(dummy);      //the constructor that takes a node
    }

    bool exist(T deta)    //checks if a certain number in the list or not
    {
        bool flag=0;
        Node* temp = head;
        while(temp != dummy)
        {
            if(temp->data == deta)
            {
                 flag = 1;
                 break;
            }
            temp = temp->next;
        }
        return flag;
    }

    void Merge(List<T> &otherList)  //merges two sorted linked lists together + removing duplicates + without using an extra list
    {
        Node *otherPtr;
        for(otherPtr = otherList.head; otherPtr != otherList.dummy; )
        {
            if(exist(otherPtr->data))        //if there is a duplicate, skip
                    otherPtr = otherPtr->next;
            else
            {
                addLast(otherPtr->data);
                otherPtr = otherPtr->next;
            }
        }
    }

    void print()   //prints the content of the list
    {
        Node* temp = head;
        while(temp != dummy)
        {
             cout<<temp->data<<" ";
             temp = temp->next;
        }
    }

    ~List()               //A destructor
    {
        Node* current = head;
        while(current != dummy)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};
int main()
{
    /*List <int> mylist1;
    mylist1.addLast(1);
    mylist1.addLast(2);
    mylist1.addLast(3);

    List <int> mylist2;
    mylist2.addLast(2);
    mylist2.addLast(6);
    mylist2.addLast(6);

    mylist1.Merge(mylist2);
    mylist1.print();*/

    /*try
    {
        List<int>::Iterator it(mylist);
             it = mylist.Begin();
             ++it;
             it = mylist.Erase(it);  //erases the number 2
    }
    catch(const char* text )
    {
        cout<<text<<endl;
    }*/


    return 0;
}
