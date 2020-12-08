#ifndef CSVSTREAMER_HPP
#define CSVSTREAMER_HPP
#include <QFile>
#include <QTextStream>



// Вспомогательный класс, использующийся для записи и чтения строк в формате CSV.
class CSVStreamer
{
private:
    // объект для хранения файла который читаем / в который пишем
    QFile File;
    // поток для обертки файла в текстовый поток для работы с ним как с текстом
    QTextStream Stream;

public:
    // конструктор, который принимает путь и флаг, сообщающий читаем мы файл или пишем в него
    CSVStreamer(const QString& path, QIODevice::OpenModeFlag flag);
    // деструктор для закрытия открытоко в конструкторе файла
    ~CSVStreamer();

    // записывает список строк как строку таблицы
    void WriteLine(const QStringList& strs);
    // читает строку таблицы и превраает в список строк (отдельных значений ячеек)
    QStringList ReadLine();
};

#endif // CSVSTREAMER_HPP
