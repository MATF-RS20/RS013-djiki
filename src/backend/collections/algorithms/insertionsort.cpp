#include "insertionsort.hpp"

InsertionSort::InsertionSort()
{
    definePseudocode();
}

InsertionSort::InsertionSort(Collection *c)
    : CollectionAlgorithm(c)
{
    definePseudocode();
}

void InsertionSort::definePseudocode()
{
    code.setInput("An array of n elements");
    code.setOutput("Sorted array");


    code += "For i = 1 to i = n - 1 do";
    code += "\tj := i";
    code += "\tWhile j > 0 and A[j-1] > A[j] do";
    code += "\t\tSwap A[j} and A[j-1]";
    code += "\t\tj := j-1";
    code += "Return sorted array";
}

void InsertionSort::solve()
{
    QVector<int> currentCollection;
    for(auto c : collection.getItems())
    {
        currentCollection.push_back(c->getItemValue());
    }

    int n = static_cast<int>(collection.getCollectionSize());
    if(n < 2)
    {
        addState(nullptr, 6);
        outcome = QString("Array sorted!");
        return;
    }

    for(int i = 1; i < n; i++)
    {
        addState(nullptr, 1);
        addState(nullptr, 2);

        int j = i;
        while(j > 0)
        {
            if(currentCollection[j-1] <= currentCollection[j])
                break;

            Item* first = collection.getItemByItemNumber(static_cast<unsigned>(j-1));
            Item* second = collection.getItemByItemNumber(static_cast<unsigned>(j));

            addState(first, second, 3);
            int temp = currentCollection[j-1];
            currentCollection[j-1] = currentCollection[j];
            currentCollection[j] = temp;

            addState(first, second, 4, currentCollection);

            j--;
            addState(nullptr, 5);
        }
    }

    addState(nullptr, 6);
    outcome = QString("Array sorted!");
}
