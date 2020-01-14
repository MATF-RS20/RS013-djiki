#ifndef GRAPHCODEEDIT_HPP
#define GRAPHCODEEDIT_HPP

#include <QPlainTextEdit>
#include <QWebEngineView>
#include <QWidget>
#include <QPainter>
#include <QTextBlock>
#include <QGridLayout>

namespace Ui {
class GraphCodeEdit;
}

class GraphCodeEdit : public QWebEngineView
{
    Q_OBJECT

public:
    explicit GraphCodeEdit(QWidget *parent = 0);
    ~GraphCodeEdit();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::GraphCodeEdit *ui;
};

#endif // GRAPHCODEEDIT_HPP
