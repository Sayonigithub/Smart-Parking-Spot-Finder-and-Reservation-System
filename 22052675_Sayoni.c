#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_SPOTS 5

// Structure for Parking Spot
struct ParkingSpot {
    int id;
    int x;
    int y;
    int available; // 1 = available, 0 = reserved
};

// Initialize parking spots with dummy data
struct ParkingSpot parkingSpots[MAX_SPOTS] = {
    {1, 0, 0, 1},
    {2, 10, 10, 1},
    {3, 5, 5, 1},
    {4, 8, 8, 1},
    {5, 3, 6, 1}
};

// Calculate Euclidean distance
double calculate_distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Find the nearest available parking spot
int find_nearest_spot(int x, int y) {
    int nearest_id = -1;
    double min_distance = DBL_MAX;

    for (int i = 0; i < MAX_SPOTS; i++) {
        if (parkingSpots[i].available) {
            double distance = calculate_distance(x, y, parkingSpots[i].x, parkingSpots[i].y);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_id = parkingSpots[i].id;
            }
        }
    }
    return nearest_id;
}

// Reserve a parking spot
void reserve_spot(int id) {
    for (int i = 0; i < MAX_SPOTS; i++) {
        if (parkingSpots[i].id == id) {
            if (parkingSpots[i].available) {
                parkingSpots[i].available = 0;
                printf("Parking spot %d reserved successfully.\n", id);
            } else {
                printf("Parking spot %d is already reserved.\n", id);
            }
            return;
        }
    }
    printf("Parking spot %d not found.\n", id);
}

// Release a parking spot
void release_spot(int id) {
    for (int i = 0; i < MAX_SPOTS; i++) {
        if (parkingSpots[i].id == id) {
            if (!parkingSpots[i].available) {
                parkingSpots[i].available = 1;
                printf("Parking spot %d released successfully.\n", id);
            } else {
                printf("Parking spot %d is already available.\n", id);
            }
            return;
        }
    }
    printf("Parking spot %d not found.\n", id);
}

// Display all parking spots sorted by distance from a given point
void display_sorted_spots(int x, int y) {
    struct ParkingSpot sortedSpots[MAX_SPOTS];
    for (int i = 0; i < MAX_SPOTS; i++) {
        sortedSpots[i] = parkingSpots[i];
    }

    // Bubble Sort based on distance
    for (int i = 0; i < MAX_SPOTS - 1; i++) {
        for (int j = 0; j < MAX_SPOTS - i - 1; j++) {
            double dist1 = calculate_distance(x, y, sortedSpots[j].x, sortedSpots[j].y);
            double dist2 = calculate_distance(x, y, sortedSpots[j + 1].x, sortedSpots[j + 1].y);
            if (dist1 > dist2) {
                struct ParkingSpot temp = sortedSpots[j];
                sortedSpots[j] = sortedSpots[j + 1];
                sortedSpots[j + 1] = temp;
            }
        }
    }

    // Display sorted spots
    printf("Parking spots sorted by distance from (%d, %d):\n", x, y);
    for (int i = 0; i < MAX_SPOTS; i++) {
        printf("Spot ID: %d, Location: (%d, %d), Available: %s\n",
               sortedSpots[i].id, sortedSpots[i].x, sortedSpots[i].y,
               sortedSpots[i].available ? "Yes" : "No");
    }
}

int main() {
    int choice, id, x, y;

    while (1) {
        printf("\n--- Smart Parking Spot Finder ---\n");
        printf("1. Find Nearest Spot\n");
        printf("2. Reserve a Spot\n");
        printf("3. Release a Spot\n");
        printf("4. Display All Spots Sorted by Distance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter your location (x y): ");
                scanf("%d %d", &x, &y);
                id = find_nearest_spot(x, y);
                if (id != -1) {
                    printf("Nearest available parking spot ID: %d\n", id);
                } else {
                    printf("No available parking spots.\n");
                }
                break;
            case 2:
                printf("Enter parking spot ID to reserve: ");
                scanf("%d", &id);
                reserve_spot(id);
                break;
            case 3:
                printf("Enter parking spot ID to release: ");
                scanf("%d", &id);
                release_spot(id);
                break;
            case 4:
                printf("Enter your location (x y) for sorting: ");
                scanf("%d %d", &x, &y);
                display_sorted_spots(x, y);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}