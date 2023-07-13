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
    bool value;		//A character array in which to store the data with Maximum number of characters to extract.

    unordered_map<string, Customer> customerRecords;  // Hash table to store customer records based on car numbers

public:
    Rent();
    void welcome();
    void fileReader(const char* carFile);
    void data();
    void invoiceAmount();	//Computes
    void invoiceRecord();
    void storeRentDetails();
    void modify();      //Prints the invoice
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

void Rent::data()
{
    cout << "\n\n\t\t\t\tPlease Enter your Name: "; //taking data from the user
    cin >> customer_Name;
    cout << endl;
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
    cout << "Please select a Car No. : ";
    cin >> car_Number;
    cout << "Number of days you wish to rent the car : ";
    cin >> numberOfDays;
    cout << endl;
    }else{
    exit(0);
    fileReader("thanks.txt");
    }

    // Store customer data in the hash table
    Customer customer;
    customer.customer_Name = customer_Name;
    customer.car_model = car_model;
    customer.car_Number = car_Number;

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
    string carNumber;
    cout << "Enter the Car Number of the customer you want to modify: ";
    cin >> carNumber;

    // Check if the customer record exists in the hash table
    if (customerRecords.find(carNumber) != customerRecords.end()) {
        Customer& customer = customerRecords[carNumber];

        // Display the current rental details
        cout << "Current Rental Details:" << endl;
        cout << "Customer Name: " << customer.customer_Name << endl;
        cout << "Car Model: " << customer.car_model << endl;
        cout << "Car Number: " << customer.car_Number << endl;
        cout << "no.of days car rented: "<<numberOfDays<<endl;

        // Prompt the user to enter the modified details
        cout << "Enter the new rental details:" << endl;
        cout << "Customer Name: ";
        cin >> customer.customer_Name;
        cout << "Car Model: ";
        cin >> customer.car_model;
        cout<<"no.of days car rented: ";
        cin>>numberOfDays;

        // Update the rental details in the hash table
        customerRecords[carNumber] = customer;

        cout << "Rental details modified successfully." << endl;
    } else {
        cout << "Customer record not found." << endl;
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


int main()
{
    //Object created for rent class and further member functions are called.
    Rent rent;
    rent.welcome();
    rent.data();
    rent.modify();
    rent.invoiceAmount();
    rent.invoiceRecord();
    rent.storeRentDetails();
    return 0;
}
