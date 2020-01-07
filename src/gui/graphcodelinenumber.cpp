#include "graphcodelinenumber.hpp"
#include "ui_graphcodelinenumber.h"
#include "graphcodeedit.hpp"

GraphCodeLineNumber::GraphCodeLineNumber(GraphCodeEdit *editor) :
    QWidget(editor),
    codeEditor(editor),
    ui(new Ui::GraphCodeLineNumber)
{
    ui->setupUi(this);
}

GraphCodeLineNumber::~GraphCodeLineNumber()
{
    delete ui;
}

QSize GraphCodeLineNumber::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void GraphCodeLineNumber::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}
