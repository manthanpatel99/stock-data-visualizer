#include "pch.h"
#include "MyForm.h"

using namespace CppCLR_WinFormsProject1;

// Function that takes a list of SmartCandlesticks and filters them by date range
List<SmartCandlestick^>^ MyForm::FilterStockData(List<SmartCandlestick^>^ smartDataList, System::DateTime fromDate, System::DateTime toDate)
{
    List<SmartCandlestick^>^ filteredData = gcnew List<SmartCandlestick^>();

    for each (SmartCandlestick ^ data in smartDataList) {
        if (data->Date >= fromDate && data->Date <= toDate) {
            filteredData->Add(data);
        }
    }

    return filteredData;
}


void MyForm::PopulateCandlestickChart(BindingList<SmartCandlestick^>^ stockDataList, String^ selectedPattern) {
	// Clear any existing series, legends, and annotations
	chart1->Series->Clear();
	chart1->Legends->Clear();
	chart1->Annotations->Clear();

	// Create a series for the Candlestick chart
	Series^ ohlcSeries = gcnew Series("ohlcSeries");
	ohlcSeries->ChartType = SeriesChartType::Candlestick;
	ohlcSeries->SetCustomProperty("OpenCloseStyle", "Triangle");
	ohlcSeries->SetCustomProperty("ShowOpenClose", "Both");
	ohlcSeries->SetCustomProperty("PointWidth", "1.0");
	ohlcSeries->YValuesPerPoint = 4;
	ohlcSeries->CustomProperties = "PriceUpColor=Lime,PriceDownColor=Red";
	ohlcSeries->XValueType = ChartValueType::DateTime;
	ohlcSeries->ChartArea = "ChartArea1";

	// Create a series for the Volume chart
	Series^ volumeSeries = gcnew Series("volumeSeries");
	volumeSeries->ChartType = SeriesChartType::Column;
	volumeSeries->XValueType = ChartValueType::DateTime;
	volumeSeries->ChartArea = "ChartArea2";

	// Track the min and max prices to scale the chart accordingly
	double minPrice = Double::MaxValue;
	double maxPrice = Double::MinValue;
	
	for (int i = 0; i < stockDataList->Count; i++) {
		// Update min and max prices
		minPrice = Math::Min(minPrice, stockDataList[i]->Low);
		maxPrice = Math::Max(maxPrice, stockDataList[i]->High);
	}

	// Bind the SmartCandlestick data to the ohlcSeries
	ohlcSeries->XValueMember = "Date";
	ohlcSeries->YValueMembers = "High,Low,Open,Close";

	// Bind the Volume data to the volumeSeries
	volumeSeries->XValueMember = "Date"; 
	volumeSeries->YValueMembers = "Volume";

	// Set the DataSource directly to the BindingList
	chart1->DataSource = stockDataList;

	// Add the OHLC series and the Volume series to the chart
	chart1->Series->Add(ohlcSeries);
	chart1->Series->Add(volumeSeries);

	// Set y-axis range based on min and max prices
	chart1->ChartAreas["ChartArea1"]->AxisY->Minimum = minPrice;
	chart1->ChartAreas["ChartArea1"]->AxisY->Maximum = maxPrice;

	// Add a legend for the ohlcSeries with green color
	Legend^ legend1 = gcnew Legend("Legend1");
	legend1->BackColor = Color::LightGray;
	legend1->BackGradientStyle = System::Windows::Forms::DataVisualization::Charting::GradientStyle::TopBottom;
	legend1->Name = "Legend1";
	legend1->Title = "Candlestick";
	legend1->TitleForeColor = Color::Green;
	chart1->Legends->Add(legend1);
}


List<SmartCandlestick^>^ MyForm::ConvertToSmartCandlesticks(List<Candlestick^>^ candlesticks)
{
	List<SmartCandlestick^>^ smartCandlesticks = gcnew List<SmartCandlestick^>();

	for each (Candlestick ^ candlestick in candlesticks) {
		SmartCandlestick^ smartCandlestick = gcnew SmartCandlestick(candlestick);
		smartCandlesticks->Add(smartCandlestick);
	}

	return smartCandlesticks;
}

bool MyForm::IsCandlestickMatchingPattern(SmartCandlestick^ candlestick, String^ selectedPattern) {
	// Logic to check if the candlestick matches the selected pattern
	// You can use if-else statements to handle different patterns
	// Return true if it matches, false otherwise

	if (selectedPattern == "isBullish") {
		return candlestick->IsBullish;
	}
	else if (selectedPattern == "isBearish") {
		return candlestick->IsBearish;
	}
	else if (selectedPattern == "isNeutral") {
		return candlestick->IsNeutral;
	}
	else if (selectedPattern == "isMarubozu") {
		return candlestick->IsMarubozu;
	}
	else if (selectedPattern == "isDoji") {
		return candlestick->IsDoji;
	}
	else if (selectedPattern == "isDragonFlyDoji") {
		return candlestick->IsDragonFlyDoji;
	}
	else if (selectedPattern == "isGravestoneDoji") {
		return candlestick->IsGravestoneDoji;
	}
	else if (selectedPattern == "isHammer") {
		return candlestick->IsHammer;
	}
	else if (selectedPattern == "isInvertedHammer") {
		return candlestick->IsInvertedHammer;
	}
	else {
		// Default to false if the pattern is not recognized
		return false;
	}
}
