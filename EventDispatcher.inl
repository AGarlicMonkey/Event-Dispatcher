template<typename RetType, typename... FuncArgs>
inline RetType Event<RetType, FuncArgs...>::broadcast(FuncArgs... args){
	/*for(Pair& target : targets){
		target.function(args...);
	}*/
}

template<typename RetType, typename... FuncArgs>
template<typename T>
inline int Event<RetType, FuncArgs...>::bind(T* context, RetType(T::*function)(FuncArgs...)){
	int ID = nextID++;

	FunctionCache<T> newCache(nextID, context, function);

	newCache.invoke();

	return nextID;
}

template<typename RetType, typename... FuncArgs>
inline void Event<RetType, FuncArgs...>::unbind(int ID){
	/*targets.remove_if([ID](const Pair& target){
		return target.ID == ID;
	});*/
}