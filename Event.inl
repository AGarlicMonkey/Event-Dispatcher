/////////EVENT BASE


/////////SINGLE EVENT
template<typename RetType, typename... FuncArgs>
inline agm::SingleEvent<RetType, FuncArgs...>::~SingleEvent(){
	unbind();
}

template<typename RetType, typename... FuncArgs>
inline RetType agm::SingleEvent<RetType, FuncArgs...>::broadcast(FuncArgs... args){
	if(target){
		return target->invoke(args...);
	}
}

template<typename RetType, typename... FuncArgs>
template<typename T>
inline void agm::SingleEvent<RetType, FuncArgs...>::bind(T* context, RetType(T::*function)(FuncArgs...)){
	if(target){
		unbind();
	}

	target = new typename EventBase<RetType, FuncArgs...>::FunctionCache<T>(-1, context, function);
}

template<typename RetType, typename... FuncArgs>
inline void agm::SingleEvent<RetType, FuncArgs...>::unbind(){
	delete target;
	target = nullptr;
}

/////////MULTI EVENT
template<typename... FuncArgs>
inline agm::MultiEvent<FuncArgs...>::~MultiEvent(){
	unbindAll();
}

template<typename... FuncArgs>
inline void agm::MultiEvent<FuncArgs...>::broadcast(FuncArgs... args){
	for(typename EventBase<void, FuncArgs...>::CacheBase* target : targets){
		target->invoke(args...);
	}
}

template<typename... FuncArgs>
template<typename T>
inline int agm::MultiEvent<FuncArgs...>::bind(T* context, void(T::*function)(FuncArgs...)){
	int ID = nextID++;
	EventBase<void, FuncArgs...>::FunctionCache<T>* newCache = new typename EventBase<void, FuncArgs...>::FunctionCache<T>(ID, context, function);
	targets.push_back(newCache);
	return ID;
}

template<typename... FuncArgs>
inline void agm::MultiEvent<FuncArgs...>::unbind(int ID){
	targets.remove_if([ID](typename EventBase<void, FuncArgs...>::CacheBase* target){
		if(target->ID == ID){
			delete target;
			return true;
		} else{
			return false;
		}
	});
}

template<typename... FuncArgs>
inline void agm::MultiEvent<FuncArgs...>::unbindAll(){
	targets.remove_if([](typename EventBase<void, FuncArgs...>::CacheBase* target){
		delete target;
		return true;
	});
}