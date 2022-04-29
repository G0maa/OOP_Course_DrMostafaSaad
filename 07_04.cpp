#include <bits/stdc++.h>
using namespace std;

int statistics_total_prints = 0;

class StudentGradesInfo {
private:
    // No name variable Bug#1
	string student_id;
	vector<double> grades; // courses_names
	vector<string> courses_names;
public:

	StudentGradesInfo() {
		assert(false);
	}

    // Use initializer list
    // Didn't set name?? Bug#1
	StudentGradesInfo(string name_, string student_id_) {
		student_id = student_id_;
	}

    // I think this should be private... users don't need to see it.
	int AdjustGrade(int grade) {
		if (grade < 0)
			return grade;
		if (grade > 100)
			return 100;
		return grade;
	}

    // تصدق سلخت قبل ما أدبح؟
    // He pushed grades, before checking if course_name is repeated or not Bug#2
	bool AddGrade(double grade, string course_name) {
		grade = AdjustGrade(grade);
		grades.push_back(grade);
        // I think this whole process should (Checking if repeated)
        // should be moved in a separate private function.
        // also comparing courses names => Another function.
        // if course name changes to struct (Course Name, lecturer, Course ID *maybe*)
        // this code will be very lengthy and repeated.
		for (int i = 0; i < (int) courses_names.size(); ++i)
			if(course_name == courses_names[i]) // course_name courses_names... will confuse people
				return false;	// already added
		courses_names.push_back(course_name);
		return true;
	}
	void PrintAllCourses() {
		++statistics_total_prints;
        // no name :c
        // Didn't use GetStudentId
        // You should use GetCourseGradeInfo here, so if we change courses_names or similar
        // it won't affect here (less changing code)
		cout << "Grades for student: " << student_id << "\n";
		for (int i = 0; i < (int) grades.size(); ++i)
			cout << "\t" << courses_names[i] << " = " << grades[i] << "\n";
	}
	pair<string, double> GetCourseGradeInfo(int pos) { // are you sure he will use 0-indexed position?
		if (pos < 0 || pos >= (int) grades.size()) // should use the GetTotalCoursesCount
			return make_pair("", -1);
		return make_pair(courses_names[pos], grades[pos]); // I think creating GetCourseName(int pos) & GetCourseGrade(int pos) would be overengineering
	}
	string GetStudentId() {
		return student_id;
	}
    // Considering the bug, this is going to be inaccurate.
	int GetTotalCoursesCount() {
		return grades.size();
	}
	// Use GetTotalCoursesCount for naming consistency
    // also courses_grades for naming consistency
	pair<double, double> get_total_gradesSum() {
		double sum = 0, total = 0;
		for (int i = 0; i < (int) grades.size(); ++i) // again use the function to return the count
			sum += grades[i], total += 100; // ever heard of multiplication?
		return make_pair(sum, total);
	}
};

int main() {
	StudentGradesInfo st1("Mostafa", "S000123");
	st1.AddGrade(70, "Math");
	st1.AddGrade(70, "programming 1");
	st1.AddGrade(85, "programming 2");

	st1.PrintAllCourses();

	pair<double, double> p = st1.get_total_gradesSum();
	cout<<p.first<<"/"<<p.second<<"\n";

	cout<<"Bye\n";

	return 0;
}