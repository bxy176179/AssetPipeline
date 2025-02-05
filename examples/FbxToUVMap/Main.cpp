#include "Framework/IConsumer.h"
#include "Framework/Processor.h"
#include "FbxProducer.h"
#include "Utilities/PerformanceProfiler.h"
#include "UVMapConsumer.hpp"

int main(int argc, char** argv)
{
	// argv[0] : exe name
	// argv[1] : input file path
	// argv[2] : output file path
	if (argc != 3)
	{
		return 1;
	}

	using namespace cdtools;

	PerformanceProfiler profiler("AssetPipeline");

	const char* pInputFilePath = argv[1];
	const char* pOutputFilePath = argv[2];
	FbxProducer producer(pInputFilePath);

	UVMapConsumer consumer(pOutputFilePath);
	consumer.SetUVMapUnitSize(512, 512);
	consumer.SetUVMapMaxSize(2048, 2048);
	Processor processor(&producer, &consumer);
	processor.Run();

	return 0;
}