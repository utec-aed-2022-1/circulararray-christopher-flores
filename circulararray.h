#include <iostream>
using namespace std;

template <class T> //es plantilla XDD
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(); //check
    CircularArray(int _capacity); //check
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int); //0,1,..... size-1
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

//Constructor por defecto 
template <class T>
CircularArray<T>::CircularArray() {
    this->capacity = 0;
    this->front = this->back = -1;
    this->arr = new T[0];
    this->len = 0;
}


//constructor que recibe la capacidad inicial
template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1; //Tanto el back como el front -1, inidica que no hay elementos
    this->len = 0;
}

//Liberamos el array------------------------
template <class T>
CircularArray<T>::~CircularArray()
{
    //delete[] this->array;
    delete[] array;
}
//-------------------------------------------


template <class T>
int CircularArray<T>::prev(int index) //Obtiene la posicion anterior del index,front
{
                    // ?      1 true   :   0 false
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)//Obtiene la siguiente posicion, back
{
    return (index + 1) % capacity;
    //return (index == capacity - 1)? 0 : index + 1;
}

template <class T>
void CircularArray<T>::push_back(T data){
    
    if(is_full()) resize();
    if(is_empty())
        this->back = this->front = 0;
    else
        this->back = next(this->back);
    array[this->back]=data; //insertando en la siguiente posición

}

//Recorriendo 
template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}


int main(){
    
}