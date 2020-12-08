#ifndef LISTDIALOG_HPP
#define LISTDIALOG_HPP

#include <QDialog>

namespace Ui {
class ListDialog;
}


// класс диалогового окна, использующийся для редактирования списка строк
// используется как для редактирования мест хранения так и для редактирования поставщиков
class ListDialog : public QDialog
{
    Q_OBJECT

public:
    // конструктор и деструктор, созданные автоматически
    explicit ListDialog(QWidget *parent = nullptr);
    ~ListDialog();

    // методы для получения / устаноки списка строк
    QList<QString> GetItems() const;
    void SetItems(const QList<QString>& v);

    bool HasDuplicates() const;

private:
    // указатель на обхект, хранящий все виджеты на диалоговом окне (создается автоматическия)
    Ui::ListDialog *ui;


private slots:
    // слот под событие, происходящее при нажатии кнопри добавить
    void CreatePushButton_Clicked();
    // слот под событие, происходящее при нажатии кнопри удалить
    void RemovePushButton_Clicked();

    // слот под событие, происходящее при изменении выбранного предмета
    // используется для обновления значиний в иджетах для редактирования этих значений
    void ItemsListWidget_SelectedChanged();
    // слот под событие, происходящее при изменении текста в поле для редактирования значения
    void NameLineEdit_TextChanged(const QString& str);
};

#endif // LISTDIALOG_HPP
