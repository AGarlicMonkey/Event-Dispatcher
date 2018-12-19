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
	Event() = default;
	~Event() = default;

	RetType broadcast(FuncArgs... args);

	template<typename T> 
	int bind(T* context, RetType(T::*function)(FuncArgs...));
	int bind(FuncType function);

	void unbind(int ID);
};

/////////INLINE INCLUDE
#include "EventDispatcher.inl"