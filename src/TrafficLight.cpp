#include "TrafficLight.h"
#include <iostream>
#include <random>

/* Implementation of class "MessageQueue" */

/*
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and
_condition.wait()
    // to wait for and receive new messages and pull them from the queue using
move semantics.
    // The received object should then be returned by the receive function.
}

template <typename T>
void MessageQueue<T>::send(T &&msg) {
  std::lock_guard<std::mutex> lck(_msg_queue_mutex);
  _queue.push_back(std::move(msg));
  _cond.notify_one();
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight() { _currentPhase = TrafficLightPhase::red; }

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an
infinite while-loop
    // runs and repeatedly calls the receive function on the message queue.
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLight::TrafficLightPhase TrafficLight::getCurrentPhase() {
  return _currentPhase;
}

void TrafficLight::simulate() {
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
  auto start_time = std::chrono::high_resolution_clock::now();
  while (true) {
    srand(time(NULL));
    auto rand_time = 2 * (rand() % 1000);
    std::cout << "Random time = " << rand_time;
    const auto threshold = std::chrono::milliseconds(4000 + rand_time);
    const auto current_time = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - start_time) > threshold) {
      start_time = current_time;
      _currentPhase = _currentPhase == TrafficLightPhase::red
                          ? TrafficLightPhase::green
                          : TrafficLightPhase::red;
      _traffic_light_phase_queue.send(std::move(_currentPhase));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
