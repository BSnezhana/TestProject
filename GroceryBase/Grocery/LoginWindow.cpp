#include "LoginWindow.hpp"
#include "ui_LoginWindow.h"
#include "CSVStreamer.hpp"



LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // привязка события нажатия кнопки к его обработчику / слоту
    connect(ui->LoginPushButton, SIGNAL(clicked()), this, SLOT(LoginPushButton_Clicked()));

    // создание обхекта вспомогательного класса для чтения списка пользователей
    CSVStreamer Streamer("Users.csv", QIODevice::ReadOnly);

    // добавление дефолтного пользователя администратора
    Accounts.append(UserAccount("Администратор", UserAccount::Admin));
    ui->UserComboBox->addItem("Администратор");

    QStringList list;
    // цикл, читающий строки до упирания в конец файла
    while ((list = Streamer.ReadLine()).size() == 2)
    {
        // добавление аккаунта, созданного из прочитанных данный текущей строки файла
        Accounts.append(UserAccount(list[0], list[1]));
        ui->UserComboBox->addItem(Accounts.last().GetName());
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::LoginPushButton_Clicked()
{
    // получение индекса выбранного аккаунта
    int index = ui->UserComboBox->currentIndex();
    // если ииндекс в допустимом диапазоне,
    if (index >= 0 && index < Accounts.size())
    {
        // станавливаем уровень доступа пользователя в главном окне и
        Window.SetUser(Accounts[index].GetStatus());

        // открываем основное окно,
        Window.show();

        // после чего закрывается окно выбора пользователя
        close();
    }
}
