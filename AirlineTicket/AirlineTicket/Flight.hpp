//
//  Ticket.hpp
//  AirlineTicket
//
//  Created by Jackson Zamorano on 10/3/22.
//

#ifndef Ticket_hpp
#define Ticket_hpp

#include <stdio.h>
#include "DoubleLinkedList.hpp"
#include "Passenger.hpp"

class Flight {
public:
    int flightNumber;
    DoubleLinkedList<Passenger>* passengers = new DoubleLinkedList<Passenger>;
};

#endif /* Ticket_hpp */
