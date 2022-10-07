#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "bookinfo.h"

class Document {
private:
    QList<BookInfo> bookList;

public:
    Document();
    ~Document();

    static Document* GetInstance();

    void addBook(BookInfo newBook);
    void addBook(string bookNumber, string bookName, string authorName, string publishDate, string publisherName, int bookInventory);
    bool deleteBook(string bookNumber);
    bool alterBook(string bookNumber, string bookName, string authorName, string publishDate, string publisherName, int bookInventory);
    QList<BookInfo> queryBook(string bookAttribute);
    QList<RegisterInfo> getRegister(string bookNumber);
    bool bookExist(string bookNumber);
    bool canBorrow(string bookNumber);
    bool returnBook(string bookNumber,string registerNumber);
    bool updateRegister(string bookNumber,string registerNumber,string borrowDate,string identificationNumber,string canBorrow);
    void writeData();
    void readData();
};

#endif // DOCUMENT_H
