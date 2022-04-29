#include <bits/stdc++.h>
using namespace std;

class StudentGradesInfo {
private:
	string student_id;
	vector<double> grades;
	vector<string> courses_names;
	const int MAX_GRADE_PER_COURSE = 100.0;


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
	

	bool GetCourseGradeInfo(int pos, pair<string, double> &result) const{
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
    friend class StudentGradesInfoWhiteBoxTester;
};
int StudentGradesInfo::statistics_total_prints = 0;

// I'm not sure about what am I supposed to do.
class StudentGradesInfoWhiteBoxTester {
public:
	StudentGradesInfo test1() {
		StudentGradesInfo std1("42019156");
		assert(std1.student_id == "42019156");
		return std1;
	}

	StudentGradesInfo test2() {
		StudentGradesInfo std = test1(); // this will copy btw.
		std.AddGrade(95.6, "Math1");
		std.AddGrade(94.4, "Math2");
		std.AddGrade(91.7, "Math3");
		assert(std.courses_names[0] == "Math1");
		assert(std.courses_names[1] == "Math2");
		assert(std.courses_names[2] == "Math3");
		assert(std.grades[0] == 95.6);
		assert(std.grades[1] == 94.4);
		assert(std.grades[2] == 91.7);
		// should output:
		// Math1 = 95.6
		// Math2 = 94.4
		// Math3 = 91.7
		return std;
	}

	void test3() {
		StudentGradesInfo std = test2();
		assert(std.courses_names.size() == 3);
		assert(std.grades.size() == 3);
		assert(std.courses_names[1] == "Math2" && std.grades[1] == 94.4);
		

		assert(std.AdjustGrade(999) == std.MAX_GRADE_PER_COURSE);
		assert(std.AdjustGrade(-999) == std.MAX_GRADE_PER_COURSE);
		assert(std.AdjustGrade(50) == std.MAX_GRADE_PER_COURSE);
	}

	void testall() {
		test1();
		test2();
		test3();
	}
};

// Same BlackBox tests but testing the private data members + functions.
class StudentGradesInfoBlackBoxTesting {
public:

    
	StudentGradesInfo test1() {
		StudentGradesInfo std1("42019156");
		assert(std1.GetStudentId() == "42019156");
		return std1;
	}

	StudentGradesInfo test2() {
		StudentGradesInfo std = test1(); // this will copy btw.
		std.AddGrade(95.6, "Math1");
		std.AddGrade(94.4, "Math2");
		std.AddGrade(91.7, "Math3");
		std.PrintAllCourses();
		// should output:
		// Math1 = 95.6
		// Math2 = 94.4
		// Math3 = 91.7
		return std;
	}

	void test3() {
		StudentGradesInfo std = test2();
		assert(std.GetTotalCoursesCount() == 3);
		pair<string, double> result;
		std.GetCourseGradeInfo(1, result);
		assert(result.first == "Math2" && result.second == 94.4);
		
		assert(std.GetCourseGradeInfo(4, result) == false);

		pair<double, double> grades_count = std.GetTotalGradesSum();
		assert(grades_count.first == 281.7 && grades_count.second == 300);
	}
    void TestAll() {
		test1();
		test2();
		test3();
    }
};

int main() {

    // StudentGradesInfoBlackBoxTesting().TestAll();
    StudentGradesInfoBlackBoxTesting().TestAll();
	cout<<"\nN/A(s) Left his mark here.\n";
	return 0;
}