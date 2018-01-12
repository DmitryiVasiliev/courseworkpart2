#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "qcustomplot.h"
class graph : public QWidget
{
    Q_OBJECT
public:
    explicit graph(QWidget *parent = 0);

private:
    QCustomPlot *customPlot;
    QVBoxLayout *vbox;
    QPushButton *res;
    QCPBars *fossil;
    QCPBars *fossil1;

public://private slots:
    void rndres(QList<QStringList> arr);
};

#endif // GRAPH_H
