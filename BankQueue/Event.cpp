#include "Event.h"

int Event::getStart() const { return starttime; }

int Event::getDuration() const { return duration; }

bool Event::isArrival() const { return is_arrival_event; };

void Event::setStart(int s) { starttime = s; };

void Event::setDuration(int d) { duration = d; };

Event::Event() : starttime(0), duration(0), is_arrival_event(true) {
   //Default ctor
}
Event::Event(int s, int d, bool arrival) : starttime(s), duration(d), is_arrival_event(arrival) {
   //Paramterized ctor
}

bool Event::operator<(const Event& other_event) const {
   if (starttime == other_event.starttime) {
      return (is_arrival_event > other_event.is_arrival_event); //This allows arrival events to be held in higher priority if two events have the same start time.
   }
   else {
      return (starttime < other_event.getStart());
   }
}// End operator<

bool Event::operator==(const Event& other_event) const {
   return (starttime == other_event.getStart());
}// End operator==

bool Event::operator>(const Event& other_event) const {
   return !(*this < other_event); //Deletegate to less than operator
}// End operator>

std::ostream& operator<<(std::ostream& os, const Event& ev) {
   os << "Start: " << ev.starttime << " Duration: " << ev.duration << " Arrival: " << std::boolalpha << ev.is_arrival_event;
   return os;
}
