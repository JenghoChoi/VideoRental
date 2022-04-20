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
//      Movie regular1{ "일반 1", Movie::REGULAR };
//      Movie regular2{ "일반 2", Movie::REGULAR };
//      Movie newRelease1{ "신작 1", Movie::NEW_RELEASE };
//      Movie newRelease2{ "신작 2",Movie::NEW_RELEASE };
//      Movie children1{ "어린이 1", Movie::CHILDRENS };
//      Movie children2{ "어린이 2", Movie::CHILDRENS };

    Customer customer{ "고객" };
    map <int, _stMovie> movieData;
    _stMovie stTempMovie;
    string movieTitle;
    int nInputOption;
    int movieRentalDays;
    int nInput;

    int nIdx = 0;
    while (1)
    {
		cout << "대여할 영화 제목과 종류, 기간을 기입하세요.(예시:일반1 0 2)" << endl;
		cout << "[ 영화 종류 번호 : 0.일반, 1.신작, 2.어린이, 3.그외 ]" << endl;
		cin >> movieTitle >> nInputOption >> movieRentalDays;
        if (nInputOption > 3 || nInputOption < 0)
        {
			cout << "잘못된 종류 번호입니다. 다시 입력하세요." << endl;
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

        cout << "영화를 계속 대여하시려면 0, 영수증 발행은 1을 입력하세요." << endl;
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

    cout << "영수증 출력 방식을 선택하세요" << endl;
    cout << "1.XML 출력, 2.JSON 출력 3.둘다 출력" << endl;
    cin >> nInput;

    if(nInput==1) customer.WriteXMLFile();       //XML 파일 생성
    else if(nInput==2) customer.WriteJSONFile(); //JSON 파일 생성
    else
    {
        customer.WriteXMLFile();   //XML 파일 생성
        customer.WriteJSONFile();  //JSON 파일 생성
    }

    cout << customer.statement() << endl;

    return 0;
}
