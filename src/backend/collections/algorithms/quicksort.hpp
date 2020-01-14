#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
#include "../../../drawing/collections/collection.hpp"
#include "../collectionalgorithm.hpp"

class QuickSort  : public CollectionAlgorithm
{
public:
    QuickSort();
    QuickSort(Collection *c);

    void definePseudocode();
    void solve();

private:
    void qsort(QVector<int>& array, int low, int high);
    int partition(QVector<int>& array, int low, int high);
};

#endif // QUICKSORT_HPP
