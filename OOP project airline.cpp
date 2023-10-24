#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Passenger {
protected:
    string firstname;
    string lastname;
    int age;
    double weight;
public:
    void set_age(int u_age);
    void set_weight(double u_weight);
    void set_firstname(string u_firstname);
    void set_lastname(string u_lastname);

    int get_age();
    double get_weight();
    string get_firstname();
    string get_lastname();

    Passenger(string u_firstname, string u_lastname, int u_age, double u_weight) {
        firstname = u_firstname;
        lastname = u_lastname;
        age = u_age;
        weight= u_weight;
    }
    virtual string getSeatClass() = 0;  //This is a virtual function. The derived classes that inherit from the base class must provide their own implementation of this function. 
//The purpose of this function is to retrieve the seat class of a passenger. It returns a string representing the class of the seat, such as "Business" or "Economy".
    virtual double getPrice() = 0; //The purpose of this function is to retrieve the price of a seat. It returns a double value representing the price of the seat in the specific class.
    void printInfo() {
        cout << "Name: " << firstname << " " << lastname << endl;
        cout << "Age: " << age << endl;
        cout << "ID: " << weight<< endl;
        cout << "Class: " << getSeatClass() << endl;
        cout << "Price: " << getPrice() << endl;
    }
};

class BusinessPassenger : public Passenger {  //derived class
public:
    BusinessPassenger(string u_firstname, string u_lastname, int u_age, double u_weight) : Passenger(u_firstname, u_lastname, u_age, u_weight) {}
    string getSeatClass() {
        return "Business";
    }
    double getPrice() {
        return 200;
    }
};

class EconomyPassenger : public Passenger {  //derived clas
public:
    EconomyPassenger(string u_firstname, string u_lastname, int u_age, double u_weight) : Passenger(u_firstname, u_lastname, u_age, u_weight) {}
    string getSeatClass() {
        return "Economy";
    }
    double getPrice() {
        return 100;
    }
};

class Airplane {
private:

    int numBusinessSeats;
    int numEconomySeats;
    Passenger v[numBusinessSeats];
    Passenger w[numEconomySeats];
public:
    void set_numBusinessSeat(int u_numBusinessSeat);

    void set_numEconomySeats(int u_numEconomySeats);

    int get_numBusinessSeats();

    int get_numEconomySeats();

    Airplane(int u_numBusinessSeat, int u_numEconomySeat) {
        numBusinessSeats = u_numBusinessSeat;
        numEconomySeats = u_numEconomySeat;

    }


    Airplane(int b, int e) {
        numBusinessSeats = b;
        numEconomySeats = e;
    }

    int isfull() {        //This function checks if there are available seats in both the business and economy classes are fully occupied.
        int i, j = 0, k = 0;
        for (i = 0; i < numBusinessSeats; i++)
            if (v[i] == 0)
                j == 1;
        for (i = 0; i < numEconomySeats; ++)
            if (w[i] == 0)
                k == 1;
        if (j == 0 && k == 0)
            return 1; //daca tot e full
        else
            return 0;
    }

//This function adds a passenger to the aircraft. It first checks if the aircraft is already full by calling the isfull() function. If the aircraft is full, it returns 0 to indicate that the passenger cannot be added. 
//Otherwise, it checks the seat class of the passenger (p->getSeatClass()) and the availability of seats in the corresponding class. 
//If there are available seats, it decreases the count of available seats (numBusinessSeats or numEconomySeats) and returns 1 to indicate successful addition of the passenger. 
//If no suitable seat is available, it returns 0.
    int addPassenger(Passenger *p) {
        if (isfull() == 1) {
            return 0;
        }
        if (p->getSeatClass() == "Business" && numBusinessSeats > 0) {
            numBusinessSeats--;
            return 1;
        } else if (p->getSeatClass() == "Economy" && numEconomySeats > 0) {
            numEconomySeats--;
            return 1;
        } else
            return 0;
    }

//This function removes a passenger from the aircraft based on the provided seat number. It checks the seat class of the passenger (p->getSeatClass()) and if the seat number is less than or equal to numBusinessSeats, 
//it indicates that the passenger was in the business class, and therefore, it increments the count of available business seats (numBusinessSeats++).
//Otherwise, it assumes the passenger was in the economy class and increments the count of available economy seats (numEconomySeats++).
    void removePassenger(int seatNumber, Passenger *p) {
        if (p->getSeatClass() == "Business" && seatNumber <= numBusinessSeats)
            numBusinessSeats++;
        else
            numEconomySeats++;

    }

//This function searches for a passenger by their full name. It first iterates over the v array to search for a matching name in the business class passengers. 
//If a match is found, it sets k = 1 to indicate that a match was found and prints the seat class and seat number of the passenger. If no match is found in the business class, 
//it then iterates over the w array to search for a matching name in the economy class passengers.
//If a match is found, it sets k = 1 and prints the seat class and seat number. If no match is found in either class, no output is produced.
    void searchPassengerByName(string name) {
        int i, k = 0;
        for (int i = 0; i < numBusinessSeats; i++) {
            string fullName = v[i].get_firstname() + " " + v[i].get_lastname();
            if (fullName == name) {
                k = 1;
                cout << "Business" << i << endl;
            }
        }
        if (k == 0) {
            for (int i = 0; i < numEconomySeats; i++) {
                string fullName = w[i].get_firstname() + " " + w[i].get_lastname();
                if (fullName == name) {
                    k = 1;
                    cout << "Economy" << i << endl;
                }
            }
        }
    }
}
int main()
{
    Airplane plane(100, 200);
    int x=1;
    while (x==1) {
        cout << "Select an option: " << endl;
        cout << "1. Add passenger" << endl;
        cout << "2. Buy seat" << endl;
        cout << "3. Search passenger by name" << endl;
        cout << "4. Remove booking" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter first name: ";
            string firstname;
            cin >> firstname;
            cout << "Enter last name: ";
            string lastname;
            cin >> lastname;
            cout << "Enter age: ";
            int age;
            cin >> age;
            cout << "Enter weight: ";
            double weight;
            cin >> weight;
            cout << "Enter class (1 for Business, 2 for Economy): ";
            int classChoice;
            cin >> classChoice;
            Passenger* p;
            if (classChoice == 1) {
                p = &BusinessPassenger(firstname, lastname, age, weight);
            } else {
                p = &EconomyPassenger(firstname, lastname, age, weight);
            }
            if (plane.addPassenger(p)) {
                cout << "Passenger added successfully!" << endl;
            } else {
                cout << "Plane is full, could not add passenger." << endl;
            }
        } else if (choice == 2) {
            Passenger* p;
            double price = p->getPrice();
            if (price > 0) {
                cout << "Seat price: " << price << endl;
                cout << "Enter amount paid by customer: ";
                double amountPaid;
                cin >> amountPaid;
                if (amountPaid < price) {
                    cout << "Insufficient amount paid. Suggesting lower priced seats." << endl;
                    if (p->getSeatClass() == "Business") {
                        for (int i = 0; i <plane.numEconomySeats; i++)
                            if(plane.w[i]==0 && price< amountPaid)
                            {cout << "Suggested seat: " << i  << endl;
                                break;}
                    }
                }

            } else
                cout << "Payment accepted. Seat booked." << endl;}

        else if(choice == 3){
            Passenger* p;
            cout << "Enter name: ";
            string name;
            cin >> name;
            plane.searchPassengerByName(name);}

        else if(choice == 4){
            Passenger* p;
            cout<<"Enter your seat number:";
            int seatNumber;
            cin>>seatNumber;
            plane.removePassenger(seatNumber);}

        else if(choice==5){
            x=0;
        }

    }}}
