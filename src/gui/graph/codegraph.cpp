#include "codegraph.hpp"
#include "ui_codegraph.h"

CodeGraph::CodeGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeGraph)
{
    ui->setupUi(this);
}

CodeGraph::~CodeGraph()
{
    delete ui;
}

void CodeGraph::on_pushButtonReturn_clicked()
{
    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

QString CodeGraph::getText()
{
    return ui->labelAlgoName->text();
}

void CodeGraph::setText(QString &str, QString html)
{
    ui->labelAlgoName->setText(str);
    ui->algoPseudocode->setHtml(html);
}

void CodeGraph::updateHTML(QString html)
{
    ui->algoPseudocode->setHtml(html);
}
