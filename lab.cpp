#include <iostream>
#include <vector>

template <typename T>
struct Node {
    T data;
    Node* next;
    unsigned priority;

    Node() : data(0), next(NULL), priority(0)
    {}

    Node(const Node<T>& o) : data(o.data), next(o.next), priority(o.priority)
    {}

    Node(T data, unsigned priority) : data(data), next(NULL), priority(priority)
    {}

    Node(T data, Node<T>* next, unsigned priority) : data(data), next(next), priority(priority)
    {}

    ~Node ()
    {
            next = NULL;
            data = 0;
            priority = 0;
    }
    Node<T>& operator = (Node<T>& o)
    {
        data = o.data;
        next = o.next;
        priority = o.priority;

        return *this;
    }

    T get_data() const { return data; }

    unsigned get_priority() const { return priority; }
};

template <typename T>
std::ostream& operator << (std::ostream& os, Node<T>& node)
{
    os << '(' << node.get_priority() << ", " << node.get_data() << ')';
    return os;
}

template <typename T>
class MyPriorityQueue
{
    Node<T>* front;
    Node<T>* rear;

public:
    MyPriorityQueue() : front(NULL), rear(NULL)
    {}

    MyPriorityQueue(const MyPriorityQueue& o) : front(o.front), rear(o.rear)
    {}

    MyPriorityQueue(Node<T>* front, Node<T>* rear) : front(front), rear(rear)
    {
        rear->next = NULL;
    }

    MyPriorityQueue(Node<T>* node) : front(node), rear(node)
    {
        front->next = NULL;
        rear->next = NULL;
    }

    ~MyPriorityQueue()
    {
        Node<T>* curr = front;
        while (curr)
        {
            Node<T>* temp = curr->next;
            curr->~Node();
            curr = temp;
        }
        front = NULL;
        rear = NULL;
    }

    void push(Node<T>* item)
    {
        if (!front)
        {
            front = item;
            rear = item;
            front->next = NULL;
            rear->next = NULL;
        }
        else
        {
            if (front->priority > item->priority)
            {
                Node<T>* temp = front;
                front = item;
                front->next = temp;
            }

            else
            {
                bool flag = false;
                Node<T>* curr = front;
                while (curr->next)
                    if (curr->next->priority > item->priority)
                    {
                        item->next = curr->next;
                        curr->next = item;
                        flag = true;
                        break;
                    }
                    else
                    {
                        curr = curr->next;
                    }
                if (!flag)
                {
                    curr->next = item;
                    rear = item;
                    rear->next = NULL;
                }
            }
        }
    }


    Node<T>* pop()
    {
        Node<T>* temp = front;
        front = front->next;
        return temp;
    }

    Node<T>* peek() const { return front; }

    size_t size() const
    {
        size_t size = 0;
        Node<T>* curr = front;

        while (curr)
        {
            size += 1;
            curr = curr->next;
        }
        return size;
    }

};

template <typename T>
std::ostream& operator << (std::ostream& os, MyPriorityQueue<T>& qu)
{
    Node<T>* curr = qu.peek();
    while (curr)
    {
        os << *curr << ' ';
        curr = curr->next;
    }
    os << std::endl;
    return os;
}

template <typename T>
class Rev_Iterator
{
        MyPriorityQueue<T> *cont;
        size_t pos;
    public:
        Rev_Iterator (): cont (NULL), pos (0)
        {}
        Rev_Iterator (const Rev_Iterator& o): cont (o.cont), pos (o.pos)
        {}
        Rev_Iterator (MyPriorityQueue<T> *cont): cont (cont), pos (cont->size())
        {}
        Rev_Iterator (MyPriorityQueue<T> *cont, size_t pos)
        {
            this->cont = cont;
            size_t size = cont->size();
            
            if (pos <= size)
                this->pos = pos;
            else
                this->pos = size;

        }
        ~Rev_Iterator()
        {
            cont = NULL;
            pos = -1;
        }

        Rev_Iterator<T>& operator = (Rev_Iterator<T> &o)
        {
            cont = o.cont;
            pos = o.pos;

            return *this;
        }

        Rev_Iterator<T>& operator ++ ()
        {
            --pos;
            if (pos <= 1)
                pos = 1;
            return *this;
        }

        Rev_Iterator<T> operator ++ (int)
        {
            Rev_Iterator<T> old (*this);
            --pos;
            if (pos <= 1)
                pos = 1;
            return old; 
        }
        Rev_Iterator<T>& operator -- ()
        {
            ++pos;
            size_t size = cont->size();
            if (pos >= size)
                pos = size;
            return *this;
        }

        Rev_Iterator<T> operator -- (int)
        {
            Rev_Iterator old (*this);
            ++pos;
            size_t size = cont->size();
            if (pos >= size)
                pos = size;
            return old;
        }
        Node<T>& operator * ()
        {
            Node<T>* ans = cont->peek();
            for (int i = 1; i < pos; ++i)
            {
                ans = ans -> next;
            }
            return *ans;
        }
};



int main ()
{
    Node <int> node1(36, 1);

    Node <int> node2(37, 2);

    Node <int> node3(38, 2);

    Node <int> node4(39, 5);

    MyPriorityQueue<int> queue(&node3);

    queue.push(&node4);

    queue.push(&node2);

    queue.push(&node1);

    Rev_Iterator <int> it (&queue);

    Node <int> node = *it;

    std::cout << queue;
    std::cout << node << std::endl; //4

    ++it;
    node = *it;
    std::cout << node << std::endl; //3

    it++;
    node = *it;
    std::cout << node << std::endl; //2

    --it;
    node = *it;
    std::cout << node << std::endl; //3

    Rev_Iterator <int> it1 (&queue, 5);
    node = *it1;
    std::cout << node << std::endl;

    Rev_Iterator <int> it2 (&queue, 2);
    node = *it2;
    std::cout << node << std::endl;
}