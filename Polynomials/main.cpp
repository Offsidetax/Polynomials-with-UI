#include "Other/form.h"

// Подключаем .NET сборки
#using <System.dll>
#using <System.Windows.Forms.dll>

#include "Other/translator.h"
#include "Other/polynomials.h"
#include "Data structures/unsorted_table.h"
#include "Data structures/RedBlack_tree.h"
#include "Data structures/hash_table_chain.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(cli::array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Application::Run(gcnew MainForm());
    return 0;
}
