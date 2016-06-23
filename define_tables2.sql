/*  Run this with 'psql -d <db_name> -af <path_to_this_file>'
 *  You must first start 'psql' and create <db_name> manually
 *  before running this script. A suitable DB name could be
 *  something like 'courseinfo'.
 */

drop table courses;
drop table lecturers;
drop table degrees;
drop table schedules;

create table lecturers (
    id              serial primary key,
    firstname       text,
    lastname        text,
    preference      int[]  -- An int[6] array representing 6 lecture timeslots a day
);

create table degrees (
    id              serial primary key,
    degree_name     text
);

create table courses (
    id                          serial primary key,
    name                        text,
    lecturer_id                 integer,
    foreign key(lecturer_id)    references lecturers (id),
    enrolled_students           integer,
    semester                    integer,
    degree_id                   integer,
    foreign key(degree_id)      references degrees (id),
    theory_course_id            integer,
    foreign key(theory_course_id) references courses (id)
);



-- Lecutrers -- 

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Fred', 'Flintstone', '{0,4,2,3,5,1}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Barny', 'Rubble', '{0,1,2,5,4,3}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Wilma', 'Flintstone', '{2,4,0,2,5,3}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Betty', 'Rubble', '{0,4,2,3,5,1}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Mitko', 'Painera', '{3,4,0,1,5,2}');

-- Degrees --

insert into degrees (id, degree_name) values
        (DEFAULT, 'Informatics');

alter sequence courses_id_seq MINVALUE 0;
alter sequence courses_id_seq restart with 0 increment by 1;
-- Dummy theory course --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, '<DUMMY_COURSE>', 1, 0, 1, 1, 0);

-- Theory Courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 01', 1, 25, 1, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 01 Lab', 1, 10, 1, 1, 1);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 02', 2, 5, 1, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 02 Lab', 2, 5, 1, 1, 3);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 03', 3, 15, 1, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 04', 4, 5, 1, 1, 0);

-- End for Informatics theory courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 05', 1, 20, 2, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 05 Lab', 1, 14, 2, 1, 7);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 06', 2, 12, 2, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 06 Lab', 2, 12, 2, 1, 9);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 07', 3, 4, 2, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 08', 4, 4, 2, 1, 0);

-- End for Computer science theory courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 09', 1, 18, 3, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 09 Lab', 1, 18, 3, 1, 13);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 10', 2, 22, 3, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 10 Lab', 2, 22, 3, 1, 15);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 11', 3, 4, 3, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 12', 4, 4, 3, 1, 0);

-- End for Software Engineering theory courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 13', 1, 9, 4, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 13 Lab', 1, 10, 4, 1, 19);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 14', 2, 5, 4, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 14 Lab', 2, 25, 4, 1, 21);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 15', 3, 2, 4, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Course 16', 4, 17, 4, 1, 0);

-- End for Network Technologies theory courses --


create table schedules (
    id              serial primary key,
    timeslots      int[]  -- An int[6] array representing 6 lecture timeslots a day
);