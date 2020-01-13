#include "graphcodeedit.hpp"
#include "ui_graphcodeedit.h"

GraphCodeEdit::GraphCodeEdit(QWidget *parent) :
    QWebEngineView(parent),
    ui(new Ui::GraphCodeEdit)
{
    ui->setupUi(this);

/*
    connect(this, &GraphCodeEdit::blockCountChanged, this, &GraphCodeEdit::updateLineNumberAreaWidth);
    connect(this, &GraphCodeEdit::updateRequest, this, &GraphCodeEdit::updateLineNumberArea);
    connect(this, &GraphCodeEdit::cursorPositionChanged, this, &GraphCodeEdit::highlightCurrentLine);
*/
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

