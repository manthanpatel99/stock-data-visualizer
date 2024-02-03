#pragma once

#include "Candlestick.h"
#include "MyForm.h"


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		//Global Variables
		List<List<Candlestick^>^>^ allData;
		DateTime fromDate; 
		DateTime toDate;   

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			allData = gcnew List<List<Candlestick^>^>();
			dateTimePickerFrom->Value = DateTime::Now.AddMonths(-12); // Default "from" date (e.g., one month ago)
			dateTimePickerTo->Value = DateTime::Now; // Default "to" date (today)

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::DateTimePicker^ dateTimePickerFrom;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerTo;
	private: System::Windows::Forms::Label^ dtpFromLabel;
	private: System::Windows::Forms::Label^ dtpToLabel;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ OpenFileButton;
	private: String^ selectedFileName = nullptr;							// Initialize with a default value or null
	private: System::Windows::Forms::Label^ label1;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<Candlestick^>^ LoadDataFromFile(System::String^ fileName, DateTime fromDate, DateTime toDate);
		List<Candlestick^>^ FilterStockData(List<Candlestick^>^ stockDataList, System::DateTime fromDate, System::DateTime toDate);
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dateTimePickerFrom = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePickerTo = (gcnew System::Windows::Forms::DateTimePicker());
			this->dtpFromLabel = (gcnew System::Windows::Forms::Label());
			this->dtpToLabel = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->OpenFileButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// dateTimePickerFrom
			// 
			this->dateTimePickerFrom->Location = System::Drawing::Point(72, 117);
			this->dateTimePickerFrom->Name = L"dateTimePickerFrom";
			this->dateTimePickerFrom->Size = System::Drawing::Size(200, 20);
			this->dateTimePickerFrom->TabIndex = 2;
			// 
			// dateTimePickerTo
			// 
			this->dateTimePickerTo->Location = System::Drawing::Point(400, 117);
			this->dateTimePickerTo->Name = L"dateTimePickerTo";
			this->dateTimePickerTo->Size = System::Drawing::Size(200, 20);
			this->dateTimePickerTo->TabIndex = 3;
			// 
			// dtpFromLabel
			// 
			this->dtpFromLabel->AutoSize = true;
			this->dtpFromLabel->Location = System::Drawing::Point(141, 101);
			this->dtpFromLabel->Name = L"dtpFromLabel";
			this->dtpFromLabel->Size = System::Drawing::Size(59, 13);
			this->dtpFromLabel->TabIndex = 4;
			this->dtpFromLabel->Text = L"Date From:";
			this->dtpFromLabel->Click += gcnew System::EventHandler(this, &Form1::label1_Click_1);
			// 
			// dtpToLabel
			// 
			this->dtpToLabel->AutoSize = true;
			this->dtpToLabel->Location = System::Drawing::Point(487, 101);
			this->dtpToLabel->Name = L"dtpToLabel";
			this->dtpToLabel->Size = System::Drawing::Size(23, 13);
			this->dtpToLabel->TabIndex = 5;
			this->dtpToLabel->Text = L"To:";
			this->dtpToLabel->Click += gcnew System::EventHandler(this, &Form1::dtpToLabel_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->InitialDirectory = L"..\\..\\..\\Stock Data";
			this->openFileDialog1->Multiselect = true;
			this->openFileDialog1->Tag = L"";
			// 
			// OpenFileButton
			// 
			this->OpenFileButton->Location = System::Drawing::Point(278, 112);
			this->OpenFileButton->Name = L"OpenFileButton";
			this->OpenFileButton->Size = System::Drawing::Size(116, 35);
			this->OpenFileButton->TabIndex = 6;
			this->OpenFileButton->Text = L"Open File";
			this->OpenFileButton->UseVisualStyleBackColor = true;
			this->OpenFileButton->Click += gcnew System::EventHandler(this, &Form1::openFileButton_Click);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(151, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(388, 36);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Manthankumar Patel\'s Stock Analyzer";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click_2);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(702, 215);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->OpenFileButton);
			this->Controls->Add(this->dtpToLabel);
			this->Controls->Add(this->dtpFromLabel);
			this->Controls->Add(this->dateTimePickerTo);
			this->Controls->Add(this->dateTimePickerFrom);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void openFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Create and configure the OpenFileDialog
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
		openFileDialog1->Title = "Open File";
		openFileDialog1->Filter = "Daily|*-Day.csv|Weekly|*-Week.csv|Monthly|*-Month.csv|All Files|*.*";
		openFileDialog1->RestoreDirectory = false;
		openFileDialog1->Multiselect = true; // Ensure multiselect is enabled


		// Show the OpenFileDialog and check if the user selected a file
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Get the selected file name
			array<String^>^ selectedFileNames = openFileDialog1->FileNames;

			// Get the selected "from" and "to" dates from DateTimePickers
			fromDate = dateTimePickerFrom->Value;
			toDate = dateTimePickerTo->Value;

			// Iterate through the selected files and load data from each file
			for each (String ^ fileName in selectedFileNames) {
				// Load data from the CSV file and add it to the list
				List<Candlestick^>^ data = LoadDataFromFile(fileName, fromDate, toDate);
				allData->Add(data);
			}
		}

		// Iterate through allData and create a new MyForm for each list of Candlestick
		for each (List<Candlestick^> ^ candlestickList in allData) {
			// Create a new instance of MyForm using the constructor
			CppCLR_WinFormsProject1::MyForm^ myForm = gcnew CppCLR_WinFormsProject1::MyForm(candlestickList, fromDate, toDate);

			// Show MyForm
			myForm->Show();
		}
	}

	
	private: System::Void label1_Click_2(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void dtpToLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
