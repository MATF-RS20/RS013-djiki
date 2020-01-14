#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP
#include "../../../drawing/collections/collection.hpp"
#include "../collectionalgorithm.hpp"

class SelectionSort  : public CollectionAlgorithm
{
public:
    SelectionSort();
    SelectionSort(Collection *c);

    void definePseudocode();
    void solve();

};

#endif // SELECTIONSORT_HPP
