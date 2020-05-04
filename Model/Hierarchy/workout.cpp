#include "workout.h"

Workout::activity Workout::getSport() {return act;}
void Workout::setSport(int x) {act = static_cast<activity>(x);}

void Workout::serialize() {

}

Workout::Workout(int x,Time start,Time end,std::string nome,std::string descr,
                 std::string luogo,Date data,std::vector<std::string>* vettoreTag)
      : EventWithDuration (start,end,nome,descr,luogo,data,vettoreTag),
      act(static_cast<activity>(x))

{

}
