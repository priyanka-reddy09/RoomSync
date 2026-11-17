#include <stdio.h>

int main()
{
    int id[10], capacity[10];
    int projector[10], video[10];

    int room[50], day[50];
    int start[50], end[50];

    int rooms = 0, bookings = 0;
    int choice, n, i, j;

    int r, d, s, e;
    int need, p, v;
    int found, booked, total_mins;

    do
    {
        printf("\n========== ROOMSYNC ==========\n");
        printf("1. Store Room Details\n");
        printf("2. Book a Room\n");
        printf("3. Find Available Rooms\n");
        printf("4. Cancel Booking\n");
        printf("5. Weekly Room Utilisation\n");
        printf("6. Exit\n");
        printf("==============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nEnter number of rooms: ");
                scanf("%d", &n);

                for(i = 0; i < n && rooms < 10; i++)
                {
                    printf("\nEnter Room ID: ");
                    scanf("%d", &id[rooms]);

                    printf("Enter Capacity: ");
                    scanf("%d", &capacity[rooms]);

                    printf("Projector (1-Yes, 0-No): ");
                    scanf("%d", &projector[rooms]);

                    printf("Video Call (1-Yes, 0-No): ");
                    scanf("%d", &video[rooms]);

                    rooms++;
                }

                printf("\nRoom details stored successfully!\n");
                break;

            case 2:
                printf("\nEnter Room ID: ");
                scanf("%d", &r);

                found = 0;

                for(i = 0; i < rooms; i++)
                {
                    if(id[i] == r)
                        found = 1;
                }

                if(found == 0)
                {
                    printf("Room not found!\n");
                    break;
                }

                printf("Enter Day (1-7): ");
                scanf("%d", &d);

                printf("Enter Start Time (HHMM): ");
                scanf("%d", &s);

                printf("Enter End Time (HHMM): ");
                scanf("%d", &e);

                if(d < 1 || d > 7 || s >= e || s < 0 || e > 2400)
                {
                    printf("Invalid booking details!\n");
                    break;
                }

                booked = 0;

                for(i = 0; i < bookings; i++)
                {
                    if(room[i] == r && day[i] == d &&
                       s < end[i] && e > start[i])
                    {
                        booked = 1;
                    }
                }

                if(booked == 1)
                {
                    printf("Room already booked!\n");
                }
                else if(bookings >= 50)
                {
                    printf("Booking limit reached!\n");
                }
                else
                {
                    room[bookings] = r;
                    day[bookings] = d;
                    start[bookings] = s;
                    end[bookings] = e;

                    bookings++;

                    printf("Booking successful!\n");
                }

                break;

            case 3:
                printf("\nEnter Required Capacity: ");
                scanf("%d", &need);

                printf("Projector Required (1-Yes, 0-No): ");
                scanf("%d", &p);

                printf("Video Call Required (1-Yes, 0-No): ");
                scanf("%d", &v);

                printf("Enter Day (1-7): ");
                scanf("%d", &d);

                printf("Enter Start Time (HHMM): ");
                scanf("%d", &s);

                printf("Enter End Time (HHMM): ");
                scanf("%d", &e);

                if(d < 1 || d > 7 || s >= e || s < 0 || e > 2400)
                {
                    printf("Invalid details!\n");
                    break;
                }

                found = 0;

                printf("\n--- AVAILABLE ROOMS ---\n");

                for(i = 0; i < rooms; i++)
                {
                    booked = 0;

                    for(j = 0; j < bookings; j++)
                    {
                        if(id[i] == room[j] && day[j] == d &&
                           s < end[j] && e > start[j])
                        {
                            booked = 1;
                        }
                    }

                    if(capacity[i] >= need &&
                       projector[i] >= p &&
                       video[i] >= v && booked == 0)
                    {
                        printf("Room ID: %d\n", id[i]);
                        found = 1;
                    }
                }

                if(found == 0)
                {
                    printf("No rooms available!\n");
                }

                break;

            case 4:
                printf("\nEnter Room ID: ");
                scanf("%d", &r);

                printf("Enter Day: ");
                scanf("%d", &d);

                printf("Enter Start Time (HHMM): ");
                scanf("%d", &s);

                found = 0;

                for(i = 0; i < bookings; i++)
                {
                    if(room[i] == r && day[i] == d &&
                       start[i] == s)
                    {
                        found = 1;

                        for(j = i; j < bookings - 1; j++)
                        {
                            room[j] = room[j + 1];
                            day[j] = day[j + 1];
                            start[j] = start[j + 1];
                            end[j] = end[j + 1];
                        }

                        bookings--;

                        printf("Booking cancelled successfully!\n");
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("Booking not found!\n");
                }

                break;

            case 5:
                printf("\n--- WEEKLY ROOM UTILISATION ---\n");

                for(i = 0; i < rooms; i++)
                {
                    total_mins = 0;

                    for(j = 0; j < bookings; j++)
                    {
                        if(id[i] == room[j])
                        {
                            int s_mins = (start[j] / 100) * 60 + (start[j] % 100);
                            int e_mins = (end[j] / 100) * 60 + (end[j] % 100);
                            total_mins = total_mins + (e_mins - s_mins);
                        }
                    }

                    printf("\nRoom ID: %d", id[i]);
                    printf("\nTotal Booked Hours: %.2f hrs (%d mins)\n", total_mins / 60.0, total_mins);
                }

                break;

            case 6:
                printf("\nThank you for using RoomSync!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while(choice != 6);

    return 0;
}
