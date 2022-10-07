#ifndef REGISTERINFO_H
#define REGISTERINFO_H


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class RegisterInfo {
private:
    std::string registerNumber;     //登记号
    std::string borrowDate;         //借书时间
    std::string identificationNumber;//借书证号
    bool isBorrowed;           //是否借出

public:
    RegisterInfo();
    RegisterInfo(std::string registerNumber, std::string borrowDate, std::string identificationNumber, bool isBorrowed);
    ~RegisterInfo();

    std::string getRegisterNumber();
    std::string getBorrowDate();
    std::string getIdentificationNumber();
    bool getIsBorrowed();

    void setRegisterNumber(std::string registerNumber);
    void setBorrowDate(std::string borrowDate);
    void setIdentificationNumber(std::string identificationNumber);
    void setIsBorrowed(bool isBorrowed);
};

#endif // REGISTERINFO_H
