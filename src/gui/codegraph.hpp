#ifndef CODEGRAPH_HPP
#define CODEGRAPH_HPP

#include <QWidget>

namespace Ui {
class CodeGraph;
}

class CodeGraph : public QWidget
{
    Q_OBJECT

public:
    explicit CodeGraph(QWidget *parent = 0);
    ~CodeGraph();

private:
    Ui::CodeGraph *ui;
};

#endif // CODEGRAPH_HPP
