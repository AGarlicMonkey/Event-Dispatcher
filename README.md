# Event-Dispatcher
A C++ event dispatcher system

Version 1.0.0

#

1. [SingleEvent](#SE)
2. [MultiEvent](#ME)

#

## <a name="SE"></a> Single Event
A ```SingleEvent``` is an event dispatcher that can bind to a single function. It can take any type of return type and any number and types of function parameters.

### Usage
You can initialise a ```SingleEvent``` that returns void and takes 0 parameters like so:
```C+++
agm::SingleEvent<> myEvent;
```
Note the empty template parameters. This specifies the return type of the event is void and that the event will not take any parameters.
You can also define it as:
```C+++
agm::SingleEvent<void> myEvent;
```
to achieve the same effect. You need either empty template parameters or pass in void.

You can now bind to a function like so:
```C+++
class Foo{
	void bar(){
		//...
	}
}

Foo myFoo;

myEvent.bind(&myFoo, &Foo::bar);
```

Once bound calliing ```broadcast``` will call that function
```C++
myEvent.broadcast(); //myFoo.bar() called
```

Calling ```unbind``` will unbind the event
```C++
myEvent.unbind();

myEvent.broadcast(); //nothing happened
```

If you call ```bind``` on an event that is already bound it will overwrite the current binding and bind to the new one.

To bind to a function that has parameters or a return type you just need to specify the types in the template like so:
```C++
class Foo{
	void bar_1(int x){
		//...
	}

	float bar_2(int x, int y){
		//...
	}

	double bar_3(){
		//...
	}
};

Foo myFoo;

agm::SingleEvent<void, int> myIntEvent;
myIntEvent.bind(&myFoo, &Foo::bar_1);

myIntEvent.broadcast(3);

agm::SingleEvent<float, int, int> myIntEvent_RetFloat;
myIntEvent_RetFloat.bind(&myFoo, &Foo::bar_2);

float a = myIntEvent_RetFloat.broadcast(23, 47);

agm::SingleEvent<double> myEvent_RetDouble;
myEvent_RetDouble.bind(&myFoo, &Foo::bar_3);

double b = myEvent_RetDouble();
```

Note that the order of the types are important. it goes: ```<Return Type, Param Type 1, Param Type 2, ... , Param Type N>```.
Even if you have a function that returns void and takes a parameter you always need ```void``` as the first template argument.

## <a name="ME"></a> Multi Event
A ```MultiEvent``` works exactly like a ```SingleEvent``` except for a few key differences:

1. A ```MultiEvent``` cannot return a value.
2. calling ```bind``` on ```MultiEvent``` returns an ID. Use this ID on ```unbind``` to remove that specific instance
3. ```MultiEvent``` has ```unbindAll``` to unbind all current instances

Note that because ```MultiEvent``` does not have a return type you don't need to include ```void``` as the first template arguement when adding parameter types

### Usage
You can use the ```MultiEvent``` like so
```C++
class Foo_1{
	void bar_1(){
		//...
	}

	void bar_2(int x){
		//...
	}

	void bar_3(int x, float y){
		//...
	}
};

class Foo_2{
	void bar_2(int x){
		//...
	}

	void bar_3(int x, float y){
		//...
	}
};

Foo_1 myFoo_1;
Foo_2 myFoo_2;

agm::MultiEvent<> myEvent;

int ID_a = myEvent.bind(&myFoo_1, &Foo_1::Bar_1);

myEvent.broadcast(); //myFoo_1.bar_1 called

myEvent.unbind(ID_a); //myFoo_1.bar_1 removed

myEvent.broadcast(); //nothing happens

agm::MultiEvent<int> myIntEvent;

int ID_a = myEvent.bind(&myFoo_1, &Foo_1::Bar_2);
int ID_b = myEvent.bind(&myFoo_2, &Foo_2::Bar_2);

myEvent.broadcast(3); //myFoo_1.bar_2 + myFoo_2.bar_2 called 

myEvent.unbindAll(); //All bindings removed;

myEvent.broadcast(5); //nothing happens

agm::MultiEvent<int, float> myIntFloatEvent;

int ID_a = myEvent.bind(&myFoo_1, &Foo_1::Bar_3);
int ID_b = myEvent.bind(&myFoo_2, &Foo_2::Bar_3);

myEvent.broadcast(2, 21342.2f); //myFoo_1.bar_3 + myFoo_2.bar_3 called 

myEvent.unbind(ID_a); //myFoo_1.bar_3 removed;

myEvent.broadcast(45, 0.5f); //myFoo_2.bar_3 called 
```
