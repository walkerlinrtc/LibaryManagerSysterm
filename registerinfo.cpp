#include "registerinfo.h"

RegisterInfo::RegisterInfo() {
    isBorrowed = false;

}

RegisterInfo::RegisterInfo(string registerNumber, string borrowDate, string identificationNumber, bool isBorrowed) {
    this -> registerNumber = registerNumber;
    this -> borrowDate = borrowDate;
    this -> identificationNumber = identificationNumber;
    this -> isBorrowed = isBorrowed;
}

RegisterInfo::~RegisterInfo() {};
string RegisterInfo::getRegisterNumber() {
    return registerNumber;
}

string RegisterInfo::getBorrowDate() {
    return borrowDate;
}

string RegisterInfo::getIdentificationNumber() {
    return identificationNumber;
}

bool RegisterInfo::getIsBorrowed() {
    return isBorrowed;
}

void RegisterInfo::setRegisterNumber(string registerNumber) {
    this -> registerNumber = registerNumber;
}

void RegisterInfo::setBorrowDate(string borrowDate) {
    this -> borrowDate = borrowDate;
}

void RegisterInfo::setIdentificationNumber(string identificationNumber) {
    this -> identificationNumber = identificationNumber;
}

void RegisterInfo::setIsBorrowed(bool isBorrowed) {
    this -> isBorrowed = isBorrowed;
}














