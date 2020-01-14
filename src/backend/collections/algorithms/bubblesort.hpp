#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP
#include "../../../drawing/collections/collection.hpp"
#include "../collectionalgorithm.hpp"

class BubbleSort  : public CollectionAlgorithm
{
public:
    BubbleSort();
    BubbleSort(Collection *c);

    void definePseudocode();
    void solve();
};

#endif // BUBBLESORT_HPP
