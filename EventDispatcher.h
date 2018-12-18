#include <list>

/////////PAIR
template<typename T>
struct Pair{
	//VARIABLES
public:
	T* context;
};

/////////EVENT DISPATCHER
template<typename RetType = void, typename... FuncArgs>
class EventDispatcher{

	//VARIABLES
private:
	//std::list
	//RetType(*function)(FuncArgs...);

	//FUNCTIONS
public:
	RetType broadcast(FuncArgs... args);

	template<typename T>
	int bind(T* context, RetType(T::*function)(FuncArgs...));

	bool unbind(int ID);
};

/////////INLINE INCLUDE
#include "EventDispatcher.inl"

/*
HOW WILL THIS WORK?
-How to bind to the delegate?
-How to broadcast the delegate?
--will probably need a struct made for broadcasting (like ue)
-How to handle ret params?
-How to handle param types?
--How to handle multiple params?
*/