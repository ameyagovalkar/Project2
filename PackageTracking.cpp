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
	
	noUpdates++;
}

bool PackageTracking::m_moveBackward()  //move iterator one step earlier in time
{ //to be completed
  //if cursor is pointing to the trailer's position
	if (cursor == trailer)
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
  
	cursor = trailer;
	cursor = cursor->prev->prev;

	/*
	struct tm timeinfo;
	char str[256];*/

	for (int i = 1; i < noUpdates-1; i++)
	{
		/*time(&cursor->timeStatus);
		localtime_s(&timeinfo, &cursor->timeStatus);
		
		cout << asctime_s(str, 256, &timeinfo);*/

		cout << cursor->timeStatus << endl << cursor->status << endl << cursor->location << endl << endl;

		cursor = cursor->prev;
	}
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{ //to be completed
  
}

void PackageTracking::m_printFullTracking() //print all the updates in the tracking chain.
{ 
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

	ifstream myfile("C:/Users/ameya/Desktop/project2-3-samanthas-team-master/TBA688567081000.txt");

	//myfile.open("C:/Users/ameya/Desktop/project2-3-samanthas-team-master/TBA688567081000.txt");
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

	//myfile.close();
	return true;
}
