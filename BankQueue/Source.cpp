#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include "ArrayQueue.h"
#include "ArrayPriorityQueue.h"
#include "Event.h"

using namespace std;

//FUNCTION DECLARATIONS
Event processstring(std::string& myline);

void processfile(ArrayPriorityQueue<Event>& pq, ifstream& file, int& number_of_customers);
void processArrival(ArrayPriorityQueue<Event>& eventListPQueue, ArrayQueue<Event>& bankQueue, bool& tellerAvailable, int currenttime, int& waittime_sum);
void processDeparture(ArrayPriorityQueue<Event>& eventListPQueue, ArrayQueue<Event>& bankQueue, bool& tellerAvailable, int currenttime, int& waittime_sum);


int main() {
   //Initialize necessary containers and variables
   ifstream myfile("inputfile.txt");
   ArrayQueue<Event> bankQueue;
   ArrayPriorityQueue<Event> eventListPQueue;
   bool tellerAvailable = true;
   int currentTime = 0;


   //Initialize Eventlist and stats variables
   int number_of_customers{ 0 };
   processfile(eventListPQueue, myfile, number_of_customers); //INITIALIZE EVENTLISTpQUEUE WITH THE ARRIVAL EVENTS IN FILE
   int waittime_sum = 0;

   //Event Loop, start simulation
   cout << "Simulation Begins" << endl;
   while (!eventListPQueue.isEmpty()) {
      currentTime = eventListPQueue.peekFront().getStart();

      if (eventListPQueue.peekFront().isArrival()) {
         cout << "Processing an arrival event at time:\t" << currentTime << endl;
         processArrival(eventListPQueue, bankQueue, tellerAvailable, currentTime, waittime_sum);
      }
      else {
         cout << "Processing a departure event at time:\t" << currentTime << endl;
         processDeparture(eventListPQueue, bankQueue, tellerAvailable, currentTime, waittime_sum);
      }
   }
   cout << "Simulation Ends" << endl;

   cout << "\nFinal Statistics: " << endl;
   cout << "\tTotal number of people processed: " << number_of_customers << endl;
   cout << "\tAverage amount of time spent waiting: " << float(waittime_sum) / float(number_of_customers) << endl;
   return 0;
}

Event processstring(std::string& myline) {
   int space_spot = myline.find(' ');//locate delimiter
   int starttime = stoi(myline.substr(0, space_spot));//First number is arrival time
   int duration = stoi(myline.substr(space_spot, myline.length()));//Second number is departure
   return Event{ starttime, duration, true };//Everything in the original file is an arrival event
} // end processstring

void processfile(ArrayPriorityQueue<Event>& pq, ifstream& file, int& number_of_customers) {
   string line{};
   if (file.is_open())
   {
      while (getline(file, line))
      {
         //get line of file and process it as string
         pq.enqueue(processstring(line)); //Adds events to priority queue
         ++number_of_customers;
      }
      file.close();
   }
   else cout << "Unable to open file";
}// End Process File

void processArrival(ArrayPriorityQueue<Event>& eventListPQueue, ArrayQueue<Event>& bankQueue, bool& tellerAvailable, int currenttime, int& waittime_sum) {
   Event next_event = eventListPQueue.peekFront(); //Grab top event
   eventListPQueue.dequeue(); //Remove top event

   if (bankQueue.isEmpty() && tellerAvailable) {

      int depaturetime = next_event.getDuration() + currenttime; //time of departure for this customer
      int waittime = depaturetime - next_event.getStart() - next_event.getDuration(); //calulating statistics
      waittime_sum += waittime; //Storing statistics

      eventListPQueue.enqueue(Event{ depaturetime, 0,false });//Make and add a departure event
      tellerAvailable = false; // Mark the teller as unavailable
   }
   else {
      bankQueue.enqueue(next_event); //Teller is not available-> add to line
   }
}// End Process Arrival

void processDeparture(ArrayPriorityQueue<Event>& eventListPQueue, ArrayQueue<Event>& bankQueue, bool& tellerAvailable, int currenttime, int& waittime_sum) {
   eventListPQueue.dequeue(); //Remove departure event
   if (!bankQueue.isEmpty()) {
      //process next customer in line
      Event next_event = bankQueue.peekFront(); //Save customer
      bankQueue.dequeue(); //Remove customer from line

      int depaturetime = next_event.getDuration() + currenttime; //time of depature for next customer
      int waittime = depaturetime - next_event.getStart() - next_event.getDuration();//Calculating statistics
      waittime_sum += waittime; //Storing stats

      eventListPQueue.enqueue(Event{ depaturetime, 0,false });//Make and add a departure event
      //tellerAvailable = false; // Mark the teller as unavailable
   }
   else {
      tellerAvailable = true; //The line was empty so the teller isn't helping anyone
   }
}// End Process Depature
