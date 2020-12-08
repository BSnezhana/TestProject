#include "CSVStreamer.hpp"
#include <QDir>



CSVStreamer::CSVStreamer(const QString& path, QIODevice::OpenModeFlag flag) : File(path) // вызов конструктора файла по определенному пути path
{
    // открытие файла на чтение / запись в зависимости от флага как текстового
    File.open(flag | QIODevice::Text);
    // привязка текстового потока к файлу
    Stream.setDevice(&File);
}
CSVStreamer::~CSVStreamer()
{
    // закрытие открытого файла
    File.close();
}

void CSVStreamer::WriteLine(const QStringList& strs)
{
    // формирование строки путем конкатенации всех строк из списка с разделителем ','
    QString line = "";
    for (int i = 0; i < strs.size() - 1; i++)
        line += strs[i] + ",";
    if (!strs.empty()) line += strs.last();
    // запись строки и перехода на следующую строку в файл
    Stream << line << '\n';
}
QStringList CSVStreamer::ReadLine()
{
    // читает строку из файла
    QString line = Stream.readLine();
    // если прочитать не получилось (конецфайла) возвращаем пустой список
    if (line.isNull()) return QStringList();
    // если прочиталась строка, она разбивается на список из строк по разделителю ','
    else return line.split(',');
}
