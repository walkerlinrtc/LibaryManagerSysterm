#ifndef BOOKINFO_H
#define BOOKINFO_H

#include <QList>    //用链表来存储

#include "registerinfo.h"

class BookInfo {
private:
    string bookNumber;        //图书编号
    string bookName;          //书名
    string authorName;        //作者名字
    string publishDate;       //出版日期
    string publisherName;      //出版社
    int bookInventory;         //库存册数

public:
    QList<RegisterInfo> registerList;

public:
    BookInfo();
    BookInfo(string bookNumber, string bookName, string authorName, string publishDate, string publisherName, int bookInventory);
    ~BookInfo();

    string getBookNumber();
    string getBookName();
    string getAuthorName();
    string getPublishDate();
    string getPublisherName();
    int getBookInventory();

    void setBookNumber(string bookNumber);
    void setBookName(string bookName);
    void setAuthorName(string authorName);
    void setPublishDate(string publishDate);
    void setPublisherName(string publisherName);
    void setBookInventory(int bookInventory);
};

#endif // BOOKINFO_H
