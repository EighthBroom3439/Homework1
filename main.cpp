#include <iostream>
#include <vector>
#include "dz2.hpp"
#include <fstream>
#include <map>
#include <string>


void add_element(int value, NodeList& list) {
    switch (list.type) {
        case 1: {
            Node* new_node = new Node(value,nullptr, nullptr);
            if (list.head == nullptr) {
                list.last = new_node;
                list.head = list.last;
                list.last -> next = nullptr;
                return;
            }
            list.last->next = new_node;
            list.last = list.last->next;
            list.last -> next = nullptr;
        }
            break;
        case 2: {
            Node* new_node = new Node(value, nullptr,nullptr);
            if (list.head == nullptr) {
                list.last = new_node;
                list.head = list.last;
                list.last -> next = nullptr;
                return;
            }
            new_node->prev = list.last;
            list.last -> next = new_node;
            list.last = list.last->next;
            list.last -> next = nullptr;
        }
            break;
        case 3: {
            Node* new_node = new Node(value,nullptr, nullptr);
            if (list.head == nullptr) {
                list.last = new_node;
                list.head = list.last;
                list.last -> next = list.head;
                return;
            }
            list.last->next = new_node;
            list.last = list.last->next;
            list.last -> next = list.head;
        }
            break;
        case 4: {
            Node* new_node = new Node(value, nullptr,nullptr);
            if (list.head == nullptr) {
                list.last = new_node;
                list.head = list.last;
                list.last -> next = list.head;
                list.head -> prev = list.last;
                return;
            }
            new_node->prev = list.last;
            list.last -> next = new_node;
            list.last = list.last->next;
            list.last -> next = list.head;
            list.head -> prev = list.last;

        }
            break;
    }
}
void print_list(NodeList list) {
    if (list.head == nullptr && list.last == nullptr) {
        std::cout<<"Список пуст"<<std::endl;
    }else {
        switch (list.type) {
            case 1: {
                if (list.head == list.last) {
                    std::cout<<list.head->data;

                }
                else {
                    while (list.head != list.last) {
                        std::cout<<list.head->data<<" -> ";
                        list.head = list.head->next;
                    }
                    std::cout<<list.last->data;
                }
            }
                break;
            case 2: {
                if (list.head == list.last) {
                    std::cout<<list.head->data;
                }
                else {
                    while (list.head != list.last) {
                        std::cout<<list.head->data<<" <-> ";
                        list.head = list.head->next;
                    }
                    std::cout<<list.last->data;
                }
            }
                break;
            case 3: {
                if (list.head == list.last) {
                    std::cout<<list.head->data;
                }
                else {
                    Node* current = list.head;
                    do {
                        std::cout<<current->data<<" -> ";
                        current = current->next;
                    }while (current != list.last);
                    std::cout<<list.last->data;
                }
            }
                break;
            case 4: {
                if (list.head == list.last) {
                    std::cout<<list.head->data;
                }
                else {
                    Node* current = list.head;
                    do {
                        std::cout<<current->data<<" <-> ";
                        current = current->next;
                    }while (current != list.last);
                    std::cout<<list.last->data;
                }
            }
        }
    }
    std::cout<<std::endl;


}
void write_to_file(const NodeList& list, const std::string& filename) {
    std::ofstream file(filename);

    if (list.head!=nullptr && list.last!=nullptr) {
        switch (list.type) {
            case 1: {
                file << ">";
            }break;
            case 2: {
                file << "<>";
            }break;
            case 3: {
                file << ">0";
            }break;
            case 4: {
                file << "<>0";
            }break;
        }
    }
    file << '\n';
    Node* cur = list.head;
    while (cur!=list.last) {
        file<<cur->data<<' ';
        cur = cur -> next;
    }
    file<<cur->data<<' ';
    file.close();
}
void read_from_file(NodeList& list, const std::string& filename) {
    if (list.head != nullptr && list.last != nullptr) {
        std::cout << "Ошибка"<<std::endl;
        return;
    }
    std::ifstream file(filename);
    std::string stroka;
    bool fl = 0;
    std::vector <int> znaki;
    while (std::getline(file,stroka)) {
        if (fl==0) {
            if (stroka == ">") {
                list.type = 1;
            }
            else if (stroka == "<>") {
                list.type = 2;
            }
            else if (stroka == ">0") {
                list.type = 3;
            }
            else {
                list.type = 4;
            }
            fl = 1;
        }
        else {
            stroka+=' ';
            std::string buf;
            for (int i = 0; i < stroka.size(); i++) {
                if (stroka[i]!=' ') {
                    buf+=stroka[i];
                }
                else {
                    if (!buf.empty()) {
                        znaki.push_back(std::stoi(buf));
                        buf.clear();
                    }
                }
            }
        }
    }
    for (auto n: znaki){add_element(n,list);}
}
std::vector<int> find_value(int value, NodeList list) {
    std::vector<int> numbers;
    if (list.head == nullptr) {
        return numbers;
    }
    int pos = 0;
    Node* current = list.head;
    if (list.type == 3 || list.type == 4) {
        do {
            if (value == current->data) {
                numbers.push_back(pos);
            }
            ++pos;
            current = current->next;
        } while (current != list.head);
    } else {
        while (current != nullptr) {
            if (value == current->data) {
                numbers.push_back(pos);
            }
            pos++;
            current = current->next;
        }
    }
    return numbers;
}
void delete_element(int value, NodeList& list) {
    if (list.head == nullptr) {
        std::cout << "Ne nashli" << std::endl;
        return;
    }
    std::vector<int> t = find_value(value, list);
    if (t.empty()) {
        std::cout << "Ne nashli" << std::endl;
        return;
    }
    Node* current = list.head;
    while (current->data != value) {
        current = current->next;
    }

    switch (list.type) {
        case 1: {
            if (current == list.head && current == list.last) {
                delete current;
                list.head = nullptr;
                list.last = nullptr;
                return;
            }
            if (current == list.head) {
                list.head = current->next;
                delete current;
            } else if (current == list.last) {
                Node* current_back = list.head;
                while (current_back->next != current) {
                    current_back = current_back->next;
                }
                current_back->next = nullptr;
                list.last = current_back;
                delete current;
            } else {
                Node* current_back = list.head;
                while (current_back->next != current) {
                    current_back = current_back->next;
                }
                current_back->next = current->next;
                delete current;
            }
        } break;
        case 2: {
            if (current == list.head && current == list.last) {
                delete current;
                list.head = nullptr;
                list.last = nullptr;
                return;
            }
            if (current == list.head) {
                list.head = current->next;
                list.head->prev = nullptr;
                delete current;
            } else if (current == list.last) {
                Node* current_back = current->prev;
                current_back->next = nullptr;
                list.last = current_back;
                delete current;
            } else {
                Node* current_back = current->prev;
                current_back->next = current->next;
                current->next->prev = current_back;
                delete current;
            }
        } break;
        case 3: {
            if (current == list.head && current == list.last) {
                delete current;
                list.head = nullptr;
                list.last = nullptr;
                return;
            }
            if (current == list.head) {
                list.head = list.head->next;
                list.last->next = list.head;
                delete current;
            } else if (current->next == list.head) {
                Node* current_back = list.head;
                while (current_back->next != current) {
                    current_back = current_back->next;
                }
                current_back->next = list.head;
                list.last = current_back;
                delete current;
            } else {
                Node* current_back = list.head;
                while (current_back->next != current) {
                    current_back = current_back->next;
                }
                current_back->next = current->next;
                delete current;
            }
        } break;
        case 4: {
            if (current == list.head && current == list.last) {
                delete current;
                list.head = nullptr;
                list.last = nullptr;
                return;
            }
            if (current == list.head) {
                list.head = current->next;
                list.head->prev = list.last;
                list.last->next = list.head;
                delete current;
            } else if (current->next == list.head) {
                Node* current_back = current->prev;
                current_back->next = list.head;
                list.head->prev = current_back;
                list.last = current_back;
                delete current;
            } else {
                Node* current_back = current->prev;
                current_back->next = current->next;
                current->next->prev = current_back;
                delete current;
            }
        } break;
    }
}


void clear_list(NodeList& list) {
    if (list.head == nullptr) {
        list.last = nullptr;
        return;
    }
    Node* current = list.head;
    while (current!=list.last) {
        Node* temp = current;
        current = current -> next;
        delete temp;
    }
    delete list.last;
    list.head = nullptr;
    list.last = nullptr;
}

int main(int argc,char* argv[]) {
    if (argc > 7) {std::cout<<"Дали не те аргументы!";return 1;}
    if (argv[1][0] != '-' or argv[1][1] != 't' or argv[1][2] != '\0' or argv[2][1] != '\0') {
        std::cout<<"Дали не те аргументы!";
        return 1;
    }
    if (argv[2][0] != '1' and argv[2][0] != '2' and argv[2][0] != '3' and argv[2][0] != '4') {
        std::cout<<"Дали не те аргументы!";
        return 1;
    }
    int listtype = std::stoi(argv[2]);
    if (argv[3][0] != '-' or argv[3][1] != 'c' or argv[3][2] != '\0') {
        std::cout<<"Дали не те аргументы!";
        return 1;
    }
    int dlina = std::stoi(argv[4]);
    if (argv[5][0] != '-' or argv[5][1] != 'e' or argv[5][2] != '\0') {
        std::cout<<"Дали не те аргументы!";
        return 1;
    }
    if (argc == 6 and dlina != 0) {
        std::cout<<"Дали не те аргументы!";
        return 1;
    }
    std::vector<int> zn;
    if (argc == 7) {
        std::string temp = argv[6];
        temp+=',';
        std::string buffer;
        for (auto n: temp) {
            if (n != ',') {
                buffer+=n;
            }else {
                zn.push_back(std::stoi(buffer));
                buffer.clear();
            }
        }
        if (zn.size() != dlina) {
            std::cout<<"Количество элементов не совпадает с данной длинной!";
            return 1;
        }
    }
    NodeList lister = {nullptr,nullptr,dlina,listtype};
    for (int i = 0; i < dlina; i++) {
        add_element(zn[i],lister);
    }
    int n = 0;
    std::string filename;
    std::cout<<"Enter the number of command which you desire:"<<std::endl;
    std::cout<<"1 - Add an element to the list"<<std::endl;
    std::cout<<"2 - Print the list"<<std::endl;
    std::cout<<"3 - Search for the element"<<std::endl;
    std::cout<<"4 - Delete the single element"<<std::endl;
    std::cout<<"5 - Delete the multiple elements"<<std::endl;
    std::cout<<"6 - Clear the list"<<std::endl;
    std::cout<<"7 - Write the list to a file"<<std::endl;
    std::cout<<"8 - Read the list from the file"<<std::endl;
    std::cout<<"0 - Exit the programm"<<std::endl;
    do {
        std::cout<<"Enter the command: ";
        std::cin>>n;std::cout<<std::endl;
        int el;
        switch (n) {
            case 1: {
                std::cout<<"Enter the element: ";std::cin>>el;std::cout<<std::endl;
                add_element(el,lister);
                break;
            }
            case 2: {
                print_list(lister);
                break;
            }
            case 3: {
                std::cout<<"Enter the element: ";std::cin>>el;std::cout<<std::endl;
                std::vector<int> adr = find_value(el,lister);
                if (!adr.empty()) {
                    for (int j = 0; j < adr.size();j++) {
                        std::cout<<adr[j]<<" ";
                    }
                    std::cout<<std::endl;
                }else {
                    std::cout<<"There is no such element in the list!"<<std::endl;
                }
                break;
            }
            case 4: {
                std::cout<<"Enter the element: ";std::cin>>el;std::cout<<std::endl;
                std::vector<int> adr = find_value(el,lister);
                if (!adr.empty()) {
                    delete_element(el,lister);
                }else {
                    std::cout<<"There is no such element in the list!"<<std::endl;
                }
                break;
            }
            case 5: {
                std::cout<<"Enter the element: ";std::cin>>el;std::cout<<std::endl;
                std::vector<int> adr = find_value(el,lister);
                if (!adr.empty()) {
                    while (adr.size() > 0) {
                        delete_element(el,lister);
                        adr = find_value(el,lister);
                    }
                }else {
                    std::cout<<"There is no such element in the list!"<<std::endl;
                }
                break;
            }
            case 6: {
                clear_list(lister);
                break;
            }
            case 7: {
                std::getline(std::cin,filename);
                std::cout<<"Enter the name of your file: ";
                std::getline(std::cin,filename);
                std::cout<<std::endl;
                write_to_file(lister,filename);
                break;
            }
            case 8: {
                std::getline(std::cin,filename);
                std::cout<<"Enter the name of your file: ";std::getline(std::cin,filename);std::cout<<std::endl;
                read_from_file(lister,filename);
                break;
            }
            case 0: {
                std::cout<<"The programm is shuttind down"<<std::endl;
            }
            default: {
                std::cout<<"Wrong move, friendo"<<std::endl;
            }
        }
    }while (n!=0);



    return 0;
}
