template <typename Derived>
class ISystem
{
public:
	static Derived& get()
	{
		static Derived sSingleton;
		return sSingleton;
	}

	ISystem()
	{
		// Initialize dependent systems
		InitDependencies();
		
		PreInit();
		Init();
	}

	ISystem(const ISystem& other) = 0;

	ISystem& operator=(const ISystem& other) = 0;

	~ISystem()
	{
		Destroy();
	}

	// Start up other systems this system depends on
	// Do it by calling SystemInterfaceDerivedClass::get()
	virtual void InitDependencies() = 0;

	virtual void PreInit() = 0;
	virtual void Init() = 0;

	virtual void Destroy() = 0;
};