#include <bits/stdc++.h>
using namespace std;
const string CurrentDate="01/01/2023";

const int Till_i_th_month_Days[12] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
int count_Leap_Year_Days(int d[]){
    int years = d[2];
    if (d[1] <= 2)
        years--;
    return ((years / 4) - (years / 100) + (years / 400));
}

int Total_days(int date1[], int date2[]){
    long int dayCount1 = (date1[2] * 365);
    dayCount1 += Till_i_th_month_Days[date1[1]];
    dayCount1 += date1[0];
    dayCount1 += count_Leap_Year_Days(date1);
    long int dayCount2 = (date2[2] * 365);
    dayCount2 += Till_i_th_month_Days[date2[1]];
    dayCount2 += date2[0];
    dayCount2 += count_Leap_Year_Days(date2);
    return (abs(dayCount1 - dayCount2));
}

int convertInInteger(string str, int start, int end){
    int temp = 0;
    for (int i = start; i <= end; i++){
        temp = temp * 10 + (str[i] - '0');
    }
    return temp;
}

class Traveller{
private:
    string Traveller_id;

public:
    string Name;
    string Id;
    list<vector<string>> list_of_tickets;

    void setTravellerId(string Traveller_id){
        this->Traveller_id = Traveller_id;
    }
    string getTravellerId(){
        return this->Traveller_id;
    }
    void setName(string Name){
        this->Name = Name;
    }
    string getName(){
        return this->Name;
    }
    void setId(string Id){
        this->Id = Id;
    }

    string getId(){
        return this->Id;
    }
    bool verifyId(string id){
        if (this->Id == id)
            return true;
        else
            return false;
    }
    void get_ticket(){
        list<vector<string>>::iterator it;
        for (it = this->list_of_tickets.begin(); it != this->list_of_tickets.end(); it++){
            for (int i = 0; i < 5; i++){
                cout << (*it)[i] << " ";
            }
            cout << endl;
        }
    }
    void updateId(string Id){
        this->Id = Id;
    }
};

class Ticket : public Traveller{
private:
    int price;

public:
    string source_station;
    string Destination_station;
    string Date; /*Date has this type as 23/04/2024 it means day = 23 , month = 04 , year = 2024 */
    string Traveller_name;

    void bookTicket(string Name, string source_station, string Destination_station, string Date){
        this->Traveller_name = Name;
        this->source_station = source_station;
        this->Destination_station = Destination_station;
        this->Date = Date;
        vector<string> v = {Name, source_station, Destination_station, Date};
        this->list_of_tickets.push_back(v);
        this->setPrice(CurrentDate,Date);
    }
    void cancelTicket(string Name, string source_station, string Destination_station, string Date){
        list<vector<string>>::iterator it;
        for (it = this->list_of_tickets.begin(); it != this->list_of_tickets.end(); it++){
            if (((*it)[0] == Name) & ((*it)[1]==source_station) &  ((*it)[2]==Destination_station) & ((*it)[3] == Date)){
                it = this->list_of_tickets.erase(it);
            }
        }
    }
    void updateTicket(string Name, string DateIs, string DateChangeTo, string Destination_station){
        list<vector<string>>::iterator it;
        for (it = this->list_of_tickets.begin(); it != this->list_of_tickets.end(); it++){
            if (((*it)[0] == Name) & ((*it)[3] == DateIs)){
                (*it)[3] = DateChangeTo;
                (*it)[2] = Destination_station;
                this->setPrice(CurrentDate,DateChangeTo);
                (*it)[4]=this->getPrice();
            }
        }
    }
    void setPrice(string CurrentDate, string TravelDate){
        int date1[] = {convertInInteger(CurrentDate, 0, 1), convertInInteger(CurrentDate, 3, 4), convertInInteger(CurrentDate, 6, 9)};
        int date2[] = {convertInInteger(TravelDate, 0, 1), convertInInteger(TravelDate, 3, 4), convertInInteger(TravelDate, 6, 9)};

        this->price = Total_days(date1, date2);

        list<vector<string>>::iterator it = this->list_of_tickets.end();
        it--;
        (*it).push_back("$"+ to_string(this->price));
    }
    int getPrice(){
        return this->price; /* Return the price of last booked Ticket */
    }
};

class Astronaut : public Ticket{
private:
    int Experience; /* Experience in numbers of years*/

public:
    void setExperience(int Experience){
        this->Experience = Experience;
    }
    int getExprience(){
        return this->Experience;
    }
};

class Passanger : public Ticket{
private:
    int Validity; /* Validity period in years */
public:
Passanger(string Name, string Id,int Validity){
        this->Name=Name;
        this->Id=Id;
        this->Validity=Validity;
}
    
    int getValidity(){
        return this->Validity;
    }
};

class Commander : public Ticket {
private:
    int Authority;

public:
    int Experience;
    string LicenseId;

    void setAuthority(int Authority){
        this->Authority = Authority;
    }
    int getAuthority(){
        return this->Authority;
    }
    void setExperience(int Experience){
        this->Experience = Experience;
    }
    int getExprience(){
        return this->Experience;
    }
    void setLicenseId(string LicenseId){
        this->LicenseId = LicenseId;
    }
    string getLicenseId(){
        return this->LicenseId;
    }
};

class SpaceTravel{
private:
    list<Passanger> list_Of_travellers; /*here in this list max number of passanger will be 8 because two travellers are Astronaut and  Commander */
    Astronaut STS_Astronaut;
    Commander STS_Commander;

public:
    bool Is_Exist_STS_Astronaut = false; /*Initially no astronaut is selected for STS_Astronaut*/
    bool Is_Exist_STS_Commander = false; /*Initially no commander is selected for STS_Commander*/
    void addTraveller(Passanger Passanger){
        /* here I use max number of passanger 8 because 2 will be Astronaut and Commander so then total traveller max will be 10 */
        if(this->No_Of_Passangers() <=8) this->list_Of_travellers.push_back(Passanger);
        else cout << "The Space Travel System is Full . You are not allowed." << endl;
    }
    int No_Of_Passangers(){
        return this->list_Of_travellers.size();
    }
    void listAllTravellers() {
        cout << "Astronaut : " << STS_Astronaut.getName() << endl; /*Print the name of selected atsronaut for STS_Astronaut*/
        cout << "Commander : " << STS_Commander.getName() << endl; /*Print the name of selected commander for STS_Commander*/

        std::list<Passanger>::iterator it = this->list_Of_travellers.begin();

        while (it != this->list_Of_travellers.end()){
            cout << "Passanger : " << (*it).getName() << endl; /*Print the name of Passangers*/
            it++;
        }
    }
    void setAstronaut(Astronaut astronaut){
        this->STS_Astronaut = astronaut;
        this->Is_Exist_STS_Astronaut = true;
    }

    void setCommander(Commander commander){
        this->STS_Commander = commander;
        this->Is_Exist_STS_Commander = true;
    }
    void upadteAstronaut(Astronaut newAstronaut){
        this->STS_Astronaut = newAstronaut;
        this->Is_Exist_STS_Astronaut = true;
    }
    void updateCommander(Commander newCommander){
        this->STS_Commander = newCommander;
        this->Is_Exist_STS_Commander = true;
    }
};

class Planet{
public:
    string Name;
    int Position_x; /*Position are relatively in Kelometers*/
    int Position_y; /*Position are relatively in Kelometers*/
    int Position_z; /*Position are relatively in Kelometers*/

    Planet(string Name, int Position_x, int Position_y, int Position_z){
        this->Name = Name;
        this->Position_x = Position_x;
        this->Position_y = Position_y;
        this->Position_z = Position_z;
    }
    vector<int> getCordinate(){
        vector<int> cordinate;
        cordinate.push_back(this->Position_x);
        cordinate.push_back(this->Position_y);
        cordinate.push_back(this->Position_z);
        return cordinate;
    }
};

long dist_between_two_station(vector<int> x, vector<int> y) {/*Using Euclidian formula for calculate distance*/
    long z = (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]) + (x[2] - y[2]) * (x[2] - y[2]);
    long distance = sqrt(z);
    return distance;
}

void Is_Flight_Take_Over(SpaceTravel spaceTravel){
    if ((!spaceTravel.Is_Exist_STS_Astronaut) & (!spaceTravel.Is_Exist_STS_Commander)){
        cout << "Sorry ! this flight can't take over due to unavailability of STS_Astronaut and STS_Commander" << endl;
    }
    else if (!spaceTravel.Is_Exist_STS_Commander){
        cout << "Sorry ! this flight can't take over due to unavailability of STS_Commander" << endl;
    }
    else if (!spaceTravel.Is_Exist_STS_Commander){
        cout << "Sorry ! this flight can't take over due to unavailability of STS_Astronaut" << endl;
    }
    else    cout << "Welcome to Everyone ! The Space Travel is prepared to arrive at your destination on schedule and with a nice travel." << endl;
}
int main()
{ /* Suppose Universe has these three planets Earth, Moon and Mars */
    Planet Planet1("Earth", 260, 340, 360);
    Planet Planet2("Moon", 60, 140, 260);
    Planet Planet3("Mars", 160, 240, 160);

    cout << "The distance between " << Planet1.Name << " " << "and " << Planet2.Name << " is :";
    cout << dist_between_two_station(Planet1.getCordinate(), Planet2.getCordinate()) << " Km" << endl;
    cout << endl;

    
    /* Current Date or Today's Date -> 1 Jan, 2023; Current Date ->  "01/01/2023" */
    /* if A Passanger Create an Id today, then his/her Validity till 31 Dec, 2032 -> "31/12/2032" of 10 years */
    /* All these passanger has created their Id today(on current date)*/

   
    
    Passanger p1=Passanger("Passanger_1","PR001",10);
    p1.setTravellerId("pr001");
  

    Passanger p2=Passanger("Passanger_2","PR002",10);
    p2.setTravellerId("pr002");
  
    Passanger p3=Passanger("Passanger_2","PR003",10);
    p3.setTravellerId("pr003");
   
    Passanger p4=Passanger("Passanger_4","PR004",10);
    p4.setTravellerId("pr004");

    Passanger p5=Passanger("Passanger_5","PR005",10);
    p5.setTravellerId("pr005");

    Passanger p6=Passanger("Passanger_6","PR006",10);
    p6.setTravellerId("pr006");

    Passanger p7=Passanger("Passanger_7","PR007",10);
    p7.setTravellerId("pr007");

    Passanger p8=Passanger("Passanger_8","PR008",10);
    p8.setTravellerId("pr008");

    Passanger p9=Passanger("Passanger_9","PR009",10);
    p9.setTravellerId("pr009");

    Passanger p10=Passanger("Passanger_10","PR010",10);
    p10.setTravellerId("pr010");

    Passanger p11=Passanger("Passanger_11","PR011",10);
    p11.setTravellerId("pr011");
   

    Astronaut A1, A2;
    A1.setName("Astronaut_1");
    A1.setId("AT001");
    A1.setTravellerId("at001");
    A1.setExperience(12); /* Astronaut has infinite Validity*/

    A2.setName("Astronaut_2");
    A2.setId("AT002");
    A2.setTravellerId("at002");
    A2.setExperience(15); /* Astronaut has infinite Validity*/

    Commander C1, C2;
    C1.setName("Commander_1");
    C1.setId("CR001");
    C1.setTravellerId("cr001");
    C1.setAuthority(60);
    C1.setExperience(12);
    C1.setLicenseId("COM001");

    C2.setName("Commander_2");
    C2.setId("CR002");
    C2.setTravellerId("cr002");
    C2.setAuthority(60);
    C2.setExperience(18);
    C2.setLicenseId("COM002");

    list<Passanger> set_Passangers;

    SpaceTravel FirstSTS, SecondSTS, ThirdSTS, FourthSTS;

    /*FIRST SPACE TRAVEL will be launched on the date 02/03/2025*/

    string FlightDateForFirstSTS = "02/03/2025";

    p1.bookTicket(p1.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
    set_Passangers.push_back(p1);

    p2.bookTicket(p2.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
    set_Passangers.push_back(p2);

    p3.bookTicket(p3.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
    set_Passangers.push_back(p3);

    p4.bookTicket(p4.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
    set_Passangers.push_back(p4);

    p5.bookTicket(p5.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
    set_Passangers.push_back(p5);

    C1.bookTicket(C1.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
    A1.bookTicket(A1.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);

    if (set_Passangers.size() > 2){
        list<Passanger>::iterator pr = set_Passangers.begin();

        while (pr != set_Passangers.end()){
            FirstSTS.addTraveller(*pr);
            pr++;
        }
        FirstSTS.setCommander(C1);
        FirstSTS.setAstronaut(A1);

        FirstSTS.listAllTravellers();
        cout << endl;
        Is_Flight_Take_Over(FirstSTS);
        cout << endl;
    }
    else    cout << "Sorry ! There weren't enough passengers. Thus, this flight (FirstSTS) cannot take off with fewer passengers." << endl;

    set_Passangers.clear();

    /*SECOND SPACE TRAVEL will be on the date 21/04/2025 */

    string FlightDateForSecondSTS = "21/04/2025";

    p5.bookTicket(p5.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    set_Passangers.push_back(p5);

    p6.bookTicket(p6.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    set_Passangers.push_back(p6);

    p7.bookTicket(p7.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    set_Passangers.push_back(p7);

    p8.bookTicket(p8.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    set_Passangers.push_back(p8);

    p9.bookTicket(p9.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    set_Passangers.push_back(p9);

    p10.bookTicket(p10.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    set_Passangers.push_back(p10);

    C2.bookTicket(C2.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
    A2.bookTicket(A2.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);

    if (set_Passangers.size() > 2){
        list<Passanger>::iterator pr = set_Passangers.begin();
        while (pr != set_Passangers.end()){
            SecondSTS.addTraveller(*pr);
            pr++;
        }

        SecondSTS.setCommander(C2);
        SecondSTS.setAstronaut(A2);

        SecondSTS.listAllTravellers();
        cout << endl;
        Is_Flight_Take_Over(SecondSTS);
        cout << endl;

        /* second SpaceTravel's Astronaut is updated due to unabilibity of first Astronaut */

        SecondSTS.upadteAstronaut(A1);

        SecondSTS.listAllTravellers();
        cout << endl;
    }
    else    cout << "Sorry ! There weren't enough passengers. Thus, this flight (SecondSTS) cannot take off with fewer passengers." << endl;
    set_Passangers.clear();
    /*THIRD SPACE TRAVEL will be on the date 30/11/2026 */

    string FlightDateForThirdSTS = "30/11/2026";

    p1.updateTicket(p1.getName(), FlightDateForFirstSTS, FlightDateForThirdSTS, Planet3.Name); /*/shifted his journey from FirstSTS to ThirdSTS*/
    set_Passangers.push_back(p1);

    p2.bookTicket(p2.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);
    set_Passangers.push_back(p2);

    p3.bookTicket(p3.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);
    set_Passangers.push_back(p3);

    p4.bookTicket(p4.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);
    set_Passangers.push_back(p4);

    p10.bookTicket(p10.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);
    set_Passangers.push_back(p10);

    p5.bookTicket(p5.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);
    set_Passangers.push_back(p5);

    A2.bookTicket(A2.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);

    if (set_Passangers.size() > 2){

        list<Passanger>::iterator pr = set_Passangers.begin();
        while (pr != set_Passangers.end()){
            ThirdSTS.addTraveller(*pr);
            pr++;
        }
        ThirdSTS.setAstronaut(A2);

        ThirdSTS.listAllTravellers();
        cout << endl;
        Is_Flight_Take_Over(ThirdSTS);
        cout << endl;

        cout << "the list of ticket booked by Passanger p5 :" << endl;
        p5.get_ticket();
        cout << endl;

        cout << "after cancelling the second ticket" << endl;
        cout << endl;

        p5.cancelTicket(p5.getName(), Planet2.Name,Planet3.Name, FlightDateForSecondSTS);

        p5.get_ticket();
        cout << endl;

        cout << "print the last booked ticket prize by passanger 5 : $";
        cout << p5.getPrice() << endl; /* Return the price of last booked ticket*/
    }
    else    cout << "Sorry ! There weren't enough passengers. Thus, this flight (ThirdSTS) cannot take off with fewer passengers." << endl;
    
    set_Passangers.clear();

    /*Fourth Space Travel will be launched on the date 02/03/2027 */

    string FlightDateForFourthSTS = "02/03/2027";
    p11.bookTicket(p11.getName(), Planet3.Name, Planet1.Name, FlightDateForFourthSTS);
    set_Passangers.push_back(p11);

    p10.bookTicket(p10.getName(), Planet3.Name, Planet1.Name, FlightDateForFourthSTS);
    set_Passangers.push_back(p10);

    C2.bookTicket(C2.getName(), Planet3.Name, Planet1.Name, FlightDateForFourthSTS);
    A2.bookTicket(A2.getName(), Planet3.Name, Planet1.Name, FlightDateForFourthSTS);

    if (set_Passangers.size() > 2){
        list<Passanger>::iterator pr = set_Passangers.begin();
        while (pr != set_Passangers.end()){
            FourthSTS.addTraveller(*pr);
            pr++;
        }

        FourthSTS.setCommander(C2);
        FourthSTS.setAstronaut(A2);

        FourthSTS.listAllTravellers();
        cout << endl;
        Is_Flight_Take_Over(FourthSTS);
        cout << endl;
    }
    else    cout << "Sorry ! There weren't enough passengers. Thus, this flight (FourthSTS) cannot take off with fewer passengers." << endl;
    
    set_Passangers.clear();
    cout << endl;

    cout << "Do you want to register for make a happy journey" << endl;
    cout << "Enter 1 for Agree otherwise Enter 0" << endl;

    int Agree;
    cin >> Agree;
    cout << Agree << endl;

    if (Agree){
        cout << "Hey ! welcome to our universe." << endl;
        cout << "First You have to make your own Id as A Passanger" << endl;
        cout << "So, Please Enter Your Name : " << endl;

        string name;
        cin >> name;
        Passanger p=Passanger(name,"PR012",10);
        p.setTravellerId("pr012");
       

        cout << "Thank you, " << p.getName() << endl;
        cout << "Your Id is : " << p.getId() << endl;
        cout << "Your Traveller Id is : " << p.getTravellerId() << endl;

        cout << "Do You want to book any Ticket for travelling ?" << endl;
        cout << "Enter 1 for Yes otherwise Enter 0" << endl;

        int yes;
        cin >> yes;
        while (yes){
            cout << "currently , You have to allow to travel by the Following Space Travel System" << endl;
            cout << 1 << " FirstSTS from " << Planet1.Name << " to " << Planet2.Name << " on " << FlightDateForFirstSTS << endl;
            cout << 2 << " SecondSTS from " << Planet2.Name << " to " << Planet3.Name << " on " << FlightDateForSecondSTS << endl;
            cout << 3 << " ThirdSTS from " << Planet1.Name << " to " << Planet3.Name << " on " << FlightDateForThirdSTS << endl;
            cout << 4 << " FourthSTS from " << Planet3.Name << " to " << Planet1.Name << " on " << FlightDateForFourthSTS << endl;
            cout << "If you want to book ticket for any of these STS, please enter the number which is given in front of the above Space Travel System details" << endl;
            string flightdate;
            string source,destination;
            int num;
            cin >> num;
            while (!((num >= 1) & (num <= 4))){
                cout << "please enter a valid number" << endl;
                cin >> num;
            }
            cout << "Hey ! Your Ticket is booked successfully" << endl;
            if (num == 1){
                p.bookTicket(p.getName(), Planet1.Name, Planet2.Name, FlightDateForFirstSTS);
                set_Passangers.push_back(p);
                FirstSTS.addTraveller(p);
                Is_Flight_Take_Over(FirstSTS);
                flightdate = FlightDateForFirstSTS;
                source=Planet1.Name;
                destination=Planet2.Name;
            }
            else if (num == 2){
                p.bookTicket(p.getName(), Planet2.Name, Planet3.Name, FlightDateForSecondSTS);
                set_Passangers.push_back(p);
                SecondSTS.addTraveller(p);
                Is_Flight_Take_Over(SecondSTS);
                flightdate = FlightDateForSecondSTS;
                source=Planet2.Name;
                destination=Planet3.Name;
            }
            else if (num == 3){
                p.bookTicket(p.getName(), Planet1.Name, Planet3.Name, FlightDateForThirdSTS);
                set_Passangers.push_back(p);
                ThirdSTS.addTraveller(p);
                source=Planet1.Name;
                destination=Planet3.Name;

                flightdate = FlightDateForThirdSTS;
                ThirdSTS.setCommander(C2);
                Is_Flight_Take_Over(ThirdSTS);
            }
            else{
                p.bookTicket(p.getName(), Planet3.Name, Planet1.Name, FlightDateForFourthSTS);
                set_Passangers.push_back(p);
                FourthSTS.addTraveller(p);
                flightdate = FlightDateForSecondSTS;
                source=Planet3.Name;
                destination=Planet1.Name;

                FourthSTS.setCommander(C2);
                FourthSTS.setAstronaut(A2);

                Is_Flight_Take_Over(FourthSTS);
            }
            cout << "Do you want to book return ticket also for this flight ?" << endl;
            cout << "Enter 1 for yes otherwise 0" << endl;

            int returnTicket;
            cin >> returnTicket;
            while (!((returnTicket == 0) | (returnTicket == 1))){
                cout << "Please Enter a valid key" << endl;
                cin >> returnTicket;
            }
            if(returnTicket){
            list<vector<string>>::iterator it = p.list_of_tickets.end();
            it--;
            (*it)[4].append(" + RETURN_TICKET");
            }

            cout << "For get booked Ticket detail call the function getTicket() by Enter 1" << endl;

            int want;
            cin >> want;
            while (want != 1){
                cout << "Please Enter 1 to get your ticket details" << endl;
                cin >> want;
            }
            p.get_ticket();
            cout << "Your Last booked Ticket Prize is : $" << p.getPrice() << endl;
            cout << endl;
            cout << "If you want to cancel your recently booked ticket press 1 else 0" << endl;

            int cancel;
            cin >> cancel;
            while (!((cancel == 0) | (cancel == 1))){
                cout << "Please Enter a valid key" << endl;
                cin >> cancel;
            }
            if (cancel == 1){
                cout << "Your Ticket which is booked for  "<< destination << " from "<< source<< " on " << flightdate << " is cancelled." << endl;
                p.cancelTicket(p.getName(), source, destination, flightdate);
            }
            else    cout << "Thank you for your Response , wish you Happy Journey!" << endl;
            cout << "Do you want to book more ticket if want then Please Enter 1 else 0" << endl;
            cin >> yes ;    
            while (!((yes == 0) | (yes == 1))){
                cout << "Please Enter a valid key" << endl;
                cin >> yes;
            }        
        }
    }
    else    cout << "Thank you for your response. You can enter 1 by rerun the code " << endl;
}