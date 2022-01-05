// Question2.h




int user_input_int(void) {
	char input[100];
	fflush(stdin);
	fgets(input, 99, stdin);
	return atoi(input);
}


void clear(void) {for(int i = 0; i < 100; i++) {printf("\n");}}


size_t * bubble_sort(size_t m[]) {
	for(int i = 50; 0 <= i; i--) {
		for(int j = i; 50 > j + 1; j++) {
			if(m[j] > m[j + 1]) {
				// Switch them.
				size_t temp =  m[j];
				m[j] = m[j + 1];
				m[j + 1] = temp;
			}
		}
	}
	return m;
}


size_t * selection_sort(size_t m[]) {
	for(int i = 0; 50 > i; i++) {
		int smol = i;
		for(int j = i; 50 > j; j++) {
			if(m[j] < m[smol]) {
				smol = j;
			}
		}
		// Switch them.
		size_t temp = m[smol];
		m[smol] = m[i];
		m[i] = temp;
	}
	return m;
}


size_t * insertion_sort(size_t m[]) {
	for(int i = 1; i < 50; i++) {
		for(int j = i; j > 0 && m[j - 1] > m[j]; j--) {
			size_t temp = m[j - 1];
			m[j - 1] = m[j];
			m[j] = temp;
		}
	}
	return m;
}


