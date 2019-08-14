#include "tvector.h"

std::shared_ptr< std::shared_ptr <Figure> > TVector::makeArray(size_t size) {
    std::shared_ptr< std::shared_ptr<Figure> > array(
                new std::shared_ptr<Figure>[size],
                std::default_delete< std::shared_ptr<Figure>[] >() );
    return array;
}

TVector::TVector() : size_(0), array_(nullptr) {
}

TVector::TVector(std::shared_ptr<Figure> &fig) : size_(1) {
    array_ = makeArray(1);
    std::shared_ptr<Figure> *ptr = array_.get();
    ptr[0] = fig;
}


bool TVector::setSize(size_t new_size) {
    if (new_size == 0)
        return false;
    size_t old_size = size_;
    if (new_size == old_size)
        return false;
    std::shared_ptr< std::shared_ptr<Figure> > tmp = array_;

    array_ = makeArray(new_size);
    if (array_ == nullptr) {
        array_ = tmp;
        return false;
    }

    size_t counter = new_size < old_size ? new_size : old_size;
    //if (new_size < old_size) counter = new_size;
    //else counter = old_size;
    for (size_t i = 0; i < counter; ++i) {
        array_.get()[i] = tmp.get()[i];
    }
    size_ = new_size;
    return true;
}
// --------------------------

bool TVector::add(std::shared_ptr<Figure> &fig) {
    return add( fig, size_);
}

bool TVector::add(std::shared_ptr<Figure> &fig, size_t pos) {
    if (fig == nullptr ) return false;
    if (pos > size_) return false;

    if ( !setSize(size_+1) ) return false;
    for (size_t i = size_-1; i > pos; --i)
        array_.get()[i] = array_.get()[i-1];
    array_.get()[pos] = fig;

    return true;
}

bool TVector::set(std::shared_ptr<Figure> &fig) {
    return set(fig, size_-1);
}

bool TVector::set(std::shared_ptr<Figure> &fig, size_t pos) {
    if (pos > size_-1) return false;
    if (fig == nullptr) return false;
    array_.get()[pos] = fig;
    return true;
}

std::shared_ptr<Figure>  TVector::get() {
    return get(size_ - 1);
}

std::shared_ptr<Figure> TVector::get(size_t pos) {
    return array_.get()[pos];
}

void TVector::del() {
    return del(size_ - 1);
}

void TVector::del(size_t pos) {
    if (size_ == 0)
        return;
    if (pos >= size_)
        return;
    for(size_t i = pos; i < size_-1; ++i)
        array_.get()[i] = array_.get()[i+1];

    setSize(size_-1);
}

size_t TVector::getSize() {
    return size_;
}

std::ostream & operator<< (std::ostream &os, TVector &vec) {
    for (size_t i = 0; i < vec.getSize(); ++i) {
        os << i <<") " << *(vec.get(i)) << std::endl;
    }
    return os;
}
