#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "UserAccount.hpp"
#include "Item.hpp"



namespace Ui {
class MainWindow;
}

// класс основного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // конструктор и деструктор, созданные автоматически
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // метод для установки уровня доступа пользователя
    void SetUser(UserAccount::Status status);

private:
    // указатель на обхект, хранящий все виджеты на диалоговом окне (создается автоматическия)
    Ui::MainWindow *ui;

    // поле для хранения уровня доступа пользователя
    UserAccount::Status UserStatus;
    // список товаров
    QList<Item> Items;

    // метод для обновления строки товара в таблице (при изменении самого товара)
    void UpdateItem(int ind);
    // метод для обновления полей редактирования значения товара
    void UpdateEdit();

private slots:
    // вспомогательные слоты событий изменения текущего предмета
    void ItemValue_ChangedS(const QString& s);
    void ItemValue_ChangedI(int i);
    void ItemValue_ChangedD(const QDate& d);
    // все 3 предыдущих просто вызывают это, которое является общим для любых изменений товара
    void ItemValue_Changed();

    // кнопка выдачи товара
    void GivePushButton_Clicked();
    // выделение товара в таблице
    void ItemsTableWidget_Selected();

    // нажатие кнопки для редактирования пользователей
    void UsersPushButton_Clicked();
    // нажатие кнопки для редактирования мест хранения
    void StoragesPushButton_Clicked();
    // нажатие кнопки для редактирования поставщиков
    void ProvidersPushButton_Clicked();

    // нажатие кнопки добавления товара
    void AddPushButton_Clicked();
    // нажатие кнопки удаления товара
    void RemovePushButton_Clicked();
};

#endif // MAINWINDOW_HPP
