#include "codecollection.hpp"
#include "ui_codecollection.h"

CodeCollection::CodeCollection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeCollection)
{
    ui->setupUi(this);
}

CodeCollection::~CodeCollection()
{
    delete ui;
}

QString CodeCollection::getText()
{
    return ui->labelAlgoName->text();
}

Ui::CodeCollection *CodeCollection::getUi()
{
    return ui;
}

void CodeCollection::setText(QString &str, QString html)
{
    ui->labelAlgoName->setText(str);
    ui->algoPseudocode->setHtml(html);
}

void CodeCollection::on_pushButtonReturn_clicked()
{
    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void CodeCollection::updateHTML(QString html)
{
    ui->algoPseudocode->setHtml(html);
}
