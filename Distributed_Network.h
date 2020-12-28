#pragma once

#ifndef DISTRIBUTED_NETWORK_H_
#define DISTRIBUTED_NETWORK_H_

#include<iostream>
using namespace std;
#include<cmath>
#include<functional>
#include"AVL.h"
#include"Machine.h"

// Distributed_Network Class
template<class T>
class Distributed_Network
{
private:
    int bit_size;
    int total_machine;
    machine<T>* network;

    // Function to sort Circular link_list
    void sort()
    {
        machine<T>* temp = network;
        while (temp->next_machine != network)
        {
            machine<T>* temp1 = new machine<T>();
            temp1 = temp->next_machine;
            while (temp1 != network)
            {
                if (temp1->machine_no < temp->machine_no)
                {
                    temp1->swap_data(temp, temp1);
                }
                temp1 = temp1->next_machine;
            }
            temp = temp->next_machine;
        }
    }

    machine<T>* pointer(int a)
    {
        machine<T>* temp = network;
        while (temp->next_machine != network)
        {
            if (temp->machine_no == a)
            {
                return temp;
            }
            temp = temp->next_machine;
        }
        return temp;
    }
public:
    Distributed_Network()
    {
        bit_size = 0;
        total_machine = 0;
        network = NULL;
    }

    // Funtions to set Bit size of Distributed Network
    void set_bit_size(int n)
    {
        bit_size = n;
    }

    // Function to set TOtal Machines in Distributed Network
    void set_total_machine(int a)
    {
        total_machine = a;
    }

    // Function to Link Machines Using IP Address
    // & also this function handle to add new machine After Creating Distribited Network
    void make_network_using_IP(T no)
    {
        hash<T> hashing;
        int total = pow(2, bit_size);
        int hash_value = (unsigned int)hashing(no) % total;
        cout << "Machine Hash Value : " << hash_value << endl;
        machine<T>* new_machine = new machine<T>();
        new_machine->set_machine_no(hash_value);
        if (network == NULL)
        {
            network = new_machine;
            new_machine->next_machine = network;
        }
        else {
            machine<T>* temp = network;
            while (temp->next_machine != network)
            {
                if (temp->machine_no == new_machine->machine_no)
                {
                    cout << "Machine with this ID already present" << endl;
                    return;
                }
                temp = temp->next_machine;
            }
            if (temp->machine_no == new_machine->machine_no)
            {
                cout << "Machine with this ID already present" << endl;
                return;
            }
            temp->next_machine = new_machine;
            new_machine->next_machine = network;
        }
        new_machine->make_file();
        this->sort();
    }

    // Function to Link Machines Using machine_no
    // & also this function handle to add new machine After Creating Distribited Network
    void make_network_using_machine_no(int no)
    {
        machine<T>* new_machine = new machine<T>();
        new_machine->set_machine_no(no);
        cout << "Machine Hash Value : " << no << endl;
        if (network == NULL)
        {
            network = new_machine;
            new_machine->next_machine = network;
        }
        else {
            machine<T>* temp = network;
            while (temp->next_machine != network)
            {
                if (temp->machine_no == new_machine->machine_no)
                {
                    cout << "Machine with this ID already present" << endl;
                    return;
                }
                temp = temp->next_machine;
            }
            if (temp->machine_no == new_machine->machine_no)
            {
                cout << "Machine with this ID already present" << endl;
                return;
            }
            temp->next_machine = new_machine;
            new_machine->next_machine = network;
        }
        new_machine->make_file();
        this->sort();
    }

    // Function to Inset Key_Value pair in Distributed_Network
    void insert_data_to_cloud(T val, T data, int k)
    {
        hash<T> hashing;
        int total = pow(2, bit_size);
        int hash_value = (unsigned int)hashing(val) % total;
        cout << "Key Hash Value : " << hash_value << endl;
        machine<T>* mac = pointer(k);
        machine<T>* test = network;
        bool check = false;
        cout << "Path : ";
        while (test->next_machine != network)
        {
            if (hash_value <= test->machine_no && mac->machine_no > test->machine_no)
            {
                cout << mac->machine_no << "->" << test->machine_no << endl;
                test->insert(val, data);
                test->limit++;
                return;
            }
            test = test->next_machine;
        }
        machine<T>* temp = mac;
        bool flag = true;
        while (temp->next_machine != mac)
        {
            cout << temp->machine_no;
            if (hash_value <= temp->machine_no)
            {
                if (temp->limit > 100)
                {
                    temp->make_extra_file();
                    temp->limit = 0;
                }
                temp->insert(val, data);
                temp->limit++;
                cout << endl;
                return;
            }
            cout << "->";
            temp = temp->next_machine;
        }
        if (hash_value <= temp->machine_no)
        {
            cout << temp->machine_no;
            if (temp->limit > 100)
            {
                temp->make_extra_file();
                temp->limit = 0;
            }
            temp->insert(val, data);
            temp->limit++;
            flag = false;
        }
        if (flag)
        {
            cout << network->machine_no;
            if (network->limit > 100)
            {
                network->make_extra_file();
                network->limit = 0;
            }
            network->insert(val, data);
            network->limit++;
        }
        cout << endl;
    }

    // Function to display all machine in Distributed_Network with Their Address
    void display_all_machines()
    {
        cout << "All Machines in DHT Ring : " << endl;
        machine<T>* temp = network;
        while (temp->next_machine != network)
        {
            cout << temp->machine_no << " " << temp << endl;
            temp = temp->next_machine;
        }
        cout << temp->machine_no << " " << temp << endl;
    }

    // Function to Create Finger_Table for each machine
    void manage_table()
    {
        machine<T>* temp = network;
        while (temp->next_machine != network)
        {
            temp->make_Finger_Table(this->bit_size, this->network);
            temp = temp->next_machine;
        }
        temp->make_Finger_Table(this->bit_size, this->network);
    }

    // Function to Display Finger_Table using Machine ID
    void display_Table_of_machines(int a)
    {
        machine<T>* temp = network;
        while (temp->next_machine != network)
        {
            if (temp->machine_no == a)
            {
                temp->display_Table(temp->machine_no);
            }
            temp = temp->next_machine;
        }
        if (temp->machine_no == a)
        {
            temp->display_Table(temp->machine_no);
        }
    }

    // Function to display AVL tree using Machine ID
    void display_AVL_of_machines(int a)
    {
        machine<T>* temp = network;
        while (temp->next_machine != network)
        {
            if (temp->machine_no == a)
            {
                temp->print_AVL();
            }
            temp = temp->next_machine;
        }
        if (temp->machine_no == a)
        {
            temp->print_AVL();
        }
    }

    // Function to reterive data from Distributed_Network
    T reterive_data_from_cloud(T key)
    {
        hash<T> hashing;
        int total = pow(2, bit_size);
        int hash_value = (unsigned int)hashing(key) % total;
        T data = "";
        machine<T>* temp = network;
        bool flag = true;
        while (temp->next_machine != network)
        {
            if (hash_value <= temp->machine_no)
            {
                data = temp->reterive(key);
                if (data != "")
                {
                    flag = false;
                    return data;
                }
            }
            temp = temp->next_machine;
        }
        if (flag)
        {
            data = network->reterive(key);
            if (data == "")
            {
                data = temp->reterive(key);
            }
        }
        return data;
    }

    // Function to reterive Data from Machine using machine_id entered by User/provider
    T reterive_data(T key, int no)
    {
        hash<T> hashing;
        int total = pow(2, bit_size);
        int hash_value = (unsigned int)hashing(key) % total;
        T data = "";
        machine<T>* temp = network;
        bool flag = true;
        while (temp->next_machine != network)
        {
            if (no == temp->machine_no)
            {
                if (hash_value <= temp->machine_no)
                {
                    data = temp->reterive(key);
                    flag = false;
                }
                machine<T>* addr = NULL;
                addr = temp->reterive_using_Lookup(hash_value);
                if (hash_value <= addr->machine_no && addr != NULL && data == "")
                {
                    data = addr->reterive(key);
                    if (data != "")
                    {
                        flag = false;
                        return data;
                    }
                }
            }
            temp = temp->next_machine;
        }
        if (flag)
        {
            data = network->reterive(key);
            if (data == "")
            {
                data = temp->reterive(key);
            }
        }
        return data;
    }

    // Function to delete Machine using Machine_no & storing its AVL Tree in the next machine
    void delete_machine_from_cloud(int id)
    {
        machine<T>* temp = network;
        if (network->machine_no == id)
        {
            while (temp->next_machine != network)
            {
                temp = temp->next_machine;
            }
            temp->next_machine = network->next_machine;
            network->next_machine->Shift_AVL_Tree_Data(network);
            network = network->next_machine;
        }
        else {
            while (temp->next_machine->machine_no != id)
            {
                temp = temp->next_machine;
            }
            temp->next_machine->next_machine->Shift_AVL_Tree_Data(temp->next_machine);
            temp->next_machine = temp->next_machine->next_machine;
        }
    }

    // Function to delete Key-Value pair from any machine 
    void delete_data(T key, int k)
    {
        hash<T> hashing;
        int total = pow(2, bit_size);
        int hash_value = (unsigned int)hashing(key) % total;
        cout << "Key Hash Value : " << hash_value << endl;
        machine<T>* mac = pointer(k);
        machine<T>* test = network;
        bool check = false;
        cout << "Path : ";
        while (test->next_machine != network)
        {
            if (hash_value <= test->machine_no && mac->machine_no > test->machine_no)
            {
                cout << mac->machine_no << "->" << test->machine_no << endl;
                test->delete_data_from_AVL_Tree(key);
                return;
            }
            test = test->next_machine;
        }
        machine<T>* temp = mac;
        bool flag = true;
        while (temp->next_machine != mac)
        {
            cout << temp->machine_no;
            if (hash_value <= temp->machine_no)
            {
                temp->delete_data_from_AVL_Tree(key);
                cout << endl;
                return;
            }
            cout << "->";
            temp = temp->next_machine;
        }
        if (hash_value <= temp->machine_no)
        {
            cout << temp->machine_no;
            temp->delete_data_from_AVL_Tree(key);
            flag = false;
        }
        if (flag)
        {
            cout << network->machine_no;
            network->delete_data_from_AVL_Tree(key);
        }
        cout << endl;
    }
};

#endif