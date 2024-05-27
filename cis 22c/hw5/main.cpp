// CIS 22C - HW5 - Kanan Ibadzade

#include <iostream>
#include "siDset.h"
#include "sItem.h"

using namespace std;

//this is unordered one

siDset* siDset::unorderedUnion(const siDset* B) const {
    int a_max = this->getNum();
    int b_max = B->getNum();
    int a = 0;
    int b = 0;
    siDset* C = new siDset(); 
    
    for (int i = 0; i < this->getNum(); ++i) {
        C->append(this->get(i));
    }

    
    for (int i = 0; i < B->getNum(); ++i) {
        bool isDuplicate = false;
        for (int j = 0; j < C->getNum(); ++j) {
            if ((B->get(i))->id == (C->get(j))->id) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            C->append(B->get(i));
        }
    }

    return C; 
}





