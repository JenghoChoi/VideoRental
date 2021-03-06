// Customer.hh
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Rental.h"
#include "tinyxml2.h"
#include "json/json.h"

// The customer class represents the customer of the store

class Customer {
public:
  Customer();
  explicit Customer( const std::string& name );

  void addRental( const Rental& arg );
  std::string getName() const;

  // Generate a statement for the customer
  std::string statement();

  //XML 파일 작성 함수
  void WriteXMLFile();

  //JSON 파일 작성 함수
  void WriteJSONFile();
  bool WriteToFile(const char* filename, const char* buffer, int len);

private:
  std::string customerName;
  std::vector< Rental > customerRentals;

};


inline Customer::Customer() {}

inline Customer::Customer( const std::string& name ): 
  customerName( name ) {}

inline void Customer::addRental( const Rental& arg ) { customerRentals.push_back( arg ); }

inline std::string Customer::getName() const { return customerName; }

#endif // CUSTOMER_HH
