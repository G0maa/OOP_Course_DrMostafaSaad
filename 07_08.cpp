#include <bits/stdc++.h>
using namespace std;

class StudentGradesInfo {
private:
	string student_id;
	vector<double> grades;
	vector<string> courses_names;
	const int MAX_GRADE_PER_COURSE = 100.0;

	friend class StudentGradesInfoWhiteBoxTester;	// as a friend

	static int statistics_total_prints;

	double AdjustGrade(double grade) const {
		if (grade < 0)
			return 0;
		if (grade > MAX_GRADE_PER_COURSE)
			return MAX_GRADE_PER_COURSE;
		return grade;
	}
public:

	StudentGradesInfo(string student_id) :
			student_id(student_id) {
	}

	bool AddGrade(double grade, const string &course_name) {
		grade = AdjustGrade(grade);

		for (int i = 0; i < (int) courses_names.size(); ++i)
			if (course_name == courses_names[i])
				return false;	// already added

		grades.push_back(grade);
		courses_names.push_back(course_name);
		return true;
	}
	void PrintAllCourses() const {
		++statistics_total_prints;

		cout << "Grades for student: " << GetStudentId() << "\n";
		for (int course_idx = 0; course_idx < (int) courses_names.size(); ++course_idx)
			cout << "\t" << courses_names[course_idx] << " = " << grades[course_idx] << "\n";
	}
	bool GetCourseGradeInfo(int pos, pair<string, double> &result) const {
		if (pos < 0 || pos >= (int) grades.size()) {
			result = make_pair("", -1);
			return false;
		}
		result = make_pair(courses_names[pos], grades[pos]);
		return true;
	}

	string GetStudentId() const {
		return student_id;
	}

	int GetTotalCoursesCount() const {
		return grades.size();
	}

	pair<double, double> GetTotalGradesSum() const {
		double sum = 0, total = 0;
		for (int grade_idx = 0; grade_idx < (int) grades.size(); ++grade_idx)
			sum += grades[grade_idx], total += MAX_GRADE_PER_COURSE;
		return make_pair(sum, total);
	}
};

int StudentGradesInfo::statistics_total_prints = 0;

// Imagine you have 5 classes using the open source class "StudentGradesInfo"
// if by chance some implemntation details changes in the open source calss
// -> You will have to edit all the 5 classes,
// the wrapper let's you edit only one class.
class StudentGradesInfoWrapper {
private:
    StudentGradesInfo std;
    static int num_studets;
    static int num_prints;
public:
    // is that a good idea?
    // I am not sure if he wants me to just directly call the function or not,
    // but that's what I did anyway,
    // so in case of changing implementation of them, just edit the wrapper.
    StudentGradesInfoWrapper(string student_id) : std(student_id) { 
        num_studets++;
    }

	bool AddGrade(double grade, const string &course_name) {
        return std.AddGrade(grade, course_name);
	}

	void PrintAllCourses() const {
        num_prints++; // is it better to call a separate function?
        std.PrintAllCourses();
	}

	bool GetCourseGradeInfo(int pos, pair<string, double> &result) const {
        return std.GetCourseGradeInfo(pos, result);
	}

	string GetStudentId() const {
        return std.GetStudentId();
	}

	int GetTotalCoursesCount() const {
        return std.GetTotalCoursesCount();
	}

	pair<double, double> GetTotalGradesSum() const {
        return std.GetTotalGradesSum();
	}

    static int GetTotalStudents() {
        return num_studets;
    }

    static int GetTotalPrints() {
        return num_prints;
    }
};


int StudentGradesInfoWrapper::num_studets = 0;
int StudentGradesInfoWrapper::num_prints = 0;

int main() {
	StudentGradesInfoWrapper st1("S000123");
	st1.AddGrade(70, "Math");
	st1.AddGrade(70, "programming 1");
	st1.AddGrade(85, "programming 2");

	st1.PrintAllCourses();

	pair<double, double> p = st1.GetTotalGradesSum();
	cout << p.first << "/" << p.second << "\n";

	StudentGradesInfoWrapper st2("S000129");
	st2.PrintAllCourses();
	st2.PrintAllCourses();
	st2.PrintAllCourses();

	cout << "Total Students " << StudentGradesInfoWrapper::GetTotalStudents() << "\n";
	cout << "Total Prints " << StudentGradesInfoWrapper::GetTotalPrints() << "\n";

	cout << "Bye\n";

	return 0;
}