#ifndef CODECOLLECTION_HPP
#define CODECOLLECTION_HPP

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class CodeCollection;
}

class CodeCollection : public QWidget
{
    Q_OBJECT

public:
    explicit CodeCollection(QWidget *parent = 0);
    ~CodeCollection();
    QString getText();
    Ui::CodeCollection *getUi();
    void setText(QString &str, QString html);

private slots:
    void on_pushButtonReturn_clicked();
    void updateHTML(QString html);

private:
    Ui::CodeCollection *ui;
};

#endif // CODECOLLECTION_HPP
