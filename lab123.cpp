#include <functional>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <iostream>

template <class Iter, typename Pred>
class FilterIterator
{
        Iter pos;
        Iter end;
        Pred pred;

        void plus()
        {
            ++pos;
            while (pos != end && (!pred(*pos)))
            {
                ++pos;
            }
        }

    public:

        typedef typename Iter::value_type value_type;
        FilterIterator (): pos (NULL), end (NULL), pred (NULL) {}
        FilterIterator (Iter pos, Iter end, Pred pred): pos (pos), end (end), pred (pred)
        {
            while ((pos!=end) && (!pred(*pos)))
                ++pos;
        }
        FilterIterator (const FilterIterator& other): pos (other.pos), end (other.end), pred (other.pred) {}
        ~FilterIterator() = default;

        void set_pred (Pred pred) {this->pred = pred;}

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

int main()
{
    std::vector <int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back (3*i);
    }

    std::function <bool (int)> ex1 = Even;

    FilterIterator<std::vector<int>::iterator, std::function <bool (int)>> fit (v.begin(), v.end(), ex1);
    FilterIterator<std::vector<int>::iterator, std::function <bool (int)>> fend (v.end(), v.end(), ex1);

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

    FilterIterator<std::list<std::string>::iterator, std::function <bool (std::string)>> fit1 (l.begin(), l.end(), ex2);
    FilterIterator<std::list<std::string>::iterator, std::function <bool (std::string)>> fend1 (l.end(), l.end(), ex2);

    for ( ; fit1 != fend1; ++fit1)
    {
        std::cout << *fit1 << " ";
    }
    std::cout << std::endl;
    
}