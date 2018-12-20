#include <list>

namespace agm{
	/////////EVENT BASE
	template<typename RetType, typename... FuncArgs>
	class EventBase{

		//DEFINITIONS
	protected:
		struct CacheBase{
			//VARIABLES
		public:
			int ID = -1;

			//FUNCTIONS
		public:
			CacheBase(int inID)
				: ID(inID){
			}

			virtual RetType invoke(FuncArgs... args) = 0;
		};

		template<typename T>
		struct FunctionCache : public CacheBase{
			//VARIABLES
		public:
			T * context;
			RetType(T::*function)(FuncArgs...);

			//FUNCTIONS
		public:
			FunctionCache(int inID, T* inContext, RetType(T::*inFunction)(FuncArgs...))
				: CacheBase(inID)
				, context(inContext)
				, function(inFunction){
			}

			virtual RetType invoke(FuncArgs... args) override{
				return (context->*function)(args...);
			}
		};

		//FUNCTIONS
	public:
		EventBase() = default;
		virtual ~EventBase() = default;
	};

	/////////SINGLE EVENT
	template<typename RetType, typename... FuncArgs>
	class SingleEvent : public EventBase<RetType, FuncArgs...>{

		//VARIABLES
	private:
		EventBase<RetType, FuncArgs...>::CacheBase* target;

		//FUNCTIONS
	public:
		SingleEvent() = default;
		~SingleEvent();

		RetType broadcast(FuncArgs... args);

		template<typename T>
		void bind(T* context, RetType(T::*function)(FuncArgs...));
		void unbind();
	};

	/////////MULTI EVENT
	template<typename... FuncArgs>
	class MultiEvent : public EventBase<void, FuncArgs...>{

		//VARIABLES
	private:
		int nextID = 0;

		std::list<EventBase<void, FuncArgs...>::CacheBase*> targets;

		//FUNCTIONS
	public:
		MultiEvent() = default;
		~MultiEvent();

		void broadcast(FuncArgs... args);

		template<typename T>
		int bind(T* context, void(T::*function)(FuncArgs...));
		void unbind(int ID);
	};
}

/////////INLINE INCLUDE
#include "Event.inl"