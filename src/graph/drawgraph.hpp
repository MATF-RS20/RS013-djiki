#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include "../graph/node.hpp"
#include "../graph/edge.hpp"
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

    ~DrawGraph() override;

public Q_SLOTS:
    /* When user selects nodes for edge this slot receives signal */
    void drawEdge(Node* node);
    /* When node is deleted this slot receives signal */
    void deleteFromNeighbours(Node* n);

private Q_SLOTS:
    /* When user clicks 'done drawing graph' checkbox this slot receives signal */
    void onDoneDrawing();
    /* When user clicks 'Clear' button this slot receives signal */
    void onClearGraph();

Q_SIGNALS:
    void doneDrawingGraph(Graph *g);

private:
    Ui::drawGraph* ui;
    void initializeScene();

    template <typename T>
    QGraphicsProxyWidget* createCheckBoxBtnOrLabel(const QString& label, const QPointF& position, QFont font);
    QGraphicsProxyWidget* clearItem;
    QGraphicsProxyWidget* helpItem;

    QString drawDirections(QFont font);
    QGraphicsTextItem* directions;

    QVector<Node*> nodes;
    QVector<Node*> selectedNodes;

    QVector<Edge*> edges;
    std::pair<bool, int> getWeightFromUser(const Node* start, const Node* end);

    QTimer* animationTimer;
};

#endif // DRAWGRAPH_HPP
