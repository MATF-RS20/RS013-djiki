#include "pseudocodeformatter.hpp"

QString PseudoCodeFormatter::highlightColor = "#5599ff";
unsigned PseudoCodeFormatter::tabWidth = 8;
unsigned PseudoCodeFormatter::dividerHeight = 25;

PseudoCodeFormatter::PseudoCodeFormatter()
{

}

QString PseudoCodeFormatter::makeInputRow(QString input)
{
    return "<tr><td colspan='2'>Input: " + input + " </td></tr>";
}

QString PseudoCodeFormatter::makeOutputRow(QString output)
{
    return "<tr><td colspan='2'>Output: " + output + " </td></tr>";
}

QString PseudoCodeFormatter::makeDivider()
{
    return "<tr><th colspan='2' style='height:" + QString::number(dividerHeight) + "'></th></tr>";
}

QString PseudoCodeFormatter::makeActiveCodeRow(unsigned lineNumber, QString line)
{
    return "<tr bgcolor='" + highlightColor + "'>" + makeLineNumberCell(lineNumber) + makeCodeCell(line) + "</tr>";
}

QString PseudoCodeFormatter::makeCodeRow(unsigned lineNumber, QString line)
{
    return "<tr>" + makeLineNumberCell(lineNumber) + makeCodeCell(line) + "</tr>";
}

QString PseudoCodeFormatter::wrapAndStyle(QString html)
{
    QString result = "";
    result += "<style>table{table-layout: fixed;} td{word-break: word-break; white-space: pre-wrap; font-family:monospace; font-size: 0.8em; color: white;}</style>";
    result += "<table border='0'>";
    result += html;
    result += "</table>";

    return  result;
}

QString PseudoCodeFormatter::makeLineNumberCell(unsigned lineNumber)
{
    return "<td>" + QString::number(lineNumber) + "." "</td>";
}


QString PseudoCodeFormatter::makeCodeCell(QString line){
    QString td;
    td  = "<td style='padding-left: " + QString::number(countAndRemoveTabs(line)*tabWidth) + "px;'>";
    td += line;
    td += "</td>";

    return td;
}

unsigned PseudoCodeFormatter::countAndRemoveTabs(QString& input)
{
    unsigned tabCount = 0;
    for(auto character : input){
        if(character == '\t')
            tabCount++;
    }

    if(tabCount)
        input.remove(0, tabCount);

    return tabCount;
}

void PseudoCodeFormatter::setHighlightColor(QString hex)
{
    highlightColor = hex;
}

void PseudoCodeFormatter::setTabWidth(unsigned pixels)
{
    tabWidth = pixels;
}

void PseudoCodeFormatter::setDividerHeight(unsigned pixels)
{
    dividerHeight = pixels;
}



