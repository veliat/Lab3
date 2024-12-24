#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include "Utilities.h"
#include "Pipe.h"
#include "CompressorStation.h"
#include "logger.h"

using namespace std;

template <typename T>
T& SelectElement(unordered_map <int, T>& elements)
{
	int Id;
	cout << "Enter number: ";
	InputCorrectNumber(Id);
	while (elements.find(Id) == elements.end())
	{
		cout << "Error!\nThe number exceeds the number of elements." << endl
			<< "Number of elements: " << elements.size() << endl
			<< "Please enter correct data: ";
		InputCorrectNumber(Id);
	}
	return elements[Id];
}

void SearchPipes(unordered_map <int, Pipe>& pipes) {
	while (true)
	{
		int commandNumber;
		cout << "By what criteria do you want to find a pipe?" << endl
			<< "1. Id" << endl
			<< "2. Name" << endl
			<< "3. Is repairing or not" << endl
			<< "4. Back" << endl
			<< "Your choice: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
		{
			int id;
			cout << "Select ID pipe: ";
			InputCorrectNumber(id);
			while (pipes.find(id) == pipes.end())
			{
				cout << "Error!\nThe number exceeds the number of elements." << endl
					<< "Number of elements: " << pipes.size() << endl
					<< "Please enter correct data: ";
				InputCorrectNumber(id);
			}
			int commandNumber1;
			cout << "Do you want to remove the pipe?" << endl
				<< "1. Yes" << endl
				<< "2. No" << endl
				<< "Your choice: ";
			InputCorrectNumber(commandNumber1);
			switch (commandNumber1)
			{
			case 1:
			{
				pipes.erase(id);
				cout << "You removed the pipe from the ID: " << id << endl << endl;
			}
			case 2:
				return;
			default:
				cout << "Error! Please enter correct data" << endl;
				break;
			}
		}
		break;
		case 2:
		{
			string name;
			cout << "Name: ";
			cin.ignore();
			getline(cin, name);
			vector<Pipe*> editPipes;
			for (auto& pair : pipes) {
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << pair.second << endl;
					editPipes.push_back(&(pair.second));
				}
			}
			if (editPipes.empty())
				cout << "Pipe with this name not found." << endl;
			else
				EditPipes(editPipes);
		}
		break;
		case 3:
		{
			bool isRepairing;
			cout << "Is the pipe being repaired? (1 - Yes, 0 - No) ";
			InputCorrectNumber(isRepairing, true);

			vector<Pipe*> editPipes;
			for (auto& pair : pipes) {
				if (pair.second.GetStatus() == isRepairing)
				{
					cout << pair.second << endl;
					editPipes.push_back(&(pair.second));
				}
			}
			if (editPipes.empty())
				cout << "Pipe with this name not found." << endl;
			else
				EditPipes(editPipes);
		}
		break;
		case 4:
			return;
		default:
			cout << "Error! Please enter correct data" << endl;
			break;
		}
	}
}

void SearchCompressorStations(unordered_map <int, CompressorStation>& compressorStations) {
	while (true)
	{
		int commandNumber;
		cout << "By what criteria do you want to find a Compressor Station?" << endl
			<< "1. Id" << endl
			<< "2. Name" << endl
			<< "3. Percent of active worskshops" << endl
			<< "4. Back" << endl
			<< "Your choice: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
		{
			int id;
			cout << "Select ID Compressor station: ";
			InputCorrectNumber(id);
			while (compressorStations.find(id) == compressorStations.end())
			{
				cout << "Error!\nThe number exceeds the number of elements." << endl
					<< "Number of elements: " << compressorStations.size() << endl
					<< "Please enter correct data: ";
				InputCorrectNumber(id);
			}
			int commandNumber1;
			cout << "Do you want to remove the pipe?" << endl
				<< "1. Yes" << endl
				<< "2. No" << endl
				<< "Your choice: ";
			InputCorrectNumber(commandNumber1);
			switch (commandNumber1)
			{
			case 1:
			{
				compressorStations.erase(id);
				cout << "You removed the compressor station from the ID: " << id << endl << endl;
			}
			case 2:
				return;
			default:
				cout << "Error! Please enter correct data" << endl;
				break;
			}
		}
		break;
		case 2:
		{
			string name;
			cout << "Name: ";
			cin.ignore();
			getline(cin, name);
			vector<CompressorStation*> editCompressorStations;
			for (auto& pair : compressorStations) {
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << pair.second << endl;
					editCompressorStations.push_back(&(pair.second));
				}
			}
			if (editCompressorStations.empty())
				cout << "Compressor Station with this name not found." << endl;
			else
				EditCompressorStations(editCompressorStations);
		}
		break;
		case 3:
		{
			int percent;
			cout << "Enter the percent of active workshops (0-100) +-5%: ";
			InputCorrectNumber(percent, true);

			vector<CompressorStation*> editCompressorStations;
			for (auto& pair : compressorStations) {
				if (pair.second.GetPercentOfActiveWorkshops() > percent - 5 && pair.second.GetPercentOfActiveWorkshops() < percent + 5)
				{
					cout << pair.second << endl;
					editCompressorStations.push_back(&(pair.second));
				}
			}
			if (editCompressorStations.empty())
				cout << "Compressor Station with this name not found." << endl;
			else
				EditCompressorStations(editCompressorStations);
		}
		break;
		case 4:
			return;
		default:
			cout << "Error! Please enter correct data" << endl;
			break;
		}
	}
}

bool HasPipeWithConnection(const unordered_map<int, Pipe>& pipes, const int& csId1, const int& csId2) {
	bool hasPipe = false;
	for (auto& pair : pipes) {
		if ((pair.second.csId1 == csId1 && pair.second.csId2 == csId2)
			|| (pair.second.csId1 == csId2 && pair.second.csId2 == csId1))
		{
			hasPipe = true;
		}
	}
	return hasPipe;
}

void ConnectPipe(unordered_map <int, Pipe>& pipes, unordered_map <int, CompressorStation>& compressorStations)
{
	cout << endl << "[ Connect the pipe and compressor stations ]" << endl;
	int diameterPipe;
	int diameter;
	cout << "Enter pipe diameter: ";
	InputCorrectNumber(diameter);
	diameterPipe = diameter;
	while ((diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error! Please enter correct data (500, 700, 1000, 1400): ";
		cin >> diameter;
	}

	int connectedPipeId = 0;
	for (auto& pair : pipes) {
		if (pair.second.GetDiameter() == diameterPipe && pair.second.FreeConnections())
		{
			connectedPipeId = pair.first;
			break;
		}
	}

	Pipe* connectedPipe{};
	if (connectedPipeId == 0) // если не найдено свободных труб с нужным диаметром
	{
		bool isRunning = true;
		while (isRunning) {
			int commandNumber1;
			cout << "Pipe with this diameter not found." << endl
				<< "Do you want to add a pipe?" << endl
				<< "1. Yes" << endl
				<< "2. No" << endl
				<< "Your choice: ";
			InputCorrectNumber(commandNumber1);
			switch (commandNumber1)
			{
			case 1:
			{
				Pipe pipe;
				cin >> pipe;
				connectedPipe = &pipe;
				pipes.insert(make_pair(connectedPipe->GetId(), *connectedPipe));
				isRunning = false;
				return;
			}
			break;
			case 2:
				return;
			default:
				cout << "Error! Please enter correct data" << endl;
				break;
			}
		}
	}
	else
	{
		connectedPipe = &pipes[connectedPipeId];
	}

	// запрашиваем две кс
	// соединяем трубу с двумя кс
	cout << "Enter the id of the first compressor station: ";
	int csId1;
	InputCorrectNumber(csId1);
	while (compressorStations.find(csId1) == compressorStations.end())
	{
		cout << "Error!\nCompressor Station with this Id not found." << endl
			<< "Please enter correct data: ";
		InputCorrectNumber(csId1);
	}
	cout << "Enter the id of the second compressor station: ";
	int csId2;
	InputCorrectNumber(csId2);
	while (compressorStations.find(csId2) == compressorStations.end()
		|| csId2 == csId1
		|| HasPipeWithConnection(pipes, csId1, csId2))
	{
		cout << "Error!\nCompressor Station with this Id not found." << endl
			<< "Please enter correct data: ";
		InputCorrectNumber(csId2);
	}
	connectedPipe->Connect(csId1, csId2);
}

vector<int> topologicalSort(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations) {
	vector<int> result;
	unordered_map<int, int> inDegree; // Количество входящих ребер для каждой вершины

	// Инициализация inDegree для каждой вершины
	for (auto& pipe : pipes) {
		inDegree[pipe.second.csId2]++;
	}

	// Создаем очередь для хранения вершин с нулевым inDegree
	queue<int> q;
	for (auto& station : stations) {
		if (inDegree.find(station.first) == inDegree.end()) {
			q.push(station.first);
		}
	}

	// Выполняем топологическую сортировку
	while (!q.empty()) {
		int currentStation = q.front();
		q.pop();
		result.push_back(currentStation);

		// Уменьшаем inDegree для всех соседних вершин
		for (auto& pipe : pipes) {
			if (pipe.second.csId1 == currentStation) {
				inDegree[pipe.second.csId2]--;
				if (inDegree[pipe.second.csId2] == 0) {
					q.push(pipe.second.csId2);
				}
			}
		}
	}

	return result;
}



int main()
{
	unordered_map <int, Pipe> pipes = {};
	unordered_map <int, CompressorStation> compressorStations = {};
	Logger logger;
	logger.log("Start");

	int commandNumber;
	while (true)
	{
		cout << "MENU:" << endl
			<< "0. Exit the program" << endl
			<< "1. Add pipe" << endl
			<< "2. Add compressor station" << endl
			<< "3. View all objects" << endl
			<< "4. Edit pipe" << endl
			<< "5. Edit compressor station" << endl
			<< "6. Save" << endl
			<< "7. Load" << endl
			<< "8. Search" << endl
			<< "9. Connect the pipe and compressor stations" << endl
			<< "10. View gas network" << endl
			<< "11. Delete gas network" << endl
			<< "12. Topological sort" << endl
			<< "What do you want to do: ";
		InputCorrectNumberNull(commandNumber);
		switch (commandNumber)
		{
		case 0:
			cout << "[ Exit the program ]" << endl;
			logger.log("Exit");
			return 0;
			break;
		case 1:
		{
			cout << "[ Add pipe ]" << endl;
			logger.log("Add pipe start");
			Pipe pipe;
			cin >> pipe;
			pipes.insert(make_pair(pipe.GetId(), pipe));
			logger.log("Add pipe finish");
			break;
		}
		case 2:
		{
			cout << "[ Add compressor station ]" << endl;
			logger.log("Add compressor station start");
			CompressorStation CS;
			cin >> CS;
			compressorStations.insert(make_pair(CS.GetId(), CS));
			logger.log("Add compressor station finish");
			break;
		}
		case 3:

			cout << "[ View all objects ]" << endl;
			logger.log("Show all objects start");

			if (pipes.size() == 0)
				cout << "Pipe not found." << endl;
			for (const auto& pair : pipes)
				cout << pair.second;

			if (compressorStations.size() == 0)
				cout << "Compressor station not found." << endl;
			for (const auto& pair : compressorStations)
				cout << pair.second;
			logger.log("Show all objects finish");
			break;

		case 4:
		{
			cout << "[ Edit pipe ]" << endl;
			logger.log("Edit pipe start");
			if (pipes.size() == 0)
				cout << "Pipe not found." << endl;
			else {
				Pipe pipe = SelectElement(pipes);
				EditPipe(pipe);
			}
			logger.log("Edit pipe finish");
			break;
		}
		case 5:
		{
			cout << "[ Add active Workshop ]" << endl;
			cout << "[ Edit compressor station ]" << endl;
			logger.log("Edit compressor station start");
			if (compressorStations.size() == 0)
				cout << "Compressor station not found." << endl;
			else {
				CompressorStation compressorStation = SelectElement(compressorStations);
				EditCompressorStation(compressorStation);
			}
			logger.log("Edit compressor station finish");
			break;
		}
		case 6:
		{
			cout << "[ Save ]" << endl;
			logger.log("Save start");
			ofstream fout;
			string fileName;
			cout << "Enter file name: ";
			cin.ignore();
			getline(cin, fileName);
			fout.open(fileName);
			if (!fout.is_open())
			{
				cout << "File opening error!" << endl;
			}
			else
			{
				fout << pipes.size() << endl;
				for (const auto& pair : pipes)
					fout << pair.second;
				fout << compressorStations.size() << endl;
				for (const auto& pair : compressorStations)
					fout << pair.second;
			}
			fout.close();
			logger.log("Save finish");
		}
			break;

		case 7:
		{
			cout << "[ Load ]" << endl;
			logger.log("Load start");
			ifstream fin;
			string fileName;
			int input;
			cout << "Enter file name: ";
			cin.ignore();
			getline(cin, fileName);
			fin.open(fileName);
			if (!fin.is_open())
			{
				cout << "File opening error!" << endl;
			}
			else
			{
				int pipeSize;
				fin >> pipeSize;
				if (pipeSize == 0)
					cout << "Pipes not found." << endl;
				while (pipeSize-- > 0)
				{
					Pipe pipe;
					fin >> pipe;
					pipes.insert(make_pair(pipe.GetId(), pipe));
				}

				int compressorStationSize;
				fin >> compressorStationSize;
				if (compressorStationSize == 0)
					cout << "Compressor stations not found." << endl;
				while (compressorStationSize-- > 0)
				{
					CompressorStation CS;
					fin >> CS;
					compressorStations.insert(make_pair(CS.GetId(), CS));
				}

				fin.close();
			}
			logger.log("Load finish");
		}
			break;
		case 8:
		{
			bool isRunning = true;
			while (isRunning) {
				int commandNumber1;
				cout << "[ Search ]" << endl
					<< "What do you want to find?" << endl
					<< "1. Pipe" << endl
					<< "2. Compressor station" << endl
					<< "3. Back" << endl
					<< "Your choice: ";
				logger.log("Search start");
				InputCorrectNumber(commandNumber1);
				switch (commandNumber1)
				{
				case 1:
					if (pipes.size() == 0)
						cout << "Pipes not found." << endl;
					else {
						cout << "[ Pipe ]" << endl;
						SearchPipes(pipes);
					}
					break;
				case 2:
					if (compressorStations.size() == 0)
						cout << "Compressor stations not found." << endl;
					else {
						cout << "[ Compressor station ]" << endl;
						SearchCompressorStations(compressorStations);
					}
					break;
				case 3:
					isRunning = false;
					break;
				default:
					cout << "Error! Please enter correct data" << endl;
					break;
				}
				logger.log("Search finish");
			}
		}
			break;
		case 9:
		{
			logger.log("Connect the pipe and compressor stations start");
			if (compressorStations.size() < 2)
				cout << "Compressor stations less than two." << endl;
			else
				ConnectPipe(pipes, compressorStations);
			logger.log("Connect the pipe and compressor stations finish");
		}
		break;
		case 10:
		{
			cout << "[ View gas Network ]" << endl;
			logger.log("View gas Network start");
			if (pipes.size() == 0)
				cout << "Pipe not found." << endl;
			if (compressorStations.size() == 0)
				cout << "Compressor station not found." << endl;
			int connectionCount = 0;
			for (const auto& pair : pipes)
				if (!pair.second.FreeConnections())
				{
					cout << "CS1 " << pair.second.csId1 << "- Pipe " << pair.first << " - CS2 " << pair.second.csId2 << endl;
					connectionCount++;
				}
			cout << "Found " << connectionCount << " connections." << endl;
			logger.log("View gas Network finish");
		}
		break;
		case 11:
		{

			cout << "[ Delete gas Network ]" << endl;
			logger.log("Delete gas Network start");
			if (pipes.size() == 0)
				cout << "Pipe not found." << endl;
			else {
				cout << "Enter the ID of the pipe you want to delete: ";
				int deleteGasNetwork;
				InputCorrectNumber(deleteGasNetwork);
				while (pipes.find(deleteGasNetwork) == pipes.end())
				{
					cout << "Error!\nPipe with this Id not found." << endl
						<< "Please enter correct data: ";
					InputCorrectNumber(deleteGasNetwork);
				}
				if (pipes[deleteGasNetwork].FreeConnections()) {
					cout << "Pipe not connected." << endl;
				}
				else {
					pipes[deleteGasNetwork].DeleteConnection();
					cout << "Connection deleted." << endl;
				}
			}
		}
		break;
		case 12:
		{
			cout << "[ Topological Sort ]" << endl;
			// Вызов функции topologicalSort
			vector<int> sortedStations = topologicalSort(pipes, compressorStations);

			// Вывод отсортированных станций
			for (int stationId : sortedStations) {
				cout << stationId << " ";
			}
			cout << endl;
		}
		break;
		default:
			cout << "Error! Please enter correct data: " << endl;
			break;
		}
	}
}