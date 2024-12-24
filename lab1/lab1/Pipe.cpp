#include "Pipe.h"

int Pipe::maxId = 0;

int Pipe::GetId()
{
	return Id;
}

void Pipe::PrintPipeStatus()
{
	cout << (isRepairing ? "Pipe is under repair" : "Pipe is in work") << endl;
}

string Pipe::GetName() const
{
	return kilometerMark;
}

int Pipe::GetDiameter() const
{
	return diameter;
}

bool Pipe::GetStatus() const
{
	return isRepairing;
}

bool Pipe::FreeConnections() const
{
	return csId1 < 1 || csId2 < 1;
}

void Pipe::Connect(const int& id1, const int& id2)
{
	csId1 = id1;
	csId2 = id2;
}

void Pipe::DeleteConnection()
{
	csId1 = 0;
	csId2 = 0;
}

void InputCorrectDiameter(int& diameter)
{
	cin >> diameter;
	while ((diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400)  || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error! Please enter correct data (500, 700, 1000, 1400): ";
		cin >> diameter;
	}
}

void EditPipes(vector <Pipe*>& pipes)
{
	cout << endl << "Do you want to change repairing status?" << endl
		<< "1. Yes" << endl
		<< "2. No" << endl
		<< "Your choice: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		bool isRepairing;
		cout << "Is the pipe being repaired? (1 - Yes, 0 - No) ";
		InputCorrectNumberNull(isRepairing, true);

		for (auto& pipe : pipes)
		{
			pipe->isRepairing = isRepairing;
			cout << "ID: " << pipe->Id << " - ";
			pipe->PrintPipeStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "Error! Please enter correct data " << endl;
		break;
	}
}

void EditPipe(Pipe& pipe)
{
	cout << "Do you want to change repairing status?" << endl
		<< "1. Yes" << endl
		<< "2. No" << endl
		<< "Your choice: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		bool isRepairing;
		cout << "Is the pipe being repaired? (1 - Yes, 0 - No) ";
		InputCorrectNumberNull(isRepairing, true);

		pipe.isRepairing = isRepairing;
		cout << "ID: " << pipe.Id << " - ";
		pipe.PrintPipeStatus();
		break;
	case 2:
		return;
	default:
		cout << "Error! Please enter correct data " << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const Pipe& pipe)
{
	out << endl << "Pipe Id: " << pipe.Id << endl;
	out << "Kilometer mark: " << pipe.kilometerMark << endl;
	out << "Pipe length: " << pipe.length << " km" << endl;
	out << "Pipe diameter (500, 700, 1000, 1400): " << pipe.diameter << " mm" << endl;
	if (pipe.isRepairing)
		out << "Pipe under repair." << endl;
	else
		out << "Pipe is in work." << endl;
	return out;
}

istream& operator>>(istream& in, Pipe& pipe)
{
	pipe.Id = ++pipe.maxId;
	cout << "Id: " << pipe.Id << endl;
	cout << "Enter kilometer mark: ";
	in.ignore();
	getline(in, pipe.kilometerMark);
	cout << "Enter the pipe length (in kilometers): ";
	InputCorrectNumber(pipe.length);
	cout << "Enter the pipe diameter (500, 700, 1000, 1400) (in millimeters): ";
	InputCorrectDiameter(pipe.diameter);
	cout << "Is the pipe being repaired? (1 - Yes, 0 - No) ";
	InputCorrectNumberNull(pipe.isRepairing, true);
	return in;
}

ofstream& operator<<(ofstream& fout, const Pipe& pipe)
{
	fout << pipe.Id << endl;
	fout << pipe.length << endl;
	fout << pipe.kilometerMark << endl;
	fout << pipe.diameter << endl;
	fout << pipe.isRepairing << endl;
	cout << "Pipe data successfully saved to file!" << endl;
	return fout;
}

ifstream& operator>>(ifstream& fin, Pipe& pipe)
{
	fin >> pipe.Id;
	pipe.maxId = pipe.Id;
	fin >> pipe.length;
	fin.ignore();
	getline(fin, pipe.kilometerMark);
	fin >> pipe.diameter;
	fin >> pipe.isRepairing;
	cout << "Pipe data loaded successfully!" << endl;
	return fin;
}

