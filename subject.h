#pragma once
#include <algorithm>
#include <vector>
#include "observer.h"

using namespace std;

class Subject {
private:
    vector<Observer*> observers;
public:
    void registerObserver(Observer* observer) {
        this->observers.push_back(observer);
    }

    void unregisterObserver(Observer* observer) {
        this->observers.erase(find(this->observers.begin(), this->observers.end(), observer));
    }

    void notify() {
        for (auto observer : this->observers) {
            observer->update();
        }
    }
};