#ifndef ISENSORNETWORKPLATFORM_H
#define ISENSORNETWORKPLATFORM_H

template <class T, class E>
class ISensorNetworkPlatform {
	public:
		virtual ~ISensorNetworkPlatform() {}
		virtual void init(T&, byte*, byte*) = 0;
		virtual E readSensorData() = 0;
		virtual void sendMessage(T&, E&) = 0;
		virtual E receiveMessage(T&) = 0;
		virtual void actuate() = 0;
		virtual void onSensorFail() = 0;
};

#endif