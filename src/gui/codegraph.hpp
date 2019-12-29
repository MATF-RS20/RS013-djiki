#ifndef CODEGRAPH_HPP
#define CODEGRAPH_HPP

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class CodeGraph;
}

class CodeGraph : public QWidget
{
    Q_OBJECT

public:
    explicit CodeGraph(QWidget *parent = 0);
    ~CodeGraph();
    QString getText();
    void setText(QString &str);

private slots:
    void on_pushButtonReturn_clicked();

private:
    Ui::CodeGraph *ui;
};

#endif // CODEGRAPH_HPP
