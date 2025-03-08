#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "city_map_h.h"
#include "comm_betn_stations.h"
#include "efficient_speakers.h"
#include "entertainment.h"
#include "info_organization.h"
#include "light_facility.h"
#include "parking_space.h"
#include "ticket_collection.h"
#include "train_route.h"

int main()
{
    int choice, decide;

    printf("\n-------------------------------------------------\n");
    printf("********Railway Station Management System********\n");
    printf("-------------------------------------------------\n");

    printf("Who are you ? \n1)Railway Man\n2)Passenger\nChoice:");
    scanf("%d",&decide);

    switch (decide)
    {
        case 1:

            do {
                printf("\n-------------------------------------------------");
                printf("\nWhich of the service would you like to choose:\n");
                printf("-------------------------------------------------\n");
                printf("1. Stations Communication\n");
                printf("2. Information organization\n");
                printf("3. Lighting facility\n");
                printf("4. Ticket Collection\n");
                printf("5. Train route traversal\n");
                printf("6. Exit\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                    case 1:
                        comm_station();
                        break;

                    case 2:
                        info_org();
                        break;

                    case 3:
                        light_fac();
                        break;

                    case 4:
                        tick_coll();
                        break;

                    case 5:
                        train_route();
                        break;

                    case 6:
                        printf("Exiting the Railway Station Management System.\n");
                        break;

                    default:
                        printf("Invalid choice! Please enter a valid option.\n");
                }

            } while (choice != 6);
                break;

        case 2:

            do {
                printf("\n-------------------------------------------------");
                printf("\nWhich of the service would you like to choose:\n");
                printf("-------------------------------------------------\n");
                printf("1. Explore city map for Path Navigation\n");
                printf("2. Train Search - Speaker Announcement\n");
                printf("3. Entertainment facilities\n");
                printf("4. Parking Space\n");
                printf("5. Exit\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                    case 1:
                        city_map();
                        break;

                    case 2:
                        speaker_announce();
                        break;

                    case 3:
                        entertain_fac();
                        break;

                    case 4:
                        park_eff();
                        break;

                    case 5:
                        printf("Exiting the Railway Station Management System.\n");
                        break;

                    default:
                        printf("Invalid choice! Please enter a valid option.\n");
                }

            } while (choice != 5);

        default:
            printf("Invalid choice! Please enter a valid option.\n");
            break;
    }
}
