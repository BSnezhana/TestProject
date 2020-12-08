#include "UsersDialog.hpp"
#include "ui_UsersDialog.h"



// функция для получения названия уровня доступа из перечисления
QString GetStatusString(UserAccount::Status status)
{
    switch (status)
    {
    case UserAccount::Admin: return "администратор";
    case UserAccount::Manager: return "менеджер";
    case UserAccount::Seller: return "продавец";
    default: return "неизвестен";
    }
}

UsersDialog::UsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);

    // заполнения списка возможных уровней доступа в эполе выбора
    ui->StatusComboBox->addItems({ "Администратор", "Менеджер", "Продавец" });

    // привязка элементов к соответствующим обработчикам сигналов / слотам
    connect(ui->CreatePushButton, &QPushButton::clicked, this, &UsersDialog::CreatePushButton_Clicked);
    connect(ui->RemovePushButton, &QPushButton::clicked, this, &UsersDialog::RemovePushButton_Clicked);

    connect(ui->AccountsListWidget, &QListWidget::itemSelectionChanged, this, &UsersDialog::AccountsListWidget_SelectedChanged);

    connect(ui->NameLineEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, &UsersDialog::NameLineEdit_TextChanged);
    connect(ui->StatusComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UsersDialog::StatusComboBox_SelectedChanged);
}

UsersDialog::~UsersDialog()
{
    delete ui;
}

const QList<UserAccount>& UsersDialog::GetAccounts() const
{
    return Accounts;
}
void UsersDialog::SetAccounts(const QList<UserAccount>& v)
{
    Accounts = v;

    // очистка элементов списка и заполнение его строками, состоящими из '[уровень доступа]: имя аккаунта'
    ui->AccountsListWidget->clear();
    for (int i = 0; i < Accounts.size(); i++)
    {
        UserAccount& account = Accounts[i];
        ui->AccountsListWidget->addItem("[" + GetStatusString(account.GetStatus()) + "]: " + account.GetName());
    }
}

bool UsersDialog::HasDuplicates() const
{
    QList<UserAccount> list = GetAccounts();

    for (int i = 0; i < list.count(); i++)
    {
        int c = 0;
        for (int j = 0; j < list.count(); j++)
            if (list[j].GetName() == list[i].GetName()) c++;
        if (c > 1) return true;
    }
    return false;
}

void UsersDialog::CreatePushButton_Clicked()
{
    // добавление нового аккаунта в список аккаунтов и в виджет со строками, представляющими эти аккаунты
    UserAccount account("Новый аккаунт...", UserAccount::Manager);
    Accounts.append(account);
    ui->AccountsListWidget->addItem("[" + GetStatusString(account.GetStatus()) + "]: " + account.GetName());
}
void UsersDialog::RemovePushButton_Clicked()
{
    // удаление аккаунта из списока аккаунтов и в виджета со строками, представляющими эти аккаунты
    int index = ui->AccountsListWidget->currentRow();
    if (index >= 0 && index < Accounts.size())
    {
        Accounts.removeAt(index);
        delete ui->AccountsListWidget->item(index);
    }
    // эмитация изменения выделения для обновления статуса полей редактирования значений
    AccountsListWidget_SelectedChanged();
}

void UsersDialog::AccountsListWidget_SelectedChanged()
{
    int index = ui->AccountsListWidget->currentRow();
    // если выбранный индекс лежит в допустимом диапазоне
    if (index >= 0 && index < Accounts.size())
    {
        // активащия полей редактирования и кнопки удаления
        ui->RemovePushButton->setEnabled(true);
        ui->NameLineEdit->setEnabled(true);
        ui->StatusComboBox->setEnabled(true);

        // установка значений для полей редактирования с отключением сигналов
        ui->NameLineEdit->blockSignals(true);
        ui->NameLineEdit->setText(Accounts[index].GetName());
        ui->NameLineEdit->blockSignals(false);
        ui->StatusComboBox->blockSignals(true);
        ui->StatusComboBox->setCurrentIndex((int)Accounts[index].GetStatus());
        ui->StatusComboBox->blockSignals(false);
    }
    else
    {
        // деактиващия полей редактирования и кнопки удаления
        ui->RemovePushButton->setEnabled(false);
        ui->NameLineEdit->setEnabled(false);
        ui->StatusComboBox->setEnabled(false);
    }
}
void UsersDialog::NameLineEdit_TextChanged(const QString& str)
{
    int index = ui->AccountsListWidget->currentRow();
    if (index >= 0 && index < Accounts.size())
    {
        // если индекс выбранного аккаунта в допустимом диапазоне
        // имя аккаунта устанавливается на новое
        Accounts[index].SetName(str);
        // обновляется строка аккаунта в списке
        ui->AccountsListWidget->item(index)->setText("[" +
            GetStatusString(Accounts[index].GetStatus()) + "]: " + Accounts[index].GetName());
    }
}
void UsersDialog::StatusComboBox_SelectedChanged()
{
    int index = ui->AccountsListWidget->currentRow();
    if (index >= 0 && index < Accounts.size())
    {
        // если индекс выбранного аккаунта в допустимом диапазоне
        // уровень доступа аккаунта устанавливается на новый
        Accounts[index].SetStatus((UserAccount::Status)ui->StatusComboBox->currentIndex());
        // обновляется строка аккаунта в списке
        ui->AccountsListWidget->item(index)->setText("[" +
            GetStatusString(Accounts[index].GetStatus()) + "]: " + Accounts[index].GetName());
    }
}
