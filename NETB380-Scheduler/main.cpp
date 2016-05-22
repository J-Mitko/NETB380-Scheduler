#include <QCoreApplication>
#include <iostream>

#include<course.h>
#include<lecturer.h>

using namespace std;

int main()
{
    Lecturer prof1(0,"prof1");
    Lecturer prof2(1,"prof2");
    Lecturer prof3(2,"prof3");
    Lecturer prof4(3,"prof4");


    Course netbA(0,"course A",9 ,15,&prof1);
    Course netbB(1,"course B",10,15,&prof2);
    Course netbC(2,"course C",20,50,&prof3);
    Course netbD(3,"course D",15,15,&prof4);
    Course netbE(4,"course E",40,20,&prof4);

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

    for(unsigned int i=0;i < prof_list.size();i++)//for every profesor
    {
        for(unsigned int j=i+1;j < prof_list.size();j++)//for every other we compare with profesor
        {
            for(int day1=0;day1 < 6;day1++)//for every day
            {
                for(int u=0;u < 6;u++)//for every hour
                {
                    if(prof_list[i]->get_pref_matrix(day1,u) ==1)//if the professor cares
                    {
                        if(prof_list[i]->get_pref_matrix(day1,u) == prof_list[j]->get_pref_matrix(day1,u))//if another professor also cares
                        {
                            //cout << "conflict" << endl;
                            int counter = prof_list[i]->get_num_of_courses();
                            for( int v=0;v < counter;v++)// THE REAL number of courses that the professor cares about
                            {
                                //int course1 = prof_list[i]->get_course_id(v);// GET 1ST COURSE OF PROF. 1 << for real shot down this line!
                                int course2;
                                int course1 = prof_list[i]->get_course(v)->get_number_students(); //profesor -> course -> num_of_students BUT YOU WANT TO DIG TO CHINA!!!

                                for( int c=0;c < counter;c++)
                                {
                                    course2 = prof_list[j]->get_course(c)->get_number_students(); //again but for the second guy lets name him J cuz he is cool
                                    if((course1) >  course2)
                                    {
                                        cout << "win"<< endl;

                                    }
                                    else if(course1 == course2)
                                    {
                                        cout<< "conflict"<< endl;
                                    }
                                    else
                                    {
                                        cout << "lose"<< endl;
                                    }

                                }

                            }
                        }
                        else
                        {
                            //cout << "no conflict" << endl;

                        }
                    }

                }
            }
        }
    }
    //fuck this for real :D kak shte go splitvash ne te znam bro :D
    return 0;
}
