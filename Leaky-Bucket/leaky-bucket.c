#include <stdio.h>

#define BUCKET_SIZE 10
#define OUT_PKT_SIZE 1

int main() {
    int storage = 0; // Initial packets in the bucket
    int queries;
    
    // Read the number of queries from the user
    printf("Enter the number of queries: ");
    scanf("%d", &queries);
    
    int packets[queries]; // Dynamically allocate array size based on user input
    
    // Read packet sizes from the user
    printf("Enter %d incoming packet sizes: ", queries);
    for (int i = 0; i < queries; i++) {
        scanf("%d", &packets[i]);
    }

    for (int i = 0; i < queries; i++) {
        int in_pkt_size = packets[i]; // Get the current incoming packet size
        int remaining = BUCKET_SIZE - storage;
        
        if (in_pkt_size <= remaining) {
            storage += in_pkt_size;
        } else {
            printf("\nPacket Loss!! %d\n", in_pkt_size - remaining);
            storage = BUCKET_SIZE; // Bucket is full
        }
        
        printf("\nBuffer Size = %d \nOutput Bucket Size = %d\n", storage, BUCKET_SIZE);
        
        if (storage >= OUT_PKT_SIZE) {
            storage -= OUT_PKT_SIZE;
        } else {
            storage = 0; // Prevent negative storage
        }
    }
    
    return 0;
}