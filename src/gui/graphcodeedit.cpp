#include "graphcodeedit.hpp"
#include "ui_graphcodeedit.h"
#include "graphcodelinenumber.hpp"

GraphCodeEdit::GraphCodeEdit(QWidget *parent) :
    QPlainTextEdit(parent),
    ui(new Ui::GraphCodeEdit)
{
    ui->setupUi(this);

    lineNumberArea = new GraphCodeLineNumber(this);

    connect(this, &GraphCodeEdit::blockCountChanged, this, &GraphCodeEdit::updateLineNumberAreaWidth);
    connect(this, &GraphCodeEdit::updateRequest, this, &GraphCodeEdit::updateLineNumberArea);
    connect(this, &GraphCodeEdit::cursorPositionChanged, this, &GraphCodeEdit::highlightCurrentLine);

    QFont font;
    font.setFamily("Times");
    font.setPointSize(12);

    const int tabStop = 8;
    QFontMetrics metrics(font);
    this->setTabStopWidth(tabStop * metrics.width(' '));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

GraphCodeEdit::~GraphCodeEdit()
{
    delete ui;
}

int GraphCodeEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width('9') * digits;

    return space;
}

void GraphCodeEdit::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void GraphCodeEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if(dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), this->width(), rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void GraphCodeEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void GraphCodeEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::blue).lighter(130);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void GraphCodeEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    //painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
