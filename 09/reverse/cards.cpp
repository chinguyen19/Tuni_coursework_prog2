#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr) {
            // The deck is empty
            return false;
        }

        // Get the data of the topmost card
        id = top_->data;

        // Move the top pointer to the next card
        top_ = top_->next;

        return true;
}

void Cards::reverse()
{
    std::shared_ptr<Card_data> current = top_;
        std::shared_ptr<Card_data> prev = nullptr;
        std::shared_ptr<Card_data> next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        top_ = prev; // Set the top pointer to the new front of the reversed deck
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
