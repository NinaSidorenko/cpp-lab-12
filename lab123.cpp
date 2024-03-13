#include <functional>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <iostream>

template <class Iter, typename T>
class FilterIterator
{
        Iter pos;
        Iter end;
        std::function<bool(T)> pred;

        void plus()
        {
            ++pos;
            while (pos != end && (!pred(*pos)))
            {
                ++pos;
            }
        }

        void check ()
        {
            while ((pos!=end) && (!pred(*pos)))
                ++pos;
        }

    public:

        typedef typename Iter::value_type value_type;
        FilterIterator (): pos (NULL), end (NULL), pred (NULL) {}
        FilterIterator (Iter pos, Iter end, std::function<bool(T)> pred): pos (pos), end (end), pred (pred)
        {
            check();
        }
        FilterIterator (const FilterIterator& other): pos (other.pos), end (other.end), pred (other.pred) {}
        ~FilterIterator() = default;

        void set_pred (std::function<bool(T)> pred) 
        {
            this->pred = pred;
            check();          
        }
        void set_pos (Iter pos)
        {
            this->pos = pos;
            check();
        }

        value_type& operator * () const {return *pos;}

        FilterIterator& operator ++() 
        {
            plus();
            return *this;
        }

        FilterIterator operator ++(int) 
        {
            FilterIterator tmp (*this);
            plus();
            return *tmp;
        }

        bool operator == (FilterIterator& o) const {return o.pos == pos;}
        bool operator != (FilterIterator& o) const {return o.pos != pos;}
};

bool Even (int num)
{
    return num%2 == 0;
}

bool Equal (std::string elem)
{
   return elem == "Bye";
}

bool Equal1 (int elem)
{
   return elem == 6;
}

int main()
{
    std::vector <int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back (3*i);
    }

    std::function <bool (int)> ex1 = Even;

    FilterIterator<std::vector<int>::iterator, int> fit (v.begin(), v.end(), ex1);
    FilterIterator<std::vector<int>::iterator, int> fend (v.end(), v.end(), ex1);

    std::cout << *fit << std::endl;

    for ( ; fit!=fend; ++fit)
    {
        std::cout << *fit << " ";
    }
    std::cout << std::endl;

    std::function <bool (int)> ex3 = Equal1;
    fit.set_pos(v.begin());
    fit.set_pred(ex3);
    fend.set_pred(ex3);

    for ( ; fit!=fend; ++fit)
    {
        std::cout << *fit << " ";
    }
    std::cout << std::endl;

    std::list <std::string> l;

    l.push_back ("Bye");
    l.push_back ("Hello");
    l.push_back ("Bye");
    l.push_back ("Bye");
    l.push_back ("Hello");   

    std::function <bool (std::string)> ex2 = Equal;

    FilterIterator<std::list<std::string>::iterator, std::string> fit1 (l.begin(), l.end(), ex2);
    FilterIterator<std::list<std::string>::iterator, std::string> fend1 (l.end(), l.end(), ex2);

    for ( ; fit1 != fend1; ++fit1)
    {
        std::cout << *fit1 << " ";
    }
    std::cout << std::endl;
    
}