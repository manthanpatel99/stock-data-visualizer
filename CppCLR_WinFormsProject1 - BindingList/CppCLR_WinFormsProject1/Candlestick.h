#pragma once
#include <cmath> // For C++ standard math functions

using namespace System;
using namespace System::Collections::Generic; // Required for List<>
using namespace System::Data; // Required for DataTable
using namespace System::Windows::Forms::DataVisualization::Charting; // Required for Chart controls
using namespace System::IO; // Required for File and StreamReader

ref class Candlestick
{
public:
    property System::String^ Ticker;
    property System::String^ Period;
    property System::DateTime Date;
    property double Open;
    property double High;
    property double Low;
    property double Close;
    property long Volume;

    //Default constructor
    Candlestick()
    {
        // Set default values for properties
        Ticker = "DefaultTicker";
        Period = "DefaultPeriod";
        Date = System::DateTime::Now;
        Open = 0.0;
        High = 0.0;
        Low = 0.0;
        Close = 0.0;
        Volume = 0;
    }

    //Constructor that reads data from a filename
    Candlestick(System::String^ s) {
        // Define a format for the date string
        System::String^ format = "MMM d, yyyy";
        System::Globalization::CultureInfo^ culture = System::Globalization::CultureInfo::InvariantCulture;

        array<System::String^>^ values = s->Split(',');
        if (values->Length == 9) {
            Ticker = values[0];
            Period = values[1];
            System::String^ dateString = values[2] + "," + values[3];
            System::String^ cleanedDateString = dateString->Replace("\"", " ")->Trim();
            System::DateTime parsedDate = System::DateTime::ParseExact(cleanedDateString, format, culture);
            Date = parsedDate;
            Open = System::Convert::ToDouble(values[4]);
            High = System::Convert::ToDouble(values[5]);
            Low = System::Convert::ToDouble(values[6]);
            Close = System::Convert::ToDouble(values[7]);
            Volume = System::Convert::ToInt64(values[8]);
        }
    }
};

ref class SmartCandlestick : public Candlestick
{
public:
    // Additional properties
    property double Range;
    property double BodyRange;
    property double TopPrice;
    property double BottomPrice;
    property double TopTail;
    property double BottomTail;

    // Additional boolean properties for pattern recognition
    property bool IsBullish;
    property bool IsBearish;
    property bool IsNeutral;
    property bool IsMarubozu;
    property bool IsDoji;
    property bool IsDragonFlyDoji;
    property bool IsGravestoneDoji;
    property bool IsHammer;
    property bool IsInvertedHammer;

    // Constructor that takes in a string from a csv stock file
    SmartCandlestick(System::String^ s) : Candlestick(s)
    {
        // Calculate additional properties
        Range = High - Low;
        BodyRange = Math::Abs(Close - Open);
        TopPrice = Math::Max(Open, Close);
        BottomPrice = Math::Min(Open, Close);
        TopTail = High - Math::Max(Open, Close);
        BottomTail = Math::Min(Open, Close) - Low;
    
        // Calculate boolean pattern properties
        CalculatePatternProperties();
    }

    // Constructor that takes a Candlestick object
    SmartCandlestick(Candlestick^ candlestick) : Candlestick()
    {
        // Set base properties from the provided Candlestick
        Ticker = candlestick->Ticker;
        Period = candlestick->Period;
        Date = candlestick->Date;
        Open = candlestick->Open;
        High = candlestick->High;
        Low = candlestick->Low;
        Close = candlestick->Close;
        Volume = candlestick->Volume;

        // Calculate additional properties specific to SmartCandlestick
        Range = High - Low;
        BodyRange = Math::Abs(Close - Open);
        TopPrice = Math::Max(Open, Close);
        BottomPrice = Math::Min(Open, Close);
        TopTail = High - Math::Max(Open, Close);
        BottomTail = Math::Min(Open, Close) - Low;

        // Calculate boolean pattern properties
        CalculatePatternProperties();
    }

private:
    // Method to calculate boolean pattern properties
    void CalculatePatternProperties()
    {
        IsBullish = Close > Open;
        IsBearish = Open > Close;
        IsNeutral = Open == Close;
        IsMarubozu = BodyRange / Range > 0.9;
        IsDoji = BodyRange / Range < 0.1;
        IsDragonFlyDoji = IsDoji && BottomTail / Range < 0.05 && TopTail / Range > 0.1;
        IsGravestoneDoji = IsDoji && TopTail / Range < 0.05 && BottomTail / Range > 0.1;
        IsHammer = BottomTail > 2 * BodyRange && TopTail / Range < 0.1;
        IsInvertedHammer = TopTail > 2 * BodyRange && BottomTail / Range < 0.1;
    }
};