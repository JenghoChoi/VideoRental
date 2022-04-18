#include <iostream>
#include "Customer.h"
#include "Movie.h"

using namespace std;

int main()
{
    Movie regular1{ "일반 1", Movie::REGULAR };
    Movie regular2{ "일반 2", Movie::REGULAR };
    Movie newRelease1{ "신작 1", Movie::NEW_RELEASE };
    Movie newRelease2{ "신작 2",Movie::NEW_RELEASE };
    Movie children1{ "어린이 1", Movie::CHILDRENS };
    Movie children2{ "어린이 2", Movie::CHILDRENS };
    Customer customer{ "고객" };

    customer.addRental({ regular1, 2 });
    customer.addRental({ regular2, 3 });
    customer.addRental({ newRelease1, 1 });
    customer.addRental({ newRelease2, 2 });
    customer.addRental({ children1, 3 });
    customer.addRental({ children2, 4 });

    cout << customer.statement() << endl;

    return 0;
}
