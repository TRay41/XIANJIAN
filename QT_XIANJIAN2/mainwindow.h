#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Windows.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MapFile();
    void ShowVal();
    QString getVal(int offset,int num);       //得到对应偏移下的值

public Q_SLOTS:
    void yaochanwanguan();
    void wulingaoshou();
    void gangjintiegu();
    void yishanlanlv();
    void getFileName();
    void ChangeFileVal();

private:
    LPVOID lpMapAddress;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
