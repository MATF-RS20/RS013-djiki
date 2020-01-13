#include "collectioncodeedit.hpp"
#include "ui_collectioncodeedit.h"

CollectionCodeEdit::CollectionCodeEdit(QWidget *parent) :
    QWebEngineView(parent),
    ui(new Ui::CollectionCodeEdit)
{
    ui->setupUi(this);

    QFont font;
    font.setFamily("Times");
    font.setPointSize(12);
    QFontMetrics metrics(font);
}

CollectionCodeEdit::~CollectionCodeEdit()
{
    delete ui;
}

void CollectionCodeEdit::resizeEvent(QResizeEvent *event)
{
    QWebEngineView::resizeEvent(event);
}
