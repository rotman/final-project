#ifndef LAYER
#define LAYER

#include <Arduino.h>
#include <ICommunicationable.h>
#include <LinkedList.h>

template <class T>
//in green house project,'T' stands for Message

class Layer {
	public:
		virtual ~Layer() {}
		virtual void initLayer(int) = 0;
		virtual void analyze() = 0;
		virtual void decodeMessage(T&) = 0;
		virtual T& prepareMessage(T&, int) = 0;
		Layer() {
			communicationArray = LinkedList<ICommunicationable*>();	
		}
		void addCommunication(ICommunicationable* type) {
			communicationArray.add(type);
		}
		void removeCommunication(int index) {
			for (int i = 0; i < communicationArray.size(); i++) {
				if (i == index) {
					communicationArray.remove(i);
					break;
				}
			}
		}
		
		LinkedList<ICommunicationable*>& getCommunicationArray() {
			return communicationArray;
		}

		int getLoopTime(){
			return this->loopTime;
		}
		void setLoopTime(int time) {
			this->loopTime = time;
		}
	protected:
		LinkedList<ICommunicationable*> communicationArray;
		int loopTime;
};

#endif
