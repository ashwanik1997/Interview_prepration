/******************************************************************************
* @file memory_operation.c
* @author Ashwani Kesharwani
* @brief This program will provide you a hardware actraction layer.
* It is easy to post for any micro controller driver.
* 
* @version 1.0
* @note read write operations for pages, sectors and bug fixing under process. 
*******************************************************************************/
// Include 
#include <stdio.h>
#include <stdint.h>

#define DEBUG  // enable debug prints

#ifdef DEBUG
#define PRINTF(fmt, arg...) printf(fmt, ##arg)
#else
#define PRINTF(fmt, arg...) do {} while(0)
#endif

#define INITIALIZED         (0u)
#define INVALID             (-1u)
#define ERROR               (1u)

#define MEM_OK          (0u)
#define MEM_NOK         (1u)

#define PAGE_SIZE       (256u)
#define SECTOR_SIZE     (4096u)
#define BLOCK_SIZE      (16*SECTOR_SIZE)

typedef int32_t ret_t;
int32_t nvm_init(void);
int32_t nvm_deinit(void);
int32_t nvm_read(uint32_t address, void *buffer, size_t size);
int32_t nvm_write(uint32_t address, const void *data, size_t size);

typedef enum {
    IDLE_STATE,
    INIT_STATE,
    DEINIT_STATE,
    READ_WRITE_STATE,
    ERROR_STATE,
} mem_state_t;

typedef struct Operation {
    int32_t (*memory_Init) (void);
    int32_t (*memory_Deinit) (void);
    int32_t (*memory_Read)(uint32_t, void *,size_t );
    int32_t (*memory_Write)(uint32_t, const void *,size_t );  
} operation_t ;

static mem_state_t mem_state = IDLE_STATE;
operation_t opt = {
    .memory_Init    = nvm_init,     /*port your init function here */
    .memory_Deinit  = nvm_deinit,  /* port your deinit function here */ 
    .memory_Read    = nvm_read,    /* port your read function here */
    .memory_Write   = nvm_write    /* port your write function here */
};

int32_t memory_Init(void)
{
    if (mem_state != IDLE_STATE) {
        return INVALID;
    }
    ret_t result = opt.memory_Init();  // Call the function
    if (result == MEM_OK) {
        mem_state = INIT_STATE;
    } else {
        mem_state = ERROR_STATE;
    }
    
    return result;
}

int32_t memory_deinit(void)
{
    if (mem_state != INIT_STATE) {
        return INVALID;
    }
    ret_t result = opt.memory_Deinit();  // Call the function
    if (result == MEM_OK) {
        mem_state = IDLE_STATE;
    } else {
        mem_state = ERROR_STATE;
    }
  
    return result;  
}

int32_t memory_read(uint32_t address, void *buffer, size_t size)
{
    if(mem_state != READ_WRITE_STATE) {
        return INVALID;
    }
    return opt.memory_Read(address, buffer, size);
}

int32_t memory_write(uint32_t address, const void *data, size_t size)
{
    if(mem_state != READ_WRITE_STATE) {
        return INVALID;
    }
    return opt.memory_Write(address, data, size);
}

int32_t start_memory_operation(void)
{
    if(mem_state != INIT_STATE) {
        return INVALID;
    }
    mem_state = READ_WRITE_STATE;
    return MEM_OK;
}

int main()
{
    PRINTF("=>>Memory operation starts from here\n");

    // Example usage
    if (memory_Init() == MEM_OK) {
        PRINTF("=>>Memory initialized successfully\n");
        if (start_memory_operation() == MEM_OK) {
            PRINTF("=>>Memory operation started\n");

            // Perform read/write operations here
            uint32_t address = 0x1000;
            uint8_t buffer[256];
            const uint8_t data[256] = {5, 2, 3, 8, 5};  // Example data

            if (memory_write(address, data, sizeof(data)) == MEM_OK) {
                PRINTF("=>>Memory write successful\n");
            } else {
                PRINTF("=>>Memory write failed\n");
            }

            if (memory_read(address, buffer, sizeof(buffer)) == MEM_OK) {
                PRINTF("=>>Memory read successful\n");
                // Print the read data
                PRINTF("=>>Read data: ");
                for (size_t i = 0; i < sizeof(buffer); ++i) {
                    PRINTF("%d ", buffer[i]);
                }
                PRINTF("\n");
            } else {
                PRINTF("=>>Memory read failed\n");
            }
        }
        if (memory_deinit() == MEM_OK) {
            PRINTF("=>>Memory deinitialized successfully\n");
        }
    }

    return 0;
}

int32_t nvm_init(void)
{
    PRINTF("=>>nvm_init called\n");
    return MEM_OK;  // Return a value
}

int32_t nvm_deinit(void)
{
    PRINTF("=>>nvm_deinit called\n");
    return MEM_OK;  // Return a value
}

int32_t nvm_read(uint32_t address, void *buffer, size_t size)
{
    PRINTF("=>>nvm_read called\n");
    // Simulate reading data
    for (size_t i = 0; i < size; ++i) {
        ((uint8_t *)buffer)[i] = i % 256;  // Example data
    }
    return MEM_OK;  // Return a value
}

int32_t nvm_write(uint32_t address, const void *data, size_t size)
{
    PRINTF("=>>size of data %ld and address: %d\n", size,  address);
    PRINTF("=>>nvm_write called\n");
    // Simulate writing data
    for (size_t i = 0; i < size; ++i) {
        PRINTF("=>>Writing %d to address %ld\n", ((const uint8_t *)data)[i], address + i *sizeof(int));
    }
    return MEM_OK;  // Return a value
}
