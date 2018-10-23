#include <bits/stdc++.h>
#include <header.h>

using namespace std;

class SinglyLinkedListNode {
	public:
		int data;
		SinglyLinkedListNode *next;

		SinglyLinkedListNode(int node_data) {
			this->data = node_data;
			this->next = nullptr;
		}
};

class SinglyLinkedList {
	public:
		SinglyLinkedListNode *head;
		SinglyLinkedListNode *tail;

		SinglyLinkedList() {
			this->head = nullptr;
			this->tail = nullptr;
		}

		void insert_node(int node_data) {
			SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

			if (!this->head) {
				this->head = node;
			} else {
				this->tail->next = node;
			}

			this->tail = node;
		}
};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
	while (node) {
		fout << node->data;

		node = node->next;

		if (node) {
			fout << sep;
		}
	}
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
	while (node) {
		SinglyLinkedListNode* temp = node;
		node = node->next;

		free(temp);
	}
}
SinglyLinkedListNode * reversed(SinglyLinkedListNode * head)
{
	SinglyLinkedListNode * p = nullptr;
	SinglyLinkedListNode * c = head;

	while(c != nullptr)
	{
		SinglyLinkedListNode * n = c->next;
		c->next = p;
		p = c;
		c = n;
	}
	return p;
}

int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2)
{
	/// copy list2
	SinglyLinkedList* list2 = new SinglyLinkedList();
	SinglyLinkedListNode * head22 = head2;
	while(head22 != nullptr)
	{
		list2->insert_node(head22->data);
		head22 = head22->next;
	}
	SinglyLinkedListNode * head222 = list2->head;



	SinglyLinkedListNode* h1 = reversed(head1);
	SinglyLinkedListNode* h2 = reversed(head222);
	std::cout << h1->data << h2->data << std::endl;
	while(h1->next && h2->next && (h1->next->data == h2->next->data) && (h1->next->next || h2->next->next))
	{
		h1 = h1->next;
		h2 = h2->next;
		std::cout << h1->data << h2->data << std::endl;
	}
	return h1->data;
}

int merge()
{
	const std::string project = ""; //balanced
	const std::string fileNum = "00";

	std::ofstream fout(prePath + project + fileNum + "out.txt");
	std::ifstream inStr(prePath + project + fileNum + ".txt");

	int tests;
	inStr >> tests;
	inStr.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
		int index;
		inStr >> index;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		SinglyLinkedList* llist1 = new SinglyLinkedList();

		int llist1_count;
		inStr >> llist1_count;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i = 0; i < llist1_count; i++) {
			int llist1_item;
			inStr >> llist1_item;
			inStr.ignore(numeric_limits<streamsize>::max(), '\n');

			llist1->insert_node(llist1_item);
		}

		SinglyLinkedList* llist2 = new SinglyLinkedList();

		int llist2_count;
		inStr >> llist2_count;
		inStr.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i = 0; i < llist2_count; i++) {
			int llist2_item;
			inStr >> llist2_item;
			inStr.ignore(numeric_limits<streamsize>::max(), '\n');

			llist2->insert_node(llist2_item);
		}

		SinglyLinkedListNode* ptr1 = llist1->head;
		SinglyLinkedListNode* ptr2 = llist2->head;

		for (int i = 0; i < llist1_count; i++) {
			if (i < index) {
				ptr1 = ptr1->next;
			}
		}

		for (int i = 0; i < llist2_count; i++) {
			if (i != llist2_count-1) {
				ptr2 = ptr2->next;
			}
		}

		ptr2->next = ptr1;

		int result = findMergeNode(llist1->head, llist2->head);

		fout << result << "\n";
	}

	fout.close();
	std::cout << areEqualFiles(prePath + project + fileNum + "out.txt",
							   prePath + project + fileNum + "output.txt") << std::endl;

	return 0;
}
