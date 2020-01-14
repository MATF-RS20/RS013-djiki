#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP
#include "../../../drawing/collections/collection.hpp"
#include "../collectionalgorithm.hpp"

class InsertionSort  : public CollectionAlgorithm
{
public:
    InsertionSort();
    InsertionSort(Collection *c);

    void definePseudocode();
    void solve();

};

#endif // INSERTIONSORT_HPP
