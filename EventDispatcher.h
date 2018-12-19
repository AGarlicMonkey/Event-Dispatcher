#include <list>
//#include <functional>

/////////EVENT DISPATCHER
template<typename RetType = void, typename... FuncArgs>
class Event{

	//DEFINITIONS
private:
	template<typename T>
	struct FunctionCache{
		//VARIABLES
	public:
		int ID = -1;
		
		T* context;
		RetType(T::*function)(FuncArgs...);

		//FUNCTIONS
	public:
		FunctionCache(int inID, T* inContext, RetType(T::*inFunction)(FuncArgs...))
			: ID(inID)
			, context(inContext)
			, function(inFunction)
		{ }

		RetType invoke(FuncArgs... args){
			return (context->*function)(args...);
		}
	};

	//VARIABLES
private:
	int nextID = 0;

	//template<typename T>
	//std::list<FunctionCache> targets;

	//FUNCTIONS
public:
	Event() = default;
	~Event() = default;

	RetType broadcast(FuncArgs... args);

	template<typename T> 
	int bind(T* context, RetType(T::*function)(FuncArgs...));

	void unbind(int ID);
};

/////////INLINE INCLUDE
#include "EventDispatcher.inl"