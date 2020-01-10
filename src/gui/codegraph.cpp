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
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
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
