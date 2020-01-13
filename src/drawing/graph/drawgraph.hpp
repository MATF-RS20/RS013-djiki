#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include "node.hpp"
#include "edge.hpp"
#include "graph.hpp"

#include <QWidget>
#include <QTimer>

namespace Ui {
class drawGraph;
}

class DrawGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DrawGraph(QWidget* parent = nullptr);

    void mousePressEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;

    QVector<Node*> getNodes() const;
    QVector<Edge*> getEdges() const;
    QTimer* getAnimationTimer() const;
    Ui::drawGraph* getUi() const;

    QGraphicsProxyWidget* clearItem;
    QGraphicsProxyWidget* helpItem;
    QGraphicsProxyWidget* doneItem;
    QGraphicsTextItem* directions;

    ~DrawGraph() override;

public Q_SLOTS:
    /* When user selects nodes for edge this slot receives signal */
    void drawEdge(Node* node);

    /* When node is deleted this slot receives signal */
    void deleteFromNeighbours(Node* n);
    /* Remove deleted edge from edges */
    void removeEdge(Edge* e);

    /* When user clicks 'done drawing graph' checkbox this slot receives signal */
    void onDoneDrawing();
    /* When user clicks 'Clear' button this slot receives signal */
    void onClearGraph();

Q_SIGNALS:
    void doneDrawingGraph(Graph *g);

private:
    Ui::drawGraph* ui;
    void initializeScene();

    bool finished;

    QVector<Node*> nodes;
    QVector<Node*> selectedNodes;

    QVector<Edge*> edges;

    QTimer* animationTimer;
};

#endif // DRAWGRAPH_HPP
