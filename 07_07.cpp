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
    // just checking for a bug.
    StudentGradesInfo(StudentGradesInfo &another) {
        cout << "\nCopy constructor was called\n";
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

class StudentGradesInfoPrinter {
private:
    int iterator = { };
    const StudentGradesInfo *std = { };
public:
    StudentGradesInfoPrinter(StudentGradesInfo *std_) : std(std_), iterator(0) { }

    bool HasNext() const {
        // cout << '\n' << (*std).GetTotalCoursesCount() << '\n';
        if(iterator < (*std).GetTotalCoursesCount())
            return true;
        else
            return false;
    }

    pair<string, double> GetNext() {
        pair<string, double> res;
        (*std).GetCourseGradeInfo(iterator, res);
        iterator++;
        return res;
    }

    void ResetIterator() {
        this->iterator = 0;
    }
};

int main() {
	StudentGradesInfo st1("S000123");
    // I had to pass it be refrence as passing it without refrence triggered copy constructor
	StudentGradesInfoPrinter printer(&st1);

	st1.AddGrade(50, "Math");
	st1.AddGrade(60, "programming 1");

	int limit = 3;
	cout << "Printing top " << limit << " Grades, if available\n";
	while (limit-- && printer.HasNext()) {
		pair<string, double> result = printer.GetNext();

		cout << "\t" << result.first << " = " << result.second << "\n";
	}

	st1.AddGrade(70, "Algorithms");
	st1.AddGrade(67, "programming 2");

	printer.ResetIterator();
	limit = 3;
	cout << "\nPrinting top " << limit << " Grades, if available\n";
	while (limit-- && printer.HasNext()) {
		pair<string, double> result = printer.GetNext();

		cout << "\t" << result.first << " = " << result.second << "\n";
	}

	return 0;
}