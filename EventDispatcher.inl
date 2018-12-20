template<typename RetType, typename... FuncArgs>
inline Event<RetType, FuncArgs...>::~Event(){
	targets.remove_if([](CacheBase* target){
		delete target;
		return true;
	});
}

template<typename RetType, typename... FuncArgs>
inline RetType Event<RetType, FuncArgs...>::broadcast(FuncArgs... args){
	for(CacheBase* target : targets){
		target->invoke(args...);
	}
}

template<typename RetType, typename... FuncArgs>
template<typename T>
inline int Event<RetType, FuncArgs...>::bind(T* context, RetType(T::*function)(FuncArgs...)){
	int ID = nextID++;
	FunctionCache<T>* newCache = new FunctionCache<T>(nextID, context, function);
	targets.push_back(newCache);
	return nextID;
}

template<typename RetType, typename... FuncArgs>
inline void Event<RetType, FuncArgs...>::unbind(int ID){
	targets.remove_if([ID](const CacheBase* target){
		return target->ID == ID;
	});
}