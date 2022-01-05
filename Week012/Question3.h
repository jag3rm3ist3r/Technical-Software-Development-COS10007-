// Question3.h


class Rectangle {
	protected:
		size_t length;
		size_t width;

	public:
		// Constructor.
		Rectangle(size_t l, size_t w) {
			pub_set_length(l);
			pub_set_width(w);
		}
		Rectangle(void) {
			std::cout << "What is the length? ";
			ui_set_length();
			std::cout << "What is the width? ";
			ui_set_width();
		}

		// Setting side lengths.
		// length
		void pub_set_length(size_t d) {length = d;}
		void ui_set_length(void) {
			size_t tmp;
			std::cin >> tmp;
			pub_set_length(tmp);
		}
		// Width
		void pub_set_width(size_t d) {width = d;}
		void ui_set_width(void) {
			size_t tmp;
			std::cin >> tmp;
			pub_set_width(tmp);
		}

		// Getting side lengths.
		// Length
		size_t pub_get_length(void) {return length;}
		void ui_get_length(void) {
			std::cout << "The length is: " << pub_get_length() << std::endl;
		}
		// Width
		size_t pub_get_width(void) {return width;}
		void ui_get_width(void) {
			std::cout << "The width is: " << pub_get_width() << std::endl;
		}
		// Area
		size_t pub_get_area(void) {
			return length * width;
		}
		void ui_get_area(void) {
			std::cout << "The area is: " << pub_get_area() << std::endl;
		}
};

class Box : Rectangle {
	protected:
		size_t depth;

	public:
		// Constructors.
		Box(size_t l, size_t w, size_t d) : Rectangle(l, w) {
			pub_set_depth(d);
		}
		Box(void) {
			std::cout << "What is the depth? ";
			ui_set_depth();
		}

		// Setting depth.
		void pub_set_depth(size_t d) {depth = d;}
		void ui_set_depth(void) {
			size_t tmp;
			std::cin >> tmp;
			pub_set_depth(tmp);
		}

		// Getting depth.
		size_t pub_get_depth(void) {return depth;}
		void ui_get_depth(void) {
			std::cout << "The depth is: " << pub_get_depth() << std::endl;
		}

		// Getting derived values.
		// Volume
		size_t pub_get_volume() {
			return pub_get_length() * pub_get_width() * pub_get_depth();
		}
		void ui_get_volume(void) {
			std::cout << "The volume is: " << pub_get_volume() << std::endl;
		}
		// Area
		size_t pub_get_area() {
			return	pub_get_length() * pub_get_width() * 2 +
					pub_get_length() * pub_get_depth() * 2 +
					pub_get_width() * pub_get_depth() * 2;
		}
		void ui_get_area(void) {
			std::cout << "The area is: " << pub_get_area() << std::endl;
		}
};


