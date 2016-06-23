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

insert into degrees (id, degree_name) values
        (DEFAULT, 'Computer Science');

insert into degrees (id, degree_name) values
        (DEFAULT, 'Software Engineering');

insert into degrees (id, degree_name) values
        (DEFAULT, 'Network Technologies');

alter sequence courses_id_seq MINVALUE 0;
alter sequence courses_id_seq restart with 0 increment by 1;
-- Dummy theory course --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, '<DUMMY_COURSE>', 1, 0, 1, 1, 0);

-- Theory Courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 (for Informatics)', 1, 25, 3, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 Lab (for Informatics)', 1, 30, 3, 1, 1);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture (for Informatics)', 2, 25, 1, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture Lab (for Informatics)', 2, 25, 1, 1, 3);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Algebra I (for Informatics)', 3, 25, 1, 1, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'History of Computing (for Informatics)', 4, 15, 8, 1, 0);

-- End for Informatics theory courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 (for Computer Science)', 1, 25, 1, 2, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 Lab (for CS)', 1, 25, 1, 2, 7);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture (for Computer Science)', 2, 25, 4, 2, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture Lab (for Computer Science)', 2, 25, 4, 2, 9);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Algebra I (for Computer Science)', 3, 25, 1, 2, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'History of Computing (for Computer Science)', 4, 25, 3, 2, 0);

-- End for Computer science theory courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 (for Software Engineering)', 1, 25, 1, 3, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 Lab (for Software Engineering)', 1, 25, 1, 3, 13);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture (for Software Engineering)', 2, 25, 1, 3, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture Lab (for Software Engineering)', 2, 25, 1, 3, 15);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Algebra I (for Software Engineering)', 3, 25, 1, 3, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'History of Computing (for Software Engineering)', 4, 25, 1, 3, 0);

-- End for Software Engineering theory courses --

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 (for Network Technologies)', 1, 25, 1, 4, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'C++ 101 Lab (for Network Technologies)', 1, 25, 1, 4, 19);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture (for Network Technologies)', 2, 15, 3, 4, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Computer Architecture Lab (for Network Technologies)', 2, 15, 3, 4, 21);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'Algebra I (for Network Technologies)', 3, 25, 2, 4, 0);

insert into courses (id, name, lecturer_id, enrolled_students, semester, degree_id, theory_course_id) values
    (DEFAULT, 'History of Computing (for Network Technologies)', 4, 25, 3, 4, 0);

-- End for Network Technologies theory courses --

create table schedules (
    id              serial primary key,
    timeslots      int[]  -- An int[6] array representing 6 lecture timeslots a day
);