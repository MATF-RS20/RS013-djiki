#include "collectioncodeedit.hpp"
#include "ui_collectioncodeedit.h"

CollectionCodeEdit::CollectionCodeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionCodeEdit)
{
    ui->setupUi(this);
}

CollectionCodeEdit::~CollectionCodeEdit()
{
    delete ui;
}
