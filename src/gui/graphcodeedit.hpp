#ifndef GRAPHCODEEDIT_HPP
#define GRAPHCODEEDIT_HPP

#include <QPlainTextEdit>
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

class GraphCodeEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit GraphCodeEdit(QWidget *parent = 0);
    ~GraphCodeEdit();
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    Ui::GraphCodeEdit *ui;
    QWidget *lineNumberArea;
};

#endif // GRAPHCODEEDIT_HPP
