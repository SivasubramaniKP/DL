
struct student {
        int id;
        string name<50>;
        int age;
};

program STUDENT_PROG {
        version STUDENT_VERS {
                int create(student) = 1;
                student read(int) = 2;
        } = 1;
} = 0x01234567;
