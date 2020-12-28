#include<iostream>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#include<time.h>
using namespace std;
#include "Distributed_Network.h"

int main()
{
    int bit = 0;
    Distributed_Network<string> net;
    cout << "Enter Bit Size for Distributed_Network : ";
    cin >> bit;
    net.set_bit_size(bit);

    int total_machine = 0;
    cout << "Enter Total Machines For Distributed_Network : ";
    cin >> total_machine;
    net.set_total_machine(total_machine);

    cout << endl;

    int n = 0;
    cout << "1) Use machine IP to make Distributed_Network." << endl
        << "2) Use machine no to make Distributed_Network." << endl
        << "3) Automatically make  Distributed_Network" << endl;
    cout << "Input your choice : ";
    cin >> n;

    cout << endl;

    if (n == 1)
    {
        string machine = "";
        for (int i = 0; i < total_machine; i++)
        {
            cout << "Enter machine IP Address : ";
            cin >> machine;
            net.make_network_using_IP(machine);
        }
    }
    else if (n == 2) {
        int machine = 0;
        for (int i = 0; i < total_machine; i++)
        {
            cout << "Enter machine no : ";
            cin >> machine;
            net.make_network_using_machine_no(machine);
        }
    }
    else if (n == 3) {
        srand(1);
        int total_space = pow(2, bit);
        for (int i = 0; i < total_machine; i++)
        {
            int  machine = rand() % total_space;
            net.make_network_using_machine_no(machine);
        }
        cout << "Distributed_Network Created" << endl;
    }
    cout << endl;

    net.display_all_machines();
    net.manage_table();

    cout << endl;

    int pair = 0;
    cout << "How much {Key-Value} you want to store in Distributed_Network Ring : ";
    cin >> pair;
    cout << endl;

    // Use For testing the file limit
    /*
    for(int i=0; i<pair; i++)
    {
        net.insert_data_to_cloud(to_string(i), to_string(i+1));
    }
    */

    for (int i = 0; i < pair; i++)
    {
        string key = "";
        cout << "Enter Key : ";
        cin >> key;
        string data = "";
        cout << "Enter Data : ";
        cin.ignore();
        getline(cin, data);
        int mac = 0;
        cout << "Enter machine no : ";
        cin >> mac;
        net.insert_data_to_cloud(key, data, mac);
        cout << endl;
    }

    cout << "DO YOU Want....." << endl;
    int choice = 0;
    cout << "1) To add new Machines" << endl
        << "2) To Delete " << endl
        << "0) Skip" << endl;
    cout << "Enter Your Choice : ";
    cin >> choice;
    cout << endl;
    n = 0;
    if (choice == 1)
    {
        cout << "1) Use machine IP to make Distributed_Network." << endl
            << "2) Use machine no to make Distributed_Network." << endl
            << "3) Automatically make  Distributed_Network" << endl;
        cout << "Input your choice : ";
        cin >> n;
    }
    else if (choice == 2)
    {
        int no = 0;
        cout << "Enter machine number you want to Delete : ";
        cin >> no;
        net.delete_machine_from_cloud(no);
    }

    cout << endl;

    if (n == 1)
    {
        string machine = "";
        cout << "Enter machine IP Address : ";
        cin >> machine;
        net.make_network_using_IP(machine);
    }
    else if (n == 2) {
        int machine = 0;
        cout << "Enter machine no : ";
        cin >> machine;
        net.make_network_using_machine_no(machine);
    }
    else if (n == 3) {
        srand(1);
        int total_space = pow(2, bit);
        int  machine = rand() % total_space;
        net.make_network_using_machine_no(machine);
        cout << "Distributed_Network Created" << endl;
    }
    net.display_all_machines();
    net.manage_table();
    cout << endl;

    int display_Table = 0;
    cout << "Enter Machine-no to print Finger Table : ";
    cin >> display_Table;
    net.display_Table_of_machines(display_Table);
    cout << endl;

    int z = 0;
    cout << "How many AVL Tree's you want to print : ";
    cin >> z;

    for (int i = 0; i < z; i++)
    {
        int AVL_no = 0;
        cout << "Enter Machine-no to print AVL Tree : ";
        cin >> AVL_no;
        net.display_AVL_of_machines(AVL_no);
        cout << endl;
    }
    int x = 0;
    cout << "HOw many Key_Value pair you want to delete : ";
    cin >> x;
    for (int i = 0; i < x; i++)
    {
        string delete_key = "";
        cout << "Enter Key YOu want to delete from Cloud : ";
        cin >> delete_key;
        int  g = 0;
        cout << "Enter Machine no to send delete request : ";
        cin >> g;
        net.delete_data(delete_key, g);
        cout << endl;
    }

    x = 0;
    cout << "How many AVL Tree's you want to print : ";
    cin >> x;
    for (int i = 0; i < x; i++)
    {
        int tree = 0;
        cout << "Enter Machine-no to print AVL Tree : ";
        cin >> tree;
        net.display_AVL_of_machines(tree);
        cout << endl;
    }
    int limit = 0;
    cout << "How much Key you want to reterive from Distributed Network : ";
    cin >> limit;

    for (int i = 0; i < limit; i++)
    {
        cout << endl;
        string test = "";
        cout << "Enter key to Reterive Data from Distributed Network : ";
        cin >> test;
        cout << test << " : " << net.reterive_data_from_cloud(test) << endl;
    }
    return 0;
}