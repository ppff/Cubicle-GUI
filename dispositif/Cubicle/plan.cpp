#include "plan.h"
Plan::Plan(){
    for(int i ; i<9 ; i++){
    Led l=new Led();
    Plan.led_list[i].fill(l,9);
    }
}
