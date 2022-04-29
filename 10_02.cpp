#include <bits/stdc++.h>
using namespace std;

class CommunityMember { };

    class Employee : public CommunityMember { };

        class Faculty : public Employee { };

            class Adminstrator : public Faculty { };

            class Teacher : public Faculty { };

                class AdminstratorTeacher: public Adminstrator, public Teacher { };

        class Staff : public Employee { };

    class Student : public CommunityMember { };

    class Alumnus : public CommunityMember { };



int main () {

}