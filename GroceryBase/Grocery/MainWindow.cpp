#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "CSVStreamer.hpp"
#include "UsersDialog.hpp"
#include "ListDialog.hpp"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // привязка элементов к соответствующим обработчикам сигналов / слотам
    connect(ui->GivePushButton, &QPushButton::clicked, this, &MainWindow::GivePushButton_Clicked);
    connect(ui->CountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::ItemValue_ChangedI);
    connect(ui->NameLineEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, &MainWindow::ItemValue_ChangedS);
    connect(ui->StorageComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::ItemValue_ChangedI);
    connect(ui->ProviderComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::ItemValue_ChangedI);
    connect(ui->ExpirationDateEdit, QOverload<const QDate&>::of(&QDateEdit::dateChanged), this, &MainWindow::ItemValue_ChangedD);
    connect(ui->ItemsTableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::ItemsTableWidget_Selected);
    connect(ui->UsersPushButton, &QPushButton::clicked, this, &MainWindow::UsersPushButton_Clicked);

    connect(ui->StoragesPushButton, &QPushButton::clicked, this, &MainWindow::StoragesPushButton_Clicked);
    connect(ui->ProvidersPushButton, &QPushButton::clicked, this, &MainWindow::ProvidersPushButton_Clicked);
    connect(ui->AddPushButton, &QPushButton::clicked, this, &MainWindow::AddPushButton_Clicked);
    connect(ui->RemovePushButton, &QPushButton::clicked, this, &MainWindow::RemovePushButton_Clicked);

    // установка типа выделения в таблице на выделение строк целиком
    ui->ItemsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // установка количества столбцов таблицы
    ui->ItemsTableWidget->setColumnCount(5);
    // установка названий столбцов
    ui->ItemsTableWidget->setHorizontalHeaderLabels({ "Название", "Количество", "Место хранения", "Поставщик", "Срок годности" });
    // параметр, который автоматически растягивает ширину последнего столбца под ширину окна
    ui->ItemsTableWidget->horizontalHeader()->setStretchLastSection(true);

    // объект для чтения товаров
    CSVStreamer Streamer("Items.csv", QIODevice::ReadOnly);

    QStringList line;
    while ((line = Streamer.ReadLine()).size() == 5)
    {
        Items.append(Item(line));
        int index = ui->ItemsTableWidget->rowCount();
        ui->ItemsTableWidget->setRowCount(index + 1);
        for (int i = 0; i < 5; i++)
            ui->ItemsTableWidget->setItem(index, i, new QTableWidgetItem(line[i]));
    }


    // объект для чтения мест хранения
    CSVStreamer SStreamer("Storages.csv", QIODevice::ReadOnly);
    // добавление пустого / отсутствующего значения в список возможных мест хранения
    ui->StorageComboBox->addItem("");
    // чтение строк мест храннения из файла до конца и добавление их с список
    while ((line = SStreamer.ReadLine()).size() == 1)
        ui->StorageComboBox->addItem(line[0]);

    // объект для чтения поставщиков
    CSVStreamer PStreamer("Providers.csv", QIODevice::ReadOnly);
    // добавление пустого / отсутствующего значения в список возможных поставщиков
    ui->ProviderComboBox->addItem("");
    // чтение строк поставщиков из файла до конца и добавление их с список
    while ((line = PStreamer.ReadLine()).size() == 1)
        ui->ProviderComboBox->addItem(line[0]);
}

MainWindow::~MainWindow()
{
    // сохранение текущего списка товаров в файл
    CSVStreamer Streamer("Items.csv", QIODevice::WriteOnly);
    for (int i = 0; i < Items.size(); i++)
        Streamer.WriteLine(Items[i].ToList());

    delete ui;
}

void MainWindow::SetUser(UserAccount::Status status)
{
    // установка поля с уровнем доступа на требуемое
    UserStatus = status;

    // деактиващия всех кнопок для редактирования
    ui->UsersPushButton->setEnabled(false);
    ui->StoragesPushButton->setEnabled(false);
    ui->ProvidersPushButton->setEnabled(false);
    ui->AddPushButton->setEnabled(false);

    switch (UserStatus)
    {
    case UserAccount::Admin:
        // активация кнопки, доступной администратору + всех кнопок доступных менеджеру
        ui->UsersPushButton->setEnabled(true);

    case UserAccount::Manager:
        // активация всех кнопок доступных менеджеру
        ui->AddPushButton->setEnabled(true);
        ui->StoragesPushButton->setEnabled(true);
        ui->ProvidersPushButton->setEnabled(true);
    }
}

void MainWindow::UpdateItem(int ind)
{
    if (ind >= 0 && ind < Items.size())
    {
        // если индекс находится в допустимом диапазоне,
        Item& item = Items[ind];
        // все значения ячеек таблицы (0го, 1го, ... столбцов) в необходимой строке
        // устанавливливаются соответственно значениям полей объекта выбранного по инексу (ind)
        ui->ItemsTableWidget->item(ind, 0)->setText(item.GetName());
        ui->ItemsTableWidget->item(ind, 1)->setText(item.GetCountString());
        ui->ItemsTableWidget->item(ind, 2)->setText(item.GetStorage());
        ui->ItemsTableWidget->item(ind, 3)->setText(item.GetProvider());
        ui->ItemsTableWidget->item(ind, 4)->setText(item.GetExpirationString());
    }
}
void MainWindow::UpdateEdit()
{
    // получение списка выделенных строк
    QItemSelectionModel *select = ui->ItemsTableWidget->selectionModel();
    QModelIndexList list = select->selectedRows();

    // цикл по всем выбранным строкам
    for (int i = 0; i < list.size(); i++)
    {
        int index = list[i].row();

        // если индекс выбранной строки лежит в допустимом диапазоне
        if (index >= 0 && index < Items.size())
        {
            Item& item = Items[index];

            // значения полей для их редактирования устанавливаются на значения выбранного товара
            // предварительно отключается подача сигналов об изменении значения для
            // избежания их вызова при программном их изменении
            ui->CountSpinBox->blockSignals(true);
            ui->CountSpinBox->setValue(item.GetCount());
            ui->CountSpinBox->blockSignals(false);

            ui->NameLineEdit->blockSignals(true);
            ui->NameLineEdit->setText(item.GetName());
            ui->NameLineEdit->blockSignals(false);

            ui->StorageComboBox->blockSignals(true);
            ui->StorageComboBox->setCurrentText(item.GetStorage());
            ui->StorageComboBox->blockSignals(false);

            ui->ProviderComboBox->blockSignals(true);
            ui->ProviderComboBox->setCurrentText(item.GetProvider());
            ui->ProviderComboBox->blockSignals(false);

            ui->ExpirationDateEdit->blockSignals(true);
            ui->ExpirationDateEdit->setDate(item.GetExpiration());
            ui->ExpirationDateEdit->blockSignals(false);

            // остановка цикла, так как одновременно можно редактировать только один товар
            break;
        }
    }
}

void MainWindow::ItemValue_ChangedS(const QString& s)
{
    ItemValue_Changed();
}
void MainWindow::ItemValue_ChangedI(int i)
{
    ItemValue_Changed();
}
void MainWindow::ItemValue_ChangedD(const QDate& d)
{
    ItemValue_Changed();
}
void MainWindow::ItemValue_Changed()
{
    // обработка изменения одного из полей редактирования значений товара

    // получение всех выделенных товаров
    QItemSelectionModel *select = ui->ItemsTableWidget->selectionModel();
    QModelIndexList list = select->selectedRows();

    // цикл по всем выделенным товарам
    for (int i = 0; i < list.size(); i++)
    {
        int index = list[i].row();

        // если индекс выбранной строки лежит в допустимом диапазоне
        if (index >= 0 && index < Items.size())
        {
            Item& item = Items[index];

            // получение значений каждого из полей редактирования значений товара
            int count = ui->CountSpinBox->value();
            QString name = ui->NameLineEdit->text();
            QString storage = ui->StorageComboBox->currentText();
            QString provider = ui->ProviderComboBox->currentText();
            QDate expiration = ui->ExpirationDateEdit->date();

            // установка всех полей товара на полученные значения
            item.SetCount(count);
            item.SetName(name);
            item.SetStorage(storage);
            item.SetProvider(provider);
            item.SetExpiration(expiration);

            // обновление строки с товаром в таблице
            UpdateItem(index);
        }
    }
}

void MainWindow::GivePushButton_Clicked()
{
    // получение всех выделенных товаров
    QItemSelectionModel *select = ui->ItemsTableWidget->selectionModel();
    QModelIndexList list = select->selectedRows();

    // цикл по всем выделенным товарам
    for (int i = 0; i < list.size(); i++)
    {
        int index = list[i].row();

        // если индекс выбранной строки лежит в допустимом диапазоне
        if (index >= 0 && index < Items.size())
        {
            Item& item = Items[index];
            // если предметов не осталось
            if (item.GetCount() < 1)
            {
                // выводится сообщение
                QMessageBox::warning(this, "Внимание!", "Товар \"" + item.GetName() + "\" закончился!");
                // итерация прерывается, так как уменьшать нечего
                continue;
            }

            // уменьшение количества товара на 1
            item.SetCount(item.GetCount() - 1);

            // вывод предупреждения елси количество меньше 6
            if (item.GetCount() <= 5)
            {
                QMessageBox::warning(this, "Внимание!", "Количество товара \"" + item.GetName() + "\" составляет: " + QString::number(item.GetCount()));
            }

            // обновление значения в поле редактирования с отключением сигналов
            ui->CountSpinBox->blockSignals(true);
            ui->CountSpinBox->setValue(item.GetCount());
            ui->CountSpinBox->blockSignals(false);
            // обновление строки товара в таблице
            UpdateItem(index);
        }
    }
}
void MainWindow::ItemsTableWidget_Selected()
{
    // получение всех выделенных товаров
    QItemSelectionModel *select = ui->ItemsTableWidget->selectionModel();
    QModelIndexList list = select->selectedRows();

    // если выделенных нет
    if (list.empty())
    {
        // отключение всех элементов для редактирования товара, так как редактировать нечего
        ui->GivePushButton->setEnabled(false);
        ui->CountSpinBox->setEnabled(false);
        ui->NameLineEdit->setEnabled(false);
        ui->StorageComboBox->setEnabled(false);
        ui->ProviderComboBox->setEnabled(false);
        ui->ExpirationDateEdit->setEnabled(false);
        ui->RemovePushButton->setEnabled(false);
    }
    else
    {
        // в противном случае активащия кнопки выдачи для всех пользователей
        ui->GivePushButton->setEnabled(true);
        switch (UserStatus)
        {
        // активащия кнопок менеджера для менеджера и администратора
        case UserAccount::Admin:
        case UserAccount::Manager:
            ui->CountSpinBox->setEnabled(true);
            ui->NameLineEdit->setEnabled(true);
            ui->StorageComboBox->setEnabled(true);
            ui->ProviderComboBox->setEnabled(true);
            ui->ExpirationDateEdit->setEnabled(true);
            ui->StoragesPushButton->setEnabled(true);
            ui->ProvidersPushButton->setEnabled(true);
            ui->RemovePushButton->setEnabled(true);
        }
    }

    // обновление полей редактирования
    UpdateEdit();
}

void MainWindow::UsersPushButton_Clicked()
{
    // создание диалога редактирования ползователей как дочернего от текцщего окна
    UsersDialog dialog(this);

    // создание списка пользователей
    QList<UserAccount> Accounts;

    // чтение списка пользователей из файла
    CSVStreamer Streamer("Users.csv", QIODevice::ReadOnly);
    QStringList list;
    while ((list = Streamer.ReadLine()).size() == 2)
        Accounts.append(UserAccount(list[0], list[1]));

    // передача списка в диалоговое окно
    dialog.SetAccounts(Accounts);

    // вызов диалогового окна и проверка на то, что была нажата кнопка Okint code;
    int code;
    while ((code = dialog.exec()) == QDialog::Accepted && dialog.HasDuplicates())
        QMessageBox::warning(this, "Ошибка.", "Имена пользователей повторяются.");
    if (code == QDialog::Accepted)
    {
        // если пользователь не отменил изменения, они записываются в файл
        CSVStreamer WStreamer("Users.csv", QIODevice::WriteOnly);
        Accounts = dialog.GetAccounts();
        for (int i = 0; i < Accounts.size(); i++)
        {
            WStreamer.WriteLine({ Accounts[i].GetName(), Accounts[i].GetStatusString() });
        }
    }
}
void MainWindow::StoragesPushButton_Clicked()
{
    // создание диалога редактирования списка
    ListDialog dialog(this);
    dialog.setWindowTitle("Редактирование мест хранения");

    // создание списка мест хранения
    QList<QString> storages;

    // чтение списка из файла
    CSVStreamer Streamer("Storages.csv", QIODevice::ReadOnly);
    QStringList list;
    while ((list = Streamer.ReadLine()).size() == 1)
        storages.append(list[0]);

    // передача списка в диалоговое окно
    dialog.SetItems(storages);

    // вызов диалогового окна и проверка на то, что была нажата кнопка Ok
    int code;
    while ((code = dialog.exec()) == QDialog::Accepted && dialog.HasDuplicates())
        QMessageBox::warning(this, "Ошибка.", "Места хранения повторяются.");
    if (code == QDialog::Accepted)
    {
        storages = dialog.GetItems();

        // если пользователь не отменил изменения, они записываются в файл
        CSVStreamer WStreamer("Storages.csv", QIODevice::WriteOnly);
        for (int i = 0; i < storages.size(); i++)
            WStreamer.WriteLine({ storages[i] });

        // блокируются сигналы виджета для выбора места хранения
        ui->StorageComboBox->blockSignals(true);
        // очистка текущих элементов
        ui->StorageComboBox->clear();
        // добавление дефолтного пустого элемента
        ui->StorageComboBox->addItem("");
        // добавления всех новых элементов
        ui->StorageComboBox->addItems(storages);
        // отключается блокировка сигналов
        ui->StorageComboBox->blockSignals(false);

        // цикл по всем имеющимся товарам
        for (int i = 0; i < Items.size(); i++)
        {
            Item& item = Items[i];
            // если текущее значение места хранения товара отсутствует в новом списке это значение заменяется на пустое
            if (!storages.contains(item.GetStorage()))
            {
                item.SetStorage("");
                ui->ItemsTableWidget->item(i, 2)->setText(item.GetStorage());
            }
        }
        // обновление полей редактирования товара
        UpdateEdit();
    }
}
void MainWindow::ProvidersPushButton_Clicked()
{
    // создание диалога редактирования списка
    ListDialog dialog(this);
    dialog.setWindowTitle("Редактирование поставщиков");

    // создание списка поставщиков
    QList<QString> providers;

    // чтение списка из файла
    CSVStreamer Streamer("Providers.csv", QIODevice::ReadOnly);
    QStringList list;
    while ((list = Streamer.ReadLine()).size() == 1)
        providers.append(list[0]);

    // передача списка в диалоговое окно
    dialog.SetItems(providers);

    // вызов диалогового окна и проверка на то, что была нажата кнопка Ok
    int code;
    while ((code = dialog.exec()) == QDialog::Accepted && dialog.HasDuplicates())
        QMessageBox::warning(this, "Ошибка.", "Поставщики повторяются.");
    if (code == QDialog::Accepted)
    {
        providers = dialog.GetItems();

        // если пользователь не отменил изменения, они записываются в файл
        CSVStreamer WStreamer("Providers.csv", QIODevice::WriteOnly);
        for (int i = 0; i < providers.size(); i++)
            WStreamer.WriteLine({ providers[i] });

        // блокируются сигналы виджета для выбора поставщиков
        ui->ProviderComboBox->blockSignals(true);
        // очистка текущих элементов
        ui->ProviderComboBox->clear();
        // добавление дефолтного пустого элемента
        ui->ProviderComboBox->addItem("");
        // добавления всех новых элементов
        ui->ProviderComboBox->addItems(providers);
        // отключается блокировка сигналов
        ui->ProviderComboBox->blockSignals(false);

        // цикл по всем имеющимся товарам
        for (int i = 0; i < Items.size(); i++)
        {
            Item& item = Items[i];
            // если текущее значение поставщика товара отсутствует в новом списке это значение заменяется на пустое
            if (!providers.contains(item.GetProvider()))
            {
                item.SetProvider("");
                ui->ItemsTableWidget->item(i, 3)->setText(item.GetProvider());
            }
        }

        // обновление полей редактирования товара
        UpdateEdit();
    }
}

void MainWindow::AddPushButton_Clicked()
{
    // создание нового товара и добавление его в список товаров
    Item item;
    Items.append(item);

    // добавление строки товара в таблицу
    int index = ui->ItemsTableWidget->rowCount();
    ui->ItemsTableWidget->setRowCount(index + 1);

    // заполнение строки товара значениями нового товара
    ui->ItemsTableWidget->setItem(index, 0, new QTableWidgetItem(item.GetName()));
    ui->ItemsTableWidget->setItem(index, 1, new QTableWidgetItem(item.GetCountString()));
    ui->ItemsTableWidget->setItem(index, 2, new QTableWidgetItem(item.GetStorage()));
    ui->ItemsTableWidget->setItem(index, 3, new QTableWidgetItem(item.GetProvider()));
    ui->ItemsTableWidget->setItem(index, 4, new QTableWidgetItem(item.GetExpirationString()));
}
void MainWindow::RemovePushButton_Clicked()
{
    if (QMessageBox::question(this, "Удаление.", "Вы уверены, что хотите удалить выделенные товары?")
            != QMessageBox::Yes) return;

    // получение списка выделенных товаров
    QItemSelectionModel *select = ui->ItemsTableWidget->selectionModel();
    QModelIndexList list = select->selectedRows();

    // формарование множества уникальных индексов выделенных товаров
    QSet<int> s_indices;
    for (int i = 0; i < list.size(); i++)
        s_indices.insert(list[i].row());
    // формирование списка из множества уникальных товаров
    QList<int> indices = s_indices.values();
    // сортировка списка по убыванию для нормального последовательного удаления товаров по индексам
    std::sort(indices.begin(), indices.end(), [](int l, int r) { return l > r; });

    for (int i = 0; i < indices.size(); i++)
    {
        int index = indices[i];

        // удаление строки товара и самого товара по каждому из отсортированных индексов
        ui->ItemsTableWidget->removeRow(index);
        Items.removeAt(index);
    }
}
