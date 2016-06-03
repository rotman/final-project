#ifndef ISensorNetworkPlatform
#define ISensorNetworkPlatform

template <class T>
class ISensorNetworkPlatform {
	public:
		virtual ~ISensorNetworkPlatform() {}
		virtual void init(T&, *byte, *byte) = 0;
		virtual Message readSensorData(T&) = 0;
		virtual void sendMessage(T&) = 0;
		virtual Message receiveMessage(T&) = 0;
}

#endif