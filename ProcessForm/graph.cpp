#include "graph.h"
#include "qcustomplot.h"
#include <QFile>
#include <QStringList>
#include <time.h>
#include <QTime>
#include <QFileInfo>
graph::graph(QWidget *parent) : QWidget(parent) {
  setWindowTitle(QString::fromUtf8("Гистограмма"));
  customPlot = new QCustomPlot(this);
  vbox = new QVBoxLayout(this);
  //   customPlot->setBackground(QColor(0,0,0,100));

  vbox->addWidget(customPlot);
 // res = new QPushButton(QString::fromUtf8("Показать или обновить гистограмму"),
      //                  this);
  vbox->addWidget(res);
  setLayout(vbox);


}

void graph::rndres(QList<QStringList> arr) {
  QPen pen;
  pen.setWidthF(2);  //Толщина контура столбца


  pen.setColor(QColor(0, 0, 0));  // Цвет контура столбца


  QVector<double> ticks;
  QVector<QString> labels;
  QVector<QString> labels1;
  QVector<double> fossilData1;
  QVector<double> ti;
  int k = 1;
  int q = 0;
  int c = 0;
  int ar[50];
  bool fo = false;
  for (int i = 0; i < arr.size(); i++) {
    for (int g = 3; g < arr.at(i).size() - 3; g += 3) {
      QFileInfo f(arr.at(i).at(g + 2));

      if (labels1.size() != 0) {

        for (int j = 0; j < labels1.size(); j++) {
          if (f.baseName() == labels1.at(j)) {
            fo = true;
            ar[j] = ar[j] + arr.at(i).at(g + 1).toInt();
            c +=  arr.at(i).at(g + 1).toInt();
            q--;
          }
        }
      }

      if ((!fo || labels1.size() == 0) && f.exists() == true) {
        labels1 << f.baseName();
        ar[q] = arr.at(i).at(g + 1).toInt();
        c += arr.at(i).at(g + 1).toInt();
        ti << k;
        k++;
      }
      if (f.exists() == true) {
        q++;
        fo = false;
      }
    }
  }

  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTicks(ti, labels1);
  customPlot->xAxis->setTicker(textTicker);
  customPlot->xAxis->setTickLabelRotation(60);
  customPlot->xAxis->setSubTicks(false);

  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setRange(0, q+2);


  customPlot->yAxis->setRange(0, 100);
  customPlot->yAxis->setPadding(20);
  customPlot->yAxis->setLabel(QString::fromUtf8("Проценты"));
  customPlot->yAxis->grid()->setSubGridVisible(true);


  QVector<double> fossilData;

  for (int i = 0; i < labels1.size(); i++) {
    qsrand(QTime::currentTime().msec());

    int r = qrand() % (i + 1) * 50;
    int g = qrand() % (i + 1) * 50;
    int b = qrand() % (i + 1) * 50;

    fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    fossil->setPen(pen);
    int e = ar[i];

    double v = (e * 100) / c;
    fossilData << v;
    ticks << i + 1;
    fossil->setBrush(QColor(r, g, b, 255));
    fossil->setData(ticks, fossilData);
    fossilData.clear();
    ticks.clear();
  }

  customPlot->replot();
}
