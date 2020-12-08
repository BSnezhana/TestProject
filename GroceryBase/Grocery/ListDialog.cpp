#include "ListDialog.hpp"
#include "ui_ListDialog.h"

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog)
{
    ui->setupUi(this);

    // привязка элементов к соответствующим обработчикам сигналов / слотам
    connect(ui->CreatePushButton, &QPushButton::clicked, this, &ListDialog::CreatePushButton_Clicked);
    connect(ui->RemovePushButton, &QPushButton::clicked, this, &ListDialog::RemovePushButton_Clicked);

    connect(ui->ItemsListWidget, &QListWidget::itemSelectionChanged, this, &ListDialog::ItemsListWidget_SelectedChanged);

    connect(ui->NameLineEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, &ListDialog::NameLineEdit_TextChanged);
}

ListDialog::~ListDialog()
{
    delete ui;
}

QList<QString> ListDialog::GetItems() const
{
    // запись всех элементов в список строк
    QList<QString> items;
    for (int i = 0; i < ui->ItemsListWidget->count(); i++)
        items.append(ui->ItemsListWidget->item(i)->text());
    return items;
}
void ListDialog::SetItems(const QList<QString>& v)
{
    // очистка текущего списка и запись новых элементов
    ui->ItemsListWidget->clear();
    for (int i = 0; i < v.size(); i++)
        ui->ItemsListWidget->addItem(v[i]);
}

bool ListDialog::HasDuplicates() const
{
    QStringList list = GetItems();

    for (int i = 0; i < list.count(); i++)
    {
        if (list.count(list[i]) > 1) return true;
    }
    return false;
}

void ListDialog::CreatePushButton_Clicked()
{
    // добавление элемента в список с дефолтной строкой
    ui->ItemsListWidget->addItem("Новый элемент...");
}
void ListDialog::RemovePushButton_Clicked()
{
    // получение списка выбранных элементов
    QList<QListWidgetItem*> items = ui->ItemsListWidget->selectedItems();
    // удаление кажддого элемента в списке
    for (QListWidgetItem* item : items) delete item;
}

void ListDialog::ItemsListWidget_SelectedChanged()
{
    // получение индекса текущего выделения в списке
    int index = ui->ItemsListWidget->currentRow();
    if (index >= 0 && index < ui->ItemsListWidget->count())
    {
        // если выбран существующий элемент, активируется кнопка удаления и поле редактирования значения
        ui->RemovePushButton->setEnabled(true);
        ui->NameLineEdit->setEnabled(true);

        // установка текста выбранного предмета в поле для его редактирования с отключением
        // отправки событий этим полем для избежания лишних вызовов
        ui->NameLineEdit->blockSignals(true);
        ui->NameLineEdit->setText(ui->ItemsListWidget->item(index)->text());
        ui->NameLineEdit->blockSignals(false);
    }
    else
    {
        ui->RemovePushButton->setEnabled(false);
        ui->NameLineEdit->setEnabled(false);
    }
}
void ListDialog::NameLineEdit_TextChanged(const QString& str)
{
    // получение индекса текущего выделения в списке
    int index = ui->ItemsListWidget->currentRow();
    // если индекс находится в допустимом диапазоне, текст выделенной строки в списке устанавливается на новый
    if (index >= 0 && index < ui->ItemsListWidget->count())
        ui->ItemsListWidget->item(index)->setText(str);
}
