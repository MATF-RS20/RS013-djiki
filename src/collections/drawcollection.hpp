#ifndef DRAWCOLLECTION_HPP
#define DRAWCOLLECTION_HPP

#include <QWidget>

namespace Ui {
class DrawCollection;
}

class DrawCollection : public QWidget
{
    Q_OBJECT

public:
    explicit DrawCollection(QWidget *parent = nullptr);
    ~DrawCollection();

private:
    Ui::DrawCollection *ui;
};

#endif // DRAWCOLLECTION_HPP
