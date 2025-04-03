#include "IOC_Contaner.h"

// инициализируем ненулевым числом
int IOCContainer::s_nextTypeId = 115094801;

enum ProcessorType
{
	x86,
	x64
};

class IProcessor
{
public:
	virtual ~IProcessor() {}
	virtual string GetProcessorInfo() = 0;
	static string types[2];
};

string IProcessor::types[] = { "x86", "x64" };

class Computer
{
	shared_ptr<IProcessor> processor;

public:
	void GetProcessor(IOCContainer& serviceLocator)
	{
		processor =  serviceLocator.GetObject<IProcessor>();
	}

	void Configure()
	{
		cout << processor->GetProcessorInfo() << endl;
	}
};

class IntelProcessor : public IProcessor
{
	string Version;
	ProcessorType Type;
	double Speed;

public:
	IntelProcessor(double speed, ProcessorType type, string version)
	{
		Version = version;
		Type = type;
		Speed = speed;
	}

	string GetProcessorInfo()
	{
		return "Intel processor: " + string(" ") + Version + string(" ") + to_string(Speed) + string(" ") + types[Type];
	}
};

class AMDProcessor : public IProcessor
{
	string Version;
	ProcessorType Type;
	double Speed;

public:
	AMDProcessor(double speed, ProcessorType type, string version)
	{
		Version = version;
		Type = type;
		Speed = speed;
	}

	string GetProcessorInfo()
	{
		return "AMD processor: " + string(" ") + Version + string(" ") + to_string(Speed) + string(" ") + types[Type];
	}
};


int main(int argc, const char* argv[])
{
	IOCContainer injector;
	Computer computer;

	injector.RegisterInstance<IProcessor>(make_shared<IntelProcessor>(4.6e9, ProcessorType::x64, "Intel123"));
	computer.GetProcessor(injector);
	computer.Configure();

	injector.RegisterInstance<IProcessor>(make_shared<AMDProcessor>(4.2e9, ProcessorType::x64, "AMD550"));
	computer.GetProcessor(injector);
	computer.Configure();

	return 0;
}