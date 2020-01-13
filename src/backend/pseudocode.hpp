#ifndef PSEUDOCODE_H
#define PSEUDOCODE_H
#include <QString>
#include <QVector>
#include "pseudocodeformatter.hpp"

class Pseudocode
{
public:
    QString generateHTML(unsigned activeLine = 0) const
    {
        PseudoCodeFormatter format;
        QString html = "";

        html += format.makeInputRow(input);
        html += format.makeOutputRow(output);
        html += format.makeDivider();

        unsigned lineNumber = 1;
        for(auto line : code){         
            if(activeLine && (lineNumber == activeLine))
                html += format.makeActiveCodeRow(lineNumber, line);
            else
                html += format.makeCodeRow(lineNumber, line);

            lineNumber++;
        }

        return format.wrapAndStyle(html);
    }

    void setInput(const char* inputLine)
    {
        input = QString(inputLine);
    }

    void setOutput(const char* outputLine)
    {
        output = QString(outputLine);
    }

    void operator+=(const char* nextLine)
    {
        code.append(nextLine);
    }

    const QVector<QString>& getCode() const
    {
        return code;
    }
private:
    QString input;
    QString output;
    QVector<QString> code;
};

#endif // PSEUDOCODE_H
