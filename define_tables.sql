/*  Run this with 'psql -d <db_name> -af <path_to_this_file>'
 *  You must first start 'psql' and create <db_name> manually
 *  before running this script. A suitable DB name could be
 *  something like 'courseinfo'.
 */

drop table lab_courses;
drop table theory_courses;
drop table lecturers;
drop table degrees;

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

create table theory_courses (
    id                          serial primary key,
    name                        text,
    lecturer_id                 integer,
    foreign key(lecturer_id)    references lecturers (id),
    enrolled_students           integer,
    semester                    integer,
    degree_id                   integer,
    foreign key(degree_id)      references degrees (id)
);

create table lab_courses (
    id                          integer,
    foreign key(id)             references theory_courses(id),
    name                        text,
    lecturer_id                 integer,
    foreign key(lecturer_id)    references lecturers (id)
);

-- Lecutrers -- 

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Fred', 'Flintstone', '{5,4,3,2,1,0}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Barny', 'Rubble', '{0,1,2,5,4,3}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Wilma', 'Flintstone', '{5,4,3,2,1,0}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Betty', 'Rubble', '{5,4,3,2,1,0}');

insert into lecturers (id, firstname, lastname, preference) values
        (DEFAULT, 'Mitko', 'Painera', '{5,4,0,1,3,2}');

-- Degrees --

insert into degrees (id, degree_name) values
        (DEFAULT, 'Informatics');

insert into degrees (id, degree_name) values
        (DEFAULT, 'Computer Science');

insert into degrees (id, degree_name) values
        (DEFAULT, 'Software Engineering');

insert into degrees (id, degree_name) values
        (DEFAULT, 'Network Technologies');

-- Theory Courses --

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'C++ 101 (for Informatics)', 1, 25, 1, 1);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Computer Arhitecture (for Informatics)', 2, 25, 1, 1);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Algebra I (for Informatics)', 3, 25, 1, 1);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'History of Computing (for Informatics)', 4, 25, 1, 1);

-- End for Informatics theory courses --

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'C++ 101 (for Computer Science)', 1, 25, 1, 2);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Computer Arhitecture (for Computer Science)', 2, 25, 1, 2);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Algebra I (for Computer Science)', 3, 25, 1, 2);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'History of Computing (for Computer Science)', 4, 25, 1, 2);

-- End for Computer science theory courses --

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'C++ 101 (for Software Engineering)', 1, 25, 1, 3);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Computer Arhitecture (for Software Engineering)', 2, 25, 1, 3);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Algebra I (for Software Engineering)', 3, 25, 1, 3);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'History of Computing (for Software Engineering)', 4, 25, 1, 3);

-- End for Software Engineering theory courses --

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'C++ 101 (for Network Technologies)', 1, 25, 1, 4);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Computer Arhitecture (for Network Technologies)', 2, 25, 1, 4);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'Algebra I (for Network Technologies)', 3, 25, 1, 4);

insert into theory_courses (id, name, lecturer_id, enrolled_students, semester, degree_id) values
    (DEFAULT, 'History of Computing (for Network Technologies)', 4, 25, 1, 4);

-- End for Network Technologies theory courses --

-- Lab Courses --

insert into lab_courses (id, name, lecturer_id) values
    (1, 'C++ Lab (for Informatics)', 1);

insert into lab_courses (id, name, lecturer_id) values
    (2, 'Computer Arhitecture Lab (for Informatics)', 2);

-- End for Informatics theory courses --

insert into lab_courses (id, name, lecturer_id) values
    (5, 'C++ Lab (for CS)', 1);

insert into lab_courses (id, name, lecturer_id) values
    (6, 'Computer Arhitecture Lab (for CS)', 2);

insert into lab_courses (id, name, lecturer_id) values
    (9, 'C++ Lab (for SE)', 1);

insert into lab_courses (id, name, lecturer_id) values
    (10, 'Computer Arhitecture Lab (for SE)', 2);

insert into lab_courses (id, name, lecturer_id) values
    (13, 'C++ Lab (for NT)', 1);

insert into lab_courses (id, name, lecturer_id) values
    (14, 'Computer Arhitecture Lab (for NT)', 2);