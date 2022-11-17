#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

double total_laneqeueu;
struct Customer
{
    double no_of_Cart_Items;
    string preferred_Packaging;
    double number_of_boxes;
    string preferred_Payment_Method;
    string exact_or_not_cash;
    double idle;
};

void parsecustomerdata(string str, Customer& customer, int i)
{
    customer.idle = (i > 0) ? 3 : 0;
    stringstream indivstring(str);
    string word;
    int counter = 1;
    while(indivstring >> word){
         switch (counter)
            {
                case 1:
                    customer.no_of_Cart_Items = (stod(word));
                    break;
                case 2:
                    customer.preferred_Packaging = (word);
                    break;
                case 3:
                    customer.number_of_boxes = (stod(word));
                    break;
                case 4:
                    customer.preferred_Payment_Method = (word);
                    break;
                case 5:
                    customer.exact_or_not_cash = (word);
                    break;
            }
            counter++;
    }
}

void display_customer_info(Customer customer, int i){
            
            cout << "Costumer #" << i+1 << ":" << endl;
            cout << "No of cart                   : "<< customer.no_of_Cart_Items << endl;
            cout << "Preferred packaging          : "<< customer.preferred_Packaging << endl;
            cout << "No. of package ";
            (customer.preferred_Packaging == "bags") ? cout <<  "bags          : ": cout <<  "boxes         : ";
            cout << customer.number_of_boxes  << endl;
            cout << "Payment method               : " << customer.preferred_Payment_Method;
            if (customer.preferred_Payment_Method == "cash") (customer.exact_or_not_cash == "e") ? cout <<  "(Exact)" : cout <<  "(Not Exact)";

}


void customers_qeueu(Customer customer){
    double decarting_time =customer.no_of_Cart_Items * 0.5;
    double scanning_time  =customer.no_of_Cart_Items * 0.5;
    double packing_time = (customer.preferred_Packaging == "bag") ? (((customer.no_of_Cart_Items) * 0.5) + ((customer.number_of_boxes) * 5)) : (((customer.no_of_Cart_Items) * 0.5) + ((customer.number_of_boxes) * 10));
    double paying_time = (customer.preferred_Payment_Method == "cash" ) ? customer.exact_or_not_cash == "e" ? 15 : 20 : 15;
    double greceipt_printing_time = ((customer.no_of_Cart_Items) * 0.3) + 2.0;
    double idle = customer.idle;
    double qeueuoverall = (decarting_time + scanning_time ) + packing_time + paying_time + greceipt_printing_time + idle;

    cout << "Total De-Carting Time        : " << decarting_time
     << "\nTotal Scanning Time          : "<< scanning_time
     << "\nTotal Packing Time           : " << packing_time
     << "\nTotal Paying Time            : " << paying_time
     << "\nIdle Time                    : "<< idle
     << "\nTotal Receipt Printing Time  : "<< greceipt_printing_time
     << "\nTotal Customer-Queue Time    : "<< qeueuoverall;
     total_laneqeueu += qeueuoverall;
}

string lowercases(string strlwr){

    string lower;
    for (int i = 0; i < strlwr.length(); i++) {
        lower += char(tolower(strlwr[i]));
    }
    return lower;
} ////https://www.tutorialspoint.com/cplusplus-program-to-check-if-input-is-an-integer-or-a-string#:~:text=Apply%20isdigit()%20function%20that,the%20value%20of%20type%20int


int main(){
    ifstream file ("file.in");
    string user_input;
    getline(file, user_input);
    int no_of_customer = stoi(user_input);
    Customer order_list[no_of_customer];
   
    cout << "No. of Customers:" << no_of_customer;
    cout <<    "\n=================================================\n";
    int i = 0;
    while(getline(file, user_input)){
        parsecustomerdata(lowercases(user_input), order_list[i], i);
        display_customer_info(order_list[i], i);
        cout << "\n------------------------------------------------\n";
        customers_qeueu(order_list[i]);
        if (no_of_customer - 1 != i) cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++\n";
        i++;
    }
    cout << "\n====================================================\n";
    cout << "Total Lane Queue Time        :" << total_laneqeueu;
    return 0;
}
