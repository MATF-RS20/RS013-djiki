#ifndef GRAPHCODEEDIT_HPP
#define GRAPHCODEEDIT_HPP

#include <QPlainTextEdit>
#include <QWebEngineView>
#include <QWidget>
#include <QPainter>
#include <QTextBlock>
#include <QGridLayout>

QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
class GraphCodeEdit;
}
QT_END_NAMESPACE

class GraphCodeLineNumber;

class GraphCodeEdit : public QWebEngineView
{
    Q_OBJECT

public:
    explicit GraphCodeEdit(QWidget *parent = 0);
    ~GraphCodeEdit();

protected:
    void resizeEvent(QResizeEvent *event) override;
/*
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
*/
private:
    Ui::GraphCodeEdit *ui;
};

#endif // GRAPHCODEEDIT_HPP
