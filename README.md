# CuteCalendar
Cross-platform calendar developed in Qt5 and C++ for the OOP course of the bachelor's degree in Computer Science at UniPD, a.y. 2019/20

## Design
It was decided to adhere to the Model-View design pattern, allowing separation between the logical model and the GUI. 
The logical model is not bounded to the GUI code, and this ensures that the hierarchy can be used even with GUIs written in different frameworks. 
	
## Model
### Type hierarchy
At the base of the hierarchy is the abstract class `Event`, which represents any event that can be handled by the application. 
The direct subtypes of Event are: 
 - `AllDayEvent`: abstract polymorphic class representing an event that spans the duration of the day; 
 - `Alert`: abstract polymorphic class representing an event with which an alert/notification is to be associated. 
 This class has two private attributes: 
     - an attribute of type `Time` indicating the time at which to show the notification; 
     - a boolean variable indicating whether you want to repeat such a notification a second time or not; 
 - `EventWithDuration`: an abstract polymorphic class representing all events characterized by a start time and an end time. This information is represented through two private attributes of type `Time`.

Finally, the concrete classes that are identified are: 
 - `ToDoList`: a list of tasks to be performed by the user; this list is encoded by a vector of objects of type `ListItem`, each of which describes a task; 
 - `Birthday`: an event of type birthday; it is characterized by the birth year of the birthday person; 
 - `Meeting`: a business meeting, so it has a vector of emails (represented as simple strings) as a private attribute; 
 - `Reminder`: a reminder, it contains a private data field of type `unsigned int` indicating the urgency level of the reminder itself; 
 - `Workout`: a workout, it features a `enum` indicating the sport of interest; 	

<p align="center"><img src="https://user-images.githubusercontent.com/27569184/208472384-6c9bb54c-f1dd-434c-9ac8-548159a297e6.png" height=250 /></p>

### Polymorphic Methods 
The `Event` class has some public pure virtual methods, namely: 
 - `virtual Event* clone() const = 0`: polymorphic cloning method, returns a pointer to a copy of the considered object. 
  This method is implemented only in the concrete classes of the hierarchy.
 - `virtual Time getDuration() const = 0`: method that allows obtaining the duration of an event. Depending on the class considered its implementation varies, in particular: 
    - `AllDayEvent` returns an object of type `Time` representing the duration of an entire day; 
	- `EventWithDuration` returns the difference between the end time and the start time of the considered event.
 - `virtual bool isCompleted() const = 0`: method to obtain the completion status of the considered event:
    - `AllDayEvent` is considered completed if the current date is after the date of the event; 
    - `EventWithDuration` is complete instead if either condition is true: 
       - the event date precedes the current event date; 
       - the event date coincides with the current date, but the event end time precedes the current time. 
   - `ToDoList` in which case the event is considered completed if and only if all the items in the list have been executed (regardless of the current date).   

The Event class also features the public virtual destructor: 
 - `virtual ~Event() = default`: which allows the invocation of the right destructor by any polymorphic object. 

### Container
The model exploits an appropriate container. Specifically, the required operations are: 
 - deletion of an event; 
 - accessing an event; 
 - insertion of a new event into a date. 
 
A `unordered-multimap` was implemented to best meet these requirements. This choice is due to several factors: 
- each event has a date associated with it; 
- there can be multiple events for the same date; 
- no order is required between events corresponding to the same date. 

To implement this data structure, a binary search tree (BST) was created, where each node is characterized by: 
- a key;
- a dynamic array, containing all elements of interest.

The key of each node corresponds to the date of the event, while the dynamic array contains instances of `DeepPtr<Event>`, where `DeepPtr` is a class template, specially developed, containing a private field of type `Event*` (polymorphic). 
This implementation allows obtaining in O(h) time, where h is the height of the tree, the array of elements that are scheduled for a specific date (the main operation of the application). 

### Serialization
CuteCalendar allows saving and reading files representing the data in the container. The format used is JSON:
- the use of a standard allows for greater maintainability of the product; 
- Qt provides classes that make it easy to manage this format.
		
The management of serialization and parsing of information in the hierarchy is based on the following points:
 - in the class `Event` there is the pure virtual function `virtual void serialize(QJsonObject &json) const = 0`, whose task is to use the object `QJsonObject` passed by reference to serialize the considered object. Note that this function is implemented by all classes derived from `Event`; 
 - every concrete class derived from the abstract class `Event` has a static identifier. This is exploited by the `Factory` class, which is responsible for parsing a JSON string and creating the corresponding object. 

## View
Widgets are used to display information about each specific event. The widgets use an iterator of type `Model::It` to interface with `Event` objects. 
		
### View hierarchy
We used a hierarchy to manage the widgets. The base of the hierarchy is the abstract polymorphic class `ModView`, which virtual methods are: 
- `virtual void setEnabled(bool)`: allows defining the activation state of the widget; 
- `virtual void pushSaves(const Model::It&) const`:  update the values of the considered event;
- `virtual void fillView(const Model::It&)`: allows to display in the widget the information of a specific event;  
- `virtual bool checkPushable(QString&) const`: checks that all values entered by the user in the widget are valid. In the case of an error, the function returns `false` and any information about the error is given in the string passed by reference;
- `virtual Event* createEvent(const QDate& date) const = 0`: creates an event with the type and values specified by the user.

The `ModView` class also features the public virtual destructor: 
- `virtual ~ModView() = default`: which allows the invocation of the right destructor by any polymorphic object. 

A concrete class, derived from `ModView`, was then identified for each concrete class in the event hierarchy. In this way, using polymorphism, a single polymorphic pointer of type `ModView*` can be used to handle the display of each type of event. 

## Exception handling
Within the project, exceptions were used as a method of error handling. Specifically:
- in the container to indicate abnormal situations, e.g., when the user attempts to delete or add an element via an invalid iterator; 
- in the `Date` and `Time` classes, in the case of incorrect parameters (`std::invalid_argument`) and for invalid string conversion; 	
- in the GUI for errors in user-specified information. 

The exceptions are issued using auxiliary classes, and handled by the `MainWindow`, which is responsible for displaying an appropriate error message. 

	
