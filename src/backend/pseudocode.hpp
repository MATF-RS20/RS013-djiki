#ifndef PSEUDOCODE_H
#define PSEUDOCODE_H
#include <QString>
#include <QVector>

class Pseudocode
{
public:
    QString generateHTML(unsigned activeLine = 0) const
    {
        QString highlighColor = "#5599ff";
        QString html = "";
        html += "<table border='0'>";
        html += "<tr><th colspan='2'>Input: " + input + " </th></tr>";
        html += "<tr><th colspan='2'>Output: " + output + " </th></tr>";
        html += "<tr><th colspan='2'></th></tr>";

        unsigned lineNumber = 1;
        for(auto line : code){
            html += "<tr" + (activeLine && (lineNumber == activeLine) ? " bgcolor='" + highlighColor + "'" : "") +">";
            html += "<td>" + QString(lineNumber) + "</td><td><pre>" + line + "</pre></td></tr>";

            lineNumber++;
        }

        html += "</table>";

        return html;
    }

    void setInput(const char* inputLine)
    {
        input = QString(inputLine);
    }

    void setOutput(const char* outputLine)
    {
        input = QString(outputLine);
    }

    void operator+=(const char* nextLine)
    {
        code.append(nextLine);
    }

private:
    QString input;
    QString output;
    QVector<QString> code;
};

#endif // PSEUDOCODE_H
