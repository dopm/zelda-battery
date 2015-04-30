/****
Copyright 2015 Alexej Magura

This file is a part of ZBatt

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****/
#include "main.hxx"
#include <iostream>

void disp(LPSYSTEM_POWER_STATUS spwr)
{
     struct hearts hrt;
     hrt.full = (char *)"+";
     hrt.empty = (char *)"-";
     if (spwr->BatteryFlag == 128) { // no system battery
	  for (int idx = 0; idx < 10; ++idx) {
	       if (idx % 2 == 0) {
		    std::cout << hrt.empty;
	       } else {
		    std::cout << hrt.full;
	       }
	  }
	  return;
     }

     if (spwr->BatteryLifePercent == 0) {
	  if (spwr->ACLineStatus != 255 && spwr->ACLineStatus) {
	       for (int hdx = 0; hdx < 10; ++hdx)
		    std::cout << (hdx < 9 ? hrt.empty : hrt.full);
	       return;
	  }
     }
     /* TODO implement remaining and expended */

     for (int jdx = 10; jdx <= spwr->BatteryLifePercent; jdx += 10)
	  std::cout << hrt.full;

     for (int kdx = spwr->BatteryLifePercent; kdx < 100; kdx += 10)
	  std::cout << hrt.empty;
}

int main(int argc, char **argv)
{

     SYSTEM_POWER_STATUS spwr;
     if (!GetSystemPowerStatus(&spwr))
	  goto fail;
     disp(&spwr);

win:
     return 0;
fail:
     return 1;
}
