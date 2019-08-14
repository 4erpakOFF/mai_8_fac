#ifndef TVECTOR_H
#define TVECTOR_H

#include <cstdio>
#include <memory>
#include "figure.h"


class TVector {
private:
    size_t size_;
    std::shared_ptr< std::shared_ptr<Figure> > array_;

    bool setSize(size_t new_size);
    std::shared_ptr< std::shared_ptr<Figure> > makeArray(size_t);

public:
    TVector();
    TVector(std::shared_ptr<Figure> &);
    //TVector(std::ostream &);

    bool add(std::shared_ptr<Figure> &);
    bool add(std::shared_ptr<Figure> &, size_t position);
    bool set(std::shared_ptr<Figure> &);
    bool set(std::shared_ptr<Figure> &, size_t position);
    std::shared_ptr<Figure> get();
    std::shared_ptr<Figure> get(size_t position);
    void del();
    void del(size_t position);
    size_t getSize();

    friend std::ostream & operator<< (std::ostream &, TVector &);

    ~TVector() {};

};

#endif // TVECTOR_H
