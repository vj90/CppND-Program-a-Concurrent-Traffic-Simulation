#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue {
 public:
  void send(T&& msg);
  T receive();

 private:
  std::mutex _msg_queue_mutex;
  std::condition_variable _cond;
  std::deque<T> _queue;
};

class TrafficLight : public TrafficObject {
 public:
  enum TrafficLightPhase { red, green };
  // constructor / desctructor
  TrafficLight();
  // getters / setters

  // typical behaviour methods
  void waitForGreen();
  void simulate();
  TrafficLightPhase getCurrentPhase();

 private:
  // typical behaviour methods
  void cycleThroughPhases();

  MessageQueue<TrafficLightPhase> _traffic_light_phase_queue;
  std::condition_variable _condition;
  std::mutex _mutex;
  TrafficLightPhase _currentPhase;
};

#endif