#include <list>
#include <functional>

/////////EVENT DISPATCHER
template<typename RetType = void, typename... FuncArgs>
class EventDispatcher{

	//DEFINITION
private:
	using FuncType = std::function<RetType(FuncArgs...)>;

	//VARIABLES
private:
	std::list<FuncType> targets;

	//FUNCTIONS
public:
	RetType broadcast(FuncArgs... args);

	int bind(std::function<RetType(FuncArgs...)> function);
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