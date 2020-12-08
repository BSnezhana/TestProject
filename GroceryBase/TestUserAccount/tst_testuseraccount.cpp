#include <QtTest>
#include "UserAccount.hpp"



class TestUserAccount : public QObject
{
    Q_OBJECT

public:
    TestUserAccount();
    ~TestUserAccount();

private slots:
    void test_get_set();
    void test_from_strings_constructor();
    void test_copy_constructor();
    void test_move_constructor();
    void test_equeals_operator();
};

TestUserAccount::TestUserAccount()
{

}

TestUserAccount::~TestUserAccount()
{

}

void TestUserAccount::test_get_set()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";

    UserAccount object;

    object.SetName(test_string);
    QCOMPARE(object.GetName(), test_string);

    object.SetStatus(UserAccount::Admin);
    QCOMPARE(object.GetStatus(), UserAccount::Admin);
    QCOMPARE(object.GetStatusString(), "admin");

    object.SetStatus(UserAccount::Manager);
    QCOMPARE(object.GetStatus(), UserAccount::Manager);
    QCOMPARE(object.GetStatusString(), "manager");

    object.SetStatus(UserAccount::Seller);
    QCOMPARE(object.GetStatus(), UserAccount::Seller);
    QCOMPARE(object.GetStatusString(), "seller");

    object.SetStatusString("admin");
    QCOMPARE(object.GetStatus(), UserAccount::Admin);
    QCOMPARE(object.GetStatusString(), "admin");

    object.SetStatusString("manager");
    QCOMPARE(object.GetStatus(), UserAccount::Manager);
    QCOMPARE(object.GetStatusString(), "manager");

    object.SetStatusString("seller");
    QCOMPARE(object.GetStatus(), UserAccount::Seller);
    QCOMPARE(object.GetStatusString(), "seller");
}
void TestUserAccount::test_from_strings_constructor()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";


    UserAccount object1(test_string, "admin");
    UserAccount object2(test_string, "manager");
    UserAccount object3(test_string, "seller");

    QCOMPARE(object1.GetName(), test_string);
    QCOMPARE(object1.GetStatus(), UserAccount::Admin);
    QCOMPARE(object1.GetStatusString(), "admin");

    QCOMPARE(object2.GetName(), test_string);
    QCOMPARE(object2.GetStatus(), UserAccount::Manager);
    QCOMPARE(object2.GetStatusString(), "manager");

    QCOMPARE(object3.GetName(), test_string);
    QCOMPARE(object3.GetStatus(), UserAccount::Seller);
    QCOMPARE(object3.GetStatusString(), "seller");
}
void TestUserAccount::test_copy_constructor()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";


    UserAccount object1(test_string, "admin");
    UserAccount object2(object1);

    QCOMPARE(object1.GetName(), object2.GetName());
    QCOMPARE(object1.GetStatus(), object2.GetStatus());
}
void TestUserAccount::test_move_constructor()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";


    UserAccount object1(test_string, "admin");
    UserAccount temp_copy(object1);
    UserAccount object2(std::move(temp_copy));

    QCOMPARE(object1.GetName(), object2.GetName());
    QCOMPARE(object1.GetStatus(), object2.GetStatus());
}
void TestUserAccount::test_equeals_operator()
{
    const QString test_string = "TEST_@#$%^&*(_098765_TEST";


    UserAccount object1(test_string, "admin");
    UserAccount object2;
    object2 = object1;

    QCOMPARE(object1.GetName(), object2.GetName());
    QCOMPARE(object1.GetStatus(), object2.GetStatus());
}

QTEST_APPLESS_MAIN(TestUserAccount)

#include "tst_testuseraccount.moc"
