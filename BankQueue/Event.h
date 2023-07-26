#pragma once

#include <fstream>
#include <string>
class Event {

private:

   int starttime;
   int duration;
   bool is_arrival_event;

public:

   int getStart() const;
   int getDuration() const;
   bool isArrival() const;
   void setStart(int);
   void setDuration(int);

   Event();
   Event(int, int, bool);
   bool operator<(const Event& other_event) const;
   bool operator==(const Event& other_event) const;
   bool operator>(const Event& other_event) const;
   friend std::ostream& operator<<(std::ostream& os, const Event& ev);

};

