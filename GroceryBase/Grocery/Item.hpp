#ifndef ITEM_HPP
#define ITEM_HPP
#include <QString>
#include <QDate>



// класс для представления товара
class Item
{
    QString Name;     // название
    QString Storage;  // место хранения
    int Count;        // количество
    QString Provider; // поставщик
    QDate Expiration; // срок годности

public:
    // конструктор из списка строк для удобного чтения из файла
    Item(const QStringList& list);
    // дефолтный конструктор
    Item();
    // конструктор копирования
    Item(const Item& i);
    // конструктор перемещения
    Item(Item&& i);
    // оператор присваивания
    Item& operator=(const Item& i);

    // методы для получения / установки значений приватных полей
    const QString& GetName() const;
    void SetName(const QString& v);
    const QString& GetStorage() const;
    void SetStorage(const QString& v);
    int GetCount() const;
    void SetCount(int v);
    QString GetCountString() const;
    void SetCountString(const QString& v);
    const QString& GetProvider() const;
    void SetProvider(const QString& v);
    QDate GetExpiration() const;
    void SetExpiration(QDate v);
    QString GetExpirationString() const;
    void SetExpirationString(const QString& v);

    // представление в виде списка строк для удобной записи в файл
    QStringList ToList() const;
};

#endif // ITEM_HPP
