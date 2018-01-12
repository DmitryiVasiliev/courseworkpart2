#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <windows.h>
#include <QStringList>
#include <QHBoxLayout>
#include <QGridLayout>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  bool IsProcessRun(wchar_t *name);
  void PrintProc(QStringList q);
  int count;
  QGridLayout *layout;
  HANDLE h;
  HANDLE h1;
  QList<QLabel *> labels;
  QVBoxLayout *mainlayout;
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
 public slots:
  void CallForm();
  void CheckProc();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
