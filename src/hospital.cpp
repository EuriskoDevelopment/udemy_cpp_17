#include<iostream>
using namespace std;

#define MAX_SPECIALIZATION 20
#define MAX_QUEUE 2

string names[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int queue_length[MAX_SPECIALIZATION+1];


int menu() {
	int choice = -1;
	while (choice == -1) {
		cout << "\nEnter your choice:\n";
		cout << "1) Add new patient\n";
		cout << "2) Print all patients\n";
		cout << "3) Get next patient\n";
		cout << "4) Exit\n";

		cin >> choice;

		if (!(1 <= choice && choice <= 4)) {
			cout << "Invalid choice. Try again\n";
            cin.clear();
            fflush(stdin);
			choice = -1;	// loop keep working
		}
	}
	return choice;
}

void add_patient() {
    int specialization;
    string name;
    int prio;

    cout << "\nEnter specialization, name, status:\n";
    cin >> specialization >> name >> prio;
    cout << "Adding " << name << " spec: " << specialization << " prio: " << prio << "\n";    

    int q_length = queue_length[specialization];
    if (q_length >= MAX_QUEUE) 
    {
        cout << "Queue full\n";
    }
    else {
        names[specialization][q_length] = name;
        queue_length[specialization]++;

    }
    
}

void print_patients() {
    for (auto& rows: names) {
        //if ()
        for (auto& column: rows)
        {
            // if queue 
        }
    }
}


void hospital_system() {
	while (true) {
		int choice = menu();

		if (choice == 1)
			add_patient();
		else if (choice == 2)
			print_patients();
		//else if (choice == 3)
			//get_next_patients();
		else
			break;
	}
}

int main() {
//freopen("c.in", "rt", stdin);
	hospital_system();
	return 0;
}