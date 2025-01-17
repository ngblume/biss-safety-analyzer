#include "BISSSafetySimulationDataGenerator.h"
#include "BISSSafetyAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

BISSSafetySimulationDataGenerator::BISSSafetySimulationDataGenerator()
{
}

BISSSafetySimulationDataGenerator::~BISSSafetySimulationDataGenerator()
{
}


//-------------------------------------------------------------------------------------------------
void BISSSafetySimulationDataGenerator::Initialize( U32 simulation_sample_rate, BISSSafetyAnalyzerSettings* settings )
//-------------------------------------------------------------------------------------------------
{
    mSimulationSampleRateHz = simulation_sample_rate;
    mSettings = settings;

    mClockGenerator.Init( 5000000, simulation_sample_rate );

    mMa = mBiSSSafetySimulationChannels.Add( settings->mMaChannel, mSimulationSampleRateHz, BIT_HIGH );
    mSlo = mBiSSSafetySimulationChannels.Add( settings->mSloChannel, mSimulationSampleRateHz, BIT_HIGH );

    mBiSSSafetySimulationChannels.AdvanceAll( mClockGenerator.AdvanceByHalfPeriod( 10.0 ) ); // insert 10 bit-periods of idle
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
U32 BISSSafetySimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate,
                                                         SimulationChannelDescriptor** simulation_channel )
//-------------------------------------------------------------------------------------------------
{
    U64 adjusted_largest_sample_requested =
        AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

    while( mMa->GetCurrentSampleNumber() < adjusted_largest_sample_requested )
    {
        CreateBiSSSafetyFrame();
    }

    *simulation_channel = mBiSSSafetySimulationChannels.GetArray();
    return mBiSSSafetySimulationChannels.GetCount();
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void BISSSafetySimulationDataGenerator::vMaSlo( BitState Cdm, BitState Cds )
//-------------------------------------------------------------------------------------------------
{
    mBiSSSafetySimulationChannels.AdvanceAll( mClockGenerator.AdvanceByHalfPeriod( 100.0 ) );

    unsigned long ulDataLengthCPW;
    ulDataLengthCPW = mSettings->mDataLengthCPW;
    unsigned long ulDataLengthSPW;
    ulDataLengthSPW = mSettings->mDataLengthSPW;
    unsigned long ulMaEdges;
    ulMaEdges = ( 32 + ( 2 * ulDataLengthCPW ) );


    for( U32 i = 0; i < ulMaEdges; i++ )
    {
        mMa->Transition();
        mBiSSSafetySimulationChannels.AdvanceAll( mClockGenerator.AdvanceByHalfPeriod( 1.0 ) );

        if( i == 2 )
            mSlo->Transition();
        if( i == 4 )
            mSlo->Transition();

        if( Cds == BIT_LOW )
        {
            if( i == 6 )
                mSlo->Transition();
            if( i == 8 )
                mSlo->Transition();
        }

        if( i == 10 )
            mSlo->Transition();
        if( i == 12 )
            mSlo->Transition();

        if( i == 14 )
            mSlo->Transition();
        if( i == 16 )
            mSlo->Transition();

        if( i == 24 )
            mSlo->Transition();
        if( i == ( ( 2 * ulDataLengthCPW ) + 8 ) )
            mSlo->Transition();

        if( i == ( ( 2 * ulDataLengthCPW ) + 16 ) )
            mSlo->Transition();
        if( i == ( ( 2 * ulDataLengthCPW ) + 20 ) )
            mSlo->Transition();

        if( i == ( ( 2 * ulDataLengthCPW ) + 24 ) )
            mSlo->Transition();
    }

    if( Cdm == BIT_HIGH )
    {
        mMa->TransitionIfNeeded( BIT_HIGH );
        mMa->Advance( 90.0 );
        mSlo->Advance( 85.0 );
        mSlo->TransitionIfNeeded( BIT_HIGH );
        mSlo->Advance( 5.0 );
    }
    else
    {
        mMa->TransitionIfNeeded( BIT_LOW );
        mMa->Advance( 90.0 );
        mMa->TransitionIfNeeded( BIT_HIGH );
        mSlo->Advance( 85.0 );
        mSlo->TransitionIfNeeded( BIT_HIGH );
        mSlo->Advance( 5.0 );
    }
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void BISSSafetySimulationDataGenerator::CreateBiSSSafetyFrame()
//-------------------------------------------------------------------------------------------------
{
    // START,CTS
    vMaSlo( BIT_LOW, BIT_LOW );
    vMaSlo( BIT_LOW, BIT_HIGH );

    // ID
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );

    // ADRESSE
    vMaSlo( BIT_LOW, BIT_LOW );
    vMaSlo( BIT_LOW, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );

    // CRC
    vMaSlo( BIT_LOW, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_LOW, BIT_LOW );
    vMaSlo( BIT_LOW, BIT_LOW );

    // RW
    vMaSlo( BIT_LOW, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_HIGH );

    // START
    vMaSlo( BIT_LOW, BIT_LOW );

    // NULL
    vMaSlo( BIT_HIGH, BIT_HIGH );

    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_HIGH );
    vMaSlo( BIT_HIGH, BIT_HIGH );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_HIGH );
    vMaSlo( BIT_HIGH, BIT_HIGH );

    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_HIGH );
    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );

    vMaSlo( BIT_HIGH, BIT_LOW );
    vMaSlo( BIT_HIGH, BIT_LOW );

    mBiSSSafetySimulationChannels.AdvanceAll( 1500.0 );
}
//-------------------------------------------------------------------------------------------------
