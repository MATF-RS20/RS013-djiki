#ifndef PSEUDOCODEFORMATTER_HPP
#define PSEUDOCODEFORMATTER_HPP

#include <QString>

class PseudoCodeFormatter
{
public:
    PseudoCodeFormatter();
    static void setHighlightColor(QString hex);
    static void setTabWidth(unsigned pixels);
    static void setDividerHeight(unsigned pixels);

    QString makeInputRow(QString input);
    QString makeOutputRow(QString output);
    QString makeDivider();
    QString makeActiveCodeRow(unsigned lineNumber, QString line);
    QString makeCodeRow(unsigned lineNumber, QString line);
    QString wrapAndStyle(QString html);

private:
    static QString highlightColor;
    static unsigned tabWidth;
    static unsigned dividerHeight;

    unsigned countAndRemoveTabs(QString& input);

    QString makeLineNumberCell(unsigned lineNumber);
    QString makeCodeCell(QString line);
};

#endif // PSEUDOCODEFORMATTER_HPP
