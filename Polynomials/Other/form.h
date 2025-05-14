#pragma once
#define NOMINMAX
#include <algorithm>

// Подключаем .NET сборки
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include <msclr/marshal_cppstd.h>
#include <vcclr.h>

#include "translator.h"
#include "polynomials.h"
#include "Data structures/unsorted_table.h"
#include "Data structures/RedBlack_tree.h"
#include "Data structures/hash_table_chain.h"
#include "Data structures/hash_table.h"
#include "Data structures/sorted_table.h"
#include "Data structures/AVL.h"

// Подключаем нужные пространства имён
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

class PolyStorage {
public:
    TRedBlackTree<std::string, PolinomXYZ<10>> rbTree;
    ChainHashTable<std::string, PolinomXYZ<10>> hashTable;
    UnsortedTable<std::string, PolinomXYZ<10>> unsortedTable;
    TAVLTree<std::string, PolinomXYZ<10>> avlTree;
    SortedTable<std::string, PolinomXYZ<10>> sortedTable;
    //HashTable<std::string, PolinomXYZ<10>> hashTableInserts;
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
        UnsortedTable,
        SortedTable,
        AVLTree,
        HashTableInserts
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
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::FromArgb(200, 230, 255);

            // ComboBox для выбора структуры данных
            comboStructure = gcnew ComboBox();
            comboStructure->Items->AddRange(gcnew cli::array<String^> { "Red-Black tree", "Unsorted table", "Hash Table (Chain method)", "Hash Table (Inserts method)", "Sorted Table", "AVL Tree" });
            comboStructure->SelectedIndex = 0;
            comboStructure->Left = 20;
            comboStructure->Top = 20;
            comboStructure->DropDownStyle = ComboBoxStyle::DropDownList;
            this->Controls->Add(comboStructure);

            // ComboBox для выбора операции над полиномами
            comboBoxOperation = gcnew ComboBox();
            comboBoxOperation->Items->AddRange(gcnew cli::array<String^> { "+", "-", "*" });
            comboBoxOperation->SelectedIndex = 0;
            comboBoxOperation->Left = 940;
            comboBoxOperation->Top = 170;
            comboBoxOperation->Width = 75;
            comboBoxOperation->DropDownStyle = ComboBoxStyle::DropDownList;
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
            txtKeySearch->Width = 300;
            this->Controls->Add(txtKeySearch);

            ////Поле для ввода ключа удаляемого полинома
            txtKeyDelete = gcnew TextBox();
            txtKeyDelete->Left = 620;
            txtKeyDelete->Top = 60;
            txtKeyDelete->Width = 300;
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
            btnAdd->BackColor = System::Drawing::Color::GhostWhite;
            this->Controls->Add(btnAdd);

            // Кнопка для поиска полинома
            btnFind = gcnew Button();
            btnFind->Text = "Find";
            btnFind->Left = 940;
            btnFind->Top = 20;
            btnFind->Click += gcnew EventHandler(this, &MainForm::btnFind_Click);
            btnFind->BackColor = System::Drawing::Color::GhostWhite;
            this->Controls->Add(btnFind);

            // Кнопка для удаления полинома
            btnDelete = gcnew Button();
            btnDelete->Text = "Delete";
            btnDelete->Left = 940;
            btnDelete->Top = 60;
            btnDelete->Click += gcnew EventHandler(this, &MainForm::btnDelete_Click);
            btnDelete->BackColor = System::Drawing::Color::GhostWhite;
            this->Controls->Add(btnDelete);

            // Кнопка для вычисления выражения
            btnCalculate = gcnew Button();
            btnCalculate->Text = "Calculate";
            btnCalculate->Left = 940;
            btnCalculate->Top = 230;
            btnCalculate->Click += gcnew EventHandler(this, &MainForm::btnCalculate_Click);
            btnCalculate->BackColor = System::Drawing::Color::GhostWhite;
            this->Controls->Add(btnCalculate);

            // ListBox для отображения полиномов
            listPolys = gcnew ListBox();
            listPolys->Left = 20;
            listPolys->Top = 150;
            listPolys->Width = 500;
            listPolys->Height = 150;
            this->Controls->Add(listPolys);

            Label^ label0 = gcnew Label();
            label0->Text = "Input key of new polinom: ";
            label0-> Left = 20;
            label0->Top = 45;
            label0->AutoSize = true;          
            this->Controls->Add(label0);

            Label^ label1 = gcnew Label();
            label1->Text = "Choose type of data structure: ";
            label1->Left = 20;
            label1->Top = 5;
            label1->AutoSize = true;
            this->Controls->Add(label1);

            Label^ label2 = gcnew Label();
            label2->Text = "Input new polinom: ";
            label2->Left = 20;
            label2->Top = 85;
            label2->AutoSize = true;
            this->Controls->Add(label2);

            Label^ label3 = gcnew Label();
            label3->Text = "Contents of the current data structure: ";
            label3->Left = 20;
            label3->Top = 135;
            label3->AutoSize = true;
            this->Controls->Add(label3);

            Label^ label4 = gcnew Label();
            label4->Text = "Enter the key of the polynomial you want to found: ";
            label4->Left = 620;
            label4->Top = 5;
            label4->AutoSize = true;
            this->Controls->Add(label4);

            Label^ label5 = gcnew Label();
            label5->Text = "Enter the key of the polynomial you want to delete: ";
            label5->Left = 620;
            label5->Top = 45;
            label5->AutoSize = true;
            this->Controls->Add(label5);

            Label^ label6 = gcnew Label();
            label6->Text = "Input key of first polinom operand: ";
            label6->Left = 620;
            label6->Top = 135;
            label6->AutoSize = true;
            this->Controls->Add(label6);

            Label^ label7 = gcnew Label();
            label7->Text = "Input key of second polinom operand: ";
            label7->Left = 620;
            label7->Top = 175;
            label7->AutoSize = true;
            this->Controls->Add(label7);

            Label^ label8 = gcnew Label();
            label8->Text = "Result of operation: ";
            label8->Left = 620;
            label8->Top = 215;
            label8->AutoSize = true;
            this->Controls->Add(label8);

            //Label^ label9 = gcnew Label();
            //label9->Text = "Choose operation: ";
            //label9->Left = 970;
            //label9->Top = 155;
            //label9->AutoSize = true;
            //this->Controls->Add(label9);
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
            case 3:
                currentStructure = Structure::HashTableInserts;
                break;
            case 4:
                currentStructure = Structure::SortedTable;
                break;
            case 5:
                currentStructure = Structure::AVLTree;
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
                    case Structure::AVLTree:
                        storage->avlTree.Insert(stdName, poly);
                        break;
                    case Structure::SortedTable:
                        storage->sortedTable.insert(stdName, poly);
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
                MessageBox::Show("Please enter both a name and a polynomial.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        System::Void btnFind_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ keyManaged = txtKeySearch->Text->Trim();
            if (String::IsNullOrEmpty(keyManaged)) {
                MessageBox::Show("Enter the key of the required polynomial.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
                case Structure::AVLTree:
                    if (auto ptr = storage->avlTree.find(key)) {
                        found = ptr;
                    }
                    break;
                case Structure::SortedTable:
                    found = storage->sortedTable.find(key);
                    break;
                }

                if (found) {
                    std::stringstream ss;
                    ss << *found;
                    MessageBox::Show(gcnew String(ss.str().c_str()), "Polynomial found");
                }
                else {
                    MessageBox::Show("Polynomial with such key not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (const char* msg) {
                MessageBox::Show(gcnew String(msg), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }


        System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ keyManaged = txtKeyDelete->Text->Trim();

            if (String::IsNullOrEmpty(keyManaged))
            {
                MessageBox::Show("Enter the key of the required polynomial.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
                case Structure::AVLTree:
                    storage->avlTree.remove(key);
                    break;
                case Structure::SortedTable:
                    storage->sortedTable.remove(key);
                    break;
                default:
                    MessageBox::Show("Incorrect data structure!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                MessageBox::Show("Polynomial deleted succefully.");
                UpdateListBox(); // обновить вывод
            }
            catch (const char* msg)
            {
                MessageBox::Show(gcnew String(msg), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnCalculate_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ key1Managed = txtKey1->Text->Trim();
            String^ key2Managed = txtKey2->Text->Trim();

            if (String::IsNullOrEmpty(key1Managed) || String::IsNullOrEmpty(key2Managed)) {
                MessageBox::Show("Please enter both keys to calculate.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            std::string key1 = msclr::interop::marshal_as<std::string>(key1Managed);
            std::string key2 = msclr::interop::marshal_as<std::string>(key2Managed);

            if (comboBoxOperation->SelectedItem == nullptr) {
                MessageBox::Show("Select an operation (addition, subtraction or multiplication).", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
                case Structure::AVLTree:
                    poly1 = storage->avlTree.find(key1);
                    poly2 = storage->avlTree.find(key2);
                    break;
                case Structure::SortedTable:
                    poly1 = storage->sortedTable.find(key1);
                    poly2 = storage->sortedTable.find(key2);
                    break;
                }

                if (!poly1 || !poly2) {
                    MessageBox::Show("One or both polynomials were not found for the given keys.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
                    MessageBox::Show("Invalid operation. Use +, -, *.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                std::stringstream ss;
                ss << result;
                richTextBox->Clear();
                richTextBox->AppendText(gcnew String(ss.str().c_str()));
                richTextBox->AppendText("\n");
            }
            catch (const char* msg) {
                MessageBox::Show(gcnew String(msg), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
};