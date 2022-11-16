#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib> 
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

void removeDupWord(string str, Customer& customer, int i)
{
    string word = "";
    customer.idle = (i > 0) ? 3 : 0;
    int counter = 1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
          
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
            }
            counter++;
            word = "";
        }
        else {
            word = word + str[i];
        }
    }

   if(customer.preferred_Payment_Method == "cash"){
        customer.exact_or_not_cash = (word);
   }else{
        customer.preferred_Payment_Method = (word);
   }
}
 

void display_customer_info(Customer customer, int i){
            
            cout << "Costumer #" << i+1 << ":" << endl;
            cout << "No of cart                   : "<< customer.no_of_Cart_Items << endl;
            cout << "Preferred packaging          : "<< customer.preferred_Packaging << endl;
            cout << "No. of package ";
            if(customer.preferred_Packaging == "bags"){
            cout                <<"bags          : ";
            } else{
            cout                <<"boxes         : ";
            } 
            cout << customer.number_of_boxes  << endl;
            cout << "Payment method               : " << customer.preferred_Payment_Method;
            if(customer.exact_or_not_cash == "e"){
                cout << "(Exact)"; 
            }else if (customer.exact_or_not_cash == "ne")
            {
                cout << "(Not Exact)"; 
            }
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
}


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
        removeDupWord(lowercases(user_input), order_list[i], i);
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


