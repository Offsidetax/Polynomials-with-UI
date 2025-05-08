#pragma once

// Подключаем .NET сборки
#using <System.dll>
#using <System.Windows.Forms.dll>

#include <msclr/marshal_cppstd.h>
#include <vcclr.h>

#include "translator.h"
#include "polynomials.h"
#include "Data structures/unsorted_table.h"
#include "Data structures/RedBlack_tree.h"
#include "Data structures/hash_table_chain.h"

// Подключаем нужные пространства имён
using namespace System;
using namespace System::Windows::Forms;

class PolyStorage {
public:
    TRedBlackTree<std::string, PolinomXYZ<10>> rbTree;
    ChainHashTable<std::string, PolinomXYZ<10>> hashTable;
    UnsortedTable<std::string, PolinomXYZ<10>> unsortedTable;
};

public ref class MainForm : public Form
{
public:
    MainForm()
    {
        InitializeComponent();
        storage = new PolyStorage();
        currentStructure = Structure::RedBlackTree;

        comboStructure->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::OnStructureChanged);
    }

    ~MainForm()
    {
        delete storage;
        storage = nullptr;
    }

private:

    enum class Structure {
        RedBlackTree,
        HashTable,
        UnsortedTable
    };

    Structure currentStructure;

    PolyStorage* storage;

    ComboBox^ comboStructure;
    ComboBox^ comboBoxOperation;
    TextBox^ txtName;
    TextBox^ txtExpression;
    Button^ btnAdd;
    TextBox^ txtKeySearch;
    Button^ btnFind;
    TextBox^ txtKeyDelete;
    TextBox^ richTextBox;
    Button^ btnDelete;
    ListBox^ listPolys;
    TextBox^ txtKey1;
    TextBox^ txtKey2;
    Button^ btnCalculate;

    void UpdateListBox()
    {
        listPolys->Items->Clear();

        switch (currentStructure)
        {
        case Structure::RedBlackTree:
            for (auto it = storage->rbTree.begin(); it != storage->rbTree.end(); ++it)
            {
                listPolys->Items->Add(gcnew String((it->key + " - " + it->value.ToString()).c_str()));
            }
            break;

        case Structure::UnsortedTable:
            for (auto it = storage->unsortedTable.begin(); it != storage->unsortedTable.end(); ++it)
            {
                const std::string& key = it->first;
                const PolinomXYZ<10>& poly = it->second;
                listPolys->Items->Add(gcnew String((key + " - " + poly.ToString()).c_str()));
            }
            break;

        case Structure::HashTable:
            for (auto it = storage->hashTable.begin(); it != storage->hashTable.end(); ++it) {
                const auto& pair = *it;
                std::string str = pair.first + " - " + pair.second.ToString();
                listPolys->Items->Add(gcnew String(str.c_str()));
            }
            break;
        }
    }

        void InitializeComponent()
        {
            this->Text = "Polynomial Interface";
            this->Width = 1200;
            this->Height = 400;

            // ComboBox для выбора структуры данных
            comboStructure = gcnew ComboBox();
            comboStructure->Items->AddRange(gcnew cli::array<String^> { "Red-Black tree", "Unsorted table", "Hash Table" });
            comboStructure->SelectedIndex = 0;
            comboStructure->Left = 20;
            comboStructure->Top = 20;
            this->Controls->Add(comboStructure);

            // ComboBox для выбора операции над полиномами
            comboBoxOperation = gcnew ComboBox();
            comboBoxOperation->Items->AddRange(gcnew cli::array<String^> { "+", "-", "*" });
            comboBoxOperation->SelectedIndex = 0;
            comboBoxOperation->Left = 940;
            comboBoxOperation->Top = 170;
            comboBoxOperation->Width = 75;
            this->Controls->Add(comboBoxOperation);

            // Поле для ввода ключа полинома
            txtName = gcnew TextBox();
            txtName->Left = 20;
            txtName->Top = 60;
            txtName->Width = 200;
            this->Controls->Add(txtName);

            // Поле для вывода выражения полинома
            txtExpression = gcnew TextBox();
            txtExpression->Left = 20;
            txtExpression->Top = 100;
            txtExpression->Width = 300;
            this->Controls->Add(txtExpression);

            ////Поле для ввода ключа искомого полинома
            txtKeySearch = gcnew TextBox();
            txtKeySearch->Left = 620;
            txtKeySearch->Top = 20;
            txtKeySearch->Width = 200;
            this->Controls->Add(txtKeySearch);

            ////Поле для ввода ключа удаляемого полинома
            txtKeyDelete = gcnew TextBox();
            txtKeyDelete->Left = 620;
            txtKeyDelete->Top = 60;
            txtKeyDelete->Width = 200;
            this->Controls->Add(txtKeyDelete);

            // Поле для ввода ключа первого полинома в выражении
            txtKey1 = gcnew TextBox();
            txtKey1->Left = 620;
            txtKey1->Top = 150;
            txtKey1->Width = 300;
            this->Controls->Add(txtKey1);

            // Поле для ввода ключа второго полинома в выражении
            txtKey2 = gcnew TextBox();
            txtKey2->Left = 620;
            txtKey2->Top = 190;
            txtKey2->Width = 300;
            this->Controls->Add(txtKey2);

            // Поле для вывода результата выражения с полиномами
            richTextBox = gcnew TextBox();
            richTextBox->Left = 620;
            richTextBox->Top = 230;
            richTextBox->Width = 300;
            this->Controls->Add(richTextBox);

            // Кнопка для добавления полинома
            btnAdd = gcnew Button();
            btnAdd->Text = "Add";
            btnAdd->Left = 340;
            btnAdd->Top = 100;
            btnAdd->Click += gcnew EventHandler(this, &MainForm::OnAddClick);
            this->Controls->Add(btnAdd);

            // Кнопка для поиска полинома
            btnFind = gcnew Button();
            btnFind->Text = "Find";
            btnFind->Left = 940;
            btnFind->Top = 20;
            btnFind->Click += gcnew EventHandler(this, &MainForm::btnFind_Click);
            this->Controls->Add(btnFind);

            // Кнопка для удаления полинома
            btnDelete = gcnew Button();
            btnDelete->Text = "Delete";
            btnDelete->Left = 940;
            btnDelete->Top = 60;
            btnDelete->Click += gcnew EventHandler(this, &MainForm::btnDelete_Click);
            this->Controls->Add(btnDelete);

            // Кнопка для вычисления выражения
            btnCalculate = gcnew Button();
            btnCalculate->Text = "Calculate";
            btnCalculate->Left = 940;
            btnCalculate->Top = 230;
            btnCalculate->Click += gcnew EventHandler(this, &MainForm::btnCalculate_Click);
            this->Controls->Add(btnCalculate);

            // ListBox для отображения полиномов
            listPolys = gcnew ListBox();
            listPolys->Left = 20;
            listPolys->Top = 150;
            listPolys->Width = 500;
            listPolys->Height = 150;
            this->Controls->Add(listPolys);
        }

        void OnStructureChanged(Object ^ sender, EventArgs ^ e)
        {
            Structure previousStructure = currentStructure;

            switch (comboStructure->SelectedIndex)
            {
            case 0:
                currentStructure = Structure::RedBlackTree;
                break;
            case 1:
                currentStructure = Structure::UnsortedTable;
                break;
            case 2:
                currentStructure = Structure::HashTable;
                break;
            default:
                currentStructure = Structure::RedBlackTree;
                break;
            }

            // Очищаем предыдущую структуру
            if (previousStructure != currentStructure) UpdateListBox();
        }

        // Обработчик клика по кнопке "Add"
        void OnAddClick(Object ^ sender, EventArgs ^ e)
        {
            String^ name = txtName->Text;
            String^ expr = txtExpression->Text;

            // Проверяем, что поля не пустые
            if (name != "" && expr != "")
            {
                try
                {
                    std::string stdName = msclr::interop::marshal_as<std::string>(name);
                    std::string infix = msclr::interop::marshal_as<std::string>(expr);

                    // Создаем объект для трансляции полинома
                    Arithmetic_Expression arithExpr(infix);

                    PolinomXYZ<10> poly(arithExpr.GetCoefficients(), arithExpr.GetDegree());

                    // Добавляем в соответствующую структуру данных
                    switch (currentStructure)
                    {
                    case Structure::RedBlackTree:
                        storage->rbTree.Insert(stdName, poly);
                        storage->rbTree.Print();
                        break;
                    case Structure::HashTable:
                        storage->hashTable.insert(stdName, poly);
                        break;
                    case Structure::UnsortedTable:
                        storage->unsortedTable.insert(stdName, poly);
                        break;
                    }


                    // Отображаем полином в ListBox
                    listPolys->Items->Add(name + " - " + expr);
                    txtName->Text = "";
                    txtExpression->Text = "";
                }
                catch (const std::exception& ex)
                {
                    MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            else
            {
                MessageBox::Show("Please enter both a name and an expression.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        System::Void btnFind_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ keyManaged = txtKeySearch->Text->Trim();
            if (String::IsNullOrEmpty(keyManaged)) {
                MessageBox::Show("Введите ключ для поиска.");
                return;
            }

            std::string key = msclr::interop::marshal_as<std::string>(keyManaged);
            PolinomXYZ<10>* found = nullptr;

            try {
                switch (currentStructure) {
                case Structure::RedBlackTree:
                    if (auto ptr = storage->rbTree.find(key)) {
                        found = ptr;
                    }
                    break;
                case Structure::UnsortedTable:
                    found = storage->unsortedTable.find(key);
                    break;
                case Structure::HashTable:
                    found = storage->hashTable.find(key);
                    break;
                }

                if (found) {
                    std::stringstream ss;
                    ss << *found;
                    MessageBox::Show(gcnew String(ss.str().c_str()), "Полином найден");
                }
                else {
                    MessageBox::Show("Полином с таким ключом не найден.");
                }
            }
            catch (const char* msg) {
                MessageBox::Show(gcnew String(msg), "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }


        System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ keyManaged = txtKeyDelete->Text->Trim();

            if (String::IsNullOrEmpty(keyManaged))
            {
                MessageBox::Show("Введите ключ для удаления.");
                return;
            }

            std::string key = msclr::interop::marshal_as<std::string>(keyManaged);

            try
            {
                switch (currentStructure)
                {
                case Structure::RedBlackTree:
                    storage->rbTree.remove(key);
                    break;
                case Structure::UnsortedTable:
                    storage->unsortedTable.remove(key);
                    break;
                case Structure::HashTable:
                    storage->hashTable.remove(key);
                    break;
                default:
                    MessageBox::Show("Неизвестная структура данных.");
                    return;
                }

                MessageBox::Show("Элемент успешно удалён.");
                UpdateListBox(); // обновить вывод
            }
            catch (const char* msg)
            {
                MessageBox::Show(gcnew String(msg), "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnCalculate_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ key1Managed = txtKey1->Text->Trim();
            String^ key2Managed = txtKey2->Text->Trim();

            if (String::IsNullOrEmpty(key1Managed) || String::IsNullOrEmpty(key2Managed)) {
                MessageBox::Show("Введите оба ключа для вычисления.");
                return;
            }

            std::string key1 = msclr::interop::marshal_as<std::string>(key1Managed);
            std::string key2 = msclr::interop::marshal_as<std::string>(key2Managed);

            if (comboBoxOperation->SelectedItem == nullptr) {
                MessageBox::Show("Выберите операцию (сложение, вычитание или умножение).");
                return;
            }

            std::string op = msclr::interop::marshal_as<std::string>(comboBoxOperation->SelectedItem->ToString());

            PolinomXYZ<10>* poly1 = nullptr;
            PolinomXYZ<10>* poly2 = nullptr;

            try {
                // Поиск полиномов по выбранной структуре
                switch (currentStructure) {
                case Structure::RedBlackTree:
                    poly1 = storage->rbTree.find(key1);
                    poly2 = storage->rbTree.find(key2);
                    break;
                case Structure::UnsortedTable:
                    poly1 = storage->unsortedTable.find(key1);
                    poly2 = storage->unsortedTable.find(key2);
                    break;
                case Structure::HashTable:
                    poly1 = storage->hashTable.find(key1);
                    poly2 = storage->hashTable.find(key2);
                    break;
                }

                if (!poly1 || !poly2) {
                    MessageBox::Show("Один или оба полинома не найдены по указанным ключам.");
                    return;
                }

                // Вычисление результата
                PolinomXYZ<10> result;
                if (op == "+")
                    result = *poly1 + *poly2;
                else if (op == "-")
                    result = *poly1 - *poly2;
                else if (op == "*")
                    result = *poly1 * *poly2;
                else {
                    MessageBox::Show("Недопустимая операция. Используйте +, -, *.");
                    return;
                }

                std::stringstream ss;
                ss << result;
                richTextBox->AppendText(gcnew String(ss.str().c_str()));
                richTextBox->AppendText("\n");
            }
            catch (const char* msg) {
                MessageBox::Show(gcnew String(msg), "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }




};
