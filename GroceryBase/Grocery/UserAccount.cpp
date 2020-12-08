#include "UserAccount.hpp"



UserAccount::UserAccount(const QString& name, const QString& status)
{
    Name = name;
    // определение уровня доступа по строке с названием уровня доступа
    if (status == "admin") UserStatus = Status::Admin;
    else if (status == "seller") UserStatus = Status::Seller;
    else if (status == "manager") UserStatus = Status::Manager;
}
UserAccount::UserAccount(const QString& name, Status status)
{
    Name = name;
    UserStatus = status;
}
UserAccount::UserAccount()
{
    Name = "";
    UserStatus = Status::Seller;
}
UserAccount::UserAccount(const UserAccount& a)
{
    // копирование полей
    Name = a.Name;
    UserStatus = a.UserStatus;
}
UserAccount::UserAccount(UserAccount&& a)
{
    // перемещение полей через std::move
    // нужно для избегания лишних выделений памяти под строку
    Name = std::move(a.Name);
    UserStatus = a.UserStatus;
}
UserAccount& UserAccount::operator=(const UserAccount& a)
{
    // копирование полей
    Name = a.Name;
    UserStatus = a.UserStatus;
    return *this;
}

const QString& UserAccount::GetName() const
{
    return Name;
}
void UserAccount::SetName(const QString& v)
{
    Name = v;
}
UserAccount::Status UserAccount::GetStatus() const
{
    return UserStatus;
}
void UserAccount::SetStatus(Status v)
{
    UserStatus = v;
}
QString UserAccount::GetStatusString() const
{
    // создание строки с названием уровня доступа из значения перечисления
    switch (UserStatus)
    {
    case Status::Admin: return "admin";
    case Status::Seller: return "seller";
    case Status::Manager: return "manager";
    default: return "unknown";
    }
}
void UserAccount::SetStatusString(const QString& v)
{
    // определение уровня доступа по строке с названием уровня доступа
    if (v == "admin") UserStatus = Status::Admin;
    else if (v == "seller") UserStatus = Status::Seller;
    else if (v == "manager") UserStatus = Status::Manager;
}
