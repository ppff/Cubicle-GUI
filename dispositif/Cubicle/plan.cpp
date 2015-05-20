#include "plan.h"
Plan::Plan(){
    for(int i ; i<9 ; i++){
    Led l=Led();
    this->led_list[i].fill(l,9);
    }
}
