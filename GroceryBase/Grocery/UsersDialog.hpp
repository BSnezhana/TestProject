#ifndef USERSDIALOG_HPP
#define USERSDIALOG_HPP

#include <QDialog>
#include "UserAccount.hpp"

namespace Ui {
class UsersDialog;
}


// класс диалогового окна для редактирования ползователей
class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    // конструктор и деструктор, созданные автоматически
    explicit UsersDialog(QWidget *parent = nullptr);
    ~UsersDialog();

    // методы для получения / устаноки списка пользователей
    const QList<UserAccount>& GetAccounts() const;
    void SetAccounts(const QList<UserAccount>& v);

    bool HasDuplicates() const;

private:
    // указатель на обхект, хранящий все виджеты на диалоговом окне (создается автоматическия)
    Ui::UsersDialog *ui;

    // список аккаунтов пользователей
    QList<UserAccount> Accounts;

private slots:
    // событие нажатия кнопки создания пользователя
    void CreatePushButton_Clicked();
    // событие нажатия кнопки удаления пользователя
    void RemovePushButton_Clicked();

    // событие изменения выделения пользователя в списке
    void AccountsListWidget_SelectedChanged();
    // событие изменения текста в поле радектирования имени пользователя
    void NameLineEdit_TextChanged(const QString& str);
    // событие изменения поля редактирования уровня доступа
    void StatusComboBox_SelectedChanged();
};

#endif // USERSDIALOG_HPP
