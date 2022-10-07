#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bookinfo.h"
#include <QMainWindow>      //主窗口
#include <QPainter>         //画图
#include <QMessageBox>      //对话框
#include <QTableWidget>     //表格组件
#include <QInputDialog>     //输入对话框


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private slots:
    void tableItemChanged(QTableWidgetItem *item);

    void on_pushButtonReturn_clicked();
    void on_pushButtonDataset_clicked();

private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    void setStyleSheet();

    bool isExist(std::string BookNumber);
    void updateTable(QList<BookInfo> bookList);
};

#endif // MAINWINDOW_H
