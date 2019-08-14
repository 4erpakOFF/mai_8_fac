#ifndef TVECTOR_H
#define TVECTOR_H

#include "rhombus.h"
//#include <cstdarg>  // На случай переменного числа аргументов


class TVector {
private:
    Rhombus *array;
    size_t size;
    bool SetSize(size_t new_size);

public:
    TVector();
    TVector(const Rhombus*);
    TVector(std::istream &);

    bool Add(const Rhombus *);
    bool Add(const Rhombus *, size_t position);
    Rhombus Get() const;
    Rhombus Get(size_t position) const;
    void Delete();
    void Delete(size_t position);
    size_t GetSize();

    friend std::ostream & operator<< (std::ostream &, const TVector &);

    ~TVector();
};

#endif // TVECTOR_H
