#include <iostream>
using namespace std;

/*
 * Class Course will be used to store the information of a single course.
 */
class Course{
public:
    Course(){
        this->point=0;
        this->credit=0;
    }
    void set_credit(float course_credit){
        this->credit=course_credit;
    }
    void set_point(float course_point){
        this->point=course_point;
    }
    float get_credit() const{
        return credit;
    }
    float get_point() const {
        return point;
    }
private:
    float credit;
    float point;
};

/*
 * Class Student will be used to perform various operation related to students.
 */
class Student{
public:
    Student(){
        id=0;
        total_course=0;
        courses= nullptr;
        cgpa=0.0;
    }
    void set_student_id(const unsigned int student_id){
        this->id=student_id;
    }
    void total_courses(const unsigned int number_of_course){
        this->total_course=number_of_course;
        courses = new Course[total_course];
    }
    void set_results(const Course *result){
        int i;
        for(i=0;i<total_course;i++){
            courses[i].set_credit(result[i].get_credit());
            courses[i].set_point(result[i].get_point());
        }
    }
    void calculate_cgpa(){
        double sum_of_multiples=0;
        double sum_of_credits=0;
        int i;
        for(i=0;i<total_course;++i){
            float credit=courses[i].get_credit();
            float point=courses[i].get_point();
            sum_of_credits+=credit;
            sum_of_multiples+=double(credit*point);
        }
        cgpa=float(sum_of_multiples/sum_of_credits);
    }

    /*
     * Utility methods
     */
    float get_cgpa() const{
        return cgpa;
    }
    unsigned int get_id() const {
        return id;
    }
private:
    unsigned int id;
    unsigned int total_course;
    Course *courses;
    float cgpa;
};

/*
 * Class Semester keep the records of all students who participated in the semester and also sort them in descending order.
 */
class Semester{
public:
    Semester(const unsigned int total_students,const unsigned int total_courses){
        students=total_students;
        courses=total_courses;
        student_list= nullptr;
    }
    void set_students(){
        int i;
        unsigned int tmp;
        student_list=new Student[students];
        for(i=0;i<students;++i){
            cout<<"\nStudent ID: ";
            cin>>tmp;
            student_list[i].set_student_id(tmp);
            student_list[i].total_courses(courses);
            int j;
            Course results[courses];
            for(j=0;j<courses;++j){
                float tmp_point;
                cout<<"Course "<<j+1<<": ";
                cin>>tmp_point;
                results[j].set_point(tmp_point);
                results[j].set_credit(3.0);
            }
            student_list[i].set_results(results);
            /*
             * Pre-calculating the CGPA
             */
            student_list[i].calculate_cgpa();
        }

        /*
        * Automatically Sort our students list
        */
        sort();
    }

    /*
     * Performing Linear search in the students array to finding a result
     */
    void get_result(unsigned int id){
        int i;
        for(i=0;i<students;++i){
            if(student_list[i].get_id()==id){
                cout<<"CGPA of Student ID: "<<id<<" is "<<student_list[i].get_cgpa()<<endl;
                cout<<"Merit position: "<<i+1<<endl;
                break;
            }
        }
    }

private:
    void sort(){
        /*
         * Bubble sort algorithm implementation.
         */
        int i,j;
        for(i=0;i<students;++i){
            for(j=0;j<students-1;++j){
                if(student_list[j+1].get_cgpa()>student_list[j].get_cgpa()){
                    Student tmp=student_list[i];
                    student_list[i]=student_list[j];
                    student_list[j]=tmp;
                }
            }
        }
    }
    unsigned int students;
    unsigned int courses;
    Student *student_list;
};


int main() {
    Semester semester_one(3/*Number of students*/,3/*Number of courses*/);
    semester_one.set_students(); //Take the inputs
    unsigned int roll;
    cout<<"Enter the student ID: ";
    cin>>roll;
    semester_one.get_result(roll); //Outputting results
    return 0;
}
