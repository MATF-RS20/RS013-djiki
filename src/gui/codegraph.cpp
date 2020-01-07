#include "codegraph.hpp"
#include "ui_codegraph.h"

CodeGraph::CodeGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeGraph)
{
    ui->setupUi(this);
}

CodeGraph::~CodeGraph()
{
    delete ui;
}

void CodeGraph::on_pushButtonReturn_clicked()
{
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

QString CodeGraph::getText()
{
    return ui->labelAlgoName->text();
}

void CodeGraph::setText(QString &str)
{
    ui->labelAlgoName->setText(str);
    QString pseudo;
    if(str == "BFS")
        pseudo = "Input: Graph G, starting node and target node\n"
              "Output: Shortest path from the starting node to the target node in graph G (if such path exists)\n\n"
              "Put only starting node in queue S\n"
              "While queue S is not empty do\n"
              "\tTake the begining of the queue S as N\n"
              "\tIf N is the target node\n"
              "\t\tThen inform that the path has been found and reconstruct it (going backwards from the target node)\n"
              "\tFor every descendant M of node N for which parent is not defined do\n"
              "\t\tRemember N as parent of M and add it to the end of queue S\n"
              "Inform that requested path doesn't exist\n";
    else if(str == "DFS")
        pseudo = "Input: Graph G, starting node and target node\n"
              "Output: Path from the starting node to the target node in graph G (if such path exists)\n\n"
              "Put starting node on stack PATH\n"
              "Insert starting node in the SET OF VISITED NODES\n"
              "While stack PATH is not empty do\n"
              "\tTake the top of the stack as N\n"
              "\tIf N is the target node\n"
              "\t\tThen inform that the path has been found and reconstruct it from the stack PATH\n"
              "\tElse if N has no unvisited descendants\n"
              "\t\tThen remove N from stack PATH\n"
              "\tElse choose first unvisited descendant and add it on top of the stack PATH and in the SET OF VISITED NODES\n"
              "Inform that requested path doesn't exist\n";
    else if(str == "Dijkstra")
        pseudo = "Input: Graph G, starting node and target node\n"
              "Output: Shortest path from the starting node to the target node in graph G (if such path exists)\n\n"
              "Put all nodes from graph G in set Q\n"
              "While Q is not empty do\n"
              "\tFind node N from Q which has with the smallest found distance to the starting node and delete it from Q\n"
              "\tIf N is the target node\n"
              "\t\tThen inform that the path has been found and reconstruct it (going backwards from the target node)\n"
              "\tFor every node M from Q which is direct neighbour of N do\n"
              "\t\tIf current distance from the starting node to M is bigger than distance from the starting node to M over node N\n"
              "\t\t\tThen change parent of node M to N and remember new distance\n"
              "Inform that requested path doesn't exist (Q is empty and path was not found)\n";
    else if(str == "FW")
        pseudo = "Input: Graph G (n nodes)\n"
              "Output: Shortest path from between all pairs of nodes\n\n"
              "Let DIST be a n x n matrix of minimum distances initialized to infinity\n"
              "For each edge (u, v) in G do\n"
              "\tSet DIST[u][v] to weight of edge (u, v)\n"
              "For each node v do\n"
              "\tset DIST[v][v] to 0\n"
              "For k in range 1 to n\n"
              "\tFor i in range 1 to n\n"
              "\t\tFor j in range 1 to n\n"
              "\t\t\tIf DIST[i][j] > DIST[i][k] + DIST[k][j]\n"
              "\t\t\t\tThen set DIST[i][j] to DIST[i][k] + DIST[k][j]\n"
              "Return matrix of distances\n";

    ui->algoPseudocode->setPlainText(pseudo);
}
