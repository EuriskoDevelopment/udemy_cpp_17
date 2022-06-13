#include<iostream>
using namespace std;

#define MAX_SPECIALIZATION 20
#define MAX_QUEUE 5

string names[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int status[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
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

void move_back(int spec)
{
	// Move all patients in queue to the right
		auto& rows = names[spec];
	    if (queue_length[spec] < MAX_QUEUE)
		{
			for (int j = 0; j < queue_length[spec]; j++)
			{
				cout << names[spec][j] <<endl;
				// if queue 
			}
		}
		else {
			cout << "Queue is full\n" << endl;
		}
}

void shift_right(int spec)
{
	//auto&& temp = names[spec][MAX_QUEUE];
	auto len = queue_length[spec];
	for (int i = len; i > 0; i--)
	{
		names[spec][i] = names[spec][i-1];
		status[spec][i] = status[spec][i-1];
	}

}

void shift_left(int spec)
{
	//auto&& temp = names[spec][MAX_QUEUE];
	auto len = queue_length[spec];
	for (int i = 0; i <= len; i++)
	{
		names[spec][i] = names[spec][i+1];
		status[spec][i] = status[spec][i+1];
	}
    queue_length[spec]--;

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
		if (prio == 0)
		{
			names[specialization][q_length] = name;
			status[specialization][q_length] = prio;
			queue_length[specialization]++;
		}
		else if (prio == 1)
		{
			// Add first and shift to right
			shift_right(specialization);
			names[specialization][0] = name;
			status[specialization][0] = prio;
			queue_length[specialization]++;
		}
		else {
			cout << "Invalid prio \n";
		}

    }
    
}

void print_patients() {
	for (int i = 0; i < MAX_SPECIALIZATION; i++)
	{
		auto& rows = names[i];
	    if (queue_length[i] > 0)
		{
			cout << "There are " << queue_length[i] << " patients in spec " << i << endl;
			for (int j = 0; j < queue_length[i]; j++)
			{
				string stat = status[i][j] ? "regular" : "urgent"; 
				cout << names[i][j] << stat << endl;
			}
		}
    }
}

void get_next_patients()
{
	int spec;
	cout << "Enter specialization\n";
	cin >> spec;

	auto len = queue_length[spec];
	if (len == 0)
	{
		cout << "No more patients\n";
	}
	else {
		cout<<names[spec][0]<<" please go with the Dr\n";
		shift_left(spec);
	}

}


void hospital_system() {
	while (true) {
		int choice = menu();

		if (choice == 1)
			add_patient();
		else if (choice == 2)
			print_patients();
		else if (choice == 3)
			get_next_patients();
		else
			break;
	}
}

int main() {
//freopen("c.in", "rt", stdin);
	hospital_system();
	return 0;
}