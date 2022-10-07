#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "registerdialog.h"
#include "document.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setWindowTitle("图书馆管理系统");
    setStyleSheet();

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "书目编号" << "图书名称" << "作者名称" << "出版日期" << "出版社" << "库存册数");

    for(int i = 0;i < ui->tableWidget->columnCount();i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    connect(ui->pushButtonAdd,&QPushButton::clicked,this,[=](){
        disconnect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChanged(QTableWidgetItem*)));
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        for(int j = 0;j < ui->tableWidget->columnCount();j++) {
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,j,new QTableWidgetItem(""));
            ui->tableWidget->item(ui->tableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChanged(QTableWidgetItem*)));
        //设置当前的条目为最后一行
        ui->tableWidget->setCurrentCell(ui->tableWidget->rowCount()-1,0);
    });

    connect(ui->pushButtonDelete,&QPushButton::clicked,this,[=](){
        int currentRow = ui->tableWidget->currentRow();
        if(currentRow == -1) {
            QMessageBox::warning(this,"system","请选择一项进行删除！");
            return;
        }
        disconnect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChanged(QTableWidgetItem*)));
        Document::GetInstance()->deleteBook(ui->tableWidget->item(currentRow,0)->text().toStdString());
        ui->tableWidget->removeRow(currentRow);
        QMessageBox::information(this,"system","图书信息删除成功！");
        Document::GetInstance()->writeData();
        connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChanged(QTableWidgetItem*)));
    });

    connect(ui->pushButtonQuery,&QPushButton::clicked,this,[=](){
        QList<BookInfo> searchResult = Document::GetInstance()->queryBook(ui->lineEdit->text().toStdString());
        updateTable(searchResult);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::isExist(string BookNumber) {
    return Document::GetInstance()->bookExist(BookNumber);
}

void MainWindow::updateTable(QList<BookInfo> bookList) {
    if(bookList.isEmpty()) {
        return;
    }
    disconnect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChanged(QTableWidgetItem*)));
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    for(int i = 0;i < bookList.size();i++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(bookList[i].getBookNumber().c_str()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(bookList[i].getBookName().c_str()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(bookList[i].getAuthorName().c_str()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(bookList[i].getPublishDate().c_str()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(bookList[i].getPublisherName().c_str()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(bookList[i].getBookInventory())));
        for(int j = 0;j < ui->tableWidget->columnCount();j++) {
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
    connect(ui->tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(tableItemChanged(QTableWidgetItem*)));
}

void MainWindow::tableItemChanged(QTableWidgetItem *item) {
    disconnect(ui->tableWidget,SIGNAL(QTableWidget::itemChanged(QTabWidgetItem*)),this,SLOT(tableItemChanged(QTabWidgetItem*)));
    int row = ui->tableWidget->currentRow();
    for(int j = 0;j < ui->tableWidget->columnCount();j++) {
        if(ui->tableWidget->item(row,j)->text() == "")
        {
            return;
        }
    }
    if(isExist(ui->tableWidget->item(row,0)->text().toStdString())) {
        //表示用户想要修改信息
        bool ret = Document::GetInstance()->alterBook(ui->tableWidget->item(row,0)->text().toStdString(),
                                                      ui->tableWidget->item(row,1)->text().toStdString(),
                                                      ui->tableWidget->item(row,2)->text().toStdString(),
                                                      ui->tableWidget->item(row,3)->text().toStdString(),
                                                      ui->tableWidget->item(row,4)->text().toStdString(),
                                                      ui->tableWidget->item(row,5)->text().toInt());
        if(!ret) {
            QMessageBox::warning(this,"system","图书信息修改失败！");
        }
        else {
            QMessageBox::information(this,"system","图书信息修改成功！");
            Document::GetInstance()->writeData();
        }
    }
    else {
        //表示是新增信息
        Document::GetInstance()->addBook(ui->tableWidget->item(row,0)->text().toStdString(),
                                         ui->tableWidget->item(row,1)->text().toStdString(),
                                         ui->tableWidget->item(row,2)->text().toStdString(),
                                         ui->tableWidget->item(row,3)->text().toStdString(),
                                         ui->tableWidget->item(row,4)->text().toStdString(),
                                         ui->tableWidget->item(row,5)->text().toInt());
        QMessageBox::information(this,"system","图书信息增加成功！");
        Document::GetInstance()->writeData();
    }
    connect(ui->tableWidget,SIGNAL(QTableWidget::itemChanged(QTabWidgetItem*)),this,SLOT(tableItemChanged(QTabWidgetItem*)));
}

void MainWindow::paintEvent(QPaintEvent *event) {
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

void MainWindow::setStyleSheet() {
    this->setWindowTitle("图书馆管理系统");
    // this->setWindowIcon(QIcon(":/Resource/winIcon.png"));

    //设置按钮样式
    QString buttonStyle = "QPushButton{"
                          "background-color:rgba(100,25,10,30);"//背景色（也可以设置图片）
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
            "background-color:rgba(200,220,70,70);"
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
    ui->pushButtonAdd->setStyleSheet(buttonStyle);
    ui->pushButtonDelete->setStyleSheet(buttonStyle);
    ui->pushButtonQuery->setStyleSheet(buttonStyle);
    ui->pushButtonReturn->setStyleSheet(buttonStyle);
    ui->pushButtonDataset->setStyleSheet(buttonStyle);
    //设置输入框样式
    ui->lineEdit->setFixedHeight(28);
    ui->lineEdit->setStyleSheet("QLineEdit{"
                                "border: 1px solid #A0A0A0;" /* 边框宽度为1px，颜色为#A0A0A0 */
                                "border-radius: 5px;" /* 边框圆角 */
                                "padding-left: 5px;" /* 文本距离左边界有3px */
                                "background-color: transparent;" /* 背景颜色 */
                                "selection-background-color: #A0A0A0;" /* 选中文本的背景颜色 */
                                "selection-color: #F2F2F2;" /* 选中文本的颜色 */
                                "font-size: 20pt;" /* 文本字体大小 */
                                "}");
    //设计表格样式
    ui->tableWidget->setStyleSheet("background:transparent");
    ui->tableWidget->verticalHeader()->hide();
}

void MainWindow::on_pushButtonReturn_clicked() {
    QTableWidgetItem* currentItem = ui->tableWidget->currentItem();
    if(currentItem) {
        string bookNumber = ui->tableWidget->item(currentItem->row(),0)->text().toStdString();
        QString registerNumber = QInputDialog::getText(this,"图书归还","请输入登记号");
        if(!registerNumber.isEmpty()) {
            if(Document::GetInstance()->returnBook(bookNumber,registerNumber.toStdString())) {
                Document::GetInstance()->writeData();
                QMessageBox::information(this,"提示","还书成功");
            }
            else {
                QMessageBox::warning(this,"提示","还书失败");
            }
        }
    }
}

void MainWindow::on_pushButtonDataset_clicked() {
    QTableWidgetItem* currentItem = ui->tableWidget->currentItem();
    if(currentItem) {
        string bookNumber = ui->tableWidget->item(currentItem->row(),0)->text().toStdString();
        if(!Document::GetInstance()->canBorrow(bookNumber)) {
            QMessageBox::warning(this,"图书借阅判定","该图书不可借阅");
        }
        RegisterDialog* dialog = new RegisterDialog(bookNumber,NULL);
        dialog->show();
        dialog->setAttribute(Qt::WA_DeleteOnClose);
    }
}
