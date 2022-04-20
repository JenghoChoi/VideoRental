#include <iostream>
#include "Customer.h"
#include "Movie.h"
#include <map>

using namespace std;

struct _stMovie
{
    string strTitle;
    int nOption;
    int nDays;
};

int main()
{
//      Movie regular1{ "�Ϲ� 1", Movie::REGULAR };
//      Movie regular2{ "�Ϲ� 2", Movie::REGULAR };
//      Movie newRelease1{ "���� 1", Movie::NEW_RELEASE };
//      Movie newRelease2{ "���� 2",Movie::NEW_RELEASE };
//      Movie children1{ "��� 1", Movie::CHILDRENS };
//      Movie children2{ "��� 2", Movie::CHILDRENS };

    Customer customer{ "��" };
    map <int, _stMovie> movieData;
    _stMovie stTempMovie;
    string movieTitle;
    int nInputOption;
    int movieRentalDays;
    int nInput;

    int nIdx = 0;
    while (1)
    {
		cout << "�뿩�� ��ȭ ����� ����, �Ⱓ�� �����ϼ���.(����:�Ϲ�1 0 2)" << endl;
		cout << "[ ��ȭ ���� ��ȣ : 0.�Ϲ�, 1.����, 2.���, 3.�׿� ]" << endl;
		cin >> movieTitle >> nInputOption >> movieRentalDays;
        if (nInputOption > 3 || nInputOption < 0)
        {
			cout << "�߸��� ���� ��ȣ�Դϴ�. �ٽ� �Է��ϼ���." << endl;
            continue;
        }
        else
        {
            stTempMovie.strTitle = movieTitle;
            stTempMovie.nOption = nInputOption;
            stTempMovie.nDays = movieRentalDays;

            movieData.insert(make_pair(nIdx, stTempMovie));
            nIdx++;
        }

        cout << "��ȭ�� ��� �뿩�Ͻ÷��� 0, ������ ������ 1�� �Է��ϼ���." << endl;
        cin >> nInput;
        if (nInput == 0)
            continue;
        else
            break;
        
    }

    for (auto it = movieData.begin(); it != movieData.end(); it++)
    {
        Movie tempMovie{ it->second.strTitle, it->second.nOption };
        customer.addRental({ tempMovie , it->second.nDays });
    }

    cout << "������ ��� ����� �����ϼ���" << endl;
    cout << "1.XML ���, 2.JSON ��� 3.�Ѵ� ���" << endl;
    cin >> nInput;

    if(nInput==1) customer.WriteXMLFile();       //XML ���� ����
    else if(nInput==2) customer.WriteJSONFile(); //JSON ���� ����
    else
    {
        customer.WriteXMLFile();   //XML ���� ����
        customer.WriteJSONFile();  //JSON ���� ����
    }

    cout << customer.statement() << endl;

    return 0;
}
