#include "CompressorStation.h"

int CompressorStation::maxId = 0;

int CompressorStation::GetId()
{
	return Id;
}

string CompressorStation::GetName() const
{
	return name;
}

void CompressorStation::PrintWorkshopStatus() const
{
	cout << "Working " << activeWorkshopCount << "/" << workshopCount << " (" << GetPercentOfActiveWorkshops() << "%)" << endl;
}

int CompressorStation::GetPercentOfActiveWorkshops() const
{
	return activeWorkshopCount * 100 / workshopCount;
}

void EditCompressorStation(CompressorStation& compressorStation)
{
	int commandNumber;
	while (true)
	{
		cout << "Do you want to change the number of active workshops?" << endl
			<< "1. Yes" << endl
			<< "2. No" << endl
			<< "Your choice: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
			cout << "Enter the number of active workshops: ";
			InputCorrectNumber(compressorStation.activeWorkshopCount, true);
			while (compressorStation.activeWorkshopCount > compressorStation.workshopCount)
			{
				cout << "Error!\n The number of active workshops cant be more than the total number of workshops." << endl
					<< "The number of workshops is " << compressorStation.workshopCount << endl
					<< "Please enter correct data: ";
				InputCorrectNumber(compressorStation.activeWorkshopCount, true);
			}
			cout << "ID: " << compressorStation.Id << " - ";
			compressorStation.PrintWorkshopStatus();
			return;
		case 2:
			return;
		default:
			cout << "Error! Please enter correct data: " << endl;
			break;
		}
	}
}

void EditCompressorStations(vector <CompressorStation*>& compressorStations)
{
	cout << endl << "Do you want to change the number of active workshops?" << endl
		<< "1. Yes" << endl
		<< "2. No" << endl
		<< "Your choice: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		cout << "Enter the percent of active workshops (0-100): ";
		float percent;
		InputCorrectNumber(percent, true);

		for (auto& compressorStation : compressorStations)
		{
			compressorStation->activeWorkshopCount = round(compressorStation->workshopCount * percent / 100);
			cout << "ID: " << compressorStation->Id << " - ";
			compressorStation->PrintWorkshopStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "Error! Please enter correct data " << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const CompressorStation& CS)
{
	out << endl << "Compressor station Id: " << CS.Id << endl;
	CS.PrintWorkshopStatus();
	out << "Number of active workshops: " << CS.activeWorkshopCount << endl;
	out << "Efficiency: " << CS.efficiency << endl << endl;
	return out;
}

istream& operator>>(istream& in, CompressorStation& CS)
{
	CS.Id = ++CS.maxId;
	cout << "Id: " << CS.Id << endl;
	cout << "Enter the name of the Compressor station: ";
	in.ignore();
	getline(in, CS.name);
	cout << "Enter the number of workshops: ";
	InputCorrectNumber(CS.workshopCount);
	cout << "Enter the number of active workshops: ";
	InputCorrectNumber(CS.activeWorkshopCount, true);
	while (CS.workshopCount < CS.activeWorkshopCount)
	{
		cout << "Error! The number of active workshops cant be more than the total number of workshops" << endl
			<< "Please enter correct data: ";
		InputCorrectNumber(CS.activeWorkshopCount, true);
	}
	cout << "Enter efficiency from 1 to 100: ";
	InputCorrectNumber(CS.efficiency, true);
	while (!(CS.efficiency >= 1 && CS.efficiency <= 100))
	{
		cout << "Error! Please enter correct data: ";
		InputCorrectNumber(CS.efficiency, true);
	}
	return in;
}

ofstream& operator<<(ofstream& fout, const CompressorStation& CS)
{
	fout << CS.Id << endl;
	fout << CS.name << endl;
	fout << CS.workshopCount << endl;
	fout << CS.activeWorkshopCount << endl;
	fout << CS.efficiency << endl;
	cout << "Compressor station data successfully saved to file!" << endl;
	return fout;
}


ifstream& operator>>(ifstream& fin, CompressorStation& CS)
{
	fin >> CS.Id;
	CS.maxId = CS.Id;
	fin.ignore();
	getline(fin, CS.name);
	fin >> CS.workshopCount;
	fin >> CS.activeWorkshopCount;
	fin >> CS.efficiency;
	cout << "Compressor station data loaded successfully!" << endl;
	return fin;
}