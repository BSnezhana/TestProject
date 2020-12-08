#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include "MainWindow.hpp"
#include "UserAccount.hpp"



QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

// окно для выбора пользователя
class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    // конструктор и деструктор, созданные автоматически
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    // указатель на обхект, хранящий все виджеты на диалоговом окне (создается автоматическия)
    Ui::LoginWindow *ui;

    // список аккаунтов пользователей
    QList<UserAccount> Accounts;

    // объект класса основного окна, которое будет вызвано при нажатии кнопки 'Войти'
    MainWindow Window;

private slots:
    // событие нажатия кнопки 'Войти'
    void LoginPushButton_Clicked();
};
#endif // LOGINWINDOW_HPP
