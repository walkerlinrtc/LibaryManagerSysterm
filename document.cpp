#include "document.h"

Document* Document::GetInstance() {
    static Document instance;
    return &instance;
}

Document::Document() {}
Document::~Document() {}

void Document::addBook(BookInfo newBook) {
    bookList.append(newBook);
}

void Document::addBook(string bookNumber, string bookName, string authorName, string publishDate, string publisherName, int bookInventory) {
    bookList.append(BookInfo(bookNumber, bookName, authorName, publishDate, publisherName, bookInventory));
}

bool Document::deleteBook(string bookNumber) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            bookList.erase(bookList.begin() + i);
            return true;
        }
    }
    return false;
}

bool Document::alterBook(string bookNumber, string bookName, string authorName, string publishDate, string publisherName, int bookInventory) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            bookList[i].setBookName(bookName);
            bookList[i].setAuthorName(authorName);
            bookList[i].setPublishDate(publishDate);
            bookList[i].setPublisherName(publisherName);
            bookList[i].setBookInventory(bookInventory);
            return true;
        }
    }
    return false;
}

QList<BookInfo> Document::queryBook(string bookAttribute) {
    if(bookAttribute.empty()) {
        return bookList;
    }
    QList<BookInfo> queryResult;
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookAttribute || bookList[i].getBookName() == bookAttribute) {
            queryResult.append(bookList[i]);
        }
    }
    return queryResult;
}

QList<RegisterInfo> Document::getRegister(string bookNumber) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            return bookList[i].registerList;
        }
    }
    return QList<RegisterInfo>();
}

bool Document::bookExist(string bookNumber) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            return true;
        }
    }
    return false;
}

bool Document::canBorrow(string bookNumber) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            foreach(RegisterInfo registerInfo,bookList[i].registerList) {
                if(registerInfo.getIsBorrowed() == false) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Document::returnBook(string bookNumber,string registerNumber) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            for(int j = 0;j < bookList[i].registerList.size();j++) {
                if(bookList[i].registerList[j].getRegisterNumber() == registerNumber) {
                    bookList[i].registerList[j].setBorrowDate("--");
                    bookList[i].registerList[j].setIdentificationNumber("--");
                    bookList[i].registerList[j].setIsBorrowed(false);
                    bookList[i].setBookInventory(bookList[i].getBookInventory() + 1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Document::updateRegister(string bookNumber, string registerNumber, string borrowDate, string identificationNumber, string canBorrow) {
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getBookNumber() == bookNumber) {
            for(int j = 0;j < bookList[i].registerList.size();j++) {
                if(bookList[i].registerList[j].getRegisterNumber() == registerNumber) {
                    bookList[i].registerList[j].setBorrowDate(borrowDate);
                    bookList[i].registerList[j].setIdentificationNumber(identificationNumber);
                    if(canBorrow == "yes") {
                        bookList[i].registerList[j].setIsBorrowed(1);
                        bookList[i].setBookInventory(bookList[i].getBookInventory() - 1);
                    }
                    else {
                        bookList[i].registerList[j].setIsBorrowed(0);
                        bookList[i].setBookInventory(bookList[i].getBookInventory() + 1);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void Document::writeData() {
    ofstream outFile("BookInfo.txt");
    for (int i = 0; i < bookList.size(); i++) {
        outFile << bookList[i].getBookNumber() << "  " << bookList[i].getBookName() << "  " << bookList[i].getAuthorName()
                << "  " << bookList[i].getPublishDate() << "  " << bookList[i].getPublisherName() << "  "
                << bookList[i].getBookInventory() << "  " << bookList[i].registerList.size() << endl;
        for (int j = 0;j < bookList[i].registerList.size();j++) {
            outFile << bookList[i].registerList[j].getRegisterNumber() << "  " << bookList[i].registerList[j].getBorrowDate() << "  "
                       << bookList[i].registerList[j].getIdentificationNumber() << "  " << bookList[i].registerList[j].getIsBorrowed() << endl;
        }
    }
    outFile.close();
}

void Document::readData() {
    ifstream inFile("BookInfo.txt");
    string bookNumber;
    string bookName;
    string authorName;
    string publishDate;
    string publisherName;
    int bookInventory;

    int registerSize = 0;
    string registerNumber;
    string borrowDate;
    string identificationNumber;
    bool isBorrowed = false;

    while (!inFile.eof()) {
        inFile >> bookNumber >> bookName >> authorName >> publishDate >> publisherName >> bookInventory;
        if (inFile.fail()) {
            break;
        }
        BookInfo newBook(bookNumber, bookName, authorName, publishDate, publisherName, bookInventory);
        inFile >> registerSize;
        if(registerSize != 0) {
            newBook.registerList.clear();
        }
        for (int i = 0;i < registerSize;i++) {
            inFile >> registerNumber >> borrowDate >> identificationNumber >> isBorrowed;
            RegisterInfo newRegister(registerNumber,borrowDate,identificationNumber,isBorrowed);
            newBook.registerList.append(newRegister);
        }
        addBook(newBook);
    }
    inFile.close();
}


















