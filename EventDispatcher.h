#include <list>
#include <functional>

/////////EVENT DISPATCHER
template<typename RetType = void, typename... FuncArgs>
class Event{

	//DEFINITIONS
private:
	using FuncType = std::function<RetType(FuncArgs...)>;

	struct Pair{
		//VARIABLES
	public:
		int ID = -1;
		FuncType function;

		//FUNCTIONS
	public:
		Pair(int inID, const FuncType &inFunction)
			: ID(inID)
			, function(inFunction)
		{ }
	};

	//VARIABLES
private:
	int nextID = 0;

	std::list<Pair> targets;

	//FUNCTIONS
public:
	RetType broadcast(FuncArgs... args);

	int bind(FuncType function);
	template<typename T> 
	int bind(T* context, RetType(T::*function)(FuncArgs...));

	void unbind(int ID);
};

/////////INLINE INCLUDE
#include "EventDispatcher.inl"