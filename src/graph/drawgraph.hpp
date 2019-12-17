#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include "../graph/node.hpp"
#include "../graph/edge.hpp"

#include <QWidget>

namespace Ui {
class drawGraph;
}

class DrawGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DrawGraph(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
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

private:
    Ui::drawGraph *ui;
    QGraphicsScene* scene;
    void initializeScene();

    template <typename T>
    T* createCheckBoxOrBtn(const QString& label, const QPointF& position) const;
    void drawDirections();
    QGraphicsTextItem* directions;

    QVector<Node*> nodes;
    QVector<Node*> selectedNodes;

    QVector<Edge*> edges;
    int getWeightFromUser(const Node* start, const Node* end);
};

#endif // DRAWGRAPH_HPP
