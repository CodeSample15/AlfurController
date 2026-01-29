#include <stdio.h>
#include <pthread.h>
#include "bluetooth.h"

#ifdef _WIN32
#define SLEEP_SEC(x) _sleep(x * 1000)
#else
#include <unistd.h>
#define SLEEP_SEC(x) sleep(x)
#endif

static simpleble_adapter_t _adapter;
static pthread_t _scan_thread;

static void adapter_on_scan_start(simpleble_adapter_t adapter, void* userdata);
static void adapter_on_scan_stop(simpleble_adapter_t adapter, void* userdata);
static void adapter_on_scan_found(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata);
static void adapter_on_scan_updated(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata);

/**
 * Check for adapters and set up adapter callbacks
 * 
 * returns 0 if success, 1 otherwise
*/
int ble_init() 
{
    //this function also runs an initialization routine on the underlying driver
    //IMPORTANT TO RUN FIRST
    size_t adapter_count = simpleble_adapter_get_count();
    if(adapter_count == 0) {
        printf("BLE - No adapter found!\n");
        return 1;
    }

    _adapter = simpleble_adapter_get_handle(0);
    if(_adapter == NULL) {
        printf("BLE - No adapter found!\n");
        return 1;
    }

    simpleble_adapter_set_callback_on_scan_start(_adapter, adapter_on_scan_start, NULL);
    simpleble_adapter_set_callback_on_scan_stop(_adapter, adapter_on_scan_stop, NULL);
    simpleble_adapter_set_callback_on_scan_found(_adapter, adapter_on_scan_found, NULL);
    simpleble_adapter_set_callback_on_scan_updated(_adapter, adapter_on_scan_updated, NULL);

    printf("BLE - Initialization successful!\n");

    return 0;
}

void ble_start_scan()
{
    printf("BLE - Scan started!\n");
    if(simpleble_adapter_scan_for(_adapter, 5000)==SIMPLEBLE_FAILURE) {
        printf("BLE - Scan failed!\n");
        return;
    }

    SLEEP_SEC(1);

    printf("BLE - Scan ended!\n");
}

//Callbacks pulled from the SimpleBLE example repo--------------------------------------------------
static void adapter_on_scan_start(simpleble_adapter_t adapter, void* userdata) {
    char* identifier = simpleble_adapter_identifier(adapter);

    if (identifier == NULL) {
        return;
    }

    printf("Adapter %s started scanning.\n", identifier);

    // Let's not forget to clear the allocated memory.
    simpleble_free(identifier);
}

static void adapter_on_scan_stop(simpleble_adapter_t adapter, void* userdata) {
    char* identifier = simpleble_adapter_identifier(adapter);

    if (identifier == NULL) {
        return;
    }

    printf("Adapter %s stopped scanning.\n", identifier);

    // Let's not forget to clear the allocated memory.
    simpleble_free(identifier);
}

static void adapter_on_scan_found(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata) {
    char* adapter_identifier = simpleble_adapter_identifier(adapter);
    char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
    char* peripheral_address = simpleble_peripheral_address(peripheral);

    if (adapter_identifier == NULL || peripheral_identifier == NULL || peripheral_address == NULL) {
        return;
    }

    printf("Adapter %s found device: %s [%s]\n", adapter_identifier, peripheral_identifier, peripheral_address);

    // Let's not forget to release the associated handles and memory
    simpleble_peripheral_release_handle(peripheral);
    simpleble_free(peripheral_address);
    simpleble_free(peripheral_identifier);
}

static void adapter_on_scan_updated(simpleble_adapter_t adapter, simpleble_peripheral_t peripheral, void* userdata) {
    char* adapter_identifier = simpleble_adapter_identifier(adapter);
    char* peripheral_identifier = simpleble_peripheral_identifier(peripheral);
    char* peripheral_address = simpleble_peripheral_address(peripheral);

    if (adapter_identifier == NULL || peripheral_identifier == NULL || peripheral_address == NULL) {
        return;
    }

    printf("Adapter %s updated device: %s [%s]\n", adapter_identifier, peripheral_identifier, peripheral_address);

    // Let's not forget to release the associated handles and memory
    simpleble_peripheral_release_handle(peripheral);
    simpleble_free(peripheral_address);
    simpleble_free(peripheral_identifier);
}