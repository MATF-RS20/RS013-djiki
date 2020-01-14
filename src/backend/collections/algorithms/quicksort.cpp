#include "quicksort.hpp"

QuickSort::QuickSort()
{
    definePseudocode();
}


QuickSort::QuickSort(Collection *c)
    : CollectionAlgorithm(c)
{
    definePseudocode();
}

void QuickSort::definePseudocode()
{
    code.setInput("An array of n elements, variable low (the starting index), variable high (the ending index)");
    code.setOutput("Sorted array");


    code += "If low < high";
    code += "\tThen set variable pi to the result of calling partition function: partition(array, low, high)";
    code += "\tRecursively call algorithm for: array, low, pi - 1";
    code += "\tRecursively call algorithm for: array, pi + 1, high";
    code += "------------------------------------------------------";
    code += "Paritition(array, low, high):";
    code += "\tSet pivot to array[high]";
    code += "\tSet i to low - 1";
    code += "\tFor j = low to j <= high -1 do";
    code += "\t\tIf array[j] < pivot:";
    code += "\t\t\tIncrement variable i and swap array[i] and array[j]";
    code += "\tSwap array[i+1] and array[high]";
    code += "\tReturn i+1";

}


void QuickSort::solve()
{
    QVector<int> currentCollection;
    for(auto c : collection.getItems())
    {
        currentCollection.push_back(c->getItemValue());
    }

    int n = static_cast<int>(collection.getCollectionSize());
    if(n < 2)
    {
        addState(nullptr, 8);
        outcome = QString("Array sorted!");
        return;
    }

    QuickSort::qsort(currentCollection, 0, currentCollection.size()-1);
 }

void QuickSort::qsort(QVector<int>& array, int low, int high)
{
    addState(nullptr, 1);
    if(low >= high)
        return;
    addState(nullptr, 2);
    int pi = partition(array, low, high);
    addState(nullptr, 3);
    qsort(array, low, pi-1);
    addState(nullptr, 4);
    qsort(array, pi+1, high);

}

int QuickSort::partition(QVector<int>& array, int low, int high)
{
    addState(nullptr, 6);
    Item* pitem = collection.getItemByItemNumber(static_cast<unsigned>(high));
    addState(pitem, 7);
    int pivot = array[high];

    addState(nullptr, 8);
    int i = low - 1;
    addState(nullptr, 9);
    for(int j = low; j < high; j++)
    {
        Item* current = collection.getItemByItemNumber(static_cast<unsigned>(j));
        addState(pitem, current, 10);
        if(array[j] < pivot){
            i++;
            Item* currentSecond = collection.getItemByItemNumber(static_cast<unsigned>(i));

            auto temp = array[i];
            array[i] = array[j];
            array[j] = temp;

            addState(current, currentSecond, 11, array);

        }
    }

    i++;
    Item* current = collection.getItemByItemNumber(static_cast<unsigned>(i));
    Item* currentSecond = collection.getItemByItemNumber(static_cast<unsigned>(high));

    auto temp = array[i];
    array[i] = array[high];
    array[high] = temp;

    addState(current, currentSecond, 12, array);

    addState(nullptr, 13);
    return i;
}
