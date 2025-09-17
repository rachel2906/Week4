#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Schedule
class Schedule {
private:
    string vehicleID;      // ID of the vehicle for this schedule
    string departureTime;  // Scheduled departure time
    string arrivalTime;    // Scheduled arrival time
    string status;         // Current status
public:
    Schedule(string v = "", string d = "", string a = "", string s = "On Time") {
        vehicleID = v;
        departureTime = d;
        arrivalTime = a;
        status = s;
    }

    void setStatus(string s) { status = s; }             // Update status
    string getStatus() { return status; }                // Get current status

    string getVehicleID() { return vehicleID; }          // Return vehicle ID
    string getDepartureTime() { return departureTime; }  // Return departure time
    string getArrivalTime() { return arrivalTime; }      // Return arrival time

    void displayInfo() {                                 // Display schedule details
        cout << "Vehicle: " << vehicleID<<endl;
        cout << "Departure: " << departureTime<<endl;
        cout << "Arrival: " << arrivalTime<<endl;
        cout << "Status: " << status << endl;
    }
};

// Vehicle
class Vehicle {
protected:
    string vehicleID;     // Unique identifier for the vehicle
    string vehicleType;   // Vehicle type: bus, train, etc.
    int capacity;         // Maximum number of passengers
    string route;         // Route name or ID
    string status;        // Vehicle status: available, delayed, etc.
public:
    Vehicle(string id = "", string type = "", int cap = 0, string r = "", string s = "Available") {
        vehicleID = id;
        vehicleType = type;
        capacity = cap;
        route = r;
        status = s;
    }

    virtual double calculateTravelTime(double baseTime) { // Calculate travel time (default)
        return baseTime;
    }

    string getID() { return vehicleID; }                 // Get vehicle ID
    string getType() { return vehicleType; }             // Get vehicle type
    string getRoute() { return route; }                  // Get route info
    string getStatus() { return status; }                // Get vehicle status

    virtual void displayInfo() {                         // Display vehicle details
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Type: " << vehicleType << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Route: " << route << endl;
        cout << "Status: " << status << endl;
    }
};

// ExpressBus (inherits Vehicle)
class ExpressBus : public Vehicle {
private:
    double speed;   // Average speed (km/h)
    int stops;      // Number of stops 
public:
    ExpressBus(string id = "", int cap = 0, string r = "", string s = "Available",
               double sp = 80, int st = 3)
        : Vehicle(id, "Express Bus", cap, r, s) {
        speed = sp;
        stops = st;
    }

    double calculateTravelTime(double baseTime) override { // Override: express saves 20% time
        return baseTime * 0.8;
    }

    void displayInfo() override {                          // Display express bus details
        Vehicle::displayInfo();
        cout << " Express Speed: " << speed
             << " km/h | Stops: " << stops << endl;
    }
};

// Passenger 
class Passenger {
private:
    string name;                      // Passenger name
    string ID;                        // Passenger ID
    vector<string> bookedTickets;     // List of booked vehicle IDs
public:
    Passenger(string n = "", string id = "") {
        name = n;
        ID = id;
    }

    void bookRide(string vehicleID) { // Add booking for a vehicle
        bookedTickets.push_back(vehicleID);
        cout << name << " booked ride on " << vehicleID << endl;
    }

    void cancelRide(string vehicleID) { // Cancel booking for a vehicle
        for (auto it = bookedTickets.begin(); it != bookedTickets.end(); ++it) {
            if (*it == vehicleID) {
                bookedTickets.erase(it);
                cout << name << " canceled ride on " << vehicleID << endl;
                return;
            }
        }
        cout << "No booking found for " << vehicleID << endl;
    }

    void displayInfo() {               // Display passenger info
        cout << "Passenger: " << name << " | ID: " << ID << endl;
        cout << "Booked Tickets: ";
        for (auto &t : bookedTickets) cout << t << " ";
        cout << endl;
    }
};

// Station
class Station {
private:
    string name;                   // Station name
    string location;               // Station location
    string type;                   // Station type: bus or train
    vector<Schedule> schedules;    // List of schedules at this station
public:
    Station(string n = "", string l = "", string t = "") {
        name = n;
        location = l;
        type = t;
    }

    void addSchedule(Schedule s) { schedules.push_back(s); } // Add new schedule
    void removeSchedule(string vehicleID) {                  // Remove schedule by vehicle ID
        for (auto it = schedules.begin(); it != schedules.end(); ++it) {
            if (it->getVehicleID() == vehicleID) {
                schedules.erase(it);
                break;
            }
        }
    }

    void displayInfo() {                                     // Display station details
        cout << "Station: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Type: " << type << endl;
        for (auto &s : schedules) {
            s.displayInfo();
        }
    }
};

// Main
int main() {
    // Create station
    Station st("Central Station", "Downtown", "Bus");

    // Create vehicles
    Vehicle v1("B001", "Bus", 40, "Route A");
    ExpressBus eb1("E100", 30, "Route B");

    // Add schedules
    Schedule sc1("B001", "08:00", "10:00");
    Schedule sc2("E100", "09:00", "10:30");
    st.addSchedule(sc1);
    st.addSchedule(sc2);

    // Passenger actions
    Passenger p1("Quang Truong", "P403");
    p1.bookRide("B102");
    p1.bookRide("B206");

    // Display info
    st.displayInfo();
    cout << endl;
    v1.displayInfo();
    eb1.displayInfo();
    cout << endl;
    p1.displayInfo();

    // Test overridden travel time
    double baseTime = 60; // 60 minutes
    cout << "Normal bus travel time: " << v1.calculateTravelTime(baseTime) << " minutes" << endl;
    cout << "Express bus travel time: " << eb1.calculateTravelTime(baseTime) << " minutes" << endl;

    return 0;
}
