#pragma once
#include "Candlestick.h"

ref class Recognizer abstract
{
public:
    int patternSize;
    String^ patternName;
    Recognizer(String^ pn, int ps) : patternName(pn), patternSize(ps) {}

    List<int>^ Recognize(List<SmartCandlestick^>^ lscs) {
        List<int>^ result = gcnew List<int>();

        for (int i = patternSize - 1; i < lscs->Count; i++) {
            List<SmartCandlestick^>^ sublist = gcnew List<SmartCandlestick^>(lscs->GetRange(i - patternSize + 1, patternSize));

            if (RecognizePattern(sublist)) {
                result->Add(i);
            }
        }

        return result;
    }

    // Polymorphic aspect of the class Recognizer
    // This function will differ for each iteration of the pattern recognizer
    // in the derived classes.
    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) abstract;
};

ref class BullishRecognizer : Recognizer {
public:
    BullishRecognizer() : Recognizer("Bullish", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsBullish;
    }
};

ref class BearishRecognizer : Recognizer {
public:
    BearishRecognizer() : Recognizer("Bearish", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsBearish;
    }
};

ref class MarubozuRecognizer : Recognizer {
public:
    MarubozuRecognizer() : Recognizer("Marubozu", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsMarubozu;
    }
};

ref class DojiRecognizer : Recognizer {
public:
    DojiRecognizer() : Recognizer("Doji", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsDoji;
    }
};

ref class DragonFlyDojiRecognizer : Recognizer {
public:
    DragonFlyDojiRecognizer() : Recognizer("DragonFlyDoji", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsDragonFlyDoji;
    }
};

ref class GravestoneDojiRecognizer : Recognizer {
public:
    GravestoneDojiRecognizer() : Recognizer("GravestoneDoji", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsGravestoneDoji;
    }
};

ref class HammerRecognizer : Recognizer {
public:
    HammerRecognizer() : Recognizer("Hammer", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsHammer;
    }
};

ref class InvertedHammerRecognizer : Recognizer {
public:
    InvertedHammerRecognizer() : Recognizer("InvertedHammer", 1) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsInvertedHammer;
    }
};

ref class BullishEngulfingRecognizer : Recognizer {
public:
    BullishEngulfingRecognizer() : Recognizer("BullishEngulfing", 2) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsBearish && lscs[1]->IsBullish && lscs[1]->TopPrice > lscs[0]->TopPrice &&
            lscs[1]->BottomPrice > lscs[0]->BottomPrice;
    }
};

ref class BearishEngulfingRecognizer : Recognizer {
public:
    BearishEngulfingRecognizer() : Recognizer("BearishEngulfing", 2) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsBullish && lscs[1]->IsBearish && lscs[1]->TopPrice > lscs[0]->TopPrice &&
            lscs[1]->BottomPrice > lscs[0]->BottomPrice;
    }
};

ref class BullishHaramiRecognizer : Recognizer {
public:
    BullishHaramiRecognizer() : Recognizer("Bullish Harami", 2) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsBearish && lscs[1]->IsBullish &&
            lscs[1]->TopPrice < lscs[0]->TopPrice && lscs[1]->BottomPrice > lscs[0]->BottomPrice;
    }
};

ref class BearishHaramiRecognizer : Recognizer {
public:
    BearishHaramiRecognizer() : Recognizer("Bearish Harami", 2) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[0]->IsBullish && lscs[1]->IsBearish &&
            lscs[1]->TopPrice < lscs[0]->TopPrice && lscs[1]->BottomPrice > lscs[0]->BottomPrice;
    }
};

ref class PeakRecognizer : Recognizer {
public:
    PeakRecognizer() : Recognizer("Peak", 3) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[1]->High > lscs[0]->High && lscs[1]->High > lscs[2]->High;
    }
};

ref class ValleyRecognizer : Recognizer {
public:
    ValleyRecognizer() : Recognizer("Valley", 3) {}

    virtual bool RecognizePattern(List<SmartCandlestick^>^ lscs) override {
        return lscs[1]->Low < lscs[0]->Low && lscs[1]->Low < lscs[2]->Low;
    }
};