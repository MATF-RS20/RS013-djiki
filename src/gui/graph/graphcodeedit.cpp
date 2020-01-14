#include "graphcodeedit.hpp"
#include "ui_graphcodeedit.h"

GraphCodeEdit::GraphCodeEdit(QWidget *parent) :
    QWebEngineView(parent),
    ui(new Ui::GraphCodeEdit)
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

GraphCodeEdit::~GraphCodeEdit()
{
    delete ui;
}

void GraphCodeEdit::resizeEvent(QResizeEvent *e)
{
    QWebEngineView::resizeEvent(e);
}

