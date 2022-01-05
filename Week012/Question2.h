// Question2.h

class GradeBook {
	private:
		char course_name[50];
		void set_course_name(char *newname) {strcpy(course_name, newname);}
		char lecturer_name[50];
		void set_lec_name(char *newname) {strcpy(lecturer_name, newname);}
	public:
		GradeBook(void) {
			pub_set_course_name();
			pub_set_lec_name();
		}

		void displayMessage(void) {
			std::cout << "Welcome to the Grade Book!" << std::endl;
			std::cout << "Course name: " << course_name << std::endl;
			std::cout << "Lecturer name: " << lecturer_name << std::endl;
		}

		void pub_set_lec_name(void) {
			std::cout << "Please type a new name for the lecturer: ";
			char tmp[50];
			std::cin >> tmp;
			set_lec_name(tmp);
		}

		void pub_get_lec_name(void) {
			std::cout << "The lecturer's name is: " << lecturer_name << std::endl;
		}

		void pub_set_course_name(void) {
			std::cout << "Please type a new name for the course: ";
			char tmp[50];
			std::cin >> tmp;
			set_course_name(tmp);
		}

		void pub_get_course_name(void) {
			std::cout << "The course name is: " << course_name << std::endl;
		}
};


