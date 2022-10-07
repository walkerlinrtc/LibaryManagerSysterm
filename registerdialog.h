#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>     //对话框
#include <QPainter>
#include <QMessageBox>

#include <string>
using namespace std;

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT

private:
    Ui::RegisterDialog *ui;
    string m_bookNumber;

private slots:
    void on_pushButton_clicked();

public:
    explicit RegisterDialog(std::string bookNumber,QWidget *parent = nullptr);
    ~RegisterDialog();

    void paintEvent(QPaintEvent *event);
    void setStyleSheet();

};

#endif // REGISTERDIALOG_H
