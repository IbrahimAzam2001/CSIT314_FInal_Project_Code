create database project_314;
use project_314;

create table teacher (
teacher_id int primary key,
teacher_firstname varchar (50),
teacher_lastname varchar(50),
teacher_email varchar(100),
teacher_password  varchar(50)
);

INSERT INTO teacher (teacher_id, teacher_firstname, teacher_lastname, teacher_email, teacher_password)
VALUES
  (27650428, 'asma' , 'sama','asmasama@gmail.com', 'asmr'),
  (26506896, 'omar', 'daoudi','omardaudi@gmail.com','umar');
  
  
create table student(
student_id int primary key,
student_firstname varchar (50),
student_lastname varchar(50),
student_email varchar(100),
student_password  varchar(50)
);

INSERT INTO student (student_id, student_firstname, student_lastname, student_email, student_password)
VALUES
  (123, 'John', 'Doe', 'johndoe@example.com', 'password1'),
  (456, 'Jane', 'Smith', 'janesmith@example.com', 'password2');
  
create table course(
course_id int primary key,
student_id int,
teacher_id int,
credits int,
prerequisite_course_id INT,

foreign key (student_id) references student(student_id),
foreign key (teacher_id) references teacher(teacher_id),
FOREIGN KEY (prerequisite_course_id) REFERENCES course(course_id)

);




create table parent(
parent_id int,
student_id int,
parent_firstname varchar (50),
parent_lastname varchar(50),
parent_email varchar(100),
parent_password  varchar(50),
primary key (parent_id),
foreign key (student_id) references student(student_id)

);


create table studentreport(
report_id int primary key,
student_id int,
teacher_id int,
parent_id int,
assessment int,
foreign key (student_id) references student(student_id),
foreign key (teacher_id) references teacher(teacher_id),
foreign key (parent_id) references parent(parent_id)

);

create table quiz(
quiz_id int primary key,
course_id int,
quiz_title varchar(50),
scheduled_time varchar (5),
foreign key  (course_id) references course(course_id)
);




