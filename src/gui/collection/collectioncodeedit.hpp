#ifndef COLLECTIONCODEEDIT_HPP
#define COLLECTIONCODEEDIT_HPP

#include <QWidget>

namespace Ui {
class CollectionCodeEdit;
}

class CollectionCodeEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionCodeEdit(QWidget *parent = 0);
    ~CollectionCodeEdit();

private:
    Ui::CollectionCodeEdit *ui;
};

#endif // COLLECTIONCODEEDIT_HPP
