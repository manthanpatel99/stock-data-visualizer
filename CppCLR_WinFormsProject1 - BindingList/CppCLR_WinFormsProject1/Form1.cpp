#include "pch.h"
#include "Form1.h"


List<Candlestick^>^ CppCLRWinFormsProject::Form1::LoadDataFromFile(System::String^ fileName, DateTime fromDate, DateTime toDate) {
    // Open the file and read data
    array<System::String^>^ lines = File::ReadAllLines(fileName);

    // Skip the header line (first line)
    bool skippedHeader = false;

    // Process the data and populate your data structure
    // (e.g., create a list of custom objects)
    List<Candlestick^>^ stockDataList = gcnew List<Candlestick^>();

    for each (System::String ^ line in lines) {
        if (!skippedHeader) {
            skippedHeader = true;
            continue; // Skip the header line
        }

        // Use the Candlestick(String^ s) constructor
        Candlestick^ data = gcnew Candlestick(line);

        // Add the data to stockDataList
        stockDataList->Add(data);
    }

    return stockDataList;
}



List<Candlestick^>^ CppCLRWinFormsProject::Form1::FilterStockData(List<Candlestick^>^ stockDataList, System::DateTime fromDate, System::DateTime toDate)
{
    List<Candlestick^>^ filteredData = gcnew List<Candlestick^>();

    for each (Candlestick ^ data in stockDataList) {
        if (data->Date >= fromDate && data->Date <= toDate) {
            filteredData->Add(data);
        }
    }

    return filteredData;
}


