#ifndef MACHINE_H_
#define MACHINE_H_

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
#include "AVL.h"

template <class T>
class Finger_Table;

// Machine Class Implementation
template<class T>
class machine
{
private:
    AVL_Tree<T> tree;
    Finger_Table<T> Table;
    ofstream machine_data;
    T data_file_name;
    int counter;
public:
    int limit;
    int machine_no;
    machine* next_machine;

    machine()
    {
        limit = 0;
        counter = 0;
        machine_no = 0;
        next_machine = NULL;
        data_file_name = "";
    }

    // Set machine_no
    void set_machine_no(int no)
    {
        machine_no = no;
    }

    // Make unique file for each machine
    void make_file()
    {
        T a = "machine";
        a += to_string(machine_no);
        a += ".txt";               // machine0.txt
        data_file_name = a;
        machine_data.open(a);
    }

    // Make extra files, if First file make more than 100 lines of data
    void make_extra_file()
    {
        counter++;
        T a = "machine";
        a += to_string(machine_no);
        a += "_";
        a += to_string(counter);
        a += ".txt";               // machine0_1.txt
        data_file_name = a;
        machine_data.close();
        machine_data.clear();
        machine_data.open(data_file_name);
        return;
    }

    // Function to insert Key_Value parir in Machine
    void insert(T val, T data)
    {
        machine_data << data << endl;
        ifstream inputFile;
        inputFile.open(data_file_name);
        int line_no = 0;
        T line = "";
        while (!inputFile.eof())
        {
            getline(inputFile, line);
            line_no++;
            if (line == data)
            {
                break;
            }
        }
        tree.insert(val, line_no, data_file_name);
    }

    // Function to reterive data from machine
    T reterive(T val)
    {
        T data = "";
        int line = tree.Find(val);
        T file_name = tree.Find_File(val);
        ifstream inputFile;
        inputFile.open(file_name);
        int line_no = 0;
        T lines = "";
        if (line == 0)
        {
            return "NO Data";
        }
        while (!inputFile.eof())
        {
            getline(inputFile, lines);
            line_no++;
            if (line == line_no)
            {
                data = lines;
            }
        }
        return data;
    }

    // Function to mange Finger_Table for machine
    void make_Finger_Table(int n, machine<T>* list)
    {
        Table.make_Table(n, list, this->machine_no);
    }

    // Function to display Finger_Table of machine
    void display_Table(int a)
    {
        Table.display(a);
    }

    // Function to swap data between two machines
    void swap_data(machine<T>* temp, machine<T>* temp1)
    {
        swap(temp->machine_no, temp1->machine_no);
        swap(temp->data_file_name, temp1->data_file_name);
        swap(temp->machine_data, temp1->machine_data);
        swap(temp->Table, temp1->Table);
        swap(temp->tree, temp1->tree);
    }

    // Function to reterive machine pointer from Finger Table
    machine<T>* reterive_using_Lookup(int n)
    {
        return Table.reterive(n);
    }

    // Function to print AVL Tree of each machine
    void print_AVL()
    {
        tree.display();
    }

    // Function to Shift_AVL_Tree_Data
    void Shift_AVL_Tree_Data(machine<T>* a)
    {
        tree.shift_data_from_different_AVL_Tree(a->tree);
    }

    // Function to delete AVL Tree Node
    void delete_data_from_AVL_Tree(T key)
    {
        tree.remove_node(key);
    }

    ~machine()
    {

    }
};

template <class T>
class machine;

// Basic Structure of Table_Node
template <class T>
struct Table_Node
{
    int no;
    machine<T>* machine_addr;
    Table_Node* next;
    Table_Node* prev;

    Table_Node(int val)
    {
        no = val;
        machine_addr = NULL;
        next = NULL;
        prev = NULL;
    }
};

// Finger_Table Class 
template <class T>
class Finger_Table
{
private:
    int flag;
    Table_Node<T>* head;
    Table_Node<T>* tail;

public:
    Finger_Table()
    {
        flag = 0;
        head = NULL;
        tail = NULL;
    }

    // Function to make Table for each Machine 
    void make_Table(int n, machine<T>* active_machine, int machine_no)
    {
        if (flag > 0)
        {
            head = NULL;
            tail = NULL;
        }
        int no = 1;
        for (int i = 0; i < n; i++)
        {
            Table_Node<T>* temp = new Table_Node<T>(no);

            if (head == NULL)
            {
                head = tail = temp;
            }
            else {
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
            int flag = true;
            int m = machine_no + pow(2, i);
            machine<T>* active = active_machine;
            while (active->next_machine != active_machine)
            {
                if (m <= active->machine_no)
                {
                    temp->machine_addr = active;
                    flag = false;
                    break;
                }
                active = active->next_machine;
            }
            if (m <= active->machine_no && flag == true)
            {
                temp->machine_addr = active;
                flag = false;
            }
            if (flag == true)
            {
                temp->machine_addr = active_machine;
            }
            no++;
        }
        flag++;
    }

    // Function to display Finger_Table
    void display(int a)
    {
        cout << "Finger Table of machine " << a << " : " << endl;
        Table_Node<T>* temp = head;
        while (temp != NULL)
        {
            cout << temp->no << " " << temp->machine_addr << " " << temp->machine_addr->machine_no << endl;
            temp = temp->next;
        }
    }

    // Function to reterive machine pointer from  machine
    machine<T>* reterive(int no)
    {
        Table_Node<T>* temp = head;
        while (temp != NULL)
        {
            if (no <= temp->machine_addr->machine_no)
            {
                return temp->machine_addr;
            }
            temp = temp->next;
        }
        return NULL;
    }

    ~Finger_Table()
    {
        delete head;
        delete tail;
    }
};

#endif