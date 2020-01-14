#include "collectioncodeedit.hpp"
#include "ui_collectioncodeedit.h"

CollectionCodeEdit::CollectionCodeEdit(QWidget *parent) :
    QWebEngineView(parent),
    ui(new Ui::CollectionCodeEdit)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background: transparent");
    this->page()->setBackgroundColor(Qt::transparent);

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
