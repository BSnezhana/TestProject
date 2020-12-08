#include <QtTest>
#include "Item.hpp"



class TestItem : public QObject
{
    Q_OBJECT

public:
    TestItem();
    ~TestItem();

private slots:
    void test_get_set();
    void test_to_from_list();
    void test_copy_constructor();
    void test_move_constructor();
    void test_equeals_operator();
};

TestItem::TestItem()
{

}
TestItem::~TestItem()
{

}

void TestItem::test_get_set()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";
    const int test_int = 0xffff;
    const QString test_int_string_val = "65535";
    const QString test_int_string = "65536";
    const int test_int_string_string_val = 0x10000;
    const QDate test_date = QDate(2012, 12, 12);
    const QString test_date_string = "2012-12-12";
    const QDate test_date2 = QDate(2016, 11, 11);
    const QString test_date_string2 = "2016-11-11";

    Item object;

    object.SetName(test_string);
    QCOMPARE(object.GetName(), test_string);

    object.SetStorage(test_string);
    QCOMPARE(object.GetStorage(), test_string);

    object.SetCount(test_int);
    QCOMPARE(object.GetCount(), test_int);
    QCOMPARE(object.GetCountString(), test_int_string_val);

    object.SetCountString(test_int_string);
    QCOMPARE(object.GetCountString(), test_int_string);
    QCOMPARE(object.GetCount(), test_int_string_string_val);

    object.SetExpiration(test_date);
    QCOMPARE(object.GetExpiration(), test_date);
    QCOMPARE(object.GetExpirationString(), test_date_string);

    object.SetProvider(test_string);
    QCOMPARE(object.GetProvider(), test_string);

    object.SetExpirationString(test_date_string2);
    QCOMPARE(object.GetExpiration(), test_date2);
    QCOMPARE(object.GetExpirationString(), test_date_string2);
}
void TestItem::test_to_from_list()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";
    const int test_int = 0xffff;
    const QDate test_date = QDate(2012, 12, 12);

    Item object;

    object.SetName(test_string);
    object.SetStorage(test_string);
    object.SetName(test_string);
    object.SetCount(test_int);
    object.SetProvider(test_string);
    object.SetExpiration(test_date);

    QStringList list = object.ToList();
    Item object2(list);

    QCOMPARE(object.GetName(), object2.GetName());
    QCOMPARE(object.GetStorage(), object2.GetStorage());
    QCOMPARE(object.GetCount(), object2.GetCount());
    QCOMPARE(object.GetProvider(), object2.GetProvider());
    QCOMPARE(object.GetExpiration(), object2.GetExpiration());
}
void TestItem::test_copy_constructor()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";
    const int test_int = 0xffff;
    const QDate test_date = QDate(2012, 12, 12);

    Item object;

    object.SetName(test_string);
    object.SetStorage(test_string);
    object.SetName(test_string);
    object.SetCount(test_int);
    object.SetProvider(test_string);
    object.SetExpiration(test_date);

    Item object2(object);

    QCOMPARE(object.GetName(), object2.GetName());
    QCOMPARE(object.GetStorage(), object2.GetStorage());
    QCOMPARE(object.GetCount(), object2.GetCount());
    QCOMPARE(object.GetProvider(), object2.GetProvider());
    QCOMPARE(object.GetExpiration(), object2.GetExpiration());
}
void TestItem::test_move_constructor()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";
    const int test_int = 0xffff;
    const QDate test_date = QDate(2012, 12, 12);

    Item object;

    object.SetName(test_string);
    object.SetStorage(test_string);
    object.SetName(test_string);
    object.SetCount(test_int);
    object.SetProvider(test_string);
    object.SetExpiration(test_date);

    Item temp_copy(object);

    Item object2(std::move(temp_copy));

    QCOMPARE(object.GetName(), object2.GetName());
    QCOMPARE(object.GetStorage(), object2.GetStorage());
    QCOMPARE(object.GetCount(), object2.GetCount());
    QCOMPARE(object.GetProvider(), object2.GetProvider());
    QCOMPARE(object.GetExpiration(), object2.GetExpiration());
}
void TestItem::test_equeals_operator()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";
    const int test_int = 0xffff;
    const QDate test_date = QDate(2012, 12, 12);

    Item object;

    object.SetName(test_string);
    object.SetStorage(test_string);
    object.SetName(test_string);
    object.SetCount(test_int);
    object.SetProvider(test_string);
    object.SetExpiration(test_date);

    Item object2;
    object2 = object = object;

    QCOMPARE(object.GetName(), object2.GetName());
    QCOMPARE(object.GetStorage(), object2.GetStorage());
    QCOMPARE(object.GetCount(), object2.GetCount());
    QCOMPARE(object.GetProvider(), object2.GetProvider());
    QCOMPARE(object.GetExpiration(), object2.GetExpiration());
}

QTEST_APPLESS_MAIN(TestItem)

#include "tst_testitem.moc"
