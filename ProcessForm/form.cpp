#include "form.h"
#include "ui_form.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QLinkedList>
#include <QDate>
#include <QList>
#include <graph.h>
#include <windows.h>
form::form(QWidget *parent) : QWidget(parent), ui(new Ui::form) {
  ui->setupUi(this);
  ui->progressBar->setValue(0);


setWindowIcon(QIcon(":/res/statistics.png"));
  ui->pushButton->setEnabled(false);
  ui->radioButton->setEnabled(false);
  ui->radioButton_2->setEnabled(false);
  ui->radioButton_3->setEnabled(false);
  ui->radioButton_4->setEnabled(false);
  ui->radioButton_5->setEnabled(false);
  ui->radioButton_6->setEnabled(false);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(Ready()));
  connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(Enabled()));
  connect(ui->checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(Enabled1()));
  connect(ui->radioButton, SIGNAL(clicked(bool)), this, SLOT(Check()));
  connect(ui->radioButton_2, SIGNAL(clicked(bool)), this, SLOT(Check2()));
  connect(ui->radioButton_3, SIGNAL(clicked(bool)), this, SLOT(Check3()));
  connect(ui->radioButton_4, SIGNAL(clicked(bool)), this, SLOT(Check4()));
  connect(ui->radioButton_5, SIGNAL(clicked(bool)), this, SLOT(Check5()));
  connect(ui->radioButton_6, SIGNAL(clicked(bool)), this, SLOT(Check6()));
}

void form::ChangeBar(QList<QStringList> arr) {
  if (!change)
    for (int i = 0; i <= 100; i++) {
      ui->progressBar->setFormat(QString::number(i) + "%");
      ui->progressBar->setValue(i);

      Sleep(qrand() % 30);

      change = true;
    }
  ui->progressBar->setFormat("Готово!");
  change = false;

  if (check4) WriteFile(arr, PathWeek);
  if (check5) WriteFile(arr, PathMonth);
  if (check6) WriteFile(arr, PathAllData);
  if (check || check2 || check3) PrintFile(arr);
}

void form::Ready() {
  if (check3) SortFile(0);
  if (check) SortFile(31);
  if (check2) SortFile(7);
  if (check4) SortFile(7);
  if (check5) SortFile(31);
  if (check6) SortFile(0);
}
void form::SortFile(int d) {
  QList<QStringList> list;
  QDate *date = new QDate;
  QFile file(
      "C:\\Users\\Dmitryi\\Documents\\Visual Studio "
      "2012\\Projects\\ConsoleApplication5\\Debug\\AllData.txt");
  QTextStream out(&file);
  out.setCodec("windows-1251");
  QList<QStringList> arr;
  file.open(QIODevice::ReadOnly);
  QString s = "";
  while (!out.atEnd()) {
    s = out.readLine();
    list << s.split("$");
  }
  file.close();
  int day = date->currentDate().day();
  int month = date->currentDate().month();
  int year = date->currentDate().year();
  if (d != 0) {
    for (int i = 0; i < list.size(); i++) {
      if ((list.at(i).at(0).toInt() <= day &&
           day - list.at(i).at(0).toInt() <= d &&
           list.at(i).at(1).toInt() == month))
        arr << list.at(i);
      else if ((list.at(i).at(0).toInt() > day &&
                list.at(i).at(1).toInt() - month == -1 &&
                list.at(i).at(0).toInt() >= day &&
                31 - list.at(i).at(0).toInt() + day <= d &&
                list.at(i).at(2).toInt() == year)) {
        arr << list.at(i);
      } else if (list.at(i).at(2).toInt() - year == -1 &&
                 list.at(i).at(1).toInt() - month == 11 &&
                 list.at(i).at(0).toInt() >= day &&
                 31 - list.at(i).at(0).toInt() + day <= d) {
        arr << list.at(i);
      }
    }
  } else {
    for (int i = 0; i < list.size(); i++) {
      arr << list.at(i);
    }
  }

  ChangeBar(arr);
}
void form::PrintFile(QList<QStringList> arr) {
  graph *gr = new graph;
  gr->rndres(arr);
  gr->setFixedSize(1000, 500);

  gr->show();
}
void form::WriteFile(QList<QStringList> arr, QString path) {
  QFile file1(path);
  file1.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream in(&file1);
  in.setCodec("windows-1251");
  if (check4)
    in << tr("Статистика использованния приложений за неделю: ") << endl;
  if (check5)
    in << tr("Статистика использованния приложений за месяц: ") << endl;
  if (check6)
    in << tr("Статистика использованния приложений за все время: ") << endl;
  in << tr("|Название                                                          "
           "                                                                   "
           "                                                                                                                 |")
     << tr("        |     Время     |") << endl;
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 3; j < arr.at(i).size() - 1; j += 3) {
        int hour ;
        int min;
        int sec;

        hour = arr.at(i).at(j + 1).toInt() / 3600;
        min = (arr.at(i).at(j + 1).toInt() % 3600) / 60;
        sec = (arr.at(i).at(j + 1).toInt() % 3600) % 60;
      in <<"| "<<arr.at(i).at(j)<<" | ";
      for(int k=0;k<250-arr.at(i).at(j).length();k++){
          in << " ";
      }

       in << " | " << hour <<tr(" ч ") << min <<tr(" м ") << sec <<tr(" с ")  << " | "<<endl;
    }
    in << endl;
  }
  file1.close();
}
void form::Check() {
  check = true;
  check2 = false;
  check3 = false;
}
void form::Check2() {
  check2 = true;
  check = false;
  check3 = false;
}
void form::Check3() {
  check3 = true;
  check = false;
  check2 = false;
}
void form::Check4() {
  check4 = true;
  check5 = false;
  check6 = false;
}
void form::Check5() {
  check5 = true;
  check4 = false;
  check6 = false;
}
void form::Check6() {
  check6 = true;
  check4 = false;
  check5 = false;
}

void form::Enabled1() {
  if (flag1) {
    ui->pushButton->setEnabled(true);
    ui->radioButton_4->setEnabled(true);
    ui->radioButton_5->setEnabled(true);
    ui->radioButton_6->setEnabled(true);
    flag1 = false;
  } else {
    if (flag) ui->pushButton->setEnabled(false);
    ui->radioButton_4->setEnabled(false);
    ui->radioButton_5->setEnabled(false);
    ui->radioButton_6->setEnabled(false);
    flag1 = true;
    check4 = false;
    check5 = false;
    check6 = false;
  }
}
void form::Enabled() {
  if (flag) {
    ui->pushButton->setEnabled(true);
    ui->radioButton->setEnabled(true);
    ui->radioButton_2->setEnabled(true);
    ui->radioButton_3->setEnabled(true);
    flag = false;
  } else {
    if (flag1) ui->pushButton->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->radioButton_3->setEnabled(false);
    check = false;
    check2 = false;
    check3 = false;

    flag = true;
  }
}
form::~form() { delete ui; }
