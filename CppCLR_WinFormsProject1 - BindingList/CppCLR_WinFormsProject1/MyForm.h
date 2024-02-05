#pragma once

#include "Candlestick.h"
#include "Recognizer.h"

namespace CppCLR_WinFormsProject1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: 
		List<Candlestick^>^ allCandlesticks;  // Declare allCandlesticks as a member variable
	private: System::Windows::Forms::ComboBox^ patternsComboBox;
	private: System::Windows::Forms::Label^ SelectPattern;
		   List<SmartCandlestick^>^ filteredData;  // Declare filteredData as a member variable
	private: System::Windows::Forms::Label^ titleLabel;

		   List<SmartCandlestick^>^ smartDataList; // Declare smartDataList as a member variable
		   BindingList<SmartCandlestick^>^ bindingList; //Declare the bindingList as a member variable

		   List<Recognizer^>^ recognizers; // List to store recognizer instances

	public:
		MyForm(void)
		{ 
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			List<Candlestick^>^ allCandlesticks;  
			List<SmartCandlestick^>^ filteredData;  
			List<SmartCandlestick^>^ smartDataList; 
			BindingList<SmartCandlestick^>^ bindingList;

			// Initialize the recognizers list
			recognizers = gcnew List<Recognizer^>();

			// Add the recognizers to the list
			recognizers->Add(gcnew BullishRecognizer());
			recognizers->Add(gcnew BearishRecognizer());
			recognizers->Add(gcnew MarubozuRecognizer());
			recognizers->Add(gcnew DojiRecognizer());
			recognizers->Add(gcnew DragonFlyDojiRecognizer());
			recognizers->Add(gcnew GravestoneDojiRecognizer());
			recognizers->Add(gcnew HammerRecognizer());
			recognizers->Add(gcnew InvertedHammerRecognizer());
			recognizers->Add(gcnew BullishEngulfingRecognizer());
			recognizers->Add(gcnew BearishEngulfingRecognizer());
			recognizers->Add(gcnew BullishHaramiRecognizer());
			recognizers->Add(gcnew BearishHaramiRecognizer());
			recognizers->Add(gcnew PeakRecognizer());
			recognizers->Add(gcnew ValleyRecognizer());

			// Populate the patternsComboBox
			for each (Recognizer ^ recognizer in recognizers) {
				patternsComboBox->Items->Add(recognizer->patternName);
			}
		}

		// Constructor that takes a List of Candlestick, start date, and end date
		MyForm(List<Candlestick^>^ candlestickList, DateTime fromDate, DateTime toDate)
		{
			InitializeComponent();

			// Assign the parameter to the member variable
			allCandlesticks = candlestickList;

			// Set the values of dateTimePickerFrom and dateTimePickerTo
			dateTimePickerFrom->Value = fromDate;
			dateTimePickerTo->Value = toDate;

			// Convert candlesticks to SmartCandlesticks
			smartDataList = ConvertToSmartCandlesticks(allCandlesticks);

			// Use the member variable to filter data
			filteredData = FilterStockData(smartDataList, fromDate, toDate);

			// Convert filteredData to BindingList
			bindingList = ConvertToBindingList(filteredData);

			// Initialize the recognizers list
			recognizers = gcnew List<Recognizer^>();

			// Add the recognizers to the list
			recognizers->Add(gcnew BullishRecognizer());
			recognizers->Add(gcnew BearishRecognizer());
			recognizers->Add(gcnew MarubozuRecognizer());
			recognizers->Add(gcnew DojiRecognizer());
			recognizers->Add(gcnew DragonFlyDojiRecognizer());
			recognizers->Add(gcnew GravestoneDojiRecognizer());
			recognizers->Add(gcnew HammerRecognizer());
			recognizers->Add(gcnew InvertedHammerRecognizer());
			recognizers->Add(gcnew BullishEngulfingRecognizer());
			recognizers->Add(gcnew BearishEngulfingRecognizer());
			recognizers->Add(gcnew BullishHaramiRecognizer());
			recognizers->Add(gcnew BearishHaramiRecognizer());
			recognizers->Add(gcnew PeakRecognizer());
			recognizers->Add(gcnew ValleyRecognizer());

			// Populate the patternsComboBox
			for each (Recognizer ^ recognizer in recognizers) {
				patternsComboBox->Items->Add(recognizer->patternName);
			}

			// Use the filtered data to populate the chart
			PopulateCandlestickChart(bindingList, nullptr);

			// Set the title based on the first candlestick's ticker and period
			if (allCandlesticks->Count > 0) {
				titleLabel->Text = allCandlesticks[0]->Ticker + " - " + allCandlesticks[0]->Period;
				this->Text = titleLabel->Text; // Set the form title
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Button^ updateButton;
	private: System::Windows::Forms::Label^ dtpToLabel;
	private: System::Windows::Forms::Label^ dtpFromLabel;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerTo;
	private: System::Windows::Forms::DateTimePicker^ dateTimePickerFrom;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<SmartCandlestick^>^ FilterStockData(List<SmartCandlestick^>^ smartDataList, System::DateTime fromDate, System::DateTime toDate);
		void PopulateCandlestickChart(BindingList<SmartCandlestick^>^ bindingList, String^ selectedPattern);
		//System::Void patternsComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		List<SmartCandlestick^>^ ConvertToSmartCandlesticks(List<Candlestick^>^ candlesticks);
		bool IsCandlestickMatchingPattern(SmartCandlestick^ candlestick, String^ selectedPattern);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->updateButton = (gcnew System::Windows::Forms::Button());
			this->dtpToLabel = (gcnew System::Windows::Forms::Label());
			this->dtpFromLabel = (gcnew System::Windows::Forms::Label());
			this->dateTimePickerTo = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePickerFrom = (gcnew System::Windows::Forms::DateTimePicker());
			this->patternsComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->SelectPattern = (gcnew System::Windows::Forms::Label());
			this->titleLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			chartArea2->Name = L"ChartArea2";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->ChartAreas->Add(chartArea2);
			legend1->BackColor = System::Drawing::Color::LightGray;
			legend1->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::TopBottom;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 70);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->CustomProperties = L"PriceUpColor=Lime, LabelValueType=Open, PointWidth=1, PriceDownColor=Red";
			series1->Legend = L"Legend1";
			series1->MarkerBorderColor = System::Drawing::Color::White;
			series1->Name = L"ohlcSeries";
			series1->XValueMember = L"Date";
			series1->YValueMembers = L"Open, High, Low, Close";
			series1->YValuesPerPoint = 4;
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series2->ChartArea = L"ChartArea2";
			series2->Legend = L"Legend1";
			series2->Name = L"volumeSeries";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(1116, 420);
			this->chart1->TabIndex = 9;
			this->chart1->Text = L"chart1";
			// 
			// updateButton
			// 
			this->updateButton->Location = System::Drawing::Point(634, 596);
			this->updateButton->Name = L"updateButton";
			this->updateButton->Size = System::Drawing::Size(75, 23);
			this->updateButton->TabIndex = 11;
			this->updateButton->Text = L"Update";
			this->updateButton->UseVisualStyleBackColor = true;
			this->updateButton->Click += gcnew System::EventHandler(this, &MyForm::updateButton_Click);
			// 
			// dtpToLabel
			// 
			this->dtpToLabel->AutoSize = true;
			this->dtpToLabel->Location = System::Drawing::Point(928, 583);
			this->dtpToLabel->Name = L"dtpToLabel";
			this->dtpToLabel->Size = System::Drawing::Size(23, 13);
			this->dtpToLabel->TabIndex = 15;
			this->dtpToLabel->Text = L"To:";
			this->dtpToLabel->Click += gcnew System::EventHandler(this, &MyForm::dtpToLabel_Click);
			// 
			// dtpFromLabel
			// 
			this->dtpFromLabel->AutoSize = true;
			this->dtpFromLabel->Location = System::Drawing::Point(533, 583);
			this->dtpFromLabel->Name = L"dtpFromLabel";
			this->dtpFromLabel->Size = System::Drawing::Size(59, 13);
			this->dtpFromLabel->TabIndex = 14;
			this->dtpFromLabel->Text = L"Date From:";
			// 
			// dateTimePickerTo
			// 
			this->dateTimePickerTo->Location = System::Drawing::Point(751, 599);
			this->dateTimePickerTo->Name = L"dateTimePickerTo";
			this->dateTimePickerTo->Size = System::Drawing::Size(200, 20);
			this->dateTimePickerTo->TabIndex = 13;
			// 
			// dateTimePickerFrom
			// 
			this->dateTimePickerFrom->Location = System::Drawing::Point(392, 599);
			this->dateTimePickerFrom->Name = L"dateTimePickerFrom";
			this->dateTimePickerFrom->Size = System::Drawing::Size(200, 20);
			this->dateTimePickerFrom->TabIndex = 12;
			// 
			// patternsComboBox
			// 
			this->patternsComboBox->FormattingEnabled = true;
			this->patternsComboBox->Location = System::Drawing::Point(1185, 120);
			this->patternsComboBox->Name = L"patternsComboBox";
			this->patternsComboBox->Size = System::Drawing::Size(152, 21);
			this->patternsComboBox->TabIndex = 16;
			// 
			// SelectPattern
			// 
			this->SelectPattern->AutoSize = true;
			this->SelectPattern->Location = System::Drawing::Point(1222, 104);
			this->SelectPattern->Name = L"SelectPattern";
			this->SelectPattern->Size = System::Drawing::Size(74, 13);
			this->SelectPattern->TabIndex = 17;
			this->SelectPattern->Text = L"Select Pattern";
			this->SelectPattern->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// titleLabel
			// 
			this->titleLabel->AutoSize = true;
			this->titleLabel->Location = System::Drawing::Point(572, 32);
			this->titleLabel->Name = L"titleLabel";
			this->titleLabel->Size = System::Drawing::Size(35, 13);
			this->titleLabel->TabIndex = 18;
			this->titleLabel->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1406, 737);
			this->Controls->Add(this->titleLabel);
			this->Controls->Add(this->SelectPattern);
			this->Controls->Add(this->patternsComboBox);
			this->Controls->Add(this->dtpToLabel);
			this->Controls->Add(this->dtpFromLabel);
			this->Controls->Add(this->dateTimePickerTo);
			this->Controls->Add(this->dateTimePickerFrom);
			this->Controls->Add(this->updateButton);
			this->Controls->Add(this->chart1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dtpToLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void updateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Update the filtered data with updated dates
		List<SmartCandlestick^>^ updatedData = FilterStockData(smartDataList, dateTimePickerFrom->Value, dateTimePickerTo->Value);

		bindingList = ConvertToBindingList(updatedData);

		chart1->DataSource = bindingList;
		chart1->DataBind();

		// Get the selected pattern from the ComboBox
		Object^ selectedItem = patternsComboBox->SelectedItem;
		String^ selectedPattern = (selectedItem != nullptr) ? selectedItem->ToString() : nullptr;

		// Find the selected recognizer in the list
		Recognizer^ selectedRecognizer = nullptr;
		for each (Recognizer ^ recognizer in recognizers) {
			if (recognizer->patternName == selectedPattern) {
				selectedRecognizer = recognizer;
				break;
			}
		}

		// Check if a recognizer is selected
		if (selectedRecognizer != nullptr) {
			// Recognize the pattern and get the indices of recognized points
			List<int>^ recognizedIndices = selectedRecognizer->Recognize(updatedData);

			// Annotate the recognized points on the chart
			AnnotateRecognizedPoints(recognizedIndices);
		}
		
	}

	private: void AnnotateRecognizedPoints(List<int>^ recognizedIndices) {
		// Clear existing annotations
		chart1->Annotations->Clear();

		// Set a constant value for the width and height
		const double annotationSize = 1.0;  // Adjust as needed

		// Add annotations for each recognized point
		for each (int index in recognizedIndices) {
			if (index >= 0 && index < chart1->Series["ohlcSeries"]->Points->Count) {
				DataPoint^ dataPoint = chart1->Series["ohlcSeries"]->Points[index];

				// Annotate the matching candlestick with a square
				RectangleAnnotation^ annotation = gcnew RectangleAnnotation();
				annotation->AxisX = chart1->ChartAreas["ChartArea1"]->AxisX;
				annotation->AxisY = chart1->ChartAreas["ChartArea1"]->AxisY;
				annotation->X = dataPoint->XValue - (annotationSize / 2.0);
				annotation->Y = dataPoint->YValues[1] - (annotationSize / 2.0);  // Y value corresponds to Low
				annotation->Width = annotationSize;
				annotation->Height = annotationSize;
				annotation->BackColor = Color::Yellow;  // Change the color as needed
				chart1->Annotations->Add(annotation);
			}
		}
	}



	private: BindingList<SmartCandlestick^>^ ConvertToBindingList(List<SmartCandlestick^>^ sourceList) {
		BindingList<SmartCandlestick^>^ bindingList = gcnew BindingList<SmartCandlestick^>();

		for each (SmartCandlestick ^ item in sourceList) {
			bindingList->Add(item);
		}

		return bindingList;
	}
};
}
