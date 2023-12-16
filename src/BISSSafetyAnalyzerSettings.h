#ifndef BISSSAFETY_ANALYZER_SETTINGS
#define BISSSAFETY_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class BISSSafetyAnalyzerSettings : public AnalyzerSettings
{
  public:
    BISSSafetyAnalyzerSettings();
    virtual ~BISSSafetyAnalyzerSettings();

    virtual bool SetSettingsFromInterfaces();
    void UpdateInterfacesFromSettings();
    virtual void LoadSettings( const char* settings );
    virtual const char* SaveSettings();


    Channel mMaChannel;
    Channel mSloChannel;

    // U32 mBitRate;
    U32 mDataLengthCPW;
    U32 mDataLengthSPW;

    double mDatenart;

  protected:
    std::auto_ptr<AnalyzerSettingInterfaceChannel> mMaChannelInterface;
    std::auto_ptr<AnalyzerSettingInterfaceChannel> mSloChannelInterface;
    // std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
    std::auto_ptr<AnalyzerSettingInterfaceInteger> mDataLengthCPWInterface;
    std::auto_ptr<AnalyzerSettingInterfaceInteger> mDataLengthSPWInterface;
    std::auto_ptr<AnalyzerSettingInterfaceNumberList> mDatenartInterface;
};

#endif // BISSSAFETY_ANALYZER_SETTINGS
