#include "bookinfo.h"

BookInfo::BookInfo() {}

BookInfo::BookInfo(string bookNumber, string bookName, string authorName, string publishDate, string publisherName, int bookInventory) {
    this->bookNumber = bookNumber;
    this->bookName = bookName;
    this->authorName = authorName;
    this->publishDate = publishDate;
    this->publisherName = publisherName;
    this->bookInventory = bookInventory;
    for (int i = 0;i < 5;i++) {
        this->registerList.append(RegisterInfo(to_string(i + 1),"--","--",false));
    }
}

BookInfo::~BookInfo() {}

string BookInfo::getBookNumber() {
    return bookNumber;
}

string BookInfo::getBookName() {
    return bookName;
}

string BookInfo::getAuthorName() {
    return authorName;
}

string BookInfo::getPublishDate() {
    return publishDate;
}

string BookInfo::getPublisherName() {
    return publisherName;
}

int BookInfo::getBookInventory() {
    return bookInventory;
}

void BookInfo::setBookNumber(string bookNumber) {
    this->bookNumber = bookNumber;
}

void BookInfo::setBookName(string bookName) {
    this->bookName = bookName;
}

void BookInfo::setAuthorName(string authorName) {
    this->authorName = authorName;
}

void BookInfo::setPublishDate(string publishDate) {
    this->publishDate = publishDate;
}

void BookInfo::setPublisherName(string publisherName) {
    this->publisherName = publisherName;
}

void BookInfo::setBookInventory(int bookInventory) {
    this->bookInventory = bookInventory;
}
