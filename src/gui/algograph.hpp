#ifndef ALGOGRAPH_HPP
#define ALGOGRAPH_HPP

#include <QWidget>

namespace Ui {
class AlgoGraph;
}

class AlgoGraph : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoGraph(QWidget *parent = 0);
    ~AlgoGraph();

private:
    Ui::AlgoGraph *ui;
};

#endif // ALGOGRAPH_HPP
