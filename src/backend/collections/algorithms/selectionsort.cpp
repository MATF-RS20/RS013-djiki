#include "selectionsort.hpp"

SelectionSort::SelectionSort()
{
    definePseudocode();
}


SelectionSort::SelectionSort(Collection *c)
    : CollectionAlgorithm(c)
{
    definePseudocode();
}

void SelectionSort::definePseudocode()
{
    code.setInput("An array of n elements");
    code.setOutput("Sorted array");


    code += "For i = 0 to i = n - 1 do";
    code += "\tmin = i";
    code += "\tFor j = i+1 to n do";
    code += "\t\tIf list[j] < list[min]";
    code += "\t\t\tmin=j";
    code += "\tIf min != i then";
    code += "\t\tswap list[min] and list[i]";
    code += "Return sorted array";
}

void SelectionSort::solve()
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

    for(int i = 0; i < n-1; i++)
    {
        addState(nullptr, 1);
        Item* item1 = collection.getItemByItemNumber(static_cast<unsigned>(i));
        addState(item1, 2);
        int min = i;

        for(int j = i; j < n; j++)
        {
            addState(nullptr, 3);
            Item* item1 = collection.getItemByItemNumber(static_cast<unsigned>(j));
            Item* item2 = collection.getItemByItemNumber(static_cast<unsigned>(min));

            addState(item1, item2, 4);
            if(currentCollection[j] < currentCollection[min])
            {
                addState(item1, 5);
                min = j;
            }
        }


        Item* item2 = collection.getItemByItemNumber(static_cast<unsigned>(min));

        addState(item1, item2, 6);
        if(min != i)
        {
            auto temp = currentCollection[min];
            currentCollection[min] = currentCollection[i];
            currentCollection[i] = temp;
            addState(item1, item2, 7, currentCollection);
        }

    }

    addState(nullptr, 8);
    outcome = QString("Array sorted!");
}
