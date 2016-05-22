#include <QCoreApplication>
#include <iostream>

#include<course.h>
#include<studentgroup.h>
#include<lecturer.h>

using namespace std;

int main()
{
    Lecturer prof1(0,"prof1");
    Lecturer prof2(1,"prof2");
    Lecturer prof3(2,"prof3");
    Lecturer prof4(3,"prof4");

    StudentGroup group1(0,"group1",10);
    StudentGroup group2(1,"group2",20);
    StudentGroup group3(2,"group3",30);
    StudentGroup group4(3,"group4",42);


    Course netbA(0,"course A",9 ,15,&prof1,&group1);
    Course netbB(1,"course B",10,15,&prof2,&group1);
    Course netbC(2,"course C",20,50,&prof3,&group2);
    Course netbD(3,"course D",15,15,&prof4,&group3);
    Course netbE(4,"course E",40,20,&prof4,&group4);

    //asigning course to lectorers
    prof1.add_course(netbA);
    prof2.add_course(netbB);
    prof3.add_course(netbC);
    prof4.add_course(netbD);
    prof4.add_course(netbE);

    int arr_1[6][6];
        arr_1[0][0]=  1;
        arr_1[0][1]=  1;
        arr_1[0][2]=  1;
        arr_1[0][3]=  1;
        arr_1[5][0]=  1;
        arr_1[5][1]=  1;

    int arr_2[6][6];
        arr_2[4][0]=  1;
        arr_2[1][1]=  1;
        arr_2[1][2]=  1;
        arr_2[0][3]=  1;

    int arr_3[6][6];
        arr_3[0][0]=  1;
        arr_3[2][1]=  1;
        arr_3[3][2]=  1;
        arr_3[0][3]=  1;

    int arr_4[6][6];
        arr_4[1][0]=  1;
        arr_4[4][1]=  1;
        arr_4[4][2]=  1;
        arr_4[4][3]=  1;

    prof1.set_pref_matrix(arr_1);
    prof2.set_pref_matrix(arr_2);
    prof3.set_pref_matrix(arr_3);
    prof4.set_pref_matrix(arr_4);
    //------------------------------


    vector<Course*> courses_list;
        courses_list.push_back(&netbA);
        courses_list.push_back(&netbB);
        courses_list.push_back(&netbC);
        courses_list.push_back(&netbD);
        courses_list.push_back(&netbE);



    vector<Lecturer*> prof_list;
        prof_list.push_back(&prof1);
        prof_list.push_back(&prof2);
        prof_list.push_back(&prof3);
        prof_list.push_back(&prof4);

    list<int> h;
    list<list<int>>day;



    for(int i=0;i<= prof_list.size();i++)
    {
        for(int j = 0;j<6;j++)
        {
            for(int u = 0;u<6;u++)
            {
                if(prof_list[i]->get_pref_matrix(j,u) == prof_list[i]->get_pref_matrix(j,u++))
                {
                   ;
                }
                if(prof_list[i]->get_pref_matrix(j,u) == prof_list[i++]->get_pref_matrix(j,u))// CONFLICT INTE
                {
                    for(int v;v<= courses_list.size();v++)// number of courses
                    {
                        int course1 = prof_list[i]->get_course_id(v);// GET 1ST COURSE OF  PROF. 1
                        int course2 = prof_list[i++]->get_course_id(v);

                        for(int c = 0;c<=4;c++)
                        {
                            if((courses_list[c]->get_course_id() == course1) > (courses_list[c]->get_course_id() == course2))
                            {
                                //win

                            }
                            else if((courses_list[c]->get_course_id() == course1) == (courses_list[c]->get_course_id() == course2))
                            {
                                //conflict
                                ;
                            }
                            else //lose
                            {
                               ;
                            }
                        }
                    }

                }
                else// no match [0][1] != [0][1]
                {

                }
            }
        }
    }
    return 0;
}
