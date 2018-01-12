#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class form;
}

class form : public QWidget {
  Q_OBJECT

 public:
  const QString PathWeek =
      "C:\\Users\\Dmitryi\\Documents\\Visual Studio "
      "2012\\Projects\\ConsoleApplication5\\ConsoleApplication5\\Week.txt";
  const QString PathMonth =
      "C:\\Users\\Dmitryi\\Documents\\Visual Studio "
      "2012\\Projects\\ConsoleApplication5\\ConsoleApplication5\\Month.txt";
  const QString PathAllData =
      "C:\\Users\\Dmitryi\\Documents\\Visual Studio "
      "2012\\Projects\\ConsoleApplication5\\ConsoleApplication5\\AllTimeData."
      "txt";
  void SortFile(int day);
  void ChangeBar(QList<QStringList> arr);
  void WriteFile(QList<QStringList> arr, QString path);
  void PrintFile(QList<QStringList> arr);
  bool flag = true;
  bool flag1 = true;
  bool check = false;
  bool check2 = false;
  bool check3 = false;
  bool check4 = false;
  bool check5 = false;
  bool check6 = false;
  bool change = false;
  explicit form(QWidget *parent = 0);
  ~form();
 public slots:
  void Check();
  void Check2();
  void Check3();
  void Check4();
  void Check5();
  void Check6();
  void Enabled();
  void Enabled1();
  void Ready();

 private:
  Ui::form *ui;
};

#endif  // FORM_H
