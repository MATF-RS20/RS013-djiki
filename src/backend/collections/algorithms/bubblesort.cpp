#include "bubblesort.hpp"
#include <QtDebug>
BubbleSort::BubbleSort()
{
    definePseudocode();
}


BubbleSort::BubbleSort(Collection *c)
    : CollectionAlgorithm(c)
{
    definePseudocode();
}

void BubbleSort::definePseudocode()
{
    code.setInput("An array of n elements");
    code.setOutput("Sorted array");


    code += "For i = 0 to i = n - 1 do";
    code += "\tSet variable swapped to false";
    code += "\tFor j = 0 to j = n - 1 do";
    code += "\t\tIf list[j] > list[j+1]";
    code += "\t\t\tThen swap list[j] and list[j+1] and set swapped to true";
    code += "\tEnd second for loop";
    code += "\tIf swapped equals to false";
    code += "\t\tBreak first for loop";
    code += "End first for loop";
    code += "Return sorted array";
}

void BubbleSort::solve()
{
    QVector<int> currentCollection;
    for(auto c : collection.getItems())
    {
        currentCollection.push_back(c->getItemValue());
    }

    unsigned n = collection.getCollectionSize();
    if(n < 2)
    {
        addState(nullptr, 10);
        outcome = QString("Array sorted!");
        return;
    }

    for(unsigned i = 0; i < n; i++){
        addState(nullptr, 1, currentCollection);

        addState(nullptr, 2);
        bool swapped = false;

        for(unsigned j = 1; j < n; j++)
        {
            addState(nullptr, 3);
            addState(collection.getItemByItemNumber(j-1), collection.getItemByItemNumber(j), 4);
            auto a = currentCollection[static_cast<int>(j-1)];
            auto b = currentCollection[static_cast<int>(j)];

            if(a > b)
            {
                currentCollection[static_cast<int>(j-1)] = b;
                currentCollection[static_cast<int>(j)] = a;
                swapped = true;
                addState(collection.getItemByItemNumber(j-1), collection.getItemByItemNumber(j), 5, currentCollection);
            }
        }
        addState(nullptr, 6);
        addState(nullptr, 7);
        if(!swapped){
            addState(nullptr, 8);
            break;
        }
    }

    addState(nullptr, 9);
    addState(nullptr, 10);
    outcome = QString("Array sorted!");
}
