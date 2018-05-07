//  ShippingStatus.cpp
//  Project2
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.

#include "ShippingStatus.h"
#include <time.h>

ShippingStatus::ShippingStatus() 
{ //to be completed
    status = " "; 
    location = " "; 
    timeStatus = time(NULL);
}

ShippingStatus::ShippingStatus(const string& status, const string& location, const time_t& timeUpdated) 
{ //to be completed
  ShippingStatus::status = status; 
  ShippingStatus::location = location; 
  timeStatus = timeUpdated; 
}

string ShippingStatus::m_getStatus()
{//to be completed
  return status; 
}

string ShippingStatus::m_getLocation()
{ //to be completed
  return location; 
}

time_t ShippingStatus::m_getTime() 
{ //to be completed
  return timeStatus; 
}


ShippingStatus& ShippingStatus::operator=(const ShippingStatus& ss)
{
	ShippingStatus *temp;
	temp = new ShippingStatus;
	temp->location = ss.location;
	temp->status = ss.status;
	temp->next = ss.next;
	temp->prev = ss.prev;
	temp->timeStatus = ss.timeStatus;
	return *this;
}

/*
bool ShippingStatus::operator==(const ShippingStatus& r) const
{
	return /*(prev == r.prev);(location == r.location) && (status == r.status) && (timeStatus == r.timeStatus) && (next == r.next) && (prev == r.prev);
}

bool ShippingStatus::operator!=(const ShippingStatus& r) const 
{
	return /*(prev != r.prev);(location != r.location) && (status != r.status) && (timeStatus != r.timeStatus) && (next != r.next) && (prev != r.prev);
}
*/
