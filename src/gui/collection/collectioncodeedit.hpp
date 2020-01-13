#ifndef COLLECTIONCODEEDIT_HPP
#define COLLECTIONCODEEDIT_HPP

#include <QWebEngineView>
#include <QWidget>

namespace Ui {
class CollectionCodeEdit;
}

class CollectionCodeEdit : public QWebEngineView
{
    Q_OBJECT

public:
    explicit CollectionCodeEdit(QWidget *parent = 0);
    ~CollectionCodeEdit();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::CollectionCodeEdit *ui;
};

#endif // COLLECTIONCODEEDIT_HPP
