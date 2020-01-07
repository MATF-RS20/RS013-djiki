#ifndef GRAPHCODELINENUMBER_HPP
#define GRAPHCODELINENUMBER_HPP

#include <QtCore/QtGlobal>
#include <QWidget>

QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
class GraphCodeLineNumber;
}
QT_END_NAMESPACE

class GraphCodeEdit;

class GraphCodeLineNumber : public QWidget
{
    Q_OBJECT

public:
    explicit GraphCodeLineNumber(GraphCodeEdit *editor);
    ~GraphCodeLineNumber();
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GraphCodeEdit *codeEditor;
    Ui::GraphCodeLineNumber *ui;
};

#endif // GRAPHCODELINENUMBER_HPP
