#include "queue.hh"

// Implement the member functions of Queue here
#include <iostream>

Queue::Queue(unsigned int cycle) : cycle_(cycle) {}

Queue::~Queue() {
    while (first_ != nullptr) {
        Vehicle* temp = first_;
        first_ = first_->next;
        delete temp;
    }
}

void Queue::enqueue(const std::string &reg) {
    if (!is_green_) {
        Vehicle* newVehicle = new Vehicle{reg, nullptr};
        if (last_ != nullptr) {
            last_->next = newVehicle;
            last_ = newVehicle;
        } else {
            first_ = newVehicle;
            last_ = newVehicle;
        }
    } else {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
    }
}

void Queue::dequeue() {
    if (is_green_ && first_ != nullptr) {
        std::cout << first_->reg_num << " ";
        Vehicle* temp = first_;
        first_ = first_->next;
        delete temp;
    }
}

void Queue::switch_light() {
    if (is_green_) {
        is_green_ = false;
        if (first_ != nullptr) {
            std::cout << "RED: Vehicle(s) ";
            Vehicle* current = first_;
            while (current != nullptr) {
                std::cout << current->reg_num << " ";
                current = current->next;
            }
            std::cout << "waiting in traffic lights" << std::endl;
        } else {
            std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
        }
    } else {
        is_green_ = true;
        if (first_ != nullptr) {
            std::cout << "GREEN: Vehicle(s) ";
            for (unsigned int i = 0; i < cycle_ && first_ != nullptr; ++i) {
                dequeue();
            }
            std::cout << "can go on" << std::endl;
        } else {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        }
        is_green_ = false;
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
    std::cout << "Current cycle is " << cycle_ << ", i.e. at most " << cycle_ << " vehicles can pass during the same green period" << std::endl;
}

void Queue::print() const {
    if (!is_green_ && first_ != nullptr) {
        std::cout << "RED: Vehicle(s) ";
        Vehicle* current = first_;
        while (current != nullptr) {
            std::cout << current->reg_num << " ";
            current = current->next;
        }
        std::cout << "waiting in traffic lights" << std::endl;
    } else if (!is_green_ && first_ == nullptr) {
        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
    } else {
        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
    }
}




