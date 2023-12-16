#ifndef BISSSAFETY_ANALYZER_RESULTS
#define BISSSAFETY_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class BISSSafetyAnalyzer;
class BISSSafetyAnalyzerSettings;

class BISSSafetyAnalyzerResults : public AnalyzerResults
{
  public:
    BISSSafetyAnalyzerResults( BISSSafetyAnalyzer* analyzer, BISSSafetyAnalyzerSettings* settings );
    virtual ~BISSSafetyAnalyzerResults();

    virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
    virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

    virtual void GenerateFrameTabularText( U64 frame_index, DisplayBase display_base );
    virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
    virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );
    // private:
    // int heinz;
  protected: // functions
  protected: // vars
    BISSSafetyAnalyzerSettings* mSettings;
    BISSSafetyAnalyzer* mAnalyzer;
};

#endif // BISSSAFETY_ANALYZER_RESULTS
