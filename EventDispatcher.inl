template<typename RetType, typename... FuncArgs>
inline RetType Event<RetType, FuncArgs...>::broadcast(FuncArgs... args){
	for(Pair& target : targets){
		target.function(args...);
	}
}

template<typename RetType, typename... FuncArgs>
template<typename T>
inline int Event<RetType, FuncArgs...>::bind(T* context, RetType(T::*function)(FuncArgs...)){
	return bind(std::bind(function, context));
}

template<typename RetType, typename... FuncArgs>
inline int Event<RetType, FuncArgs...>::bind(FuncType function){
	int funcID = nextID++;
	targets.push_back({ funcID, function });
	return funcID;
}

template<typename RetType, typename... FuncArgs>
inline void Event<RetType, FuncArgs...>::unbind(int ID){
	targets.remove_if([ID](const Pair& target){
		return target.ID == ID;
	});
}