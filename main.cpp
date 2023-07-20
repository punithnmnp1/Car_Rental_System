#include <iostream>  //input/output
#include <fstream>		//file
#include <unistd.h>   //sleep
#include <iomanip>  //setting width
#include <ctime>	//time
#include <unordered_map>  //hash table

using namespace std;

// customer class
class Customer
{
public:
    string customer_Name;
    string address;
    int car_model;
    string car_Number;
};

//Rent class
// inherited class from customer class
class Rent : public Customer
{
private:
    // additional integer variables defined
    int numberOfDays;
    int rent_Fee;
    char str[200];
    bool value;
    bool ch;	//A character array in which to store the data with Maximum number of characters to extract.

    unordered_map<string, Customer> customerRecords; // Hash table to store customer records based on car numbers

    unordered_map<string, string> carIndex;
public:
    Rent();
    void welcome();
    void fileReader(const char* carFile);
    void data();
    void invoiceAmount();	//Computes
    void invoiceRecord();   //Prints the invoice
    void storeRentDetails();
    void modify();
    void addToIndex(const string& car_Number, const string& customerKey);
    void removeFromIndex(const string& car_Number);
    void displayIndex();
    void storingRentDetails();
    bool isCarNumberUnique(const string& car_Number);
    void cancelBooking();
};

Rent::Rent()
{
    numberOfDays = 0;
    rent_Fee = 0;
}

void Rent::welcome()
{
    ifstream inputFile("welcome.txt"); //displaying welcome ASCII image text on output screen fn1353
    if (!inputFile) {
        cout << "Cannot open input file.\n";
    }
    char str[1000];
    while (inputFile) {
        inputFile.getline(str, 1000);  // delim defaults to '\n' cp
        if (inputFile)
            cout << str << endl;
    }
    inputFile.close();
    sleep(1);
    cout << "\nStarting the program please wait....." << endl;
    sleep(1);
    cout << "\nloading up files....." << endl;
    sleep(1); //function which waits for (n) seconds
    system("CLS"); //cleares screen
}

void Rent::fileReader(const char* carFile)
{
    ifstream inputFile;
    inputFile.open(carFile); //displaying details of model A
    if (!inputFile) {
        cout << "Error in printing file. File not found!" << endl;
    }
    while (inputFile) {
        inputFile.getline(str, 200);
        if (inputFile)
            cout << str << endl;
    }
}

void Rent::addToIndex(const string& car_Number, const string& customerKey)
{
    carIndex[car_Number] = customerKey;
}

void Rent::removeFromIndex(const string& car_Number)
{
    carIndex.erase(car_Number);
}
void Rent::displayIndex()
{
    cout << "Car Index:" << endl;
    for (const auto& pair : carIndex) {
        cout << "Car Number: " << pair.first << ", Customer Key: " << pair.second << endl;
    }
    cout << endl;
}

bool Rent::isCarNumberUnique(const string& car_Number) {
    ifstream inputFile("rental_details.txt");
    string line;
    while (getline(inputFile, line)) {
        if (line.find(car_Number) != string::npos) {
            return false;  // Car number already exists in the file
        }
    }
    return true;  // Car number is unique
}

void Rent::data()
{

    do {
        //giving user a choice to select among three different models
        cout << "\t\t\t\t__________________________________________________________________" << endl;
        cout << "\t\t\t\tChoose a Car from the options below. \n ";
        cout << "\t\t\t\tChoose a number corresponding to the car you want to Select." << endl;
        cout << "\t\t\t\t__________________________________________________________________" << endl;
        cout << "\t\t\t\t1. Toyota 2021." << endl;
        cout << "\t\t\t\t2. Hyundai 2019." << endl;
        cout << "\t\t\t\t3. Ford 2020." << endl;
        cout << "\t\t\t\t4. Maruthi Suzuki 2022." << endl;
        cout << "\t\t\t\t5. Benz 2023." << endl;
        cout << "\t\t\t\t6. Lamborgini 2021." << endl;
        cout << endl;
        cout << "\t\t\t\t__________________________________________________________________" << endl;
        cout << "\n\t\t\t\tChoose: ";
        cin >> car_model;
        cout << endl;

        switch (car_model) {
        case 1:
            system("CLS");
            cout << "You have chosen Toyota model 2021" << endl;
            fileReader("Toyota.txt");
            sleep(2);
            break;
        case 2:
            system("CLS");
            cout << "You have chosen Hyundai model 2019" << endl;
            fileReader("Hyundai.txt");
            sleep(2);
            break;
        case 3:
            system("CLS");
            cout << "You have chosen Ford model 2020" << endl;
            fileReader("Ford.txt");
            sleep(2);
            break;
        case 4:
            system("CLS");
            cout << "You have chosen Maruthi Suzuki model 2022" << endl;
            fileReader("Maruthi_Suzuki.txt");
            sleep(2);
            break;
        case 5:
            system("CLS");
            cout << "You have chosen Benz model 2023" << endl;
            fileReader("Benz.txt");
            sleep(2);
            break;
        case 6:
            system("CLS");
            cout << "You have chosen Lamborgini model 2021" << endl;
            fileReader("Lamborgini.txt");
            sleep(2);
            break;
        default:
            cout << "Invalid Car Model. Please try again!" << endl;
            fileReader("thanks.txt");
            exit(0);
        }
    } while (car_model < 1 && car_model > 6);

    cout << "________________________________________________________________________________________________" << endl;
    cout << "Please provide the following information:" << endl;

    //getting data from user related to rental service
    cout<< "Are you sure u want to rent this car, click 1  for yes and click 0 for no:";
    cin>>value;
    if(value==1){
    cout << "Please Enter your Name: "; //taking data from the user
    cin >> customer_Name;
    cout << "enter your address:";
    cin >> address;
    bool uniqueCarNumber = false;
    do {
        cout << "Please enter a Car No.: ";
        cin >> car_Number;

        if (isCarNumberUnique(car_Number)) {
            uniqueCarNumber = true;
        } else {
            cout << "Car Number is already assigned. Please enter a unique Car No." << endl;
        }
    } while (!uniqueCarNumber);
    cout << "Number of days you wish to rent the car : ";
    cin >> numberOfDays;
    cout << endl;
    }else{
    system("CLS");
     data();

    }

    // Store customer data in the hash table
    Customer customer;
    customer.customer_Name = customer_Name;
    customer.address=address;
    customer.car_model = car_model;
    customer.car_Number = car_Number;
    string customerKey = to_string(rand());  // Generate a random key for the customer record
    customerRecords[customerKey] = customer;
    addToIndex(car_Number, customerKey);

    customerRecords[car_Number] = customer;
}

void Rent::invoiceAmount()
{
    sleep(1);
    system("CLS");
    cout << "Calculating rent. Please wait......" << endl;
    sleep(2);
    if (car_model == 1)
        rent_Fee = numberOfDays * 150;
    if (car_model == 2)
        rent_Fee = numberOfDays * 160;
    if (car_model == 3)
        rent_Fee = numberOfDays * 175;
    if (car_model == 4)
        rent_Fee = numberOfDays * 190;
    if (car_model == 5)
        rent_Fee = numberOfDays * 200;
    if (car_model == 6)
        rent_Fee = numberOfDays * 225;
}
void Rent::modify()
{
    system("CLS");
    string car_Number;
    cout<<"do you wish to modify (if yes enter 1 else enter 0):";
    cin>>ch;
    if(ch==1){
    cout << "Enter the Car Number of the customer you want to modify: ";
    cin >> car_Number;

    // Check if the customer record exists in the hash table
   if (carIndex.find(car_Number) != carIndex.end()) {
        string customerKey = carIndex[car_Number];
        Customer& customer = customerRecords[customerKey];

        // Display the current rental details
        cout << "Current Rental Details:" << endl;
        cout << "Customer Name: " << customer.customer_Name << endl;
        cout << "Customer address :"<< customer.address<<endl;
        cout << "Car Number: " << customer.car_Number << endl;
        cout << "no.of days car rented: "<<numberOfDays<<endl;

        // Prompt the user to enter the modified details
        cout << "Enter the new rental details:" << endl;
        cout << "Customer Name: ";
        cin >> customer.customer_Name;
        cout << "Customer's address: ";
        cin >>customer.address;
        cout<<"no.of days car rented: ";
        cin>>numberOfDays;

        // Update the rental details in the hash table
        customerRecords[car_Number] = customer;

        cout << "Rental details modified successfully." << endl;
    } else {
        cout << "Customer record not found." << endl;
    }
}
else{
 return;
 }
}

void Rent::invoiceRecord()
{
    time_t now = time(0);		//getting local time
    char* date = ctime(&now); 	//Converting to a string
    cout << setw(80) << date << endl;
    cout << "\n\t\t                       CAR RENTAL - CUSTOMER INVOICE                  " << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	| Invoice No.  " << "					|" << setw(10) << "#1001" << " |" << endl;  //can be automatically generated
    cout << "\t\t	| Customer Name " << "				|" << setw(10) << customer_Name << " |" << endl;
    cout << "\t\t	| Car Model  " << "					|" << setw(10) << car_model << " |" << endl;     //car model
    cout << "\t\t	| Car No.  " << "					|" << setw(10) << car_Number << " |" << endl;
    cout << "\t\t	| Number of days  " << "				|" << setw(10) << numberOfDays << " |" << endl;
    cout << "\t\t	| Rental Amount  " << "				|" << setw(10) << rent_Fee << " |" << endl;
    cout << "\t\t	| Caution Money  " << "				|" << setw(10) << "0" << " |" << endl;      //Can be calculated
    cout << "\t\t	| Advanced  " << "					|" << setw(10) << "0" << " |" << endl;		//Can be calculated
    cout << "\t\t	|___________________________________________________________|" << endl;
    cout << "\t\t	| Total Rental Amount    " << "			|" << setw(6) << "R " << rent_Fee << " |" << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t	 NOTE: This is a computer-generated invoice. " << endl;
    cout << "\t\t	       It does not require an authorized signature." << endl;
    cout << "\t\t	***********************************************************" << endl;
    cout << "\t\t	You are advised to pay up the amount before the due date." << endl;
    cout << "\t\t	Otherwise, a penalty fee will be applied" << endl;
    cout << "\t\t	***********************************************************" << endl;

    system("PAUSE");
    system("CLS");

}
void Rent::storeRentDetails()
{
    ofstream outputFile;
    char fname[15];
    time_t now = time(0);		//getting local time
    char* date = ctime(&now);
    cout << " \t\t   enter the filename which you need to store the details of this rent:";
    cin>>fname;
    outputFile.open(fname,ios::app); // open the file in append mode

    // Check if the file was opened successfully
    if (!outputFile) {
        cout << "Error in opening file for writing." << endl;
        return;
    }

    // Write rent details to the
    outputFile << "Rent details generated at:"<< date << endl;
    outputFile << "Customer Name: " << customer_Name << endl;
    outputFile << "Customer address:"<< address <<endl;
    outputFile << "Car Model: " << car_model << endl;
    outputFile << "Car Number: " << car_Number << endl;
    outputFile << "Number of Days: " << numberOfDays << endl;
    outputFile << "Rent Fee: " << rent_Fee << endl;
    outputFile << endl;

    // Close the file
    outputFile.close();

    cout << "Rent details have been stored successfully." << endl;
    fileReader("thanks.txt");
}
 void Rent::storingRentDetails()
{
    ofstream outputFile;
    time_t now = time(0);		//getting local time
    char* date = ctime(&now);
    outputFile.open("rental_details.txt", ios::app); // open the file in append mode

    // Check if the file was opened successfully
    if (!outputFile) {
        cout << "Error in opening file for writing." << endl;
        return;
    }

    // Write rent details to the file
    outputFile << "bill generated at:"<< date << endl;
    outputFile << "Customer Name: " << customer_Name << endl;
    outputFile << "Address: " << address << endl;
    outputFile << "Car Model: " << car_model << endl;
    outputFile << "Car Number: " << car_Number << endl;
    outputFile << "Number of Days: " << numberOfDays << endl;
    outputFile << "Rent Fee: " << rent_Fee << endl;
    outputFile << endl;

    // Close the file
    outputFile.close();


}
void Rent::cancelBooking()
{
    string car_Number;
    cout << "Enter the Car Number of the customer you want to cancel the booking for: ";
    cin >> car_Number;

    // Check if the customer record exists in the hash table
    if (carIndex.find(car_Number) != carIndex.end()) {
        string customerKey = carIndex[car_Number];
        Customer& customer = customerRecords[customerKey];

        // Display the current rental details
        cout << "Current Rental Details:" << endl;
        cout << "Customer Name: " << customer.customer_Name << endl;
        cout << "Customer address: " << customer.address << endl;
        cout << "Car Number: " << customer.car_Number << endl;
        cout << "Number of days car rented: " << numberOfDays << endl;

        // Prompt the user for confirmation
        char choice;
        cout << "Are you sure you want to cancel this booking? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            // Remove the rental details from the hash table and the carIndex
            customerRecords.erase(customerKey);
            removeFromIndex(car_Number);

            // Update the rental_details.txt file to indicate the booking is canceled
            ifstream inputFile("rental_details.txt");
            ofstream outputFile("temp_rental_details.txt");

            string line;
            while (getline(inputFile, line)) {
                if (line.find(car_Number) != string::npos) {
                    // Add a marker/message to indicate the booking is canceled
                    outputFile << line << " [Booking Canceled]" << endl;
                } else {
                    outputFile << line << endl;
                }
            }

            inputFile.close();
            outputFile.close();

            // Remove the old rental_details.txt and rename temp_rental_details.txt to rental_details.txt
            remove("rental_details.txt");
            rename("temp_rental_details.txt", "rental_details.txt");

            cout << "Booking for Car Number " << car_Number << " has been canceled." << endl;
            exit(0); // Terminate the program after canceling the booking
        } else {
            cout << "Booking cancellation has been aborted." << endl;
        }
    } else {
        cout << "Customer record not found." << endl;
    }
}


int main()
{
    //Object created for rent class and further member functions are called.
    Rent rent;
    rent.welcome();
    rent.data();
    rent.modify();
    rent.invoiceAmount();
    rent.invoiceRecord();
    rent.displayIndex();
    rent.storeRentDetails();
    rent.storingRentDetails();
    cout << "\nDo you want to cancel a car rental booking? (Y/N): ";
    char cancelChoice;
    cin >> cancelChoice;

    if (cancelChoice == 'Y' || cancelChoice == 'y') {
        rent.cancelBooking();
    }
    return 0;
}
