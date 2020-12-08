#include <QtTest>
#include "CSVStreamer.hpp"



class TestCSVStreamer : public QObject
{
    Q_OBJECT

public:
    TestCSVStreamer();
    ~TestCSVStreamer();

private slots:
    void test_no_file_write_read();
    void test_empty_file_write_read();
    void test_no_file_write_read_nothing();
    void test_empty_file_write_read_nothing();
    void test_no_file_write_read_enpty_lines();
    void test_empty_file_write_read_enpty_lines();
};

TestCSVStreamer::TestCSVStreamer()
{

}

TestCSVStreamer::~TestCSVStreamer()
{

}

void TestCSVStreamer::test_no_file_write_read()
{
    if (QFile::exists("test.csv"))
        QFile::remove("test.csv");

    {
        CSVStreamer writer("test.csv", QIODevice::WriteOnly);
        for (int i = 0; i < 10; i++)
        {
            QStringList list;
            for (int j = 0; j < 3; j++)
            {
                list.push_back(QString::number(i) + ": " + QString::number(j));
            }
            writer.WriteLine(list);
        }
    }
    {
        CSVStreamer reader("test.csv", QIODevice::ReadOnly);
        for (int i = 0; i < 10; i++)
        {
            QStringList list;
            for (int j = 0; j < 3; j++)
            {
                list.push_back(QString::number(i) + ": " + QString::number(j));
            }
            QCOMPARE(list, reader.ReadLine());
        }
        QCOMPARE(reader.ReadLine(), QStringList());
    }
}
void TestCSVStreamer::test_empty_file_write_read()
{
    if (!QFile::exists("test.csv"))
        QFile("test.vsv").open(QIODevice::WriteOnly);

    {
        CSVStreamer writer("test.csv", QIODevice::WriteOnly);
        for (int i = 0; i < 10; i++)
        {
            QStringList list;
            for (int j = 0; j < 3; j++)
            {
                list.push_back(QString::number(i) + ": " + QString::number(j));
            }
            writer.WriteLine(list);
        }
    }
    {
        CSVStreamer reader("test.csv", QIODevice::ReadOnly);
        for (int i = 0; i < 10; i++)
        {
            QStringList list;
            for (int j = 0; j < 3; j++)
            {
                list.push_back(QString::number(i) + ": " + QString::number(j));
            }
            QCOMPARE(list, reader.ReadLine());
        }
        QCOMPARE(reader.ReadLine(), QStringList());
    }
}
void TestCSVStreamer::test_no_file_write_read_nothing()
{
    if (QFile::exists("test.csv"))
        QFile::remove("test.csv");

    {
        CSVStreamer writer("test.csv", QIODevice::WriteOnly);
    }
    {
        CSVStreamer reader("test.csv", QIODevice::ReadOnly);
        QCOMPARE(reader.ReadLine(), QStringList());
    }
}
void TestCSVStreamer::test_empty_file_write_read_nothing()
{
    if (!QFile::exists("test.csv"))
        QFile("test.vsv").open(QIODevice::WriteOnly);


    {
        CSVStreamer writer("test.csv", QIODevice::WriteOnly);
    }
    {
        CSVStreamer reader("test.csv", QIODevice::ReadOnly);
        QCOMPARE(reader.ReadLine(), QStringList());
    }
}
void TestCSVStreamer::test_no_file_write_read_enpty_lines()
{
    if (QFile::exists("test.csv"))
        QFile::remove("test.csv");

    {
        CSVStreamer writer("test.csv", QIODevice::WriteOnly);
        for (int i = 0; i < 10; i++)
        {
            writer.WriteLine(QStringList());
        }
    }
    {
        CSVStreamer reader("test.csv", QIODevice::ReadOnly);
        for (int i = 0; i < 10; i++)
        {
            QCOMPARE(QStringList({ "" }), reader.ReadLine());
        }
        QCOMPARE(reader.ReadLine(), QStringList());
    }
}
void TestCSVStreamer::test_empty_file_write_read_enpty_lines()
{
    if (!QFile::exists("test.csv"))
        QFile("test.vsv").open(QIODevice::WriteOnly);


    {
        CSVStreamer writer("test.csv", QIODevice::WriteOnly);
        for (int i = 0; i < 10; i++)
        {
            writer.WriteLine(QStringList());
        }
    }
    {
        CSVStreamer reader("test.csv", QIODevice::ReadOnly);
        for (int i = 0; i < 10; i++)
        {
            QCOMPARE(QStringList({ "" }), reader.ReadLine());
        }
        QCOMPARE(reader.ReadLine(), QStringList());
    }
}

QTEST_APPLESS_MAIN(TestCSVStreamer)

#include "tst_testcsvstreamer.moc"
