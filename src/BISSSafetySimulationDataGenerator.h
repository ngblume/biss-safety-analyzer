#ifndef BISSSAFETY_SIMULATION_DATA_GENERATOR
#define BISSSAFETY_SIMULATION_DATA_GENERATOR

#include <AnalyzerHelpers.h>
#include <SimulationChannelDescriptor.h>
#include <string>
class BISSSafetyAnalyzerSettings;

class BISSSafetySimulationDataGenerator
{
  public:
    BISSSafetySimulationDataGenerator();
    ~BISSSafetySimulationDataGenerator();

    void Initialize( U32 simulation_sample_rate, BISSSafetyAnalyzerSettings* settings );
    U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

  protected:
    BISSSafetyAnalyzerSettings* mSettings;
    U32 mSimulationSampleRateHz;

  protected:
    void CreateBiSSSafetyFrame();
    void vMaSlo( BitState Cdm, BitState Cds );

    ClockGenerator mClockGenerator;

    SimulationChannelDescriptorGroup mBiSSSafetySimulationChannels;
    SimulationChannelDescriptor* mMa;
    SimulationChannelDescriptor* mSlo;

    SimulationChannelDescriptor mSerialSimulationData;
};
#endif // BISSSAFETY_SIMULATION_DATA_GENERATOR