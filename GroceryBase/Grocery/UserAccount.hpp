#ifndef USERACCOUNT_HPP
#define USERACCOUNT_HPP
#include <QTextStream>



// класс для описания аккаунта
class UserAccount
{
public:
    // перечисление возможных уровней доступа
    enum Status
    {
        Admin,
        Manager,
        Seller,
    };

private:
    QString Name;       // имя аккаунта
    Status UserStatus;  // уровень доступа

public:
    // конструктор из двух строк
    UserAccount(const QString& name, const QString& status);
    // конструктор из строки и статуса
    UserAccount(const QString& name, Status status);
    // дефолтный конструктор
    UserAccount();
    // конструктор копирования
    UserAccount(const UserAccount& a);
    // конструктор перемещения
    UserAccount(UserAccount&& a);
    // оператор присваивания
    UserAccount& operator=(const UserAccount& a);

    // методы доступа к приватным полям
    const QString& GetName() const;
    void SetName(const QString& v);
    Status GetStatus() const;
    void SetStatus(Status v);
    QString GetStatusString() const;
    void SetStatusString(const QString& v);
};

#endif // USERACCOUNT_HPP
