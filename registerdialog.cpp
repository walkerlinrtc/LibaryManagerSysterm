#include "registerdialog.h"
#include "ui_registerdialog.h"

#include "comboboxdelegate.h"
#include "document.h"

RegisterDialog::RegisterDialog(string bookNumber,QWidget *parent) : QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);

    m_bookNumber = bookNumber;
    BookInfo bookInfo = Document::GetInstance()->queryBook(bookNumber).at(0);
    this->setWindowTitle(QString::fromStdString(bookInfo.getBookName()) + " 登记号数据集");
    // this->setWindowIcon(QIcon(":/Resource/winIcon.png"));

    setStyleSheet();

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "登记号" << "借阅日期" << "借书证号" << "是否借出");
    ui->tableWidget->setItemDelegateForColumn(3,new ComboboxDelegate(3,QStringList() << "是" << "否",this));
    for(int i = 0;i < ui->tableWidget->columnCount();i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    QList<RegisterInfo> bookRegister = Document::GetInstance()->getRegister(bookNumber);
    for (int i = 0;i < bookRegister.size();i++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bookRegister[i].getRegisterNumber())));
        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(bookRegister[i].getBorrowDate())));
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(bookRegister[i].getIdentificationNumber())));
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString(bookRegister[i].getIsBorrowed() == 1 ? "是" : "否")));
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::paintEvent(QPaintEvent *event) {
    //绘制背景图片，定义画家对象，形参指定this表示在当前窗体内开始绘图
    QPainter painter(this);
    //定义图片对象
    QPixmap pixMap;
    //加载图片资源
    //pixMap.load(":/Resource/background.jpg");
    //设置透明度
    painter.setOpacity(0.8);
    //在(0,0)开始画pixMap，图片的宽高跟主窗体一致
    painter.drawPixmap(0, 0, this->width(), this->height(), pixMap);
}

void RegisterDialog::setStyleSheet() {
    QString buttonStyle = "QPushButton{"
                          "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
            "border-style:outset;"                  //边框样式（inset/outset）
            "border-width:3px;"                     //边框宽度像素
            "border-radius:10px;"                   //边框圆角半径像素
            "border-color:rgba(255,255,255,30);"    //边框颜色
            "font:bold 16px;"                       //字体，字体大小
            "color:rgba(0,0,0,100);"                //字体颜色
            "padding:6px;"                          //填衬
            "}"
            //鼠标悬停样式
            "QPushButton:hover{"
            "background-color:rgba(100,255,100,100);"
            "border-color:rgba(255,255,255,200);"
            "color:rgba(0,0,0,200);"
            "}"
            //鼠标按下样式
            "QPushButton:pressed{"
            "background-color:rgba(100,255,100,200);"
            "border-color:rgba(255,255,255,30);"
            "border-style:inset;"
            "color:rgba(0,0,0,100);"
            "}";
    ui->pushButton->setStyleSheet(buttonStyle);

    //设计表格样式
    ui->tableWidget->setStyleSheet("background:transparent");
    ui->tableWidget->verticalHeader()->hide();
}

void RegisterDialog::on_pushButton_clicked() {
    QTableWidgetItem* currentItem = ui->tableWidget->currentItem();
    if(currentItem) {
        int row = currentItem->row();
        Document::GetInstance()->updateRegister(m_bookNumber,ui->tableWidget->item(row,0)->text().toStdString(),
                                                ui->tableWidget->item(row,1)->text().toStdString(),
                                                ui->tableWidget->item(row,2)->text().toStdString(),
                                                ui->tableWidget->item(row,3)->text().toStdString());
        Document::GetInstance()->writeData();
        QMessageBox::information(this,"提示","数据集更新成功");
    }
}
