// Week9Question3.h


struct Sentence {
	char word[20];
	struct Sentence * next;
};
typedef struct Sentence sentence;
typedef sentence * sent_ptr;
sent_ptr head = NULL;


// Push a new word to the top of the stack.
sent_ptr pushWord(void) {
	sent_ptr newWord = (sentence *) malloc(sizeof(sentence));
	newWord->next = head;
	head = newWord;
	return head;
}

// Pop a word from the top of the stack.
sent_ptr popWord(sent_ptr popped) {
	head = head->next;
	return popped;
}

