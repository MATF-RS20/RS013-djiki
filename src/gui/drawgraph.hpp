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
    void onDoneCreatingNodes();
    void onDoneAddingEdges();
    void onClearGraph();

private:
    void initializeScene() const;

    template <typename T>
    T* createCheckBoxOrBtn(const QString& label, const QPointF& position) const;

    Ui::drawGraph *ui;

    QVector<Node*> nodes;
    QGraphicsScene* scene;

    QVector<Node*> selectedNodes;

    bool doneCreatingNodes = false;
};

#endif // DRAWGRAPH_HPP
