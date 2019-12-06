#include "algograph.hpp"
#include "ui_algograph.h"

AlgoGraph::AlgoGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoGraph)
{
    ui->setupUi(this);
}

AlgoGraph::~AlgoGraph()
{
    delete ui;
}
