#include <bits/stdc++.h>
using namespace std;
// why not just add more constructor that has seconds only and edit hours, mintues, and seconds?
class Time {
private:
	// int hours;
	// int minutes;
	// int seconds;
    int total_seconds;
public:
	Time(int hours, int minutes, int seconds) {

		SetTime(hours, minutes, seconds);
	}
	void SetTime(int hours, int minutes, int seconds) {

		// this->hours = hours;
		// this->minutes = minutes;
		// this->seconds = seconds;
        total_seconds = hours * 60 * 60;
        total_seconds += minutes * 60;
        total_seconds += seconds;
	}
	int GetTotalSeconds() {
		// return hours * 60 * 60 + minutes * 60 + seconds;
        return total_seconds;
	}
	int GetTotalMinutes() {
		// return hours * 60 + minutes;
        return total_seconds / 60; // double warning
	}
	void PrintHHMMSS() {
		cout<<ToSring(":")<<"\n";
	}
	string ToSring(string seperator = "-") {
		ostringstream oss;
        int temp = total_seconds;
        int hours = temp / (60 * 60);
        temp -= (hours * 60 * 60);
        int minutes = temp / 60;
        temp -= minutes * 60;
        int seconds = temp / 60;
		oss << hours << seperator << minutes << seperator << seconds;

		return oss.str();
	}
	int GetHours() {
		return total_seconds / (60 * 60);
	}
	Time SetHours(int hours) {
        if(total_seconds < 0)
            total_seconds = 0;
        total_seconds += (hours * 60 * 60);
        return *this;
	}
	int GetMinutes() {
        int temp = total_seconds;
        int hours = temp / (60 * 60);
        temp -= (hours * 60 * 60);
        int minutes = temp / 60;
		return minutes;
	}
	Time SetMinutes(int minutes) {
		if (total_seconds < 0)
			total_seconds = 0;

		this->total_seconds += (minutes * 60);
        return *this;
	}
	int GetSeconds() {
        int temp = total_seconds;
        int hours = temp / (60 * 60);
        temp -= (hours * 60 * 60);
        int minutes = temp / 60;
        temp -= minutes * 60;
        int seconds = temp / 60;
		return seconds;
	}
	Time SetSeconds(int seconds) {
		if (seconds < 0)
			seconds = 0;
		this->total_seconds += seconds;
        return *this;
	}
};

int main() {
	// This will print wrongly. E.g. every 60 second should be added as a minute. Every 60 minutes should be added as an hour
	// Time t(0, 120, 120);
	// t.PrintHHMMSS();	// proper printing: 2:2:0
    Time t(3, 9, 5);
    // t.PrintHHMMSS();

    // half answer forgot &
    t.SetHours(5).SetMinutes(45).SetSeconds(13);
    // t.SetHours(5).SetMinutes(45);
    t.PrintHHMMSS();
	return 0;
}

// for 07, same idea, I just didn't think about delegation as much as I should have.