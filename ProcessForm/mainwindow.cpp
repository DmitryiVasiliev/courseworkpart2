#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>
#include <QFileIconProvider>
#include <QFileInfo>
#include <windows.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <graph.h>
#include <form.h>
#include <string.h>
#include <shellapi.h>
#include <psapi.h>
#include <tlhelp32.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QAction *newAct =
      new QAction(QIcon(":/res/agt_reload_6441.png"), tr("Текущее состояние"), this);
  connect(newAct, SIGNAL(triggered(bool)), this, SLOT(CheckProc()));
setWindowIcon(QIcon(":/res/repeat.ico"));
  ui->mainToolBar->addAction(newAct);
  QAction *OtAc = new QAction(QIcon(":/res/statistics.png"), tr("Отчёт"), this);
  connect(OtAc, SIGNAL(triggered(bool)), this, SLOT(CallForm()));
  ui->mainToolBar->addAction(OtAc);
}
void MainWindow::CallForm() {
  form *f = new form;
  f->show();
}
MainWindow::~MainWindow() { delete ui; }
void MainWindow::CheckProc() {
  if (IsProcessRun(L"ConsoleApplication5.exe")) {
    h = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"1");
    h1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"2");
    SetEvent(h1);
    WaitForSingleObject(h, INFINITE);
    QTextCodec *codec = QTextCodec::codecForName("windows-1251");
    QTextCodec::setCodecForLocale(codec);
    QFile file(
        "C:\\Users\\Dmitryi\\Documents\\Visual Studio "
        "2012\\Projects\\ConsoleApplication5\\Debug\\test.txt");
    QString s = "";
    QTextStream out(&file);
    out.setCodec("windows-1251");
    QStringList arr;
    file.open(QIODevice::ReadOnly);
    while (!file.atEnd()) {
      s = out.readAll();
    }
    count = arr.size();
    arr = s.split("$");

    PrintProc(arr);
    file.close();
    file.remove();
  } else {
    QMessageBox *msg = new QMessageBox;
    msg->setText("Приложениие CheckTime не запущено");
    msg->show();
  }
}

void MainWindow::PrintProc(QStringList q) {
  if (labels.size() > 0) {
    for (int i = 0; i < labels.size(); i++) {
      labels.at(i)->clear();
      ui->gridLayout_2->removeWidget(labels.at(i));
    }
    labels.clear();
  }

  for (int j = 0; j < (q.size()); j++) {
    labels << new QLabel;
  }
  for (int j = 0; j < (q.size() - 1); j += 3) {


    QString s = q.at(j);
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == 92) s[i] = 47;
    }
    QFileInfo fi(s);
    QString n = fi.baseName();
    QFileIconProvider pr;

    labels.at(j)->setPixmap(pr.icon(fi).pixmap(16, 16));

    labels.at(j + 1)->setText(q.at(j + 1));

    labels.at(j + 2)->setText(q.at(j + 2));
    for (int i = 0; i < 3; i++) {
      ui->gridLayout_2->addWidget(labels.at(j + i), j, i);
    }
  }
}
bool MainWindow::IsProcessRun(wchar_t *processName) {
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  PROCESSENTRY32 pe;
  pe.dwSize = sizeof(PROCESSENTRY32);
  Process32First(hSnapshot, &pe);

  while (1) {
    if (wcscmp(pe.szExeFile, processName) == 0) return true;
    if (!Process32Next(hSnapshot, &pe)) return false;
  }
}
