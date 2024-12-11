class SoundProcessor {
public:
	SoundProcessor(int argc, char** argv);
	void run();
private:
	static void RegisterConverters();
	int argc;
	char** argv;
};