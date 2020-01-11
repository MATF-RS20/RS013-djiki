#include "drawcollection.hpp"
#include "ui_drawcollection.h"

DrawCollection::DrawCollection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawCollection)
{
    ui->setupUi(this);
}

DrawCollection::~DrawCollection()
{
    delete ui;
}
