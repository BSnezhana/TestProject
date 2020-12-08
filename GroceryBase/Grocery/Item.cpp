#include "Item.hpp"



Item::Item(const QStringList& list)
{
    Name = list[0];          // имя из первой строки списка (т. е. первого столбца в таблице CSV)
    Count = list[1].toInt(); // тоже что и в предыдущем, только строка превращается в int
    Storage = list[2];       // аналогично первому
    Provider = list[3];      // аналогично первому
    Expiration = QDate::fromString(list[4], Qt::DateFormat::ISODate); // аналогично второму, но теперь строка кастится к типу QDate
}
Item::Item()
{
    Count = 0;
}
Item::Item(const Item& i)
{
    // копирование полей
    Name = i.Name;
    Storage = i.Storage;
    Count = i.Count;
    Provider = i.Provider;
    Expiration = i.Expiration;
}
Item::Item(Item&& i)
{
    // перемещение полей через std::move
    // нужно для избегания лишних выделений памяти под строки и дату
    Name = std::move(i.Name);
    Storage = std::move(i.Storage);
    Count = i.Count;
    Provider = std::move(i.Provider);
    Expiration = std::move(i.Expiration);
}
Item& Item::operator=(const Item& i)
{
    // простое копироание объекта из i
    Name = i.Name;
    Storage = i.Storage;
    Count = i.Count;
    Provider = i.Provider;
    Expiration = i.Expiration;
    // возвращается сылка на текцщий обхект чтобы можно было использовать запись item1 = item2 = item3 = ...
    // это не используется, однако это стандарт определения оперотора присваивания
    return *this;
}


const QString& Item::GetName() const
{
    return Name;
}
void Item::SetName(const QString& v)
{
    Name = v;
}
const QString& Item::GetStorage() const
{
    return Storage;
}
void Item::SetStorage(const QString& v)
{
    Storage = v;
}
int Item::GetCount() const
{
    return Count;
}
void Item::SetCount(int v)
{
    Count = v;
}
QString Item::GetCountString() const
{
    return QString::number(Count);
}
void Item::SetCountString(const QString& v)
{
    Count = v.toInt();
}
const QString& Item::GetProvider() const
{
    return Provider;
}
void Item::SetProvider(const QString& v)
{
    Provider = v;
}
QDate Item::GetExpiration() const
{
    return Expiration;
}
void Item::SetExpiration(QDate v)
{
    Expiration = v;
}
QString Item::GetExpirationString() const
{
    return Expiration.toString(Qt::DateFormat::ISODate);
}
void Item::SetExpirationString(const QString& v)
{
    Expiration = QDate::fromString(v, Qt::DateFormat::ISODate);
}

QStringList Item::ToList() const
{
    // создание списка строк из полей класса, некоторые из которых (те, что не являются строками) явно прикасчены к QString
    return { Name, QString::number(Count), Storage, Provider, Expiration.toString(Qt::DateFormat::ISODate) };
}
