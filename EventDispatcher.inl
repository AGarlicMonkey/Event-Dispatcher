/////////EVENT BASE


/////////SINGLE EVENT
template<typename RetType, typename... FuncArgs>
inline SingleEvent<RetType, FuncArgs...>::~SingleEvent(){
	unbind();
}

template<typename RetType, typename... FuncArgs>
inline RetType SingleEvent<RetType, FuncArgs...>::broadcast(FuncArgs... args){
	if(target){
		return target->invoke(args...);
	}
}

template<typename RetType, typename... FuncArgs>
template<typename T>
inline void SingleEvent<RetType, FuncArgs...>::bind(T* context, RetType(T::*function)(FuncArgs...)){
	if(target){
		unbind();
	}

	target = new typename EventBase<RetType, FuncArgs...>::FunctionCache<T>(-1, context, function);
}

template<typename RetType, typename... FuncArgs>
inline void SingleEvent<RetType, FuncArgs...>::unbind(){
	delete target;
}

/////////MULTI EVENT
template<typename... FuncArgs>
inline MultiEvent<FuncArgs...>::~MultiEvent(){
	targets.remove_if([](EventBase::CacheBase* target){
		delete target;
		return true;
	});
}

template<typename... FuncArgs>
inline void MultiEvent<FuncArgs...>::broadcast(FuncArgs... args){
	for(EventBase::CacheBase* target : targets){
		target->invoke(args...);
	}
}

template<typename... FuncArgs>
template<typename T>
inline int MultiEvent<FuncArgs...>::bind(T* context, void(T::*function)(FuncArgs...)){
	int ID = nextID++;
	EventBase::FunctionCache<T>* newCache = new typename EventBase<void, FuncArgs...>::FunctionCache<T>(nextID, context, function);
	targets.push_back(newCache);
	return nextID;
}

template<typename... FuncArgs>
inline void MultiEvent<FuncArgs...>::unbind(int ID){
	targets.remove_if([ID](const EventBase::CacheBase* target){
		if(target->ID == ID){
			delete target;
			return true;
		}
	});
}