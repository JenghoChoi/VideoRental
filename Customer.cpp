// Customer.cc
#include <sstream>
#include <vector>
#include "Customer.h"

using std::ostringstream;
using std::vector;

std::string Customer::statement()
{
  double totalAmount = 0.;
  int frequentRenterPoints = 0;

  std::vector< Rental >::iterator iter = customerRentals.begin();
  std::vector< Rental >::iterator iter_end = customerRentals.end();

  // result will be returned by statement()
  std::ostringstream result;
  result << "Rental Record for " << getName() << "\n";

  // Loop over customer's rentals
  for ( ; iter != iter_end; ++iter ) {

    double thisAmount = 0.;
    Rental each = *iter;

    // Determine amounts for each rental
    switch ( each.getMovie().getPriceCode() ) {

      case Movie::REGULAR:
        thisAmount += 2.;
        if ( each.getDaysRented() > 2 )
          thisAmount += ( each.getDaysRented() - 2 ) * 1.5 ;
        break;

      case Movie::NEW_RELEASE:
        thisAmount += each.getDaysRented() * 3;
        break;

      case Movie::CHILDRENS:
        thisAmount += 1.5;
        if ( each.getDaysRented() > 3 )
          thisAmount += ( each.getDaysRented() - 3 ) * 1.5;
        break;

	  case Movie::OTHERS: //기존 종류 이외의 영화는 모두 2달러로 통일
		  thisAmount += each.getDaysRented() * 2;
		  break;
    }

    // Add frequent renter points
    frequentRenterPoints++;

    // Add bonus for a two day new release rental
    if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
         && each.getDaysRented() > 1 ) frequentRenterPoints++;

    // Show figures for this rental
    result << "\t" << each.getMovie().getTitle() << "\t"
           << thisAmount << std::endl;
    totalAmount += thisAmount;
  }

  // Add footer lines
  result << "Amount owed is " << totalAmount << "\n";
  result << "You earned " << frequentRenterPoints
         << " frequent renter points";

  return result.str();
}

void Customer::WriteXMLFile()
{
	double totalAmount = 0.;
	int frequentRenterPoints = 0;

	std::vector< Rental >::iterator iter = customerRentals.begin();
	std::vector< Rental >::iterator iter_end = customerRentals.end();

	tinyxml2::XMLDocument m_xmlDocument;
	tinyxml2::XMLNode* pNode;
	pNode = m_xmlDocument.NewElement("Root");
	m_xmlDocument.InsertFirstChild(pNode);
	tinyxml2::XMLElement* pElement;

	// Loop over customer's rentals
	for (; iter != iter_end; ++iter) {

		double thisAmount = 0.;
		Rental each = *iter;
		// 영화 정보 Element 추가
		pElement = m_xmlDocument.NewElement("MovieData");

		// Determine amounts for each rental
		switch (each.getMovie().getPriceCode()) {

		case Movie::REGULAR:
			thisAmount += 2.;
			if (each.getDaysRented() > 2)
				thisAmount += (each.getDaysRented() - 2) * 1.5;
			break;

		case Movie::NEW_RELEASE:
			thisAmount += each.getDaysRented() * 3;
			break;

		case Movie::CHILDRENS:
			thisAmount += 1.5;
			if (each.getDaysRented() > 3)
				thisAmount += (each.getDaysRented() - 3) * 1.5;
			break;

		case Movie::OTHERS: //기존 종류 이외의 영화는 모두 2달러로 통일
			thisAmount += each.getDaysRented() * 2;
			break;
		}

		// Add frequent renter points
		frequentRenterPoints++;

		// Add bonus for a two day new release rental
		if ((each.getMovie().getPriceCode() == Movie::NEW_RELEASE)
			&& each.getDaysRented() > 1) frequentRenterPoints++;

		// Show figures for this rental
// 		result << "\t" << each.getMovie().getTitle() << "\t"
// 			<< thisAmount << std::endl;
		pElement->SetAttribute("Title", each.getMovie().getTitle().c_str());
		pElement->SetAttribute("Amount", thisAmount);
		pNode->InsertEndChild(pElement);

		totalAmount += thisAmount;
	}

	pElement = m_xmlDocument.NewElement("TotalAmount");
	pElement->SetText(totalAmount);
	pNode->InsertEndChild(pElement);

	pElement = m_xmlDocument.NewElement("RentalPoints");
	pElement->SetText(frequentRenterPoints);
	pNode->InsertEndChild(pElement);

	tinyxml2::XMLError m_error = m_xmlDocument.SaveFile("VideoRental.xml");

}

void Customer::WriteJSONFile()
{
	Json::Value root;
	Json::Value MovieData;
	double totalAmount = 0.;
	int frequentRenterPoints = 0;

	std::vector< Rental >::iterator iter = customerRentals.begin();
	std::vector< Rental >::iterator iter_end = customerRentals.end();

	// Loop over customer's rentals
	for (; iter != iter_end; ++iter) {

		Json::Value MovieDataSub;

		double thisAmount = 0.;
		Rental each = *iter;

		// Determine amounts for each rental
		switch (each.getMovie().getPriceCode()) {

		case Movie::REGULAR:
			thisAmount += 2.;
			if (each.getDaysRented() > 2)
				thisAmount += (each.getDaysRented() - 2) * 1.5;
			break;

		case Movie::NEW_RELEASE:
			thisAmount += each.getDaysRented() * 3;
			break;

		case Movie::CHILDRENS:
			thisAmount += 1.5;
			if (each.getDaysRented() > 3)
				thisAmount += (each.getDaysRented() - 3) * 1.5;
			break;

		case Movie::OTHERS: //기존 종류 이외의 영화는 모두 2달러로 통일
			thisAmount += each.getDaysRented() * 2;
			break;
		}

		// Add frequent renter points
		frequentRenterPoints++;

		// Add bonus for a two day new release rental
		if ((each.getMovie().getPriceCode() == Movie::NEW_RELEASE)
			&& each.getDaysRented() > 1) frequentRenterPoints++;

		MovieDataSub["Title"] = each.getMovie().getTitle();
		MovieDataSub["Amount"] = thisAmount;
		MovieData.append(MovieDataSub);
		
		totalAmount += thisAmount;
	}

	root["MovieData"] = MovieData; //앞에서 MovieData 쌓고 여기서 삽입

	Json::Value TotalAmount;
	root["TotalAmount"] = totalAmount;
	Json::Value RentalPoints;
	root["RentalPoints"] = frequentRenterPoints;
	Json::StyledWriter writer;

	std::string output = writer.write(root);

	bool bError = WriteToFile("VideoRental.json", output.c_str(), output.length());
}

bool Customer::WriteToFile(const char* filename, const char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "wb");
	if (fp == nullptr)
	{
		return false;
	}
	size_t fileSize = fwrite(buffer, 1, len, fp);

	fclose(fp);
	return true;
}