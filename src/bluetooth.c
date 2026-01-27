#include <stdio.h>
#include "bluetooth.h"

int check_for_ble_adapters() 
{
    //this function also runs an initialization routine on the underlying driver
    //IMPORTANT TO RUN FIRST
    size_t adapter_count = simpleble_adapter_get_count();
    if(adapter_count == 0) {
        printf("No BLE adapter found!\n");
        return 1;
    }

    return 0;
}