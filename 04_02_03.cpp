// I skipped many stuff :U
// https://github.com/mostafa-saad/ArabicCompetitiveProgramming/blob/master/19-object-oriented-programming/04_homework_03_answer.cpp
class Apartment {
  private:
    int rooms, bathrooms;

  public:
    Apartment(int rooms, int bathrooms) : rooms(rooms) , bathrooms(bathrooms) { }

    int getRooms() {
        return rooms;
    }

    int getBathrooms() {
        return bathrooms;
    }

    void setRooms(int rooms_) {
        rooms = rooms_;
    }

    void setBathrooms(int Bathrooms_) {
        bathrooms = Bathrooms_;
    }
};

// yeah so, we created the object apartment, and it should be part of building,
// now... where to store it again?
// I think, best is to have a function that increments num_apartments,
// and creates new object of it, and store it in some kind of a data structure.
// well I don't know how tho :U
class building {
 private:
    int elevators, num_apartments;
    Apartment *apartments = new Apartment(3,2)[num_apartments];
 public:
    building(int elevators, int num_apartments) : elevators(elevators), num_apartments(num_apartments) {}
    // set get for ints like before.
    // dunno how to do it for the apartments.
};