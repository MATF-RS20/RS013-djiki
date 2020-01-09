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

void CodeGraph::setText(QString &str)
{
    ui->labelAlgoName->setText(str);
    ui->algoPseudocode->setHtml("<table border='0'><tr><td colspan='2'><pre>Input: Graph G, starting node and target node </pre></td></tr><tr><td colspan='2'><pre>Output: Shortest path from the starting node to the target node in graph G (if such path exists) </pre></td></tr><tr><th colspan='2'></th></tr><tr><td><pre>1</pre></td><td><pre>Put only starting node in queue S</pre></td></tr><tr><td><pre>2</pre></td><td><pre>While queue S is not empty do</pre></td></tr><tr><td><pre>3</pre></td><td><pre>\tTake the begining of the queue S as N</pre></td></tr><tr><td><pre>4</pre></td><td><pre>\tIf N is the target node </pre></td></tr><tr bgcolor='#5599ff'><td><pre>5</pre></td><td><pre>\t\tThen inform that the path has been found and reconstruct it (going backwards from the target node)</pre></td></tr><tr><td><pre>6</pre></td><td><pre>\tFor every descendant M of node N for which parent is not defined do</pre></td></tr><tr><td><pre>7</pre></td><td><pre>\t\tRemember N as parent of M and add it to the end of queue S</pre></td></tr><tr><td><pre>8</pre></td><td><pre>Inform that requested path doesn't exist</pre></td></tr></table>");
}
