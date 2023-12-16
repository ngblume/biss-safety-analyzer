#include "BISSSafetyAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


BISSSafetyAnalyzerSettings::BISSSafetyAnalyzerSettings()
    : mMaChannel( UNDEFINED_CHANNEL ), mSloChannel( UNDEFINED_CHANNEL ), mDataLengthCPW( 24 ), mDataLengthSPW( 16 ), mDatenart( )
{
    //---------------------------------------------------------------------------------------------------------------------------------
    // MaChannel = MASTER OUT / CLOCK
    mMaChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mMaChannelInterface->SetTitleAndTooltip( "MA", "" );
    mMaChannelInterface->SetChannel( mMaChannel );
    //---------------------------------------------------------------------------------------------------------------------------------
    // SloChannel = Slave OUT / DATA
    mSloChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mSloChannelInterface->SetTitleAndTooltip( "SLO", "" );
    mSloChannelInterface->SetChannel( mSloChannel );
    //---------------------------------------------------------------------------------------------------------------------------------
    // DataType (Register OR Single Cycle Data)
    mDatenartInterface.reset( new AnalyzerSettingInterfaceNumberList() );
    mDatenartInterface->SetTitleAndTooltip( "Data Type", "Specify the type of data to be analyzed" );
    mDatenartInterface->AddNumber( 0, "Register Data", "" );
    mDatenartInterface->AddNumber( 1, "Single Cycle Data SAFETY", "" );
    mDatenartInterface->SetNumber( mDatenart );
    //---------------------------------------------------------------------------------------------------------------------------------
    // DataLength CPW
    mDataLengthCPWInterface.reset( new AnalyzerSettingInterfaceInteger() );
    mDataLengthCPWInterface->SetTitleAndTooltip( "CPW - Data length (Bit)", "Specify the CPW (Control Position Word) serial data length in bit" );
    mDataLengthCPWInterface->SetMax( 64 );
    mDataLengthCPWInterface->SetMin( 9 );
    mDataLengthCPWInterface->SetInteger( mDataLengthCPW );
    //---------------------------------------------------------------------------------------------------------------------------------
    // DataLength SPW
    mDataLengthSPWInterface.reset( new AnalyzerSettingInterfaceInteger() );
    mDataLengthSPWInterface->SetTitleAndTooltip( "SPW - Data length (Bit)", "Specify the SPW (Safety Position Word) serial data length in bit" );
    mDataLengthSPWInterface->SetMax( 64 );
    mDataLengthSPWInterface->SetMin( 9 );
    mDataLengthSPWInterface->SetInteger( mDataLengthSPW );
    //---------------------------------------------------------------------------------------------------------------------------------
    AddInterface( mMaChannelInterface.get() );
    AddInterface( mSloChannelInterface.get() );
    AddInterface( mDataLengthCPWInterface.get() );
    AddInterface( mDataLengthSPWInterface.get() );
    AddInterface( mDatenartInterface.get() );

    AddExportOption( 0, "Export as text/csv file" );
    AddExportExtension( 0, "text", "txt" );
    AddExportExtension( 0, "csv", "csv" );

    ClearChannels();
    AddChannel( mMaChannel, "MA", false );
    AddChannel( mSloChannel, "SLO", false );
    //---------------------------------------------------------------------------------------------------------------------------------

}
//---------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------
BISSSafetyAnalyzerSettings::~BISSSafetyAnalyzerSettings()
//---------------------------------------------------------------------------------------------------------------------------------
{
}
//---------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------
bool BISSSafetyAnalyzerSettings::SetSettingsFromInterfaces()
//---------------------------------------------------------------------------------------------------------------------------------
{
    mMaChannel = mMaChannelInterface->GetChannel();
    mSloChannel = mSloChannelInterface->GetChannel();
    mDataLengthCPW = mDataLengthCPWInterface->GetInteger();
    mDataLengthSPW = mDataLengthSPWInterface->GetInteger();
    mDatenart = mDatenartInterface->GetNumber();

    ClearChannels();
    AddChannel( mMaChannel, "MA", true );
    AddChannel( mSloChannel, "SLO", true );

    return true;
}
//---------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------
void BISSSafetyAnalyzerSettings::UpdateInterfacesFromSettings()
//---------------------------------------------------------------------------------------------------------------------------------
{
    mMaChannelInterface->SetChannel( mMaChannel );
    mSloChannelInterface->SetChannel( mSloChannel );
    mDataLengthCPWInterface->SetInteger( mDataLengthCPW );
    mDataLengthSPWInterface->SetInteger( mDataLengthSPW );
    mDatenartInterface->SetNumber( mDatenart );
}
//---------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------
void BISSSafetyAnalyzerSettings::LoadSettings( const char* settings )
//---------------------------------------------------------------------------------------------------------------------------------
{
    SimpleArchive text_archive;
    text_archive.SetString( settings );

    text_archive >> mMaChannel;
    text_archive >> mSloChannel;
    text_archive >> mDataLengthCPW;
    text_archive >> mDataLengthSPW;
    text_archive >> mDatenart;

    ClearChannels();
    AddChannel( mMaChannel, "MA", true );
    AddChannel( mSloChannel, "SLO", true );

    UpdateInterfacesFromSettings();
}
//---------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------
const char* BISSSafetyAnalyzerSettings::SaveSettings()
//---------------------------------------------------------------------------------------------------------------------------------
{
    SimpleArchive text_archive;

    text_archive << mMaChannel;
    text_archive << mSloChannel;
    text_archive << mDataLengthCPW;
    text_archive << mDataLengthSPW;
    text_archive << mDatenart;

    return SetReturnString( text_archive.GetString() );
}
//---------------------------------------------------------------------------------------------------------------------------------
