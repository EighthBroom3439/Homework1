//
// Created by internet on 25.11.2025.
//

#ifndef D32_DZ2_HPP
#define D32_DZ2_HPP

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};
struct NodeList {
    Node* head = nullptr;
    Node* last = nullptr;
    int size = 0;
    int type = 0;
};
void add_element(int);
void print_list(struct NodeList*);
std::vector<int> find_value(int, NodeList);
void delete_element(int, NodeList&);
void clear_list(struct NodeList&);
void write_to_file(const NodeList&,const std::string&);
void read_from_file(NodeList&, const std::string&);
#endif //D32_DZ2_HPP