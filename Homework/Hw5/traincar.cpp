// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//


// TOTAL WEIGHT AND COUNT CARS COUNTS THE NUMBER OF EACH TYPE OF CAR
// AND CALCULATES THE TOTAL WEIGHT OF THE ENTIRE TRAIN
void TotalWeightAndCountCars(TrainCar* train, int& total_weight, int& num_engines, int& num_freight_cars, int& num_passenger_cars, int& num_dining_cars, int& num_sleeping_cars) {
    // INITIALIZING THE INTEGERS TO START COUNT AT 0
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;

    // CONDITION LOOPS THROUGH ALL THE CONTENTS OF THE DOUBLY LINKED LIST
    while (train != NULL) {

        // IF EACH CAR MATCHES A TYPE, ADD IT TO THE CORRESPONDING VARIABLE
        if (train->isEngine() == true) {
            num_engines++;
        }
        else if (train->isFreightCar() == true) {
            num_freight_cars++;
        }
        else if (train->isPassengerCar() == true) {
            num_passenger_cars++;
        }
        else if (train->isDiningCar() == true) {
            num_dining_cars++;
        }
        else if (train->isSleepingCar() == true) {
            num_sleeping_cars++;
        }

        // COUNTS THE TOTAL WEIGHT BY ITERATING THROUGH THE LIST AND GETTING THE WEIGHT OF EACH CAR
        total_weight += train->getWeight();
        train = train->next; // HELPS ITERATE THROUGH ALL THE CARS
    }
}

// CALCULATE SPEED ITERATES THROUGH THE TRAIN AND USES THE GIVEN FORMULA TO FIND A TRAIN'S SPEED
float CalculateSpeed(TrainCar* train) {
    float total_weight = 0.0;
    float num_engines = 0.0;

    // ITERATES THROUGH THE TRAIN TO COUNT ENGINES TO FIND THE TOTAL HORSEPOWER
    // ALSO FINDS THE TOTAL WEIGHT OF THE TRAIN FOR ONE OF THE DENOMINATOR VALUES
    while (train != NULL) {
        if (train->isEngine() == true) {
            num_engines++;
        }
        total_weight += train->getWeight();
        train = train->next;
    }

    // USING GIVEN FORMULA, NUM IS NUMERATOR, DEN IS DENOMINATOR
    float total_horsepower = num_engines * 3000.0;
    float num = total_horsepower * 550 * 3600;
    float den = (20.0/0.01) * 0.02 * 5280.0 * total_weight;
    return (float) num / den;
}

// THIS METHOD CALCULATES THE AVERAGE DISTANCE A PASSENGER CAR IS TO A DINING CAR
// IF ONE PASSENGER CANT REACH A DINING CAR BC IT IS BLOCKED, THE AVG WILL BE INF
float AverageDistanceToDiningCar(TrainCar* train) {
    double num_passenger_cars = 0.0;
    double total_distance = 0.0;
    TrainCar* temp_forward_train = train;
    TrainCar* temp_backward_train = train;

    // LOOP THROUGH THE WHOLE TRAIN AND CREATE A FORWARD AND BACKWARD THAT RESETS EVERY CAR
    while (train != NULL) {
        double forward = 0;
        double backward = 0;

        // CONSTRAINT IS WHEN THE CAR IS A PASSENGER CAR
        // IF ITS A PASSENGER CAR...
        // WE COUNT THE NUMBER OF PASSENGER CARS FOR THE DENOMINATOR
        if (train->isPassengerCar() == true) {
            num_passenger_cars++;
            
            // TEMP FORWARD TRAIN TRAIN IS A TRAIN COPY THAT ITERATES FORWARD THROUGH THE TRAIN AT EVERY CAR
            // THIS COUNTS THE DISTANCE TO A DINING CAR FOR EVERY PASSENGER CAR
            while (temp_forward_train != NULL) {
                if (temp_forward_train->next == NULL) {
                    forward = -1;
                    break;
                }
                else if (temp_forward_train->isDiningCar() == true) {
                    break;
                }
                else if (temp_forward_train->isPassengerCar() == true || temp_forward_train->isSleepingCar() == true) {
                    forward++;
                }
                // IF IT IS A FREIGHT OR ENGINE CAR THAT BLOCKS IT SET FORWARD EQUAL TO -1
                else if (temp_forward_train->isFreightCar() == true || temp_forward_train->isEngine() == true) {
                    forward = -1;
                    break;
                }
                temp_forward_train = temp_forward_train->next;
            }

            // TEMP BACKWARD TRAIN IS A TRAIN COPY THAT ITERATES BACKWARDS THROUGH THE TRAIN AT EVERY CAR
            // THIS COUNTS THE DISTANCE TO A DINING CAR FOR EVERY PASSENGER CAR
            while (temp_backward_train != NULL) {
                if (temp_backward_train->prev == NULL) {
                    backward = -1;
                    break;
                }
                else if (temp_backward_train->isDiningCar() == true) {
                    break;
                }
                else if (temp_backward_train->isPassengerCar() == true || temp_backward_train->isSleepingCar() == true) {
                    backward++;
                }
                // IF IT IS A FREIGHT OR ENGINE CAR THAT BLOCKS IT SET BACKWARD EQUAL TO -1
                else if (temp_backward_train->isFreightCar() == true || temp_backward_train->isEngine() == true) {
                    backward = -1;
                    break;
                }
                temp_backward_train = temp_backward_train->prev;
            }
        } 

        // THESE IF ELSE STATEMENTS DECIDE WHICH DISTANCE FOR ONE CAR TO REACH A DINING CAR FORWARD/BACKWARD IS SHORTER FOR EACH CAR
        // THEN IT APPENDS THE DISTANCE TO TOTAL DISTANCE, WHICH IS USED TO CALCULATE THE AVG

        if (forward < 0 && backward < 0) { // IF THE CAR CANNOT REACH A DINING CAR CHECKING FORWARD OR BACKWARD, IT'S INFINITE
            return -1;
        }
        else if (backward < 0) { // IF THE BACKWARD CANT REACH, USE FORWARD
            total_distance += forward;
        }
        else if (forward < 0) {
            total_distance += backward;
        }
        else if (backward > forward) { // IF THE BACKWARD IS SLOWER, USE FORWARD
            total_distance += forward;
        }
        else {
            total_distance += backward;
        }

        train = train->next;
        temp_forward_train = train;
        temp_backward_train = train;
    }

    float total_avg_distance = total_distance / num_passenger_cars;
    return total_avg_distance;
}

// THIS METHOD CHECKS THE DISTANCE OF THE CLOSEST SLEEPER CAR TO AN ENGINE
int ClosestEngineToSleeperCar(TrainCar* train) {
    int closest = 0;
    TrainCar* temp_forward_train = train;
    TrainCar* temp_backward_train = train;

    // LOOP THROUGH ALL THE CARS IN THE DOUBLY LINKED LIST
    while (train != NULL) {
        double forward = 0;
        double backward = 0;

        // CONSTRAINT FOR WHEN YOU REACH A SLEEPING CAR
        if (train->isSleepingCar() == true) {

            // FOR EVERY CAR, LOOP THROUGH THE TRAIN AGAIN FORWARDS
            // THIS COUNTS THE DISTANCE BEFORE IT REACHES AN ENGINE, IF IT REACHES AN ENGINE THE LOOP BREAKS
            // AND FORWARD DISTANCE IS COUNTED
            while (temp_forward_train != NULL) {
                if (temp_forward_train->isEngine() == true) {
                    break;
                }
                else if (temp_forward_train->next == NULL) {
                    break;
                }
                else {
                    forward++;
                }
                temp_forward_train = temp_forward_train->next;
            }

            // FOR EVERY CAR, LOOP THROUGH THE TRAIN AGAIN BACKWARDS
            // THIS COUNTS THE DISTANCE BEFORE IT REACHES AN ENGINE, IF IT REACHES AN ENGINE THE LOOP BREAKS
            // AND BACKWARD DISTANCE IS COUNTED
            while (temp_backward_train != NULL) {

                if (temp_backward_train->isEngine() == true) {
                    break;
                }
                else if (temp_backward_train->prev == NULL) {
                    break;
                }
                else {
                    backward++;
                }
                temp_backward_train = temp_backward_train->prev;
            }
        }

        // THESE IF STATEMENTS COMPARE THE DISTANCE FORWARD TO THE DISTANCE BACKWARDS
        if (closest < forward || closest < backward) { 
            // IF THE FORWARD IS LESS THAN BACKWARD AND FORWARD ISNT 0, THE CLOSEST IS THE FORWARD
            if (forward < backward) {
                if (forward != 0) {
                    closest = forward;
                }
                else {
                    closest = backward;
                }
            }
            // ELSE THE CLOSEST IS THE BACKWARD IF BACKWARD ISNT EQUAL TO 0
            else {
                if (backward != 0) {
                    closest = backward; 
                }
                else {
                    closest = forward;
                }
            }
        }
        train = train->next;
        temp_forward_train = train;
        temp_backward_train = train;
    }
    return closest;
}

// PUSHBACK AT THE END OF A DOUBLY LINKED LIST AND RE ALIGN ALL POINTERS TO THE RIGHT NODES
void PushBack(TrainCar*& simple, TrainCar* method) {
    if (simple == NULL) {
        // SETS NULL POINTER EQUAL TO THE METHOD
        simple = method;
        return;
    }
    // ITERATE THROUGH THE LIST RECURSIVELY
    PushBack(simple->next, method);
    // SET THE NEXT NODE'S PREVIOUS TO SIMPLE
    simple->next->prev = simple;
}


// RECURSIVELY DELETE ALL THE CARS TO PREVENT MEMORY LEAKS
void DeleteAllCars(TrainCar*& simple) {
    // IF THE LIST IS FINALLY EMPTY, RETURN
    if (simple == NULL) {
        return;
    }
    DeleteAllCars(simple->next);
    delete simple;
}

// FIND THE SIZE OF A TRAIN BY ITERATING THROUGH IT AND COUNTING EACH CAR
float findSize(TrainCar* train) {
   int count = 0;
   while (train != NULL){
       count++;
       train = train->next;
   }
   return count;
}

// POPFRONT REMOVES THE FIRST INDEX OF THE TRAIN AND ALSO RETURNS THE NODE IT REMOVES
TrainCar* PopFront(TrainCar*& train) {
    // CREATE A FRONT POINTER TRAIN
    TrainCar* front = train;

    // IF THE TRAIN IS ALREADY EMPTY RETURN NULL
    if (train == NULL) {
        return NULL;
    } 
    // IF THE TRAIN ONLY CONTAINS ONE NODE, SET THE TRAIN EQUAL TO NULL TO DELETE IT, AND RETURN FRONT
    else if (train->next == NULL) {
        train = NULL;
        return front;
    }
    // IF THE TRAIN IS LONGER THAN ONE NODE
    else if (train->next != NULL) {
        // SET THE TRAIN EQUAL TO THE NEXT NODE AND SET THE PREVIOUS EQUAL TO NULL
        train = train->next;
        train->prev = NULL;
        // SET THE NEXT OF FRONT EQUAL TO NULL SO FRONT ONLY CONTAINS WHAT WAS POPPED BACK
        front->next = NULL;
        return front;
    }
    return front;
}

// POPBACK RECURSIVELY REMOVES THE LAST INDEX AS WELL AS RETURNS THE NODE IT REMOVES
TrainCar* PopBack(TrainCar*& train) {
    // IF THE TRAIN IS AT THE LAST INDEX
    if (train->next == NULL) {
        // CREATE A TEMPORARY VARIABLE TO HOLD THE LAST VALUE
        TrainCar* temp = train;
        temp->prev = NULL;
        train = NULL; // SET THE CURRENT EQUAL TO NULL AS IT'S AT THE LAST INDEX
        return temp;
    }
    // RECURSIVELY ITERATE TO THE LAST NODE 
    return PopBack(train->next);
}

// SHIPFRIEGHT SHIPS ALL FREIGHT CARS USING THE LEAST AMOUNT OF ENGINES AND CREATING THE LEAST AMOUNT OF TRAINS
std::vector <TrainCar*> ShipFreight(TrainCar*& all_engines, TrainCar*& all_freight, float min_speed, float max_cars) {
    // CREATE A VECTOR OF MULTIPLE TRAINS
    std::vector <TrainCar*> alltrains;
    float speed;
    float train_size;
    
    // CONSTRAINT TO KEEP LOOPING WHILE THERE ARE STILL FREIGHT CARS OR ENGINES LEFT
    while (all_engines != NULL && all_freight != NULL) {

        // AT EACH LOOP, CREATE A NEW TRAIN WITH AN ENGINE, AND CALCULATE THE SPEED AND TRAIN SIZE
        TrainCar* newTrain = NULL;
        PushBack(newTrain, PopFront(all_engines));
        speed = CalculateSpeed(newTrain);
        train_size = findSize(newTrain);

        // WHILE THE TRAIN AT THE CURRENT LOOP IS SMALLER THAN THE MAXIMUM ALLOWED CARS PER TRAIN
        while (train_size < max_cars) {

            // IF THE SPEED IS TOO FAST, ADD A FREIGHT CAR THE THE TRAIN AND RECALCULATE THE SPEED AND TRAIN SIZE
            if (speed > min_speed) {
                if (all_freight != NULL && train_size < max_cars) {
                    PushBack(newTrain, PopFront(all_freight));
                    speed = CalculateSpeed(newTrain);
                    train_size = findSize(newTrain);
                }
                else {
                    break;
                }
            }

            // IF THE TRAIN IS TOO SLOW, THERE ARE 2 OPTIONS:
            // 1. CHECK IF THERE ARE ANY ENGINES LEFT, AND ADD AN ENGINE IF THE SIZE ISNT ALREADY 1 AWAY FROM THE MAX SIZE
            //    IT WOULD BE A WASTE OF AN ENGINE IF YOU ADD IT AT THE END OF A TRAIN. IF THERE ARE NO ENGINES LEFT AT ALL, JUST BREAK
            // 2. DELETE THE FREIGHT CAR AT THE END OF THE TRAIN TO SPEED UP THE TRAIN AND ADD THE DELETED FREIGHT CAR
            //    BACK TO ALL_FREIGHTS USING PUSHBACK AND POPBACK
            if (speed < min_speed) {
                if (all_engines != NULL && train_size < max_cars-1) {
                    PushBack(newTrain, PopFront(all_engines));
                    speed = CalculateSpeed(newTrain);
                    train_size = findSize(newTrain);
                }
                else if (all_engines == NULL ) {
                    break;
                }
                else {
                    PushBack(all_freight, PopBack(newTrain));
                    speed = CalculateSpeed(newTrain);
                    train_size = findSize(newTrain);
                    break;
                }
            }
        }

        // THIS IF STATEMENT JUST CHECKS IF IT'S TOO SLOW AGAIN FOR THE LAST TRAIN CAR
        if (speed < min_speed) {
            PushBack(all_freight, PopBack(newTrain));
        }

        alltrains.push_back(newTrain);
    }
    return alltrains;
}

void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3) {
    // COUNTING THE CARS IN TRAIN 1
    train2 = NULL;
    train3 = NULL;
    
    // USE PREVIOUS METHOD TO GET TOTAL ENGINES
    int total_weight = 0, num_engines = 0, num_freight_cars = 0, num_passenger_cars = 0, num_dining_cars = 0, num_sleeping_cars = 0;
    TotalWeightAndCountCars(train1, total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);

    // CALCULATE THE SIZE OF THE FIRST TRAIN AND SECOND TRAIN BASED ON ODD/EVEN
    // ALSO CALCULATING HOW TO SPLIT THE ENGINES
    int total_size = findSize(train1);
    int train2_size = 0;
    int train2_engines = 0;
    int train3_engines = 0;
    if (total_size % 2 == 0 || num_engines % 2 == 0) {
        train2_size = total_size / 2;
        train2_engines = num_engines / 2;
        train3_engines = num_engines - train2_engines;
    }
    else {
        train2_size = (total_size / 2) + 1;
        train2_engines = (num_engines / 2) + 1;
        train3_engines = num_engines - train2_engines; 
    }
    
    int iterator = 0;
    int engine_iterator = 0;
    // ITERATE UNTIL THE 2ND TRAIN CAR REACHES IT'S MAX SIZE
    // GOES THROUGH TRAIN 1 AND DELETES EACH INDEX AND PUSHBACK TO TRAIN 2
    while (iterator < train2_size) {
        if (train1->isEngine() == true && train2_engines != engine_iterator) {
            PushBack(train2, PopFront(train1));
            engine_iterator++;
        }
        else if (train1->isEngine() == true && train2_engines == engine_iterator) {
            PushBack(train1, PopFront(train1));
            iterator--;
        }
        else if (iterator + 1 == train2_size  && engine_iterator == 0) {
            PushBack(train2, PopFront(train1)); 
        }
        else {
            PushBack(train2, PopFront(train1));
        }
        iterator++;
    }

    // GOES THROUGH FROM THE REST OF TRAIN ONE TO THE END OF THE LIST
    // DELETES EACH INDEX AND PUSHBACK TO TRAIN 3
    // IF THERE IS NO ENGINE IN TRAIN 2 AND TWO ENGINES IN TRAIN 3, SWAP THE ENGINE WITH THE BACK OF TRAIN 2
    int engine_iterator_2 = 0;
    while(train1 != NULL) {
        if (train1->isEngine()) {
            engine_iterator_2++;
        }
        if (engine_iterator == 0 && train1->isEngine() == true && engine_iterator_2 != train3_engines) {
            PushBack(train3, PopBack(train2));
            PushBack(train2, PopFront(train1));
        }
        else {
            PushBack(train3, PopFront(train1));
        }
    }
    train1 = NULL;

}