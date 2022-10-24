#include "List.h"

void List::excuteList(string date) {
    validDate(date);

    vector<vector<string>> fileData = File::getBooking(date);

    cout << date << " 스터디룸 상태입니다." << endl;
    cout << left << setw(6) << "스터디룸 ";
    for (int i = 9; i < 20; ++i) {
        string hour = to_string(i);
        string time;
        if (hour.length() == 1) time = "0" + hour + ":00";
        else time = hour + ":00";
        cout << left << setw(6) << time;

        if (hour.length() == 1) time = "0" + hour + ":30";
        else time = hour + ":30";
        cout << left << setw(6) << time;
    }

    cout << endl;
    for (int i = 1; i < 10; i++) {
        cout << left << setw(7) << i;
        for (int j = 0; j < 22; j++) {
            if (fileData[i][j] == "0") cout << left << setw(7) << " 가능 ";
            else cout << left << setw(7) << "X";
        }
        cout << endl;
    }
}

void List::validDate(string date) {
    int inputYear = stoi(date.substr(0, 4));
    int inputMonth = stoi(date.substr(5, 2));
    int inputDay = stoi(date.substr(8, 2));

    if (inputYear < 2000 || inputYear > 3000)
        throw WrongRuleArgumentException(date, "연(year)은 2000 이상, 3000 이하만 가능합니다.");
    if (inputMonth < 1 || inputMonth > 12)
        throw WrongRuleArgumentException(date, "존재하지 않는 달(month)입니다.");
    if (inputMonth == 2) {
        if ((inputYear % 4 == 0 && inputYear % 100 != 0) || (inputYear % 100 == 0 && inputYear % 400 == 0)) {
            if (inputDay < 0 || inputDay > 29)
                throw WrongRuleArgumentException(date, "존재하지 않는 일(day)입니다.");
        }
        else {
            if (inputDay < 0 || inputDay > 28)
                throw WrongRuleArgumentException(date, "존재하지 않는 일(day)입니다.");
        }
    }
    else if (inputMonth == 4 || inputMonth == 6 || inputMonth == 9 || inputMonth == 11) {
        if (inputDay < 0 || inputDay > 30) throw WrongRuleArgumentException(date, "존재하지 않는 일(day)입니다.");
    }
    else {
        if (inputDay < 0 || inputDay > 31) throw WrongRuleArgumentException(date, "존재하지 않는 일(day)입니다.");
    }


    time_t now;
    time(&now);

    time_t inputDate;
    struct tm user_stime;

    user_stime.tm_year = inputYear - 1900;   // 주의 :년도는 1900년부터 시작
    user_stime.tm_mon = inputMonth - 1;      // 주의 :월은 0부터 시작
    user_stime.tm_mday = inputDay+1;
    user_stime.tm_hour = 0;
    user_stime.tm_min = 0;
    user_stime.tm_sec = 0;
    user_stime.tm_isdst = 0;              // 썸머 타임 사용 안함

    inputDate = mktime(&user_stime);

    double d_diff = difftime(inputDate, now);
    int tm_day = d_diff / (60 * 60 * 24);

    if (tm_day >= 90)
        throw WrongRuleArgumentException(date, "최대 90일 후까지 확인할 수 있습니다.");
    if (d_diff < 0)
        throw WrongRuleArgumentException(date, "과거 날짜는 조회할 수 없습니다.");

}

