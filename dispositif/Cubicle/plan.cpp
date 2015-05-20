#include "plan.h"

Plan::Plan()
{

        for (int i=0; i<9; i++)
            Led l=new Led();
           Plan.led_list[i].fill(l, 9);

}

