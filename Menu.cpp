#include "Menu.h"
#include "Input_Validation_Extended.h"
#include <fstream>
#include <unistd.h>

void Menu::populateMenu(std::vector<MenuItem>& entireMenu)
{
    //put some default values in our Menu
    const int numItems = 7;
    MenuItem Item1;
    MenuItem Item2;
    MenuItem Item3;
    MenuItem Item4;
    MenuItem Item5;
    MenuItem Item6;
    MenuItem Item7;

    entireMenu.push_back(Item1); //add to the end of list the Item1
    entireMenu.push_back(Item2); //add to the end of list the Item2
    entireMenu.push_back(Item3); //add to the end of list the Item3
    entireMenu.push_back(Item4); //add to the end of list the Item4
    entireMenu.push_back(Item5); //add to the end of list the Item5
    entireMenu.push_back(Item6); //add to the end of list the Item6
    entireMenu.push_back(Item7); //add to the end of list the Item7

    std::vector<std::string> defaultMenuNames = { "Green Tea", "Burrito", "Pizza", "Soda", "Burger", "Pasta", "Catfish" };
    std::vector<char> defaultAddLetters = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
    std::vector<char> defaultRemoveLetters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };

    for (int i = 0; i < numItems; i++)
    {
        //add each item to the default list efficiently 
        entireMenu[i].setName(defaultMenuNames[i]);
        entireMenu[i].setAddLetter(defaultAddLetters[i]);
        entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]);
        entireMenu[i].setItemCost((3.00 + i)); //set a random starter cost for each item
        entireMenu[i].setCount(0); //initialze all counts to 0
        entireMenu[i].setDesc("delicious"); //set all default desc to "delicous"
    }


}

void Menu::showMenu(std::vector<MenuItem>& m)
{
    std::cout << std::fixed << std::setprecision(2);//set doubles to 2 decimal places
    std::cout << "DrT's Effcient Menu" << std::endl;
    std::cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC" << std::endl;
    for (int i = 0; i < m.size(); i++)
    {
        std::cout << m[i].getAddLetter() << ")" << std::setw(10) << m[i].getName()
            << std::setw(5) << "$" << m[i].getItemCost() << std::setw(5) << "(" << m[i].getRemoveLetter()
            << ")" << std::setw(7) << m[i].getCount() << std::setw(13) << m[i].getDesc()
            << std::endl;
    }
}

void Menu::acceptOrder(std::vector<MenuItem>& m)
{
    char option = '\0';// the user-selected menu item
    double subtotal = 0.0;
    double tip;

    do
    {
        std::cout << "\nPlease choose an item (x to Exit): ";
        std::cin >> option;

        for (int i = 0; i < m.size(); i++)
        {
            if (option == m[i].getAddLetter())
            {
                std::cout << "\nMenu Item " << m[i].getAddLetter() << " selected.";
                m[i].setCount(m[i].getCount() + 1); //increment the count by 1
                std::cout << "\033[2J\033[1;1H"; //clear screen 
                std::cout << "\n1 UP on " << m[i].getName() << std::endl;
                subtotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
                showMenu(m); //show the updated menu
                std::cout << "\nSubtotal: $" << subtotal << std::endl;
            }
            else if (option == m[i].getRemoveLetter())
            {
                std::cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected.";
                if (m[i].getCount() > 0) //subtract if and only if the count is > 0
                {
                    m[i].setCount(m[i].getCount() - 1); //decrement the count by 1
                    std::cout << "\033[2J\033[1;1H"; //clear screen 
                    std::cout << "\n1 DOWN on " << m[i].getName() << std::endl;
                    subtotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
                    showMenu(m); //show the updated menu
                    std::cout << "\nSubtotal: $" << subtotal << std::endl;
                }
                else //the the user why you blocked item removal 
                {

                    std::cout << "\nItem count must be > 0 to remove: " << m[i].getName() << std::endl;
                }
            }
            else if (
                option != m[i].getAddLetter() &&
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X'
                ) //test for all of my valid inputs
            {
                if (i == 0)
                {
                    std::cout << "\nInvalid input (" << option << "). Please try again." << std::endl;
                }
            }
        }
    } while (option != 'x' && option != 'X');
    std::cout << "\nThank you for placing your order." << std::endl;
    //handle the tip process here
    system("clear");
    double tip20 = subtotal * .20;
    std::cout << "\nYour total is: $" << subtotal << " Would you like to leave a tip? (20% tip = $" << tip20 << ")" <<std::endl;
    std::cout << "Enter tip amount: ";
    std::cin >> tip;

    //handle reciept generation here
    system("clear");
    std::cout << "\n\n\n";
    showReciept(m, tip, subtotal);

    //handle payment
    system("clear");
    payment(subtotal, tip);

    //write reciept to txt file
    saveReciept(m, tip, subtotal);

    
}

void Menu::showReciept(std::vector<MenuItem>& m, double tip, double foodTotal)
{
    double totalBill = tip + foodTotal;
    std::cout << "____________________________________" << std::endl;
    std::cout << "\tDR_T Restaurant Receipt" << std::endl;
    std::cout << "\n\tAmout  Item         Cost" << std::endl;
    for (int i = 0; i < m.size(); i++)
    {
        if (m[i].getCount() >= 1)
        {
            std::cout <<  "\t" << m[i].getCount() << ")  "<< m[i].getName() << "          "  << m[i].getItemCost() << "\n\n";
        }
    }
    std::cout << std::setw(13) << "Food: $" << foodTotal << std::endl;
    std::cout << std::setw(13) << "Tip: $" << tip << std::endl;
    std::cout << std::setw(13) << "Total Bill: $" << totalBill << std::endl;
    std::cout << "____________________________________" << std::endl;

}

void Menu::payment(double foodTotal, double tip)
{
    int total = foodTotal + tip;
    std::string lastName;
    int lastFour;
    int cvc;
    int userInput;
    bool check = true;

    while (check != false)
    {
        std::cout << "How would you like to pay (1: Card | 2: Cash): ";
        userInput = validateInt(userInput);
        if (userInput == 1)
        {

            std::cout << "______________________" << std::endl;
            std::cout << "Credit Card Center" << std::endl;
            std::cout << "Your Total: $" << total << std::endl;

            std::cout << "Enter Last Name: ";
            lastName = validateString(lastName);

            std::cout << "Enter Last Four Digits: ";
            lastFour = validateInt(lastFour);

            std::cout << "Enter CVC Number: ";
            cvc = validateInt(cvc);

            std::cout << "...Processing Payment..." << std::endl;
            std::cout << "Payment Completed!" << std::endl;
            check = false;
        }
        else if (userInput == 2)
        {
            double userMoney;
            double change;

            std::cout << "______________________" << std::endl;
            std::cout << "Cash Checkout" << std::endl;
            std::cout << "Your Total: $" << total << std::endl;
            std::cout << "Enter Cash Amount (*Change will be provided): ";
            userMoney = validateDouble(userMoney);
            if (userMoney > total)
            {
                change = userMoney - total;
                std::cout << "Your Change: $" << change << std::endl;
                std::cout << "THANK YOU!" << std::endl;
            }
            check = false;
        }
        else
        {
            std::cout << "Invalid Payment Option!! Try Again" << std::endl;
        }
    }
}

void Menu::saveReciept(std::vector<MenuItem>& m, double tip, double foodTotal)
{
    std::ofstream reciept;
    reciept.open("reciept.txt");
    double totalBill = tip + foodTotal;

    reciept << "____________________________________\n";
    reciept << "\tDR_T Restaurant Receipt\n";
    reciept << "\n\tAmout  Item         Cost\n";

    for (int i = 0; i < m.size(); i++)
    {
        if (m[i].getCount() >= 1)
        {
            reciept << "\t" << m[i].getCount() << ")  " << m[i].getName() << "          " << m[i].getItemCost() << "\n\n";
        }
    }

    reciept << std::setw(13) << "Food: $" << foodTotal << std::endl;
    reciept << std::setw(13) << "Tip: $" << tip << std::endl;
    reciept << std::setw(13) << "Total Bill: $" << totalBill << std::endl;
    reciept << "____________________________________" << std::endl;

}

