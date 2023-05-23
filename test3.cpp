#include <vector>
#include <iostream>

typedef std::vector<std::string> DonutBox;


void findBoxes(const DonutBox& box, DonutBox& current_box, std::vector<DonutBox>& boxes) {
    if (current_box.size() == box.size()) {
        boxes.push_back(current_box);
        return;
    }
    for (unsigned int i = 0; i < box.size(); i++) {
        bool contains = false;
        for (unsigned int j = 0; j < current_box.size(); j++) {
            if (current_box[j] == box[i]) {
                contains = true;
                break;
            }
        }

        if(!contains){
            current_box.push_back(box[i]);
        }
        else{
            continue;
        }
        findBoxes(box,current_box,boxes);
        current_box.pop_back();
    }
    return;

}

int main() {
    DonutBox donuts, tmp;
    std::vector<DonutBox> boxes;
    donuts.push_back("strawberry"); donuts.push_back("chocolate"); donuts.push_back("maple");
    findBoxes(donuts, tmp, boxes);
    for(int i = 0; i < boxes.size(); i++){
        std::cout << "HAHA: ";
        for(int j = 0; j < boxes[i].size(); j++){
            std::cout << boxes[i][j];
        }
        std::cout << "\n";
    }
}