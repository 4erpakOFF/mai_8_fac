#include "tvector.h"

TVector::TVector() : size(0) {
    array = nullptr;
}

TVector::TVector(const Rhombus *rhmb) : size(1) {
    array = new Rhombus [1];
    array[0] = *rhmb;
}

TVector::TVector(std::istream &is) : TVector() {
    size_t new_side, new_h;
    std::cout << "Вводите пары сторон и высот ромбов: " << std::endl;
    while (is.peek() != '\n') {
        is >> new_side;
        is >> new_h;
        if(!is)
            break;
        Rhombus rhmb( new_side, new_h );
        if ( rhmb.Square() != 0 ) {
            TVector::SetSize(size+1);
            array[size-1] = rhmb;
        }
    } //while (is.peek() != '\n');
}
// ------------------------------------
bool TVector::SetSize(size_t new_size) {
    size_t old_size = size;
    if (new_size == old_size)
        return false;
    Rhombus *tmp = array;

    array = new Rhombus [new_size];

    if (array == nullptr) {
        delete [] array;
        array = tmp;
        return false;
    }
    size_t counter;
    if (new_size < old_size)
        counter = new_size;
    else
        counter = old_size;

    for (size_t i = 0; i < counter; ++i){
        array[i] = tmp[i];
    }
    delete [] tmp;
    size = new_size;
    return true;
}

bool TVector::Add(const Rhombus *ptr_rhmb) {
    if (ptr_rhmb == nullptr )
        return false;
    if( TVector::SetSize(size+1) )
        array[size-1] = *ptr_rhmb;
    else
        return false;

    return true;
}

bool TVector::Add(const Rhombus *ptr_rhmb, size_t pos) {
    if (ptr_rhmb == nullptr )
        return false;
    if (pos > this->size)
        return false;

    if (pos == this->size)
        return TVector::Add(ptr_rhmb);
    if ( !TVector::SetSize(size+1) )
        return false;
    for (size_t i = size-1; i > pos; --i)
        array[i] = array[i-1];
    array[pos] = *ptr_rhmb;

    return true;
}

Rhombus TVector::Get() const {
    return array[size-1];
}

Rhombus TVector::Get(size_t pos) const {
    return array[pos];
}

void TVector::Delete() {
    return Delete(size-1);
}

void TVector::Delete(size_t pos) { // перекидываем в конец и обрубаем
    if (size == 0)
        return;
    for (size_t i = pos; i < size-1; ++i)
        array[i] = array[i+1];

    SetSize(size-1);   // SetSize сам чистит память
}

size_t TVector::GetSize() {
    return this->size;
}
//----------------------------------------

std::ostream & operator<< (std::ostream &os, const TVector &vec){
    for (size_t i = 0; i < vec.size; ++i) {
        os << i << ") " << vec.array[i];
    }
    return os;
}

TVector::~TVector() {
    delete [] array;
}
