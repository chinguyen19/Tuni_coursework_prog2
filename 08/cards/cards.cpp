#include "cards.hh"

// TODO: Implement the methods here

// Constructor
Cards::Cards() : top_(nullptr) {}

// Get the topmost card for testing
Card_data* Cards::get_topmost() {
    return top_;
}

// Adds a new card with the given id as the topmost element
void Cards::add(int id) {
    Card_data* newCard = new Card_data{id, top_};
    top_ = newCard;
}

// Prints the content of the data structure with ordinal numbers
// from top to bottom
void Cards::print_from_top_to_bottom(std::ostream& s) {

    Card_data* current = top_;
    int index = 1;
    while (current != nullptr) {
        s << index << ": " << current->data << std::endl;
        current = current->next;
        index++;
    }
}

// Removes the topmost card and passes its id in the reference parameter
bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        return false;
    }

    id = top_->data;
    Card_data* temp = top_;
    top_ = top_->next;
    delete temp;
    return true;
}

// Moves the last element of the data structure as the first one
bool Cards::bottom_to_top() {
    if (top_ == nullptr || top_->next == nullptr) {
        return false;
    }

    Card_data* current = top_;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    Card_data* temp = current->next;
    current->next = nullptr;
    temp->next = top_;
    top_ = temp;
    return true;
}

// Moves the first element of the data structure as the last one
bool Cards::top_to_bottom() {
    if (top_ == nullptr || top_->next == nullptr) {
        return false;
    }

    Card_data* current = top_;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = top_;
    top_ = top_->next;
    current->next->next = nullptr;
    return true;
}

// Prints the content of the data structure with ordinal numbers
// from the last element to the top
void Cards::print_from_bottom_to_top(std::ostream& s) {

    recursive_print(top_, s);
}

// Recursive helper function for printing from bottom to top
int Cards::recursive_print(Card_data* top, std::ostream& s) {
    if (top == nullptr) {
        return 0;
    }

    int count = recursive_print(top->next, s);
    s << count + 1 << ": " << top->data << std::endl;
    return count + 1;
}

// Destructor
Cards::~Cards() {
    while (top_ != nullptr) {
        Card_data* temp = top_;
        top_ = top_->next;
        delete temp;
    }
}
