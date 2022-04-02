#include <iostream>
using namespace std;

template <class T> //es plantilla XDD
class CircularArray
{
private:
    T *array;
    int capacity,len; //len : size
    int back, front;
    
public:
    CircularArray(); //check
    CircularArray(int _capacity); //check
    virtual ~CircularArray();//check
    void push_front(T data);//check
    void push_back(T data);//check | Review?
    void insert(T data, int pos);//check
    T pop_front();//check
    T pop_back();//check
    bool is_full();//check
    bool is_empty();//check
    int size();//check
    void clear();//check
    T &operator[](int); //0,1,..... size-1 | check
    void sort();//check
    bool is_sorted();//check
    // void reverse();
    CircularArray *reverse(); // done

    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
    void expand();
};


//----------------------------------Insert
template <class T>
void CircularArray<T>::insert(T data, int pos) {
    if (this->is_full() || this->is_empty()) {
        cout << "No se puede insertar\n";
        return;
    }
    for (int i = this->size(); i > pos; i--) {
        (*this)[i] = (*this)[i-1];
    }
    (*this)[pos] = data;
}

//-------------------------------------class*class reverse-1
template <class T>
CircularArray<T> * CircularArray<T>::reverse() {
    CircularArray<T>* temp = new CircularArray<T>(this->capacity);
    int it = this->back;
    for (int i = 0; i < this->size(); i++) {
        temp->push_back(this->array[it]);
        it = this->prev(it);
    }
    return temp;
}


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
void CircularArray<T>::push_front (T data) {
    if (this->is_empty()) {
        this->array[0] = data;
        this->back = this->front = 0;
    } else if (this->is_full()) {
        this->expand();
        this->front = this->prev(this->front);
        this->array[this->front] = data;
    } else {
        this->front = this->prev(this->front);
        this->array[this->front] = data;
    }
    this->len++;
}
//------------------------

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

//------------------------------PUSH_BACK
template <class T>
void CircularArray<T>::push_back(T data){
    
    if(is_full()) resize();
    if(is_empty())
        this->back = this->front = 0;
    else
        this->back = next(this->back);
    array[this->back]=data; //insertando en la siguiente posición
    this->len++;
}
//----------------------------------


//Recorriendo 
template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}
//------------------------------------Operator []
template <class T>
T& CircularArray<T>::operator[] (int i) {
    if (this->is_empty ()) {
        cout << "Lista vacía.\n";
        exit (0);
    }
    return this->array[(i)%(this->capacity+1)];
}
//------------------------------------is_sorted
template <class T>
bool CircularArray<T>::is_sorted() {
    int it = this->front;
    for (int i = 0; i < this->size()-1; i++) {
        if ((*this)[it] > (*this)[it+1]) { return false; }
        it = this->next(it);
    }
    return true;
}

//----------------------------------sort
template <class T>
void CircularArray<T>::sort() {
    this->mergesort(0, this->size()-1);
}
//-----------------------------------clear
template <class T>
void CircularArray<T>::clear () {
    this->len = 0;
    this->front = this->back = -1;
}

//-------------------------------------size
template <class T>
int CircularArray<T>::size () {
    return this->len;
}
//--------------------------------------pop_front
template <class T>
T CircularArray<T>::pop_front () {
    if (this->size() == 1) {
        this->len--;
        this->front = this->back = -1;
        return this->array[0];
    } else if (!this->is_empty ()) {
        this->len--;
        T temp = this->array[this->front];
        this->front = this->next(this->front);
        return temp;
    }
}

//----------------------------------pop_back
template <class T>
T CircularArray<T>::pop_back () {
    if (this->size() == 1) {
        this->len--;
        this->front = this->back = -1;
        return this->array[0];
    } else if (!this->is_empty ()) {
        this->len--;
        T temp = this->array[this->back];
        this->back = this->prev(this->back);
        return temp;
    }
}



//------------------------------------is_empty:
template <class T>
bool CircularArray<T>::is_empty() {
    return this->front == -1;
}

//-----------------------------------is_full?
template <class T>
bool CircularArray<T>::is_full() {
    return this->front == this->next(this->back) && !this->is_empty();
}




// int main(){
    
// }