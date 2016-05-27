#include "rn4020.h"
#include "../mcc_generated_files/mcc.h"
#include "../i2c/i2c_helpers.h"
#include "../helpers/helpers.h"
#include <string.h>

#define I2C_RETRY_MAX 5

remote_i2c_request_t remoteRequest;

uint8_t i2cTimeout;
I2C_MESSAGE_STATUS i2cStatus;

RN4020status_t bluetoothState;
RN4020status_t oldBluetoothState;

bool RN4020_WaitFor(const uint8_t* msg) {
    uint16_t timeout = UINT16_MAX;

    while (timeout-- && commandsCount == 0);

    if (timeout > 0)
        return (strcmp(EUSART_GetCommand(), msg) == 0);
    else
        return false;
}

bool RN4020_WakeModule() {
    if (!BT_WAKE_GetValue()) {
        RN4020_ClearInput();
        BT_WAKE_SetHigh();
        return RN4020_WaitFor(RN4020_CMD);
    }
    else
        return true;
}

bool RN4020_VerifyServices() {
    RN4020_ClearInput();
    RN4020_ListServices();

    // Check that both services (battery, vironmetre) exist
    if (RN4020_WaitFor(VIRONMETRE_SERVICE_ID_STR) &&
            RN4020_WaitFor(CONNECTION_VALUE_STR) &&
            RN4020_WaitFor(CONNECTION_CHAR_STR) &&
            RN4020_WaitFor(REQUEST_VALUE_STR) &&
            RN4020_WaitFor(ANSWER_VALUE_STR) &&
            RN4020_WaitFor(ANSWER_CHAR_STR) &&
            RN4020_WaitFor(BATTERY_SERVICE_ID) &&
            RN4020_WaitFor(BATTERY_VALUE_STR) &&
            RN4020_WaitFor(BATTERY_CHAR_STR) &&
            RN4020_WaitFor(RN4020_END)) {
        return true;
    }
    else {
        RN4020_ClearInput();
        return false;
    }
}

bool RN4020_AdvertisePresence() {
    printf("A,0600\r\n"); // Advertise only every 1536ms to keep avg current low
    return RN4020_WaitFor(RN4020_AOK);
}

void RN4020_ManageRequest() {
    uint8_t i = 0;

    switch (remoteRequest.status) {
        default:
        case NO_REQUEST:
            // No request, do nothing
            break;

        case REQUEST_NOT_PROCESSED:
            // Start I2C operation (need to change sync to async)

            i2cTimeout = 0;
            i2cStatus = I2C_MESSAGE_PENDING;

            while (!I2C_MasterQueueIsEmpty());

            switch (remoteRequest.data[0]) {
                case REQUEST_READ:
                    I2C_MasterRead(remoteRequest.data + 2,
                            remoteRequest.data[1],
                            sensorState.addr,
                            &i2cStatus);
                    remoteRequest.status = REQUEST_WORKING;
                    break;

                case REQUEST_WRITE:
                    I2C_MasterWrite(remoteRequest.data + 2,
                            remoteRequest.data[1],
                            sensorState.addr,
                            &i2cStatus);
                    remoteRequest.status = REQUEST_WORKING;
                    break;
                default:
                    break;
            }
            break;

        case REQUEST_WORKING:
            // Keep on working until the I2C request status changes  
            // wait for the message to be sent or status has changed.
            // Start timeout counter only when message started to send
            while (i2cStatus == I2C_MESSAGE_PENDING && sensorState.plugged);

            if (sensorState.plugged == false) {
                remoteRequest.status = REQUEST_FAIL;
                break;
            }

            if (i2cStatus != I2C_MESSAGE_PENDING) {
                if (i2cTimeout++ > I2C_RETRY_MAX)
                    remoteRequest.status = REQUEST_FAIL;
                else if (i2cStatus == I2C_MESSAGE_FAIL)
                    remoteRequest.status = REQUEST_FAIL;
                else if (i2cStatus == I2C_MESSAGE_COMPLETE)
                    remoteRequest.status = REQUEST_DONE;
            }
            break;

        case REQUEST_DONE:
            if (RN4020_WakeModule()) {
                // Notify all went well
                printf(RN4020_WRITE_CHAR, ANSWER_HANDLE);
                printf("%02X", remoteRequest.data[0]);
                printf("%02X", remoteRequest.data[1]);

                if (remoteRequest.data[0] == REQUEST_READ) {
                    for (i = 0; i < remoteRequest.data[1]; i++)
                        printf("%02X", remoteRequest.data[i + 2]);
                }

                RN4020_EXECCMD();
                if (RN4020_WaitFor(RN4020_AOK)) {
                    BT_WAKE_SetLow();
                    remoteRequest.status = NO_REQUEST;
                }
            }
            break;

        case REQUEST_FAIL:
            // TODO : Notify fail
            remoteRequest.status = NO_REQUEST;
            break;
    }
}

void RN4020_NotifyPlug() {

    if (RN4020_WakeModule()) {
        printf(RN4020_WRITE_CHAR, CONNECTION_HANDLE);
        printf("%02X", sensorState.plugged);
        if (sensorState.plugged)
            printf("%02X", sensorState.addr);
        RN4020_EXECCMD();
        RN4020_WaitFor(RN4020_AOK);
        BT_WAKE_SetLow();
    }
}

void RN4020_ClearInput() {
    while (commandsCount > 0)
        EUSART_GetCommand();
}

void RN4020_GetMessage() {
    uint8_t* command = NULL;
    uint16_t receivedHandle = 0;

    if (commandsCount > 0 && remoteRequest.status == NO_REQUEST) {
        command = EUSART_GetCommand();

        // Handle request
        if (startsWith(command, RN4020_REMOTE_VALUE_CHANGE)) {
            command = command + 3;
            receivedHandle = ASCIIToHex16(command);

            if (receivedHandle == REQUEST_HANDLE) {
                command = command + 5;
                remoteRequest.length = 0;

                do {
                    remoteRequest.data[remoteRequest.length++] = ASCIIToHex8(command);
                    command = command + 2;
                }
                while (*command != '.');

                remoteRequest.status = REQUEST_NOT_PROCESSED;
            }
        }
    }
}
