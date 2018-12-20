#include <list>

/////////EVENT DISPATCHER
template<typename RetType = void, typename... FuncArgs>
class Event{

	//DEFINITIONS
private:
	struct CacheBase{
		//VARIABLES
	public:
		int ID = -1;

		//FUNCTIONS
	public:
		CacheBase(int inID)
			: ID(inID)
		{ }

		virtual RetType invoke(FuncArgs... args) = 0;
	};

	template<typename T>
	struct FunctionCache : public CacheBase{
		//VARIABLES
	public:
		T* context;
		RetType(T::*function)(FuncArgs...);

		//FUNCTIONS
	public:
		FunctionCache(int inID, T* inContext, RetType(T::*inFunction)(FuncArgs...))
			: CacheBase(inID)
			, context(inContext)
			, function(inFunction)
		{ }

		virtual RetType invoke(FuncArgs... args) override{
			return (context->*function)(args...);
		}
	};

	//VARIABLES
private:
	int nextID = 0;

	std::list<CacheBase*> targets;

	//FUNCTIONS
public:
	Event() = default;
	~Event();

	RetType broadcast(FuncArgs... args);

	template<typename T> 
	int bind(T* context, RetType(T::*function)(FuncArgs...));

	void unbind(int ID);
};

/////////INLINE INCLUDE
#include "EventDispatcher.inl"