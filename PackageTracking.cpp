//  PackageTracking.cpp
//  Project2
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.

#include "PackageTracking.h"
#include <time.h>


PackageTracking::PackageTracking(const string& strnum) 
{ //to be completed
  //ifstream myFile(strnum + ".txt"); 

  header = new ShippingStatus;
  trailer = new ShippingStatus;
  cursor = new ShippingStatus;

  header->next = trailer;
  trailer->prev = header; 

  cursor->prev = header;
  cursor->next = trailer;

  noUpdates = 0; 
}

void PackageTracking::m_addUpdate(const string& status, const string& location, const time_t& timeUpdated) //add a new update
{ 
	ShippingStatus *node;
	node = new ShippingStatus;
	node->status = status;
	node->location = location;
	node->timeStatus = timeUpdated;

	node->prev = trailer->prev;
	trailer->prev = node;
	node->next = trailer;

	cursor = header;
	for (int i = 1; i <= noUpdates; i++)
	{
		cursor = cursor->next;
	}
	cursor->next = node;

	cursor = node;

	if (noUpdates < 1)
	{
		header->next = node;
	}
	else
	{

	}
	
	m_setCurrent(timeUpdated);

	noUpdates++;
}

bool PackageTracking::m_moveBackward()  //move iterator one step earlier in time
{ //to be completed
  //if cursor is pointing to the trailer's position
	if (cursor == header)
	{
		return false;
	}
  else 
  {
    //moves cursor back one position
    cursor = cursor->prev; 
    return true;
  }
}

bool PackageTracking::m_moveForward() //move iterator one step forward in time
{ //to be completed
  //if cursor is pointing to the trailer's position
	if (cursor == trailer)
	{
		return false;
	}
  else 
  {
    //move cursor forward one position
    cursor = cursor->next; 
    return true; 
  }
}

string PackageTracking::m_getLocation()  //return the location of the current update
{ //to be completed
	return cursor->location;
}

time_t PackageTracking::m_getTime()  //return the time of the current update
{ //to be completed
	return cursor->timeStatus;
}

string PackageTracking::m_getStatus()  //return the status of the current update
{ //to be completed
	return cursor->status;
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{ //to be completed
  return noUpdates;
}

void PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update)
{	//to be completed
  
	ShippingStatus *tracker;
	tracker = header->next;


	while (tracker != cursor)
	{
		/*time(&cursor->timeStatus);
		localtime_s(&timeinfo, &cursor->timeStatus);
		
		cout << asctime_s(str, 256, &timeinfo);*/

		cout << tracker->timeStatus << endl << tracker->status << endl << tracker->location << endl << endl;

		tracker = tracker->next;
	}
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{
	ShippingStatus *tracker_;
	tracker_ = cursor;

	if (noUpdates == 0)
	{
		return ;
	}

	while (tracker_ != trailer)
	{
		cout << tracker_->m_getTime() << '\t';
		cout << tracker_->m_getStatus() << endl;
		cout << tracker_->m_getLocation() << endl << endl;

		tracker_ = tracker_->next;
	}
}

void PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
	ShippingStatus *tracker_;
	tracker_ = header->next;

	if (noUpdates == 0)
	{
		cout << "No package information yet on record!/n";
		return;
	}
	while (tracker_ != trailer)
	{
		cout << tracker_->m_getTime() << '\t';
		cout << tracker_->m_getStatus() << endl;
		cout << tracker_->m_getLocation() << endl << endl;
		tracker_ = tracker_->next;
	}
}

bool PackageTracking::m_setCurrent(const time_t& timeUpdated) //view an update.
{ //to be completed
	
		cursor = header;

		while (cursor != trailer)
		{
			while (cursor->timeStatus == timeUpdated)
			{
					return true;	
			}
			m_moveForward();
		}
	return false;
}

bool PackageTracking::m_readTrackingFile(string fileName)
{ //to be completed

	fstream fileReader;
	fileReader.open(fileName, ios::in);

	if (fileReader.fail()) 
	{
		return false;
	}

	string nextInput, tempStatus, tempLocation;
	time_t tempTime;

	while (!fileReader.eof())
	{

		fileReader >> nextInput;

		if (nextInput == "new") {
			getline(fileReader, nextInput, ';');
			tempStatus = nextInput.substr(1, nextInput.length()); //to skip \n
			getline(fileReader, nextInput, ';');
			tempLocation = nextInput;
			getline(fileReader, nextInput, '\n');

			stringstream conversion(nextInput);
			conversion >> tempTime;

			m_addUpdate(tempStatus, tempLocation, tempTime);
		}
		else
			if (nextInput == "back")
			{
				m_moveBackward();
			}
			else
				if (nextInput == "forward") {
					m_moveForward();
				}
	}
	return true;

	/*
	ifstream myfile;

	myfile.open(fileName);

	if (!myfile)
	{
		return false;
	}

	string x;

	while (getline(cin, x))
	{
		if (x == "new")
		{
			string status;
			string location;
			time_t timeUpdated;
			string info;
			string colon = ";";

			getline(cin, info);

			int infoL = info.length();

			std::size_t first = info.find(colon);

			if (first != std::string::npos)
			{
				status = info.substr(0, first);
			}

			std::size_t second = info.find(colon, first);

			if (second != std::string::npos)
			{
				location = info.substr(first, second);
			}

			string timeU = info.substr(second);
			timeUpdated = time_t(stoi(timeU));


			m_addUpdate(status, location, timeUpdated);
		}
		else
		{
			if (x == "back")
			{
				m_moveBackward();
			}
			else
			{
				if (x == "forward")
				{
					m_moveForward();
				}

			}

		}
	}

	myfile.close();
	return true;
	*/
}
