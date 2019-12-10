#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include "../graph/node.hpp"
#include "../graph/edge.hpp"

#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>

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
    void drawEdge(Node* node);
    void onClearGraph();
    void onDoneDrawing();
    void deleteFromNeighbours(Node* n);

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
